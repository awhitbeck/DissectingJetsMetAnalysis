Code for plotting distributions.  Current, this repo contains code to plot
stacked histograms for signal and backgrounds and to compare shapes of 
different signals.

# Setting up code

# Plotting distributions

There are two step.  Plot the distributions for a each of the input 
samples.  This is done with code in <code>src/</code>.  Each script in
<code>src/</code> will produce a root file with a number of histograms
for each of the variables.  Each histogram is weight to a specific luminosity, 
which is specified in the constructor of the <code>weightProducer</code> class:

<pre>

</pre> 

With the individual histograms in hand, the code in <code>script/</code> can 
be used to combine these histograms and plot them with nice formatting.