#include "TClonesArray.h"
#include "classes/DelphesClasses.h"
#include <vector>
#include "TLorentzVector.h"

using namespace std;

class razorCalc{

public: 

  double mR ; 
  double R ; 
  
  double minJetPt ;
  double maxJetEta ;
  double minJetMass ;
  unsigned int    minJets ;
  bool debug;

  vector<TLorentzVector> hemispheres;
  TLorentzVector MET;

  razorCalc(double minJetPt_ = 50. ,
	    double maxJetEta_ = 2.5 ,
	    double minJetMass_ = 50. ,
	    int    minJets_ = 2 , 
	    bool   debug_ = false);
  
  vector<TLorentzVector> getHemispheres(vector<TLorentzVector> jets);
  float computeMR(TLorentzVector hem1, TLorentzVector hem2);
  float computeR2(TLorentzVector hem1, TLorentzVector hem2, TLorentzVector pfMet);

  void computeVars(vector<TLorentzVector> jets, double METpx , double METpy );
  void clearVars();

};

