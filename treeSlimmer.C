#include "examples/sumJetMassCalc.cc"
#include "TClonesArray.h"
#include "external/ExRootAnalysis/ExRootTreeReader.h"
#include "TChain.h"
#include "TH1.h"
#include "classes/DelphesClasses.h"
#include "TCanvas.h"
#include "TLorentzVector.h"

#include <algorithm>
#include <vector>

using namespace std;

// for pt ordering objects
bool ptSorting( TLorentzVector i , TLorentzVector j ){
  return i.Pt() < j.Pt() ;
}

void treeSlimmer(const char *inputFile)
{


  TTree* outTree = new TTree("analysisTree","");

  //defining tree structure - - - - - - - - 
  double HT = 0. ;
  double MHT = 0. ;
  double MET = 0. ;
  int NJets = 0  ;

  double sumJetMass = 0. ;  
  double leadJetPt = 0. ;
  double mEff = 0. ;
  double dEta = 0. ;
  double alphaT = 0. ;
  double mT2skinny = 0. ;
  double mT2fatjets = 0. ;
  double mRazor = 0. ; 
  double dRazor = 0. ;
  
  outTree->Branch("HT",&HT,"HT/D");
  outTree->Branch("MHT",&MHT,"MHT/D");
  outTree->Branch("MET",&MET,"MET/D");
  outTree->Branch("NJets",&NJets,"NJets/I");

  outTree->Branch("sumJetMass",&sumJetMass,"sumJetMass/D");
  outTree->Branch("leadJetPt",&leadJetPt,"leadJetPt/D");
  outTree->Branch("mEff",&mEff,"mEff/D");
  outTree->Branch("dEta",&dEta,"dEta/D");
  outTree->Branch("alphaT",&alphaT,"alphaT/D");
  outTree->Branch("mT2skinny",&mT2skinny,"mT2skinny/D");
  outTree->Branch("mT2fatjets",&mT2fatjets,"mT2fatjets/D");
  // - - - - - - - - - - - - - - - - - - - -

  // Create chain of root trees
  TChain chain("Delphes");
  chain.Add(inputFile);

  // Create object of class ExRootTreeReader
  ExRootTreeReader *treeReader = new ExRootTreeReader(&chain);
  Long64_t numberOfEntries = treeReader->GetEntries();

  // Get pointers to branches used in this analysis
  TClonesArray *branchFatJet = treeReader->UseBranch("FatJet");
  TClonesArray *branchJet = treeReader->UseBranch("Jet");
  TClonesArray *branchMET = treeReader->UseBranch("MissingET");

  sumJetMassCalc SMJcalc;

  // Loop over all events
  for(Int_t entry = 0; entry < numberOfEntries; ++entry)
  {
    // Load selected branches with data from specified event
    treeReader->ReadEntry(entry);
    
    sumJetMass = 0. ;
    HT = 0. ;
    TLorentzVector MHTvec( 0. , 0. , 0. , 0. ) ;
    leadJetPt = 0. ;
    vector< TLorentzVector > skinnyJets_pt30eta25 ; 
    vector< TLorentzVector > skinnyJets_pt30eta50 ; 

    // If event contains at least 1 jet
    if(branchJet->GetEntries() > 0)
    {

      SMJcalc.compute( branchFatJet ) ;
      sumJetMass = SMJcalc.sumJetMass ;

      for( int iJet = 0 ; iJet < branchJet->GetEntries() ; iJet++){

	Jet *jet = (Jet*) branchJet->At( iJet );

	//save jets with relevant kinematics ==========
	if( jet->PT > 30. && fabs( jet->Eta ) < 2.5 ){
	  skinnyJets_pt30eta25.push_back( jet->P4() ) ;
	}

	if( jet->PT > 30. && fabs( jet->Eta ) < 5.0 ){
	  skinnyJets_pt30eta50.push_back( jet->P4() ) ;
	}
	// ============================================

      }// end loop over individual jets 

      // make sure that the jets are pt ordered
      sort( skinnyJets_pt30eta25.begin() , skinnyJets_pt30eta25.end() , ptSorting);
      sort( skinnyJets_pt30eta50.begin() , skinnyJets_pt30eta50.end() , ptSorting);

      // get number of jets
      NJets = skinnyJets_pt30eta25.size() ;
      
      // get leading jet pt
      if( skinnyJets_pt30eta25.size() > 0 )
	leadJetPt = skinnyJets_pt30eta25[0].Pt() ;
      
      // get deltaEta of two leading jets
      if( skinnyJets_pt30eta25.size() > 1 )
	dEta = fabs( skinnyJets_pt30eta25[0].Eta() - skinnyJets_pt30eta25[1].Eta() ) ;

      // loop over all jets with pt>30 and |eta|<2.5
      for( unsigned int iJet = 0 ; iJet < skinnyJets_pt30eta25.size() ; iJet++ ){
	HT += skinnyJets_pt30eta25[ iJet ].Pt() ; 
      }

      // loop over all jets with pt>30 and |eta|<5.0
      for( unsigned int iJet = 0 ; iJet < skinnyJets_pt30eta50.size() ; iJet++ ){
	HT += skinnyJets_pt30eta50[ iJet ].Pt() ; 
	MHTvec -= skinnyJets_pt30eta50[ iJet ] ;
      }

    }// if branch is good

    MHT = MHTvec.Pt();
    MissingET *MET_ = (MissingET*) branchMET->At( 0 ) ;
    // this is a hilariously confusing line.  MET_ is the Delphes MissingET object, 
    // MET_->MET is the actually MET variable computed by Delphes, MET is the local 
    // MET variable which is mapped to a branch of the output tree.
    MET = MET_->MET ;
    mEff = HT + MET ; 

    // put event into output tree
    outTree->Fill();

  }// end loop over events

  //write output tree
  TFile* file = new TFile("outputTest.root","RECREATE");
  outTree->Write();

}

