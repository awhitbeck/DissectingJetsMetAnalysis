#include "TClonesArray.h"
#include "classes/DelphesClasses.h"

class alphaTCalc{

public: 

  double alphaT ; 
  
  double minJetPt ;
  double maxJetEta ;
  double minJetMass ;
  int    minJets ;
  vector<TLorentzVector> hemispheres;

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

  vector<TLorentzVector> getHemispheres(vector<TLorentzVector> jets){

    int nJets = jets.size();
  
    vector<TLorentzVector> possibleHem1s; 
    //holds possible hemisphere combinations
    vector<TLorentzVector> possibleHem2s;

    int nComb = pow(2, nJets);

    for(int i = 1 ; i < nComb-1 ; i++){
      //note we omit the trivial hemisphere combinations (0 and nComb-1)
    
      TLorentzVector j_temp1, j_temp2;
      // ---------------------------------------------------
      // ---------------------------------------------------
      // my decomposition method
      // for each of the ith combinations, decompose
      // i bit-wise.  Each bit is a boolean determining
      // whether or not the jet goes into collection 1 
      // or collection 2.  
      for( int iJet = 0 ; iJet < nJets ; iJet++ ){
	if( ( ( i >> iJet ) & 1 ) == 1 )
	  j_temp1 += jets[iJet];
	else 
	  j_temp2 += jets[iJet];
      }
      // done decomposing jets
      // ---------------------------------------------------
      // ---------------------------------------------------

      possibleHem1s.push_back(j_temp1);
      possibleHem2s.push_back(j_temp2);
    
    }// end for loop over nComb

    //step 2: choose the partition that minimizes m1^2 + m2^2
  
    double dHtMin = 1e10;
  
    TLorentzVector myHem1 = possibleHem1s[0] ;
    TLorentzVector myHem2 = possibleHem2s[0] ;
  
    for(size_t i=0; i < possibleHem1s.size(); i++){
      double dHT = fabs( possibleHem1s[i].Pt() - possibleHem2s[i].Pt() );    
      if( dHT < dHtMin ){
	dHtMin = dHT;
	myHem1 = possibleHem1s[i] ; 
	myHem2 = possibleHem2s[i] ; 
      }
    }// end for loop over possible hemispheres
 
    //return the hemispheres in decreasing order of pt  
    vector<TLorentzVector> hemsOut;
    if(myHem1.Pt() > myHem2.Pt()){
      hemsOut.push_back(myHem1);     
      hemsOut.push_back(myHem2);
    } else {
      hemsOut.push_back(myHem2);      
      hemsOut.push_back(myHem1);
    }
  
    return hemsOut;
  
  }

  double compute( vector<TLorentzVector> jets ){
    // all variables to zero
    clearVars();
    hemispheres = getHemispheres( jets );

    return compute( hemispheres[0] , hemispheres[1] );
  }

  double compute( TLorentzVector jet1 , 
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
  
    

