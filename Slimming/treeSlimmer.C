#include "TClonesArray.h"
#include "TChain.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TLorentzVector.h"
#include "TFile.h"

#include <algorithm>
#include <vector>
#include <iostream>

#include "classes/DelphesClasses.h"
#include "external/ExRootAnalysis/ExRootTreeReader.h"
#include "sumJetMassCalc.cc"
#include "razorCalc.cc"
#include "MT2Calc.cc"
#include "alphaTCalc.cc"

using namespace std;
bool debug = false;

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
  double METphi = 0. ;
  double dPhi = -999. ;
  double dPhi1 = -999. ;
  double dPhi2 = -999. ; 
  double dPhi3 = -999. ; 
  double dPhi4 = -999. ; 

  int NJets = 0  ;
  int NLeptons = 0 ; 
  
  double sumJetMass = 0. ;  
  double leadJetPt = 0. ;
  double mEff = 0. ;
  double dEta = 0. ;
  double alphaT_dHThemi = 0. ;
  double alphaT = 0. ;
  double mT2 = 0. ;
  double mT2_zeroMass = 0. ;
  double mRazor = 0. ; 
  double dRazor = 0. ;

  vector<TLorentzVector> Jets;

  outTree->Branch("HT",&HT,"HT/D");
  outTree->Branch("MHT",&MHT,"MHT/D");
  outTree->Branch("MET",&MET,"MET/D");
  outTree->Branch("METphi",&METphi,"METphi/D");
  outTree->Branch("dPhi",&dPhi,"dPhi/D");
  outTree->Branch("dPhi1",&dPhi1,"dPhi1/D");
  outTree->Branch("dPhi2",&dPhi2,"dPhi2/D");
  outTree->Branch("dPhi3",&dPhi3,"dPhi3/D");
  outTree->Branch("dPhi4",&dPhi4,"dPhi4/D");

  outTree->Branch("Jets",&Jets);
  outTree->Branch("NJets",&NJets,"NJets/I");
  outTree->Branch("NLeptons",&NLeptons,"NLeptons/I");
  outTree->Branch("sumJetMass",&sumJetMass,"sumJetMass/D");
  outTree->Branch("leadJetPt",&leadJetPt,"leadJetPt/D");
  outTree->Branch("mEff",&mEff,"mEff/D");
  outTree->Branch("dEta",&dEta,"dEta/D");
  outTree->Branch("alphaT",&alphaT,"alphaT/D");
  outTree->Branch("alphaT_dHThemi",&alphaT_dHThemi,"alphaT_dHThemi/D");
  outTree->Branch("mT2",&mT2,"mT2/D");
  outTree->Branch("mT2_zeroMass",&mT2_zeroMass,"mT2_zeroMass/D");
  outTree->Branch("mRazor",&mRazor,"mRazor/D");
  outTree->Branch("dRazor",&dRazor,"dRazor/D");
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
  TClonesArray *branchMuon = treeReader->UseBranch("Muon");
  TClonesArray *branchElectron = treeReader->UseBranch("Electron");

  sumJetMassCalc SMJHelper(0.,5.0,50.,0);
  razorCalc razorHelper(0.,5.0,0.,2);
  MT2Calc mt2Helper;
  MT2Calc mt2HelperZeroMass(true);
  alphaTCalc alphaTHelper;

  // Loop over all events
  for(Int_t entry = 0; entry < numberOfEntries; ++entry)
  {

    // Load selected branches with data from specified event
    treeReader->ReadEntry(entry);
    
    NLeptons = branchMuon->GetEntries() + branchElectron->GetEntries();
    
    sumJetMass = 0. ;
    HT = 0. ;
    TLorentzVector MHTvec( 0. , 0. , 0. , 0. ) ;
    leadJetPt = 0. ;
    vector< TLorentzVector > skinnyJets_pt30eta25 ; 
    vector< TLorentzVector > skinnyJets_pt30eta50 ; 
    Jets = skinnyJets_pt30eta50;

    // If event contains at least 1 jet
    if(branchJet->GetEntries() > 0)
    {

      SMJHelper.compute( branchFatJet ) ;
      sumJetMass = SMJHelper.sumJetMass ;

      if( debug ) cout << "--------- new event ------------" << endl;

      for( int iJet = 0 ; iJet < branchJet->GetEntries() ; iJet++){

	Jet *jet = (Jet*) branchJet->At( iJet );

	if( debug ){
	  cout << "jet pt: " << jet->PT ;
	  cout << " eta: " << jet->Eta ;
	  cout << " phi: " << jet->Phi << endl;
	}

	//save jets with relevant kinematics ==========
	if( jet->PT > 30. && fabs( jet->Eta ) < 2.5 ){
	  skinnyJets_pt30eta25.push_back( jet->P4() ) ;
	}

	if( jet->PT > 30. && fabs( jet->Eta ) < 5.0 ){
	  skinnyJets_pt30eta50.push_back( jet->P4() ) ;
	  MHTvec -= jet->P4() ;
	}
	// ============================================

      }// end loop over individual jets 

      MHT = MHTvec.Pt();
      MissingET *MET_ = (MissingET*) branchMET->At( 0 ) ;
      // this is a hilariously confusing line.  Let me explain:  
      // MET_ is the Delphes MissingET object, 
      // MET_->MET is the actually MET variable computed by Delphes, MET is the local 
      // MET variable which is mapped to a branch of the output tree.
      MET = MET_->MET ;
      METphi = MET_->Phi;
      
      TLorentzVector METp4( MET_->P4() );
      
      if( skinnyJets_pt30eta50.size() == 1 ){
	dPhi = abs( skinnyJets_pt30eta50[0].DeltaPhi( METp4 ) ) ;
	dPhi1 = abs( skinnyJets_pt30eta50[0].DeltaPhi( METp4 ) ) ;
      }
      if( skinnyJets_pt30eta50.size() == 2 ){
	dPhi1 = abs( skinnyJets_pt30eta50[0].DeltaPhi( METp4 ) ) ;
	dPhi2 = abs( skinnyJets_pt30eta50[1].DeltaPhi( METp4 ) ) ;
      }
      if( skinnyJets_pt30eta50.size() >= 2 ){
	dPhi = min( abs( skinnyJets_pt30eta50[0].DeltaPhi( METp4 ) ) , abs( skinnyJets_pt30eta50[1].DeltaPhi( METp4 ) ) );
      }
      if( skinnyJets_pt30eta50.size() == 3 ){
	dPhi1 = abs( skinnyJets_pt30eta50[0].DeltaPhi( METp4 ) ) ;
	dPhi2 = abs( skinnyJets_pt30eta50[1].DeltaPhi( METp4 ) ) ;
	dPhi3 = abs( skinnyJets_pt30eta50[2].DeltaPhi( METp4 ) ) ;
      }
      if( skinnyJets_pt30eta50.size() >= 4 ){
	dPhi1 = abs( skinnyJets_pt30eta50[0].DeltaPhi( METp4 ) ) ;
	dPhi2 = abs( skinnyJets_pt30eta50[1].DeltaPhi( METp4 ) ) ;
	dPhi3 = abs( skinnyJets_pt30eta50[2].DeltaPhi( METp4 ) ) ;
	dPhi4 = abs( skinnyJets_pt30eta50[3].DeltaPhi( METp4 ) ) ;
      }
      // make sure that the jets are pt ordered
      sort( skinnyJets_pt30eta25.begin() , skinnyJets_pt30eta25.end() , ptSorting);
      sort( skinnyJets_pt30eta50.begin() , skinnyJets_pt30eta50.end() , ptSorting);

      if( debug )
	cout << "computing RAZOR, MT2, and alphaT" << endl;

      if( skinnyJets_pt30eta50.size() > 1 ){

	if( debug ){
	  cout << "MET: " << MET << " METphi: " << " MET*cos(METphi): " << MET*cos(METphi) << endl;
	  for( unsigned int iTest = 0 ; iTest < skinnyJets_pt30eta50.size() ; iTest++ ){
	    cout << "skinnyJet Pt: " << skinnyJets_pt30eta50[iTest].Pt() << endl;
	  }
	}
  

	// RAZOR variables
	razorHelper.computeVars( skinnyJets_pt30eta50 , MET*cos(METphi) , MET*sin(METphi) );
	mRazor = razorHelper.mR;
	dRazor = razorHelper.R;

	if( debug ){ 
	  cout << "Hemisphere 1: " << razorHelper.hemispheres[0].Pt() << endl;
	  cout << "Hemisphere 2: " << razorHelper.hemispheres[1].Pt() << endl;
	  cout << "mR: " << mRazor << " R2: " << dRazor << endl;
	}

	// MT2 
	mT2_zeroMass = mt2HelperZeroMass.compute(razorHelper.hemispheres[0] , razorHelper.hemispheres[1] ,
						 MET*cos(METphi) , MET*sin(METphi) ,
						 0. , 0. );
	
	mT2 = mt2Helper.compute( razorHelper.hemispheres[0] , razorHelper.hemispheres[1] ,
				 MET*cos(METphi) , MET*sin(METphi) , 
				 0. , 0. );
	
	if( debug )
	  cout << "MT2: " << mT2 << " MT2(zero mass): " << mT2_zeroMass << endl;

	// alpha_T
	alphaT_dHThemi = alphaTHelper.compute( skinnyJets_pt30eta50 );
	alphaT = alphaTHelper.compute( razorHelper.hemispheres[0] , 
				       razorHelper.hemispheres[1] );
	
	if( debug ) 
	  cout << "alphaT: " << alphaT << " alphaT_dHThemi: " << alphaT_dHThemi << endl;

      }

      if( debug ) 
	cout << "done" << endl;

      // get deltaEta of two leading jets
      if( skinnyJets_pt30eta25.size() > 1 ) 
	dEta = fabs( skinnyJets_pt30eta25[0].Eta() - skinnyJets_pt30eta25[1].Eta() ) ;
      
      if( debug ) 
	cout << "dEta: " << dEta << endl;

      // get number of jets
      NJets = skinnyJets_pt30eta25.size() ;

      if( debug ) 
	cout << "NJets: " << NJets << endl;

      // get leading jet pt
      if( skinnyJets_pt30eta25.size() > 0 ){
	leadJetPt = skinnyJets_pt30eta25[0].Pt() ;
	if( debug ) 
	  cout << "leadJetPt: " << leadJetPt << endl;
      }
      
      // loop over all jets with pt>30 and |eta|<2.5
      for( unsigned int iJet = 0 ; iJet < skinnyJets_pt30eta25.size() ; iJet++ ){
	HT += skinnyJets_pt30eta25[ iJet ].Pt() ; 
      }
      if( debug ) 
	cout << "HT: " << HT << endl;

      // loop over all jets with pt>30 and |eta|<5.0
      for( unsigned int iJet = 0 ; iJet < skinnyJets_pt30eta50.size() ; iJet++ ){
	MHTvec -= skinnyJets_pt30eta50[ iJet ] ;
      }

      if( debug ) 
	cout << "MHT: " << MHT << endl;

    }// if branch is good

    mEff = HT + MET ; 
    if( debug ) 
      cout << "mEff: " << mEff << endl;
    
    // put event into output tree
    outTree->Fill();

  }// end loop over events

  if( debug )
    cout << "loop over n-events done..." << endl;

  //write output tree
  TFile* file = new TFile("outputTest.root","RECREATE");
  if(file) file = file ; // dummy line to prevent compiler warnings.
  
  if( debug ) 
    cout << "write" << endl;

  outTree->Write();
  file->Close();

  //delete file;
  //delete treeReader;
  //delete outTree;

}

int main(int argc, char** argv){
  
  cout << "verify" << endl;
  
  treeSlimmer(argv[1]);
  cout << "done" << endl;

  return 0;

}
