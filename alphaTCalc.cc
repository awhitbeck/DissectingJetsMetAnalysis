#include "TClonesArray.h"
#include "classes/DelphesClasses.h"

class alphaTCalc{

public: 

  double alphaT ; 
  
  double minJetPt ;
  double maxJetEta ;
  double minJetMass ;
  int    minJets ;

  alphaTCalc(double minJetPt_ = 0. ,
	     double maxJetEta_ = 5.0 ,
	     double minJetMass_ = 0. ,
	     int    minJets_ = 2 ){
    
    minJetPt = minJetPt_ ; 
    maxJetEta = maxJetEta_ ; 
    minJetMass = minJetMass_ ; 
    minJets = minJets_ ; 

    clearVars();

  }

  void clearVars(){

    alphaT = 0. ;

  }

  double  compute( TLorentzVector jet1 , 
		   TLorentzVector jet2 ){

    // all variables to zero
    clearVars();
    
    double MT = sqrt( pow( (jet1.Et()+jet2.Et() ) , 2 ) - 
		      pow( (jet1.Px()+jet2.Px() ) , 2 ) -
		      pow( (jet1.Py()+jet2.Py() ) , 2 ) ) ;

    if( jet1.Et() < jet2.Et() )
      alphaT = jet1.Et() / MT ; 
    else 
      alphaT = jet2.Et() / MT ; 

    return alphaT;   

  }

};
  
    

