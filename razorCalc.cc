#include "razorCalc.h"
#include <iostream>

razorCalc::razorCalc(double minJetPt_   ,
		     double maxJetEta_  ,
		     double minJetMass_ ,
		     int    minJets_ ,
		     bool   debug_ ){
  
  minJetPt = minJetPt_ ; 
  maxJetEta = maxJetEta_ ; 
  minJetMass = minJetMass_ ; 
  minJets = minJets_ ; 
  debug = debug_ ;

  clearVars();
  
};

void razorCalc::computeVars(vector<TLorentzVector> jets, double METpx , double METpy){
  
  vector<TLorentzVector> goodJets;

  for( unsigned int iJet = 0 ; iJet < jets.size() ; iJet++ ){

    if( jets[iJet].Pt()>minJetPt || 
	abs(jets[iJet].Eta())<maxJetEta || 
	jets[iJet].M()>=minJetMass){
      
      goodJets.push_back( jets[iJet] );
      
    }
    
    clearVars();  
    if( goodJets.size() < minJets ) continue;

  }
  
  hemispheres = getHemispheres(goodJets);
  
  if( debug ){
    cout << "-------------" << endl;
    for( unsigned int iHem = 0 ; iHem < hemispheres.size() ; iHem++ ){
      
      cout << "hemisphere " << iHem << endl;
      cout << "pt: " << hemispheres[iHem].Pt() ;
      cout << " eta: " << hemispheres[iHem].Eta() ;
      cout << " phi: " << hemispheres[iHem].Phi() << endl;
    
    }// end loop over hemispheres
  }  // end debug outputs
  
  MET = TLorentzVector(METpx, METpy, 0.0, 0.0);
  
  mR = computeMR(hemispheres[0], hemispheres[1]);
  R = computeR2(hemispheres[0], hemispheres[1], MET);

};

vector<TLorentzVector> razorCalc::getHemispheres(vector<TLorentzVector> jets){

  int nJets = jets.size();
  
  vector<TLorentzVector> possibleHem1s; 
  //holds possible hemisphere combinations
  vector<TLorentzVector> possibleHem2s;

  //stolen from
  //https://github.com/pierinim/BSMatLHC/blob/master/BSMApp/src/CMS/CMSHemisphere.cc
  
  int nComb = pow(2, nJets);

  if( debug ) 
    cout << "nComb: " << nComb << endl;
 
  //step 1: store all possible partitions of the input jets
  
  int j_count;
  
  for(int i = 1 ; i < nComb-1 ; i++){
    //note we omit the trivial hemisphere combinations (0 and nComb-1)
    
    TLorentzVector j_temp1, j_temp2;
    int itemp = i;    
    j_count = nComb/2;
    int count = 0;
    
    while(j_count > 0){
      //decompose i into binary '1's and '0's ; put the '1' jets into j_temp1 and the '0' jets into j_temp2
      
      if(itemp/j_count == 1){
	j_temp1 += jets[count];
      } else {
	j_temp2 += jets[count];
      }
      
      itemp -= j_count*(itemp/j_count); 
      //note this is always (0 or 1)*j_count
      j_count /= 2;
      count++;
      
    }// end while loop over j_count
    
    possibleHem1s.push_back(j_temp1);
    possibleHem2s.push_back(j_temp2);
    
  }// end for loop over nComb

  //step 2: choose the partition that minimizes m1^2 + m2^2
  
  double mMin = -1;
  
  TLorentzVector myHem1;
  TLorentzVector myHem2;
  
  for(size_t i=0; i < possibleHem1s.size(); i++){
    
    double mTemp = possibleHem1s[i].M2() + possibleHem2s[i].M2();
    
    if( debug )
      cout << "mTemp: " << mTemp << endl;
    
    if(mMin < 0 || mTemp < mMin){
      
      mMin = mTemp;
      myHem1 = possibleHem1s[i];
      myHem2 = possibleHem2s[i];
      
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
  
};

float razorCalc::computeMR(TLorentzVector hem1, TLorentzVector hem2){
    
  return sqrt(pow(hem1.P() + hem2.P(),2) -
	      pow(hem1.Pz() + hem2.Pz(),2)
	      );
  
};
  
float razorCalc::computeR2(TLorentzVector hem1, TLorentzVector hem2, TLorentzVector pfMet){
  
  double mR_ = computeMR(hem1, hem2);
  double term1 = pfMet.Pt()/2*(hem1.Pt()
			       + hem2.Pt());
  double term2 = pfMet.Px()/2*(hem1.Px()
			       + hem2.Px()) + pfMet.Py()/2*(hem1.Py()
							    + hem2.Py());
  
  //dot product of MET with (p1T + p2T)
  
  double mTR = sqrt(term1 - term2);    
  return (mTR / mR_) * (mTR / mR_);
  
};

void razorCalc::clearVars(){
  
  mR = 0. ;
  R  = 0. ;
  
};

    

