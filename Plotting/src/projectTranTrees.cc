#include "tranTree.cc"
#include "selectBaseline.cc"
#include "select4Jets.cc"
#include "filterHighWeights.cc"
#include "fillHisto.cc"
#include "fillHisto2D.cc"
#include "analyzer.cc"
#include "weightProducer.cc"

#include "TString.h"
#include "TChain.h"
#include "TFile.h"
#include "TMath.h"

#include <cstdio>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

#include "helpers.h"

using namespace std;

typedef fillHisto<tranTree> hFiller;
typedef fillHisto2D<tranTree> hFiller2D;

int main(int argc, char** argv){

  TString sample = argv[1];
  TChain* t = new TChain("otree");
  bool compressed;
  if( argc == 3 ){
    if( strcmp(argv[2],"compressed") == 0 ){
      cout << "================== NOTE: ================" << endl;
      cout << "I'll be using the compressed signal samples" << endl;
      compressed=true;
      t->Add("root://cmsxrootd.fnal.gov///store/user/ntran/SUSY/theory_JPM/samples-compressed/ProcJPM_"+sample+"-test.root");
      //t->Add("/uscmst1b_scratch/lpc1/3DayLifetime/ntran/SUSY/forAndrew/backgrounds-v7-noDPhi-com/ProcJPM_"+sample+"-test.root");
      sample+="_compressed";
    }else{
      cout << "================== NOTE: ================" << endl;
      cout << "I'll be using the UNcompressed signal samples" << endl;
      compressed=false;
      t->Add("root://cmsxrootd.fnal.gov///store/user/ntran/SUSY/theory_JPM/samples-uncompressed/ProcJPM_"+sample+"-test.root");
      //t->Add("/uscmst1b_scratch/lpc1/3DayLifetime/ntran/SUSY/forAndrew/backgrounds-v7-noDPhi-unc/ProcJPM_"+sample+"-test.root");
    }
  }else{
    cout << "================== NOTE: ================" << endl;
    cout << "I guess this is background ... " << endl;
    compressed=false;
    t->Add("root://cmsxrootd.fnal.gov///store/user/ntran/SUSY/theory_JPM/samples-uncompressed/ProcJPM_"+sample+"-test.root");
    //t->Add("/uscmst1b_scratch/lpc1/3DayLifetime/ntran/SUSY/forAndrew/backgrounds-v7-noDPhi-unc/ProcJPM_"+sample+"-test.root");
  }

  tranTree *ntuple = new tranTree(t);

  selectBaseline<tranTree> *select = new selectBaseline<tranTree>(ntuple);
  //filterHighWeights<tranTree> *weightFilter = new filterHighWeights<tranTree>(ntuple);
  
  analyzer<tranTree> a(ntuple,17);
  a.verbosity=0;
  a.setReportEvery(200000);
  //a.addProcessor( weightFilter );
  a.addProcessor( select );

  /* - - - - - - - - - - - - - - - - - - - - - - - 2D histograms - - - - - - - - - - - - - - - - - - - - - - */
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
  hFiller *fillHToverMHT = new hFiller(ntuple,50,0,50,sample,"MHTOvHT","lheWeight",10000.); a.addProcessor( fillHToverMHT );
  fillHToverMHT->histo->SetTitle(";H_{T}^{miss}/#sqrt(H_{T}};Events");

  /* - - - - - - - - - - - - - - - - - - - - - - - 2D histograms - - - - - - - - - - - - - - - - - - - - - - */
  hFiller2D fillmR_R2(ntuple,"mRazor",50,300,5000,"dRazor",50,0,1,sample,"lheWeight",10000.); a.addProcessor( &fillmR_R2 );
  fillmR_R2.histo->SetTitle(";R^{2};m_{R} [GeV]");
  hFiller2D fillHT_MHT(ntuple,"HT",50,500,2500,"MHT",50,200,1000,sample,"lheWeight",10000.); a.addProcessor( &fillHT_MHT );
  fillHT_MHT.histo->SetTitle(";H_{T} [GeV];H_{T}^{miss} [GeV]");
  hFiller2D fillMT2_MHT(ntuple,"mT2",50,200,2000,"MHT",50,200,1000,sample,"lheWeight",10000.); a.addProcessor( &fillMT2_MHT );
  fillMT2_MHT.histo->SetTitle(";m_{T2} [GeV];H_{T}^{miss} [GeV]");
  hFiller2D fillMT2CMS_MHT(ntuple,"mT2_zeroMass",50,0,800,"MHT",50,200,1000,sample,"lheWeight",10000.); a.addProcessor( &fillMT2CMS_MHT );
  fillMT2CMS_MHT.histo->SetTitle(";m_{T2}^{CMS} [GeV];H_{T}^{miss} [GeV]");
  hFiller2D fillMT2_HT(ntuple,"mT2",50,200,2000,"HT",50,500,2500,sample,"lheWeight",10000.); a.addProcessor( &fillMT2_HT );
  fillMT2_HT.histo->SetTitle(";m_{T2} [GeV];H_{T} [GeV]");
  hFiller2D fillMT2CMS_HT(ntuple,"mT2_zeroMass",50,0,800,"HT",50,500,2500,sample,"lheWeight",10000.); a.addProcessor( &fillMT2CMS_HT );
  fillMT2CMS_HT.histo->SetTitle(";m_{T2}^{CMS};H_{T} [GeV]");
  hFiller2D fillAlphaT_dPhi(ntuple,"alphaT",50,0,2,"dPhi",50,0,TMath::Pi(),sample,"lheWeight",10000.); a.addProcessor( &fillAlphaT_dPhi );
  fillAlphaT_dPhi.histo->SetTitle(";#alpha_{T};#Delta#phi");
  hFiller2D fillAlphaTdHThemi_dPhi(ntuple,"alphaT_dHThemi",50,0,2,"dPhi",50,0,TMath::Pi(),sample,"lheWeight",10000.); a.addProcessor( &fillAlphaTdHThemi_dPhi );
  fillAlphaTdHThemi_dPhi.histo->SetTitle(";#alpha_{T};#Delta#phi");
  
  a.looper();

  TFile* outFile = new TFile("genericPlotter_"+sample+".root","UPDATE");
  
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
  fillalphaT->histo->Write();
  fillmRazor->histo->Write();
  filldRazor->histo->Write();
  fillmEff->histo->Write();
  fillNJets->histo->Write();
  fillNLeptons->histo->Write();
  filldPhi->histo->Write();
  filldEta->histo->Write();
  fillsumJetMass->histo->Write();
  fillleadJetPt->histo->Write();
  fillHToverMHT->histo->Write();
  fillmR_R2.histo->Write();
  fillHT_MHT.histo->Write();
  fillMT2_MHT.histo->Write();
  fillMT2CMS_MHT.histo->Write();
  fillMT2_HT.histo->Write();
  fillMT2CMS_HT.histo->Write();
  fillAlphaT_dPhi.histo->Write();
  fillAlphaTdHThemi_dPhi.histo->Write();

  select->histo->Write("baselineYields_"+sample);
  outFile->Close();

}  

