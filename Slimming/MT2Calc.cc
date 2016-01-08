#include "lester_mt2_bisect.h"

class MT2Calc{

public: 

  double MT2 ; 
  bool ZeroMassJets;

  MT2Calc(bool ZeroMassJets_=false);
  void clearVars();
  double compute(TLorentzVector vis1 , TLorentzVector vis2,
		 double METpx , double METpy ,
		 double mInvis1 , double mInvis2 );
  
};

MT2Calc::MT2Calc(bool ZeroMassJets_){

    clearVars();
    ZeroMassJets = ZeroMassJets_ ;
};

void MT2Calc::clearVars(){

    MT2 = 0. ;

};

double MT2Calc::compute( TLorentzVector vis1 , TLorentzVector vis2, 
		       double METpx , double METpy , 
		       double mInvis1 , double mInvis2 ){
  
  // all variables to zero
  clearVars();

  if( ZeroMassJets ){
    MT2 = asymm_mt2_lester_bisect::get_mT2(0.,vis1.Px(),vis1.Py(),
					   0.,vis2.Px(),vis2.Py(),
					   METpx,METpy,
					   mInvis1 , mInvis2 , 
					   0. );
  }else{
        MT2 = asymm_mt2_lester_bisect::get_mT2(vis1.M(),vis1.Px(),vis1.Py(),
					       vis2.M(),vis2.Px(),vis2.Py(),
					       METpx,METpy,
					       mInvis1 , mInvis2 , 
					       0. );
  }
  
  return MT2;

};
  
    

