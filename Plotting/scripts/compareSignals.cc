#include <iostream>

#include "TROOT.h"
#include "THStack.h"
#include "TString.h"
#include "TLegend.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TH1F.h"

#include "samples.cc"

/* ---------------------------------------
   To compile and run: 
   g++ `root-config --cflags --glibs` compareSignals.cc -o compareSignals.exe ; ./compareSignals.exe
   --------------------------------------- */

using namespace std;

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
			       "M_{T2}^{m=0} [GeV]",			       
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

void initSamples(plotterInput* output){
  
  plotterInput GjN1_GjN1_1000;
  GjN1_GjN1_1000.lineColor=kRed; 
  GjN1_GjN1_1000.histoTag="GjN1_GjN1_1000"; 
  GjN1_GjN1_1000.legLabel="2 partons"; 
  GjN1_GjN1_1000.stack=false;

  plotterInput GjN1_GjjN1_1000;
  GjN1_GjjN1_1000.lineColor=kOrange; 
  GjN1_GjjN1_1000.histoTag="GjN1_GjjN1_1000"; 
  GjN1_GjjN1_1000.legLabel="3 partons"; 
  GjN1_GjjN1_1000.stack=false;

  plotterInput GjjN1_GjjN1_1000;
  GjjN1_GjjN1_1000.lineColor=kYellow; 
  GjjN1_GjjN1_1000.histoTag="GjjN1_GjjN1_1000"; 
  GjjN1_GjjN1_1000.legLabel="4 partons"; 
  GjjN1_GjjN1_1000.stack=false;

  plotterInput GjjN1_GjjjN1_1000;
  GjjN1_GjjjN1_1000.lineColor=kGreen; 
  GjjN1_GjjjN1_1000.lineStyle=1; 
  GjjN1_GjjjN1_1000.histoTag="GjjN1_GjjjN1_1000"; 
  GjjN1_GjjjN1_1000.legLabel="5 partons"; 
  GjjN1_GjjjN1_1000.stack=false;

  plotterInput GjjjN1_GjjjN1_1000;
  GjjjN1_GjjjN1_1000.lineColor=kBlue;
  GjjjN1_GjjjN1_1000.lineStyle=1;
  GjjjN1_GjjjN1_1000.histoTag="GjjjN1_GjjjN1_1000"; 
  GjjjN1_GjjjN1_1000.legLabel="6 partons"; 
  GjjjN1_GjjjN1_1000.stack=false;

  plotterInput GjjjN1_GjjjjN1_1000;
  GjjjN1_GjjjjN1_1000.lineColor=kCyan; 
  GjjjN1_GjjjjN1_1000.lineStyle=1; 
  GjjjN1_GjjjjN1_1000.histoTag="GjjjN1_GjjjjN1_1000"; 
  GjjjN1_GjjjjN1_1000.legLabel="7 partons"; 
  GjjjN1_GjjjjN1_1000.stack=false;

  plotterInput GjjjjN1_GjjjjN1_1000;
  GjjjjN1_GjjjjN1_1000.lineColor=kMagenta+1; 
  GjjjjN1_GjjjjN1_1000.lineStyle=1; 
  GjjjjN1_GjjjjN1_1000.histoTag="GjjjjN1_GjjjjN1_1000"; 
  GjjjjN1_GjjjjN1_1000.legLabel="8 partons"; 
  GjjjjN1_GjjjjN1_1000.stack=false;

  output[6] = GjjjjN1_GjjjjN1_1000;
  output[5] = GjjjN1_GjjjjN1_1000;
  output[4] = GjjjN1_GjjjN1_1000;
  output[3] = GjjN1_GjjjN1_1000;
  output[2] = GjjN1_GjjN1_1000;
  output[1] = GjN1_GjjN1_1000;
  output[0] = GjN1_GjN1_1000;

}

void initSamplesCompressed(plotterInput* output){
  
  plotterInput GjN1_GjN1_1000;
  GjN1_GjN1_1000.lineColor=kRed; 
  GjN1_GjN1_1000.lineStyle=1;
  GjN1_GjN1_1000.histoTag="GjN1_GjN1_1000_compressed"; 
  GjN1_GjN1_1000.legLabel="2 partons comp."; 
  GjN1_GjN1_1000.stack=false;

  plotterInput GjN1_GjjN1_1000;
  GjN1_GjjN1_1000.lineColor=kOrange; 
  GjN1_GjjN1_1000.lineStyle=1;
  GjN1_GjjN1_1000.histoTag="GjN1_GjjN1_1000_compressed"; 
  GjN1_GjjN1_1000.legLabel="3 partons comp."; 
  GjN1_GjjN1_1000.stack=false;

  plotterInput GjjN1_GjjN1_1000;
  GjjN1_GjjN1_1000.lineColor=kYellow; 
  GjjN1_GjjN1_1000.lineStyle=1;
  GjjN1_GjjN1_1000.histoTag="GjjN1_GjjN1_1000_compressed"; 
  GjjN1_GjjN1_1000.legLabel="4 partons comp."; 
  GjjN1_GjjN1_1000.stack=false;

  plotterInput GjjN1_GjjjN1_1000;
  GjjN1_GjjjN1_1000.lineColor=kGreen; 
  GjjN1_GjjjN1_1000.lineStyle=1;
  GjjN1_GjjjN1_1000.histoTag="GjjN1_GjjjN1_1000_compressed"; 
  GjjN1_GjjjN1_1000.legLabel="5 partons comp."; 
  GjjN1_GjjjN1_1000.stack=false;

  plotterInput GjjjN1_GjjjN1_1000;
  GjjjN1_GjjjN1_1000.lineColor=kBlue; 
  GjjjN1_GjjjN1_1000.lineStyle=1;
  GjjjN1_GjjjN1_1000.histoTag="GjjjN1_GjjjN1_1000_compressed"; 
  GjjjN1_GjjjN1_1000.legLabel="6 partons comp."; 
  GjjjN1_GjjjN1_1000.stack=false;

  plotterInput GjjjN1_GjjjjN1_1000;
  GjjjN1_GjjjjN1_1000.lineColor=kCyan; 
  GjjjN1_GjjjjN1_1000.lineStyle=1;
  GjjjN1_GjjjjN1_1000.histoTag="GjjjN1_GjjjjN1_1000_compressed"; 
  GjjjN1_GjjjjN1_1000.legLabel="7 partons comp."; 
  GjjjN1_GjjjjN1_1000.stack=false;
  
  plotterInput GjjjjN1_GjjjjN1_1000;
  GjjjjN1_GjjjjN1_1000.lineColor=kMagenta+1; 
  GjjjjN1_GjjjjN1_1000.lineStyle=1;
  GjjjjN1_GjjjjN1_1000.histoTag="GjjjjN1_GjjjjN1_1000_compressed"; 
  GjjjjN1_GjjjjN1_1000.legLabel="8 partons comp."; 
  GjjjjN1_GjjjjN1_1000.stack=false;

  output[6] = GjjjjN1_GjjjjN1_1000;
  output[5] = GjjjN1_GjjjjN1_1000;
  output[4] = GjjjN1_GjjjN1_1000;
  output[3] = GjjN1_GjjjN1_1000;
  output[2] = GjjN1_GjjN1_1000;
  output[1] = GjN1_GjjN1_1000;
  output[0] = GjN1_GjN1_1000;

}

void initSamplesByMass(plotterInput* output ){
  
  plotterInput GjN1_GjN1_500;
  GjN1_GjN1_500.lineColor=kRed; 
  GjN1_GjN1_500.lineStyle=1;
  GjN1_GjN1_500.histoTag="GjN1_GjN1_500"; 
  GjN1_GjN1_500.legLabel="m_{#tilde{g}}=500 GeV"; 
  GjN1_GjN1_500.stack=false;

  plotterInput GjN1_GjN1_1000;
  GjN1_GjN1_1000.lineColor=kGreen; 
  GjN1_GjN1_1000.lineStyle=1;
  GjN1_GjN1_1000.histoTag="GjN1_GjN1_1000"; 
  GjN1_GjN1_1000.legLabel="m_{#tilde{g}}=1000 GeV"; 
  GjN1_GjN1_1000.stack=false;
  
  plotterInput GjN1_GjN1_1500;
  GjN1_GjN1_1500.lineColor=kBlue; 
  GjN1_GjN1_1500.lineStyle=1;
  GjN1_GjN1_1500.histoTag="GjN1_GjN1_1500"; 
  GjN1_GjN1_1500.legLabel="m_{#tilde{g}}=1500 GeV"; 
  GjN1_GjN1_1500.stack=false;

  plotterInput GjjjjN1_GjjjjN1_500;
  GjjjjN1_GjjjjN1_500.lineColor=kRed; 
  GjjjjN1_GjjjjN1_500.lineStyle=2;
  GjjjjN1_GjjjjN1_500.histoTag="GjjjjN1_GjjjjN1_500"; 
  GjjjjN1_GjjjjN1_500.legLabel="m_{#tilde{g}}=500 GeV";
  GjjjjN1_GjjjjN1_500.stack=false;

  plotterInput GjjjjN1_GjjjjN1_1000;
  GjjjjN1_GjjjjN1_1000.lineColor=kGreen; 
  GjjjjN1_GjjjjN1_1000.lineStyle=2;
  GjjjjN1_GjjjjN1_1000.histoTag="GjjjjN1_GjjjjN1_1000"; 
  GjjjjN1_GjjjjN1_1000.legLabel="m_{#tilde{g}}=1000 GeV";
  GjjjjN1_GjjjjN1_1000.stack=false;
  
  plotterInput GjjjjN1_GjjjjN1_1500;
  GjjjjN1_GjjjjN1_1500.lineColor=kBlue; 
  GjjjjN1_GjjjjN1_1500.lineStyle=2;
  GjjjjN1_GjjjjN1_1500.histoTag="GjjjjN1_GjjjjN1_1500"; 
  GjjjjN1_GjjjjN1_1500.legLabel="m_{#tilde{g}}=1500 GeV";
  GjjjjN1_GjjjjN1_1500.stack=false;

  output[0] = GjN1_GjN1_500;
  output[1] = GjN1_GjN1_1000;
  output[2] = GjN1_GjN1_1500;
  output[3] = GjjjjN1_GjjjjN1_500;
  output[4] = GjjjjN1_GjjjjN1_1000;
  output[5] = GjjjjN1_GjjjjN1_1500;


}

void initSamplesByMassCompressed(plotterInput* output ){
  
  plotterInput GjN1_GjN1_500;
  GjN1_GjN1_500.lineColor=kRed; 
  GjN1_GjN1_500.lineStyle=1;
  GjN1_GjN1_500.histoTag="GjN1_GjN1_500_compressed"; 
  GjN1_GjN1_500.legLabel="m_{#tilde{g}}=500 GeV"; 
  GjN1_GjN1_500.stack=false;

  plotterInput GjN1_GjN1_1000;
  GjN1_GjN1_1000.lineColor=kGreen; 
  GjN1_GjN1_1000.lineStyle=1;
  GjN1_GjN1_1000.histoTag="GjN1_GjN1_1000_compressed"; 
  GjN1_GjN1_1000.legLabel="m_{#tilde{g}}=1000 GeV"; 
  GjN1_GjN1_1000.stack=false;
  
  plotterInput GjN1_GjN1_1500;
  GjN1_GjN1_1500.lineColor=kBlue; 
  GjN1_GjN1_1500.lineStyle=1;
  GjN1_GjN1_1500.histoTag="GjN1_GjN1_1500_compressed"; 
  GjN1_GjN1_1500.legLabel="m_{#tilde{g}}=1500 GeV"; 
  GjN1_GjN1_1500.stack=false;

  output[0] = GjN1_GjN1_500;
  output[1] = GjN1_GjN1_1000;
  output[2] = GjN1_GjN1_1500;

  plotterInput GjjjjN1_GjjjjN1_500;
  GjjjjN1_GjjjjN1_500.lineColor=kRed; 
  GjjjjN1_GjjjjN1_500.lineStyle=2;
  GjjjjN1_GjjjjN1_500.histoTag="GjjjjN1_GjjjjN1_500_compressed"; 
  GjjjjN1_GjjjjN1_500.legLabel="m_{#tilde{g}}=500 GeV";
  GjjjjN1_GjjjjN1_500.stack=false;

  plotterInput GjjjjN1_GjjjjN1_1000;
  GjjjjN1_GjjjjN1_1000.lineColor=kGreen; 
  GjjjjN1_GjjjjN1_1000.lineStyle=2;
  GjjjjN1_GjjjjN1_1000.histoTag="GjjjjN1_GjjjjN1_1000_compressed"; 
  GjjjjN1_GjjjjN1_1000.legLabel="m_{#tilde{g}}=1000 GeV";
  GjjjjN1_GjjjjN1_1000.stack=false;
  
  plotterInput GjjjjN1_GjjjjN1_1500;
  GjjjjN1_GjjjjN1_1500.lineColor=kBlue; 
  GjjjjN1_GjjjjN1_1500.lineStyle=2;
  GjjjjN1_GjjjjN1_1500.histoTag="GjjjjN1_GjjjjN1_1500_compressed"; 
  GjjjjN1_GjjjjN1_1500.legLabel="m_{#tilde{g}}=1500 GeV";
  GjjjjN1_GjjjjN1_1500.stack=false;

  output[3] = GjjjjN1_GjjjjN1_500;
  output[4] = GjjjjN1_GjjjjN1_1000;
  output[5] = GjjjjN1_GjjjjN1_1500;

}

int main(int argc, char** argv){

  gROOT->ProcessLine(".L ~/tdrstyle.C");
  gROOT->ProcessLine("setTDRStyle()");

  //const int NumSamples = 7;
  //plotterInput allSamples[NumSamples];
  //initSamples(allSamples);
  //initSamplesCompressed(allSamples);

  const int NumSamples = 6;
  plotterInput allSamples[NumSamples];
  initSamplesByMass(allSamples);
  //initSamplesByMassCompressed(allSamples);
  
  for( int i = 0 ; i < NumVars ; i++ ){

    TFile* f = new TFile("genericPlotter.root");
    TLegend* leg = new TLegend(0.01,0.01,0.99,0.99);
    leg->SetNColumns(3);
    leg->SetBorderSize(0);
    leg->SetFillColor(0);
  
    double max = 0;
    double bkgYield = 0;

    TCanvas* can  = new TCanvas("can","can",1200,800);
    bool first = true;

    for( int s = 0 ; s < NumSamples ; s++ ){

      allSamples[s].histo = (TH1F*) f->Get(vars[i]+"_"+allSamples[s].histoTag);
      if( allSamples[s].histo == 0 ){
	cout << "Histo: " << vars[i]+"_"+allSamples[s].histoTag << " not found" << endl;
	continue;
      }
      allSamples[s].histo->GetXaxis()->SetTitle(axisLabel[i]);
      allSamples[s].histo->GetXaxis()->CenterTitle();
      allSamples[s].histo->GetYaxis()->CenterTitle();
      allSamples[s].histo->Scale(1./allSamples[s].histo->Integral());
      if( allSamples[s].histo->GetMaximum() > max ) max = allSamples[s].histo->GetMaximum();
      allSamples[s].setStyle();
      if( first ){
	allSamples[s].histo->Draw("HIST");
	first = false ;
      }else
	allSamples[s].histo->Draw("SAME,HIST");
      leg->AddEntry(allSamples[s].histo,allSamples[s].legLabel,"f");
		      
    }

    allSamples[0].histo->SetMaximum(max*1.3);

    can->SaveAs(vars[i]+"_compareSignalsByMass.png");
    can->SaveAs(vars[i]+"_compareSignalsByMass.eps");

    can->SetLogy();
    can->SaveAs(vars[i]+"_compareSignalsByMassLogY.png");
    can->SaveAs(vars[i]+"_compareSignalsByMassLogY.eps");

    TCanvas* legCan = new TCanvas("legCan","legCan",1200,200);
    leg->Draw();
    legCan->SaveAs("compareSignalsByMassLegend.png");
    legCan->SaveAs("compareSignalsByMassLegend.eps");
     
    delete legCan;
    delete can;
  }

  return 0;

}
