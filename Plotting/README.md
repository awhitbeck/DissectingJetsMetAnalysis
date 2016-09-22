Code for plotting distributions.  Currently, this repo contains code to plot
stacked histograms for signal and backgrounds and to compare shapes of 
different signals.

# Setting up code
<pre>
cmsrel CMSSW_7_4_2
cd CMSSW_7_4_2/src/
cmsenv

git clone https://github.com/awhitbeck/RA2bUtils
git clone https://github.com/awhitbeck/AnalysisTools
git clone https://github.com/awhitbeck/DissectingJetsMetAnalysis

cd DissectingJetsMetAnalysis/Plotting/src 
make all
cd ../script/
make all
cd -
</pre>
# Plotting distributions

#### Raw plots
There are two step.  Plot the distributions for a each of the input 
samples.  This is done with code in <code>src/</code>.  Each script in
<code>src/</code> will produce a root file with a number of histograms
for each of the variables.  

To generate distributions from Nhan's skimmed trees, use <code>projectTranTrees</code>. 
Some relevant things to note: This code generates a set of histograms.  This 
list of histograms is determined by the processor list in the analyzer object, a.

e.g.
<pre>
analyzer<tranTree> a(ntuple,17);
a.verbosity=0;
a.setReportEvery(200000);
a.addProcessor( select );

/* - - - - - - - - - - - - - - - - - - - - - - - 1D histograms - - - - - - - - - - - - - - - - - - - - - - */
hFiller *fillHT = new hFiller(ntuple,50,500,2500,sample,"HT","lheWeight",10000.);   a.addProcessor( fillHT );
fillHT->histo->SetTitle(";HT [GeV];Events");
</pre> 

See [here](https://github.com/awhitbeck/AnalysisTools/blob/master/src/fillHisto.cc) for more information on 
constructor information, but in short the binning of the histogram, the branch name that should
be used to fill the histogram, the branch name of the weight, and the lumi should be provided.

To generate histograms for each of the skimmed samples, you can run the following:
<pre>
python runProjectTranTrees.py
</pre>

#### Formatting plots
With the individual histograms in hand, the code in <code>script/</code> can 
be used to combine these histograms and plot them with nice formatting.  

If everything in the previous step when fine, you should have a root file for 
each sample with many histograms each.  The plotting/formatting scripts expect that
these histograms will all be in one file, so you should first <code>hadd</code> them:
<pre>
hadd genericPlotter.root ../src/genericPlotter_*.root
</pre>

Then simply run <code>./makeStack</code> or <code>./compareSignals</code>.
