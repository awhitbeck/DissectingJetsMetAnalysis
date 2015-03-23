#include "TClonesArray.h"
#include "classes/DelphesClasses.h"

class sumJetMassCalc{

public: 

  double sumJetMass ; 
  int numJetMassJets ;  
  
  double minJetPt ;
  double maxJetEta ;
  double minJetMass ;
  int    minJets ;

  sumJetMassCalc(double minJetPt_ = 50. ,
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

    sumJetMass = 0. ;
    numJetMassJets = 0 ;

  }

  void compute( TClonesArray* branchJet ){

    // all variables to zero
    clearVars();

    for( int iJet = 0 ; iJet < branchJet->GetEntries() ; iJet++){
      
      Jet *jet = (Jet*) branchJet->At( iJet );

      if( jet->Mass > minJetMass  && jet->PT   > minJetPt  && fabs( jet->Eta ) < maxJetEta ){
	sumJetMass += jet->Mass ;
	numJetMassJets++;
      }

    }// end loop over jets

    if( numJetMassJets < minJets ) sumJetMass = 0.0 ; 

  }

};
  
    

