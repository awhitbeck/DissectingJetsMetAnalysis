#ifndef SELECT4JETS
#define SELECT4JETS

#include "processor.h"
#include <iostream>

using namespace std;

template <class TreeType> class select4Jets : public processor<TreeType> {

public : 

  TH1F* histo;
  TreeType* ntuple;

  select4Jets()
    : processor<TreeType>("select4Jets")
  { 
    ntuple = 0; 
  };
  select4Jets( TreeType *ntuple_ )
    : processor<TreeType>("select4Jets")
  {
    ntuple = ntuple_;
    histo = new TH1F("select4JetsYields","select4JetsYields",1,0.5,1.5);
  };

  void postProcess()override{};
  bool process( ) override {

    histo->Fill(0);
    if( ntuple->NJets>3 ) histo->Fill(1);
    else return false;

    return true;

  };

};

#endif
