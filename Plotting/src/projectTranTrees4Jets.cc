#include "tranTree.cc"
#include "selectBaseline.cc"
#include "select4Jets.cc"
#include "filterHighWeights.cc"
#include "fillHisto.cc"
#include "analyzer.cc"
#include "weightProducer.cc"

#include "TString.h"
#include "TChain.h"
#include "TFile.h"

#include <cstdio>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

#include "helpers.h"

using namespace std;

typedef fillHisto<tranTree> hFiller;

int main(int argc, char** argv){

  TString sample = argv[1];
  TChain* t = new TChain("otree");
  t->Add("root://cmsxrootd.fnal.gov///store/user/ntran/SUSY/theory_JPM/samples-uncompressed/ProcJPM_"+sample+"-test.root");

  tranTree *ntuple = new tranTree(t);

  selectBaseline<tranTree> *select = new selectBaseline<tranTree>(ntuple);
  select4Jets<tranTree> *select4jets = new select4Jets<tranTree>(ntuple);
  //filterHighWeights<tranTree> *weightFilter = new filterHighWeights<tranTree>(ntuple);
  
  analyzer<tranTree> a(ntuple,18);
  a.verbosity=0;
  a.setReportEvery(200000);
  //a.addProcessor( weightFilter );
  a.addProcessor( select );
  a.addProcessor( select4jets );

  hFiller *fillHT = new hFiller(ntuple,50,500,2500,sample,"HT","lheWeight",10000.);   a.addProcessor( fillHT );
  fillHT->histo->SetTitle(";HT [GeV];Events");
  hFiller *fillMHT = new hFiller(ntuple,50,200,1000,sample,"MHT","lheWeight",10000.); a.addProcessor( fillMHT );
  fillMHT->histo->SetTitle(";MHT [GeV];Events");
  hFiller *fillMET = new hFiller(ntuple,50,200,1000,sample,"MET","lheWeight",10000.); a.addProcessor( fillMET );
  fillMET->histo->SetTitle(";MET [GeV];Events");
  hFiller *fillmT2 = new hFiller(ntuple,50,200,2000,sample,"mT2","lheWeight",10000.); a.addProcessor( fillmT2 );
  fillmT2->histo->SetTitle(";m_{T2} [GeV];Events");
  hFiller *fillmT2zeroMass = new hFiller(ntuple,50,0,800,sample,"mT2_zeroMass","lheWeight",10000.); a.addProcessor( fillmT2zeroMass );
  fillmT2zeroMass->histo->SetTitle(";m_{T2} [GeV];Events");
  hFiller *fillalphaT = new hFiller(ntuple,50,0,2,sample,"alphaT","lheWeight",10000.); a.addProcessor( fillalphaT );
  fillalphaT->histo->SetTitle(";#alpha_{T};Events");
  hFiller *fillalphaTdHThemi = new hFiller(ntuple,50,0,2,sample,"alphaT_dHThemi","lheWeight",10000.); a.addProcessor( fillalphaTdHThemi );
  fillalphaTdHThemi->histo->SetTitle(";#alpha_{T};Events");
  hFiller *fillmRazor = new hFiller(ntuple,50,300,5000,sample,"mRazor","lheWeight",10000.); a.addProcessor( fillmRazor );
  fillmRazor->histo->SetTitle(";m_{R} [GeV];Events");
  hFiller *filldRazor = new hFiller(ntuple,50,0,1,sample,"dRazor","lheWeight",10000.); a.addProcessor( filldRazor );
  filldRazor->histo->SetTitle(";#DeltaR;Events");
  hFiller *fillmEff = new hFiller(ntuple,50,500,3000,sample,"mEff","lheWeight",10000.); a.addProcessor( fillmEff );
  fillmEff->histo->SetTitle(";m_{eff} [GeV];Events");
  hFiller *fillNJets = new hFiller(ntuple,11,-0.5,10.5,sample,"NJets","lheWeight",10000.); a.addProcessor( fillNJets );
  fillNJets->histo->SetTitle(";n_{jets};Events");
  hFiller *fillNLeptons = new hFiller(ntuple,4,-0.5,3.5,sample,"NLeptons","lheWeight",10000.); a.addProcessor( fillNLeptons );
  fillNLeptons->histo->SetTitle(";n_{lep};Events");
  hFiller *filldPhi = new hFiller(ntuple,50,0.,3.1415,sample,"dPhi","lheWeight",10000.); a.addProcessor( filldPhi );
  filldPhi->histo->SetTitle(";#Delta#phi;Events");
  hFiller *filldEta = new hFiller(ntuple,50,0.,5.,sample,"dEta","lheWeight",10000.); a.addProcessor( filldEta );
  filldEta->histo->SetTitle(";#Delta#eta;Events");
  hFiller *fillsumJetMass = new hFiller(ntuple,50,100.,800.,sample,"sumJetMass","lheWeight",10000.); a.addProcessor( fillsumJetMass );
  fillsumJetMass->histo->SetTitle(";#Sigma M_{j} [GeV];Events");
  hFiller *fillleadJetPt = new hFiller(ntuple,50,30,300,sample,"leadJetPt","lheWeight",10000.); a.addProcessor( fillleadJetPt );
  fillleadJetPt->histo->SetTitle(";p_{T,j1};Events");
  
  a.looper();

  TFile* outFile = new TFile("genericPlotter4Jets_"+sample+".root","UPDATE");

  /*
  for( unsigned int iProc = 0 ; iProc < a.processorList.size() ; iProc++ ){
    if( filler<tranTree>* myFiller = dynamic_cast<filler<tranTree>* >( a.processorList[iProc] ) ){
      myFiller->histo->Write();
    }
  }
  */

  fillHT->histo->Write();
  fillMHT->histo->Write();
  fillMET->histo->Write();
  fillmT2->histo->Write();
  fillmT2zeroMass->histo->Write();
  fillalphaTdHThemi->histo->Write();
  fillmRazor->histo->Write();
  filldRazor->histo->Write();
  fillmEff->histo->Write();
  fillNJets->histo->Write();
  fillNLeptons->histo->Write();
  filldPhi->histo->Write();
  filldEta->histo->Write();
  fillsumJetMass->histo->Write();
  fillleadJetPt->histo->Write();

  select->histo->Write("baselineYields_"+sample);
  select4jets->histo->Write("4JetsYields_"+sample);
  outFile->Close();

}  

