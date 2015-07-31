from ROOT import *

inputDir = "/afs/cern.ch/work/w/whitbeck/public/DissectingJetsPlusMET_Shared/TranTrees/"


# ------------------------------------------------------------
# ------------------------------------------------------------
# ------------------------------------------------------------


class sampleInfo :

    def __init__( self , fileName , tag , color , line , xsec , weight=1. , legendLabel="" ) :
        self.fileName = fileName
        self.color    = color
        self.line     = line
        self.xsec     = xsec
        self.tag      = tag
        self.inputFile= None
        self.tree = TChain("otree")
        self.weight   = weight
        self.legendLabel = legendLabel
        #self.addToChain()

    ### this method will take a directory as an argument, loop over 
    ### all of the files in the directory and add them individually
    ### to the chain with the appropriate director prefix. 
    def addToChain( self ):

        proc = subprocess.Popen( [ "ls /eos/uscms/{0}".format( self.fileName ) ] , stdout = subprocess.PIPE , shell = True )
        ( files , errors ) = proc.communicate()
        for f in files.split("\n") :
            if f.find("No such file or directory") == -1 :
                f = redirector+f[11:]
            self.tree.Add( "{0}".format( f ) )

# ------------------------------------------------------------
# ------------------------------------------------------------
# ------------------------------------------------------------

backgroundSample = [ sampleInfo( inputDir+"/ProcJPM_ttbar.root" , "ttbar" , kMagenta+1 , 1 , 1 , 1 , "t#bar{t}" ) , 
                  sampleInfo( inputDir+"/ProcJPM_znunu.root" , "znunu" , kBlue+1 , 1 , 1 , 1 , "Z#rightarrow#nu#nu" ) , 
                  sampleInfo( inputDir+"/ProcJPM_Wjets.root" , "Wjets" , kCyan+1 , 1 , 1 , 1 , "W#rightarrow l#nu" ) , 
                  sampleInfo( inputDir+"/ProcJPM_QCD.root"   , "QCD"   , kGreen+1 , 1 , 1 , 1 , "QCD" ) 
                  ]
         
signalSample = [ #sampleInfo( inputDir+"ProcJPM_GjjjjN1_GjjjjN1__500_.root" , "Gluino8j_500" , kRed+1 , 1 , 1 , 1 , ".5 TeV Gluino #rightarrow 4j,#tilde{#chi_{0}}" ) , 
                 #sampleInfo( inputDir+"ProcJPM_GjjjjN1_GjjjjN1__1000_.root" , "Gluino8j_1000" , kRed+1 , 2 , 1 , 1 , "1 TeV Gluino #rightarrow 4j,#tilde{#chi_{0}}" ) ,
                 #sampleInfo( inputDir+"ProcJPM_GjjjjN1_GjjjjN1__1500_.root" , "Gluino8j_1500" , kRed+1 , 3 , 1 , 1 , "1.5 TeV Gluino #rightarrow 4j,#tilde{#chi_{0}}" ) , 
                 #sampleInfo( inputDir+"ProcJPM_GjjjN1_GjjjN1__500_.root" , "Gluino6j_500" , kOrange+1 , 1 , 1 , 1 , ".5 TeV Gluino #rightarrow 3j,#tilde{#chi_{0}}" ) ,
                 #sampleInfo( inputDir+"ProcJPM_GjjjN1_GjjjN1__1000_.root" , "Gluino6j_1000" , kOrange+1 , 2 , 1 , 1 , "1 TeV Gluino #rightarrow 3j,#tilde{#chi_{0}}" ) ,
                 #sampleInfo( inputDir+"ProcJPM_GjjjN1_GjjjN1__1500_.root" , "Gluino6j_1500" , kOrange+1 , 3 , 1 , 1 , "1.5 TeV Gluino #rightarrow 3j,#tilde{#chi_{0}}" ) ,
                 sampleInfo( inputDir+"ProcJPM_GjjN1_GjjN1__500_.root" , "Gluino4j_500" , kRed , 1 , 1 , 1 , ".5 TeV Gluino #rightarrow 2j,#tilde{#chi_{0}}" ) , 
                 sampleInfo( inputDir+"ProcJPM_GjjN1_GjjN1__1000_.root" , "Gluino4j_1000" , kRed , 2 , 1 , 1 , "1 TeV Gluino #rightarrow 2j,#tilde{#chi_{0}}" ) , 
                 sampleInfo( inputDir+"ProcJPM_GjjN1_GjjN1__1500_.root" , "Gluino4j_1500" , kRed , 3 , 1 , 1 , "1.5 TeV Gluino #rightarrow 2j,#tilde{#chi_{0}}" ),
                 sampleInfo( inputDir+"ProcJPM_GjN1_GjN1__500_.root" , "Gluino2j_500" , kOrange , 1 , 1 , 1 , ".5 TeV Gluino #rightarrow j,#tilde{#chi_{0}}" ) , 
                 sampleInfo( inputDir+"ProcJPM_GjN1_GjN1__1000_.root" , "Gluino2j_1000" , kOrange , 2 , 1 , 1 , "1 TeV Gluino #rightarrow j,#tilde{#chi_{0}}" ) , 
                 sampleInfo( inputDir+"ProcJPM_GjN1_GjN1__1500_.root" , "Gluino2j_1500" , kOrange , 3 , 1 , 1 , "1.5 TeV Gluino #rightarrow j,#tilde{#chi_{0}}" )
              ]         

for s in backgroundSample : 
    s.tree.Add(s.fileName)
for s in signalSample : 
    s.tree.Add(s.fileName)


