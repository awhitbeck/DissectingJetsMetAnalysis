#include "TClonesArray.h"
#include "classes/DelphesClasses.h"

class MT2Calc{

public: 

  double MT2 ; 
  
  double minJetPt ;
  double maxJetEta ;
  double minJetMass ;
  int    minJets ;

  MT2Calc(double minJetPt_ = 50. ,
	  double maxJetEta_ = 2.5 ,
	  double minJetMass_ = 50. ,
	  int    minJets_ = 2 ){
    
    minJetPt = minJetPt_ ; 
    maxJetEta = maxJetEta_ ; 
    minJetMass = minJetMass_ ; 
    minJets = minJets_ ; 

    clearVars();

  }

  void clearVars(){

    MT2 = 0. ;

  }

  void compute( TClonesArray* branchJet ){

    // all variables to zero
    clearVars();

  }

};
  
    

