#include "dissectingJetsMETdPhiTest.cc"
#include "selectBaseline.cc"
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
#include <vector>

#include "helpers.h"
using namespace std;

typedef dissectingJetsMETdPhiTest treeType;
typedef fillHisto<treeType> hFiller;

int main(int argc, char** argv){

  TString sample = argv[1];
  TChain* t = buildChain("dPhiTestFiles.txt",sample,"analysisTree");
  
  treeType *ntuple = new treeType(t);
  weightProducer<treeType> *weightProd = new weightProducer<treeType>(ntuple,sample);
  selectBaseline<treeType> *select = new selectBaseline<treeType>(ntuple,16);
  
  analyzer<treeType> a(ntuple);
  a.addProcessor( select );

  hFiller *filldPhi = new hFiller(ntuple,20,0.,3.1415,sample,"dPhi",weightProd); a.addProcessor( filldPhi );
  hFiller *filldPhi1 = new hFiller(ntuple,20,0.,3.1415,sample,"dPhi1",weightProd); a.addProcessor( filldPhi1 );
  hFiller *filldPhi2 = new hFiller(ntuple,20,0.,3.1415,sample,"dPhi2",weightProd); a.addProcessor( filldPhi2 );
  hFiller *filldPhi3 = new hFiller(ntuple,20,0.,3.1415,sample,"dPhi3",weightProd); a.addProcessor( filldPhi3 );
  hFiller *filldPhi4 = new hFiller(ntuple,20,0.,3.1415,sample,"dPhi4",weightProd); a.addProcessor( filldPhi4 );
  hFiller *fillHT = new hFiller(ntuple,200,500,2500,sample,"HT",weightProd);   a.addProcessor( fillHT );
  hFiller *fillMHT = new hFiller(ntuple,200,200,1000,sample,"MHT",weightProd); a.addProcessor( fillMHT );
  hFiller *fillMET = new hFiller(ntuple,200,200,1000,sample,"MET",weightProd); a.addProcessor( fillMET );
  hFiller *fillmT2 = new hFiller(ntuple,200,200,2500,sample,"mT2",weightProd); a.addProcessor( fillmT2 );
  hFiller *fillalphaT = new hFiller(ntuple,200,0,2,sample,"alphaT",weightProd); a.addProcessor( fillalphaT );
  hFiller *fillmRazor = new hFiller(ntuple,200,200,4000,sample,"mRazor",weightProd); a.addProcessor( fillmRazor );
  hFiller *filldRazor = new hFiller(ntuple,200,0,1,sample,"dRazor",weightProd); a.addProcessor( filldRazor );
  hFiller *fillmEff = new hFiller(ntuple,200,400,4000,sample,"mEff",weightProd); a.addProcessor( fillmEff );
  hFiller *fillNJets = new hFiller(ntuple,11,-0.5,10.5,sample,"NJets",weightProd); a.addProcessor( fillNJets );
  hFiller *fillNLeptons = new hFiller(ntuple,4,-0.5,3.5,sample,"NLeptons",weightProd); a.addProcessor( fillNLeptons );
  hFiller *filldEta = new hFiller(ntuple,20,0.,5.,sample,"dEta",weightProd); a.addProcessor( filldEta );
  hFiller *fillsumJetMass = new hFiller(ntuple,200,100.,1000.,sample,"sumJetMass",weightProd); a.addProcessor( fillsumJetMass );

  a.looper();

  TFile* outFile = new TFile("genericPlotter_"+sample+".root","UPDATE");

  for( unsigned int iProc = 0 ; iProc < a.processorList.size() ; iProc++ ){
    if( hFiller* myFiller = dynamic_cast<hFiller*>( a.processorList[iProc] ) ){
      myFiller->histo->Write();
    }
  }

  /*
  filldPhi->histo->Write();
  filldPhi1->histo->Write();
  filldPhi2->histo->Write();
  filldPhi3->histo->Write();
  filldPhi4->histo->Write();
  */

  select->histo->Write("baselineYields_"+sample);
  outFile->Close();

}  

