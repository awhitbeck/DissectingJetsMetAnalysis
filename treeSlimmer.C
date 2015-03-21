/*
Simple macro showing how to access branches from the delphes output root file,
loop over events, and plot simple quantities such as the jet pt and the di-electron invariant
mass.

gSystem->Load("libDelphes");
root -l DissectingJetsMetAnalysis/treeSlimmer.C+'("delphes_output.root")'
*/

//------------------------------------------------------------------------------
#include "examples/sumJetMassCalc.cc"
#include "TClonesArray.h"
#include "external/ExRootAnalysis/ExRootTreeReader.h"
#include "TChain.h"
#include "TH1.h"
#include "classes/DelphesClasses.h"
#include "TCanvas.h"

void treeSlimmer(const char *inputFile)
{


  TTree* outTree = new TTree("analysisTree","");

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

  // Create chain of root trees
  TChain chain("Delphes");
  chain.Add(inputFile);

  // Create object of class ExRootTreeReader
  ExRootTreeReader *treeReader = new ExRootTreeReader(&chain);
  Long64_t numberOfEntries = treeReader->GetEntries();

  // Get pointers to branches used in this analysis
  //TClonesArray *branchJet = treeReader->UseBranch("Jet");
  TClonesArray *branchFatJet = treeReader->UseBranch("FatJet");
  TClonesArray *branchJet = treeReader->UseBranch("Jet");

  // Book histograms
  TH1 *histHT = new TH1F("histHT", ";H_{T} [GeV];Events", 100, 0.0, 1000.0);
  TH1 *histSMJ = new TH1F("histSMJ", ";#Sigma m_{j} [GeV];Events", 100, 40.0, 1000.);

  sumJetMassCalc SMJcalc;

  // Loop over all events
  for(Int_t entry = 0; entry < numberOfEntries; ++entry)
  {
    // Load selected branches with data from specified event
    treeReader->ReadEntry(entry);
    
    sumJetMass = 0. ;
    HT = 0. ;

    // If event contains at least 1 jet
    if(branchJet->GetEntries() > 0)
    {

      SMJcalc.compute( branchJet ) ;
      sumJetMass = SMJcalc.sumJetMass ;

      for( int iJet = 0 ; iJet < branchJet->GetEntries() ; iJet++){

	Jet *jet = (Jet*) branchJet->At( iJet );

	if( jet->PT > 30. && fabs( jet->Eta ) < 2.5 ){
	  HT += jet->PT ; 
	  NJets ++ ; 
	}

      }// end loop over individual jets 

    }// if branch is good

    histHT->Fill(HT);
    histSMJ->Fill(sumJetMass);

    outTree->Fill();

  }// end loop over events

  TFile* file = new TFile("outputTest.root","RECREATE");
  outTree->Write();

  // Show resulting histograms
  TCanvas* c1 = new TCanvas("c1","c1",500,500);
  histHT->Draw();
  TCanvas* c2 = new TCanvas("c2","c2",500,500);
  histSMJ->Draw();

}

