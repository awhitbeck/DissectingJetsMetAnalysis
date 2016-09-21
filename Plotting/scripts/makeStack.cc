#include <iostream>

#include "TROOT.h"
#include "THStack.h"
#include "TString.h"
#include "TLegend.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TH1F.h"

#include "samples.cc"

using namespace std;

const int NumSamples = 8;
const int NumVars = 15 ;

TString vars[NumVars] = { "HT" , 
			  "MHT" , 
			  "mT2" , 
			  "mT2_zeroMass" , 
			  "alphaT" , 
			  "alphaT_dHThemi" , 
			  "mRazor" , 
			  "dRazor" ,
			  "mEff" , 
			  "MHTOvHT", 
			  "NJets" , 
			  "NLeptons" , 
			  "dPhi" , 
			  "dEta" , 
			  "sumJetMass"                          
                        };
TString axisLabel[NumVars] = { "H_{T} [GeV]" ,			       
			       "#slash{H}_{T} [GeV]",			       
			       "M_{T2} [GeV]",			       
			       "M_{T2}^{CMS} [GeV]",			       
			       "#alpha_{T}",			       
			       "#alpha_{T}",			       
			       "m_{R} [GeV]",			       
			       "R^{2}",			       
			       "m_{eff} [GeV]",			       
			       "#slash{H}_{T}/#sqrt{H_{T}}",			       
			       "N_{j}",			       
			       "N_{lep}",			       
			       "#Delta#phi",			       
			       "#Delta#eta",			       
			       "M_{J} [GeV]"                             
                             };

void initSamples(plotterInput* allSamples){

  gROOT->ProcessLine(".L ~/tdrstyle.C");
  gROOT->ProcessLine("setTDRStyle()");

  plotterInput QCD;
  QCD.fillColor=kGreen+1; QCD.histoTag="QCD"; QCD.legLabel="QCD"; QCD.stack=true;
  plotterInput znunu;
  znunu.fillColor=kBlue+1; znunu.histoTag="znunu"; znunu.legLabel="Z(#nu#nu)"; znunu.stack=true;
  plotterInput Wjets;
  Wjets.fillColor=kCyan+1; Wjets.histoTag="Wjets"; Wjets.legLabel="W(l#nu)"; Wjets.stack=true;
  plotterInput ttbar;
  ttbar.fillColor=kMagenta+1; ttbar.histoTag="ttbar"; ttbar.legLabel="t#bar{t}"; ttbar.stack=true;
  
  plotterInput allBkg[4] = {QCD,znunu,Wjets,ttbar};
  
  plotterInput GjN1_GjN1_1000;
  GjN1_GjN1_1000.lineColor=kRed+0; 
  GjN1_GjN1_1000.histoTag="GjN1_GjN1_1000"; 
  GjN1_GjN1_1000.legLabel="2 partons"; 
  GjN1_GjN1_1000.stack=false;

  plotterInput GjjjjN1_GjjjjN1_1000;
  GjjjjN1_GjjjjN1_1000.lineColor=kRed+2; 
  GjjjjN1_GjjjjN1_1000.histoTag="GjjjjN1_GjjjjN1_1000"; 
  GjjjjN1_GjjjjN1_1000.legLabel="8 partons"; 
  GjjjjN1_GjjjjN1_1000.stack=false;
  
  plotterInput GjN1_GjN1_1000_compressed;
  GjN1_GjN1_1000_compressed.lineColor=kRed+0; 
  GjN1_GjN1_1000_compressed.lineStyle=2;
  GjN1_GjN1_1000_compressed.histoTag="GjN1_GjN1_1000_compressed"; 
  GjN1_GjN1_1000_compressed.legLabel="2 partons comp."; 
  GjN1_GjN1_1000_compressed.stack=false;
  
  plotterInput GjjjjN1_GjjjjN1_1000_compressed;
  GjjjjN1_GjjjjN1_1000_compressed.lineColor=kRed+2; 
  GjjjjN1_GjjjjN1_1000_compressed.lineStyle=2;
  GjjjjN1_GjjjjN1_1000_compressed.histoTag="GjjjjN1_GjjjjN1_1000_compressed"; 
  GjjjjN1_GjjjjN1_1000_compressed.legLabel="8 partons comp."; 
  GjjjjN1_GjjjjN1_1000_compressed.stack=false;
  
  plotterInput allSig[4]={GjN1_GjN1_1000,GjjjjN1_GjjjjN1_1000,GjN1_GjN1_1000_compressed,GjjjjN1_GjjjjN1_1000_compressed};
  
  allSamples[0] = QCD;
  allSamples[1] = znunu;
  allSamples[2] = Wjets;
  allSamples[3] = ttbar;
  allSamples[4] = GjN1_GjN1_1000;
  allSamples[5] = GjjjjN1_GjjjjN1_1000;
  allSamples[6] = GjN1_GjN1_1000_compressed;
  allSamples[7] = GjjjjN1_GjjjjN1_1000_compressed;

}

int main(int argc, char** argv){

  plotterInput allSamples[NumSamples];
  initSamples(allSamples);

  for( int i = 0 ; i < NumVars ; i++ ){

    TFile* f = new TFile("genericPlotter.root");
    TLegend* leg = new TLegend(0.01,0.01,0.99,0.99);
    leg->SetNColumns(4);
    leg->SetBorderSize(0);
    leg->SetFillColor(0);
  
    THStack* stack = new THStack("stack","stack");

    double max = 0;
    double bkgYield = 0;

    for( int s = 0 ; s < NumSamples ; s++ ){
      if( ! allSamples[s].stack ) continue;
      allSamples[s].histo = (TH1F*) f->Get(vars[i]+"_"+allSamples[s].histoTag);
      if( allSamples[s].histo == 0 ) continue; 
      if( allSamples[s].histoTag == "QCD" ) allSamples[s].histo->Scale(1./7.);
      if( allSamples[s].histo->GetMaximum() > max ) max = allSamples[s].histo->GetMaximum();
      allSamples[s].setStyle();

      bkgYield+=allSamples[s].histo->Integral();
      stack->Add(allSamples[s].histo);
      leg->AddEntry(allSamples[s].histo,allSamples[s].legLabel,"f");
		    
    } 
    
    TCanvas* can  = new TCanvas("can","can",1200,800);
 
    stack->Draw("HIST");
    stack->GetXaxis()->SetTitle(axisLabel[i]);
    stack->GetXaxis()->CenterTitle();
    stack->GetYaxis()->SetTitle("Events");
    stack->GetYaxis()->CenterTitle();
    
    max = stack->GetMaximum();

    for( int s = 0 ; s < NumSamples ; s++ ){

      if( allSamples[s].stack ) continue;
      allSamples[s].histo = (TH1F*) f->Get(vars[i]+"_"+allSamples[s].histoTag);
      if( allSamples[s].histo == 0 ) continue;
      //cout << "Integral: " << allSamples[s].histo->Integral() << endl;
      allSamples[s].histo->Scale(bkgYield/allSamples[s].histo->Integral());
      if( allSamples[s].histo->GetMaximum() > max ) max = allSamples[s].histo->GetMaximum();
      allSamples[s].setStyle();
      allSamples[s].histo->Draw("SAME,HIST");
      leg->AddEntry(allSamples[s].histo,allSamples[s].legLabel,"f");
		      
    }

    stack->SetMaximum(max*1.3);

    can->SaveAs(vars[i]+"_allStack.png");
    can->SaveAs(vars[i]+"_allStack.eps");

    can->SetLogy();
    can->SaveAs(vars[i]+"_allStackLogY.png");
    can->SaveAs(vars[i]+"_allStackLogY.eps");

    TCanvas* legCan = new TCanvas("legCan","legCan",1200,200);
    leg->Draw();
    legCan->SaveAs("allStackLegend.png");
    legCan->SaveAs("allStackLegend.eps");
     
    delete legCan;
    delete can;
  }

  return 0;

}
