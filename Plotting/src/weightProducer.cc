#ifndef WEIGHTPRODUCER
#define WEIGHTPRODUCER

#include "filler.h"
#include <iostream>
#include <string>
#include <map>
#include <cassert>

#include "TString.h"

using namespace std;

template <class TreeType> class weightProducer : public processor<TreeType> {

public : 

  TString sample;
  double weight;
  double lumi;
  int nEvents;
  TreeType* ntuple;

  weightProducer()
    : processor<TreeType>("weightProducer")
  {
    ntuple = 0;
    sample = "";
    weight = -999.;
    nEvents = 1 ;
  };

  weightProducer( TreeType* ntuple_ , 
		  TString sample_ = "ttbar" ,
		  double lumi_ = 10.)
    : processor<TreeType>("weightProducer")
  {
    ntuple = ntuple_;
    sample = sample_;
    weight = -999.;
    lumi = lumi_;
    nEvents = ntuple->fChain->GetEntries();

    if( sample == "znunu_0_600" )        weight = 539.8068575*lumi/nEvents;
    if( sample == "znunu_600_1200" )     weight = 26.7158033166*lumi/nEvents;
    if( sample == "znunu_1200_2000" )    weight = 1.92569864467*lumi/nEvents;
    if( sample == "znunu_2000_2900" )    weight = 0.150861660513*lumi/nEvents;
    if( sample == "znunu_2900_3900" )    weight = 0.015104699949*lumi/nEvents;
    if( sample == "znunu_3900_5000" )    weight = 0.00155900261758*lumi/nEvents;
    if( sample == "znunu_5000_100000" )  weight = 0.000153373693727*lumi/nEvents;
      
    if( sample == "Wjets_0_400" )        weight = 6363.608615*lumi/nEvents;
    if( sample == "Wjets_400_900" )      weight = 432.88054467*lumi/nEvents;
    if( sample == "Wjets_900_1600" )     weight = 23.3849837436*lumi/nEvents;
    if( sample == "Wjets_1600_2500" )    weight = 1.65095612398*lumi/nEvents;
    if( sample == "Wjets_2500_3500" )    weight = 0.129479800515*lumi/nEvents;
    if( sample == "Wjets_3500_4600" )    weight = 0.0121681361371*lumi/nEvents;
    if( sample == "Wjets_4600_5700" )    weight = 0.001086189415*lumi/nEvents;
    if( sample == "Wjets_5700_100000" )  weight = 0.000106971454914*lumi/nEvents;
      
    if( sample == "ttbar_0_600" )        weight = 435.841349313*lumi/nEvents;
    if( sample == "ttbar_600_1200" )     weight = 32.6826950495*lumi/nEvents;
    if( sample == "ttbar_1200_1900" )    weight = 2.0582766*lumi/nEvents;
    if( sample == "ttbar_1900_2700" )    weight = 0.168654823762*lumi/nEvents;
    if( sample == "ttbar_2700_3600" )    weight = 0.01588917*lumi/nEvents;
    if( sample == "ttbar_3600_4600" )    weight = 0.0015207095742*lumi/nEvents;
    if( sample == "ttbar_4600_100000" )  weight = 0.000141367514851*lumi/nEvents;
      
    if( sample == "QCD_0_300" )         weight = 10290243.9856*lumi/nEvents;
    if( sample == "QCD_300_600" )       weight = 265934.6*lumi/nEvents;
    if( sample == "QCD_600_1000" )      weight = 12545.2493946*lumi/nEvents;
    if( sample == "QCD_1000_1600" )     weight = 971.531366405*lumi/nEvents;
    if( sample == "QCD_1600_2400" )     weight = 68.1967181166*lumi/nEvents;
    if( sample == "QCD_2400_3300" )     weight = 4.84510532511*lumi/nEvents;
    if( sample == "QCD_3300_4300" )     weight = 0.429963067413*lumi/nEvents;
    if( sample == "QCD_4300_5300" )     weight = 0.03827015*lumi/nEvents;
    if( sample == "QCD_5300_6300" )     weight = 0.003799263*lumi/nEvents;
    if( sample == "QCD_6300_100000" )   weight = 0.0004130418*lumi/nEvents;

    try{
      if( weight <= 0. ) throw weight;
    }catch( double w ){
      std::cout << "Exception caught in weightProducer::weightProducer()" << std::endl;
      std::cout << " - sample not found ... weight set to default: " << w << std::endl;
      assert(0);
    }

  };

  void postProcess()override{};
  bool process( ) override {
    return true;
  };

};

#endif
