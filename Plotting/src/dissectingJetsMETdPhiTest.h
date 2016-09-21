//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Feb 22 17:05:58 2016 by ROOT version 6.02/05
// from TTree analysisTree/
// found on file: QCD_1000_1600_113_slim.root
//////////////////////////////////////////////////////////

#ifndef dissectingJetsMETdPhiTest_h
#define dissectingJetsMETdPhiTest_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include "TLorentzVector.h"

// Header file for the classes stored in the TTree if any.

class dissectingJetsMETdPhiTest {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Double_t        HT;
   Double_t        MHT;
   Double_t        MET;
   Double_t        METphi;
   Double_t        dPhi;
   Double_t        dPhi1;
   Double_t        dPhi2;
   Double_t        dPhi3;
   Double_t        dPhi4;
   std::vector<TLorentzVector> *Jets;
   Int_t           NJets;
   Int_t           NLeptons;
   Double_t        sumJetMass;
   Double_t        leadJetPt;
   Double_t        mEff;
   Double_t        dEta;
   Double_t        alphaT;
   Double_t        alphaT_dHThemi;
   Double_t        mT2;
   Double_t        mT2_zeroMass;
   Double_t        mRazor;
   Double_t        dRazor;

   // List of branches
   TBranch        *b_HT;   //!
   TBranch        *b_MHT;   //!
   TBranch        *b_MET;   //!
   TBranch        *b_METphi;   //!
   TBranch        *b_dPhi;   //!
   TBranch        *b_dPhi1;   //!
   TBranch        *b_dPhi2;   //!
   TBranch        *b_dPhi3;   //!
   TBranch        *b_dPhi4;   //!
   TBranch        *b_Jets;   //!
   TBranch        *b_NJets;   //!
   TBranch        *b_NLeptons;   //!
   TBranch        *b_sumJetMass;   //!
   TBranch        *b_leadJetPt;   //!
   TBranch        *b_mEff;   //!
   TBranch        *b_dEta;   //!
   TBranch        *b_alphaT;   //!
   TBranch        *b_alphaT_dHThemi;   //!
   TBranch        *b_mT2;   //!
   TBranch        *b_mT2_zeroMass;   //!
   TBranch        *b_mRazor;   //!
   TBranch        *b_dRazor;   //!

   dissectingJetsMETdPhiTest(TTree *tree=0);
   virtual ~dissectingJetsMETdPhiTest();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef dissectingJetsMETdPhiTest_cxx
dissectingJetsMETdPhiTest::dissectingJetsMETdPhiTest(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("QCD_1000_1600_113_slim.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("QCD_1000_1600_113_slim.root");
      }
      f->GetObject("analysisTree",tree);

   }
   Init(tree);
}

dissectingJetsMETdPhiTest::~dissectingJetsMETdPhiTest()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t dissectingJetsMETdPhiTest::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t dissectingJetsMETdPhiTest::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void dissectingJetsMETdPhiTest::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   Jets = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("HT", &HT, &b_HT);
   fChain->SetBranchAddress("MHT", &MHT, &b_MHT);
   fChain->SetBranchAddress("MET", &MET, &b_MET);
   fChain->SetBranchAddress("METphi", &METphi, &b_METphi);
   fChain->SetBranchAddress("dPhi", &dPhi, &b_dPhi);
   fChain->SetBranchAddress("dPhi1", &dPhi1, &b_dPhi1);
   fChain->SetBranchAddress("dPhi2", &dPhi2, &b_dPhi2);
   fChain->SetBranchAddress("dPhi3", &dPhi3, &b_dPhi3);
   fChain->SetBranchAddress("dPhi4", &dPhi4, &b_dPhi4);
   fChain->SetBranchAddress("Jets", &Jets, &b_Jets);
   fChain->SetBranchAddress("NJets", &NJets, &b_NJets);
   fChain->SetBranchAddress("NLeptons", &NLeptons, &b_NLeptons);
   fChain->SetBranchAddress("sumJetMass", &sumJetMass, &b_sumJetMass);
   fChain->SetBranchAddress("leadJetPt", &leadJetPt, &b_leadJetPt);
   fChain->SetBranchAddress("mEff", &mEff, &b_mEff);
   fChain->SetBranchAddress("dEta", &dEta, &b_dEta);
   fChain->SetBranchAddress("alphaT", &alphaT, &b_alphaT);
   fChain->SetBranchAddress("alphaT_dHThemi", &alphaT_dHThemi, &b_alphaT_dHThemi);
   fChain->SetBranchAddress("mT2", &mT2, &b_mT2);
   fChain->SetBranchAddress("mT2_zeroMass", &mT2_zeroMass, &b_mT2_zeroMass);
   fChain->SetBranchAddress("mRazor", &mRazor, &b_mRazor);
   fChain->SetBranchAddress("dRazor", &dRazor, &b_dRazor);
   Notify();
}

Bool_t dissectingJetsMETdPhiTest::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void dissectingJetsMETdPhiTest::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t dissectingJetsMETdPhiTest::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef dissectingJetsMETdPhiTest_cxx
