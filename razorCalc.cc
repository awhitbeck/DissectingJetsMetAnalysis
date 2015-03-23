#include "TClonesArray.h"
#include "classes/DelphesClasses.h"

class razorCalc{

public: 

  double mR ; 
  double R ; 
  
  double minJetPt ;
  double maxJetEta ;
  double minJetMass ;
  int    minJets ;

  razorCalc(double minJetPt_ = 50. ,
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

    mR = 0. ;
    R  = 0. ;
  }

  void compute( TClonesArray* branchJet ){

    // all variables to zero
    clearVars();

  }

};
  
    

