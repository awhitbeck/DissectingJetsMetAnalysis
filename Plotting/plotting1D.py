from inputFiles_tranTrees import *
from ROOT import *

gROOT.ProcessLine(".L ~/tdrstyle.C")
gROOT.ProcessLine("setTDRStyle()")

def enum(**enums):
    return type('Enum',(),enums)

verbosity = enum(NONE=0,ERRORS=1,SOME=2,ALL=3)
debug = verbosity.SOME

HT         = 0. 
MHT        = 0.
MET        = 0. 
METphi     = 0.
NJets      = 0.
NLeptons   = 0.
PTLepton   = 0. 
sumJetMass = 0. 
leadJetPt  = 0. 
mEff       = 0. 
dEta       = 0. 
alphaT     = 0.
mT2        = 0.
mRazor     = 0.
dRazor     = 0. 
lheWeight  = 0. 
MHTOvHT    = 0. 

histoTemplates = { "HT" : TH1F("HT",";H_{T} [GeV];Events (a.u)",50,500,2500)    , 
                   "MHT" : TH1F("MHT",";H^{miss}_{T} [GeV];Events (a.u.)",100,200,1500) ,
                   "MET" : TH1F("MET",";E^{miss}_{T} [GeV];Events (a.u.)",40,200,1000) ,
                   "METphi" : TH1F("METphi",";#phi_{E^{miss}_{T}};Events (a.u.)",16,-3.1415,3.1415) ,
                   "NJets" : TH1F("NJets",";n_{jets};Events (a.u.)",15,-0.5,14.5) ,
                   "NLeptons" : TH1F("NLeptons",";n_{lep};Events (a.u.)",5,-0.5,4.5) ,
                   "PTLepton" : TH1F("PTLeptons",";p_{T,lep} [GeV];Events (a.u.)",100,30,530) ,
                   "sumJetMass" : TH1F("sumJetMass",";#Sigma M_{j} [GeV];Events (a.u.)",50,100,1000) ,
                   "leadJetPt" : TH1F("leadJetPt",";p_{T,lead jet} [GeV];Events (a.u.)",50,30,530) ,
                   "mEff" : TH1F("mEff",";m_{eff} [GeV];Events (a.u.)",50,0,3500) ,
                   "dEta" : TH1F("dEta",";#Delta#eta;Events (a.u.)",20,0,5) ,
                   "alphaT" : TH1F("alphaT",";#alpha_{T};Events (a.u.)",20,0,2) ,
                   "mT2" : TH1F("mT2",";m_{T2} [GeV];Events (a.u.)",100,0,2500) ,
                   "mRazor" : TH1F("mRazor",";m_{R} [GeV];Events (a.u.)",100,0,4000)  ,
                   "dRazor" : TH1F("dRazor",";dR;Events (a.u.)",20,0,1)  ,
                  "MHTOvHT" : TH1F("MHTOvHT",";H^{miss}_{T}/H_{T};Events (a.u.)",30,0,30)    
                   }



treeVars = { "HT" : HT                 ,
             "MHT" : MHT               ,
             "MET" : MET               ,
             "METphi" : METphi         ,
             "NJets" : NJets           ,
             "NLeptons" : NLeptons     ,
             "PTLepton" : PTLepton     ,
             "sumJetMass" : sumJetMass ,
             "leadJetPt" : leadJetPt   ,
             "mEff" : mEff             ,
             "dEta" : dEta             ,
             "alphaT" : alphaT         ,
             "mT2" : mT2               ,
             "mRazor" : mRazor         ,
             "dRazor" : dRazor         ,
             "lheWeight" : lheWeight   ,
             "MHTOvHT" : MHTOvHT    
              }

histosBackground = {}
histosSignal = {}

### filling histograms

def fillHistos( sample  ) : 

    histo = {}

    if debug >= verbosity.SOME : 
        print sample.tag

    #### initialized histograms
    for v in treeVars : 

        if v == "lheWeight" : continue

        histo[v] = histoTemplates[v]
        histo[v].SetName( histoTemplates[v].GetName() + "_" + sample.tag )

    #### loop over tree!
    numEvents = sample.tree.GetEntries()
    for i in range( numEvents ) : 
        
        #if i > 10000 : break 

        sample.tree.GetEntry(i)
        if debug >= verbosity.SOME : 
            if i % 100000 == 0 : 
                print "event:",i,"/",numEvents

        treeVars["lheWeight"] = getattr(sample.tree,"lheWeight")

        for v in treeVars :

            if v == "lheWeight" : continue

            treeVars[v] = getattr(sample.tree,v)
            if debug >= verbosity.ALL :  print "{0}: {1}".format(v,treeVars[v]) 

            histo[v].Fill( treeVars[v] , treeVars["lheWeight"] )

    return histo

#### backgrounds
for s in backgroundSample : 
    
    histosBackground[s.tag] = fillHistos( s )

    for v in treeVars : 
        if v == "lheWeight" : continue
        histosBackground[s.tag][v] = TH1F(histoTemplates[v]) 
        histosBackground[s.tag][v].SetName(v+"_"+s.tag)
        histosBackground[s.tag][v].Sumw2()
        histosBackground[s.tag][v].SetLineColor(1)
        histosBackground[s.tag][v].SetFillColor(s.color)
        histosBackground[s.tag][v].SetLineWidth(2)
        histosBackground[s.tag][v].GetXaxis().SetNdivisions(505)


#### signals
for s in signalSample : 
    
    histosSignal[s.tag] = fillHistos( s )

    for v in treeVars : 
        if v == "lheWeight" : continue
        histosSignal[s.tag][v].Scale(1./1000.)
        histosSignal[s.tag][v] = TH1F(histoTemplates[v]) 
        histosSignal[s.tag][v].SetName(v+"_"+s.tag)
        histosSignal[s.tag][v].Sumw2()
        histosSignal[s.tag][v].SetLineColor(s.color)
        histosSignal[s.tag][v].SetLineStyle(s.line)
        histosSignal[s.tag][v].SetLineWidth(2)
        histosSignal[s.tag][v].GetXaxis().SetNdivisions(505)

###### plotting things
can = {}
stack = {}

for v in treeVars : 
    
    if v == "lheWeight" : continue
    
    #######################
    ##  stacked histograms
    #######################
    leg = TLegend(.6,.6,.9,.9)
    leg.SetBorderSize(0)
    leg.SetFillColor(0)

    stack[v] = THStack("stack_{0}".format(v,s),"stack_{0}".format(v,s))

    for s in backgroundSample : 

        stack[v].Add( histosBackground[s.tag][v] )
        leg.AddEntry(histosBackground[s.tag][v],s.legendLabel,"f")        

    can["stack_"+v] = TCanvas("can_stack_"+v,"can_stack_"+v,500,500)
    
    stack[v].Draw("histo")
    stack[v].GetXaxis().SetTitle( histoTemplates[v].GetXaxis().GetTitle() )
    stack[v].GetXaxis().SetNdivisions( 505 )
    stack[v].GetYaxis().SetTitle( histoTemplates[v].GetYaxis().GetTitle() )
    maxY = stack[v].GetMaximum()
    print maxY

    for s in signalSample :
        if histosSignal[s.tag][v].GetMaximum() > maxY : maxY = histosSignal[s.tag][v].GetMaximum()
        print maxY

    stack[v].GetYaxis().SetRangeUser( 0. , maxY*1.5 )
    stack[v].Draw("histo")

    for s in signalSample :
        histosSignal[s.tag][v].Draw("histo,SAME")
        leg.AddEntry(histosSignal[s.tag][v],s.legendLabel,"f")

    leg.Draw()

    can["stack_"+v].SaveAs("~/www/DissectingJetsMET/1DplotsNormalized/stacked_"+v+".eps")
    can["stack_"+v].SaveAs("~/www/DissectingJetsMET/1DplotsNormalized/stacked_"+v+".png")
    can["stack_"+v].SaveAs("~/www/DissectingJetsMET/1DplotsNormalized/stacked_"+v+".pdf")
    
    ##########################
    ##  unit norm  histograms
    ##########################    

    can[v] = TCanvas("can_"+v,"can_"+v,500,500)
    first = True
    
    maximumBin = []
    for s in signalSample : 
        histosSignal[s.tag][v].Scale(1./histosSignal[s.tag][v].Integral())
        maximumBin.append( histosSignal[s.tag][v].GetMaximum() )
    for s in backgroundSample : 
        histosBackground[s.tag][v].SetLineColor(s.color)
        histosBackground[s.tag][v].SetFillColor(0)

        histosBackground[s.tag][v].Scale(1./histosBackground[s.tag][v].Integral())
        maximumBin.append( histosBackground[s.tag][v].GetMaximum() )

    maxY = max( maximumBin )*1.3

    #### draw background histograms
    for s in backgroundSample : 
        #### need to have first histo draw axis and set range...
        if first :             
            histosBackground[s.tag][v].Draw("histo")
            histosBackground[s.tag][v].GetYaxis().SetRangeUser(0.,maxY)
            first = False
        #### the rest just get drawn with SAME
        else : 
            histosBackground[s.tag][v].Draw("histo,SAME")

        #### putting histo into legend - label taken from sample info
        leg.AddEntry(histosBackground[s.tag][v],s.legendLabel,"l")

    #### draw signal histograms
    for s in signalSample : 
        histosSignal[s.tag][v].Draw("histo,SAME")
        leg.AddEntry(histosSignal[s.tag][v],s.legendLabel,"l")

    leg.Draw()
    

    can[v].SaveAs("~/www/DissectingJetsMET/1DplotsNormalized/normalized_"+v+".eps")
    can[v].SaveAs("~/www/DissectingJetsMET/1DplotsNormalized/normalized_"+v+".png")
    can[v].SaveAs("~/www/DissectingJetsMET/1DplotsNormalized/normalized_"+v+".pdf")
    
    
