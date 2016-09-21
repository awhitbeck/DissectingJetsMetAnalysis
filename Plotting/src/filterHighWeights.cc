#ifndef FILTERHIGHWEIGHTS
#define FILTERHIGHWEIGHTS

#include "processor.h"
#include <iostream>

using namespace std;

template <class TreeType> class filterHighWeights : public processor<TreeType> {

public : 

  TH1F* histo;
  TreeType* ntuple;
  int cutMask;

  filterHighWeights(){ ntuple = 0; };
  filterHighWeights( TreeType *ntuple_ , int cutMask_ = 0 ){
    ntuple = ntuple_;
    histo = new TH1F("filterhighweightsYields","filterhighweightsYields",1,0.5,1.5);
    cutMask = cutMask_;
  };
  
  bool process( ) override {
    
    /*
    cout << "HT: " << ntuple->HT << " mask: " << static_cast<bool>(cutMask&1) << endl;
    cout << "MHT: " << ntuple->MHT << " mask: " << static_cast<bool>(cutMask&2) << endl;
    cout << "NJets: " << ntuple->NJets << " mask: " << static_cast<bool>(cutMask&4) << endl;
    cout << "NLeptons: " << ntuple->NLeptons << " mask: " << static_cast<bool>(cutMask&8) << endl;
    cout << "dPhi: " << ntuple->dPhi << " mask: " << static_cast<bool>(cutMask&16) << endl;
    */

    histo->Fill(0);
    if( ntuple->lheWeight < .1 || static_cast<bool>(cutMask&1) ) histo->Fill(1);
    else{
      //cout << "lheWeight cut failed" << endl;
      return false;
    }

    return true;

  };

};

#endif
