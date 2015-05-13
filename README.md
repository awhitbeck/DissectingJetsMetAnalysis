Code for slimming output Delphes output trees.  Currently only only jet and MET information is used to compute
final kinematic variables.  These variables are then saved to a root tree (fileName: outputTest.root ; 
treeName: analysisTree).  Information about the variables and how they are computed is below. 


<table> 
<tr>  
  <td> <b>variable</b> </td>
  <td> <b>description</b> </td>
  <td> <b>type</b> </td>
</tr> 
<tr> 
  <td> HT </td>
  <td> scalar sum of jet pt.  Only skinny jets whose pt>30 and whose |η|<2.5 are considered. </td> 
  <td> double </td>
</tr>
<tr>
  <td> MHT </td>
  <td> magnitude of the vector sum of -p_T,jet.  Only skinny jets whose pt>30 and whose |η|<5.0 are 
considered. </td>
  <td> double </td>
</tr>
<tr>
  <td> NJets </td>
  <td> number of skinny jets whose pt>30 and whose |η|<2.5 </td>
  <td> int </td>
</tr>
<tr>
  <td> MET </td>
  <td> taken directly from Delphes calculation -- put reference -- </td>
  <td> double </td>
</tr>
<tr> 
  <td> sumJetMass </td>
  <td> sum of fat jet mass. -- Fat jet clustering specifics -- Only fat jets whose pt>0, mass>50, 
|η|<5.0 are considered. </td>
  <td> double </td> 
</tr>
<tr>
  <td> leadJetPt </td>
  <td> pt of the leading jet.  Only skinny jets whose pt>30 and whose |η|<2.5 are considered. </td>
  <td> double </td>
</tr>
<tr>
  <td> mEff </td>
  <td> HT + MET -- HT and MET are the same as above. </td>
  <td> double </td>
</tr>
<tr>
  <td> dEta </td> 
  <td> Δη between the two leading (in pT) jets.  Only skinny jets whose pt>30 and whose |η|<2.5 are 
considered. </td>
  <td> double </td>
</tr>
<tr>  
  <td> MT2 </td>
  <td> As implemented here: http://www.hep.phy.cam.ac.uk/~lester/mt2/.  The input visible jets 
  are taken to be the same as the 'megajets' used in the razor variables.</td>
  <td> double </td>
</tr>
<tr>
  <td> alphaT </td>
  <td> -- not implemented yet -- </td>
  <td> double </td>
</tr>
<tr>
  <td> mR (mRazor) </td>
  <td> Transverse mass of the 'megajets'.  These megajets are found by combining the event into 
  two jets, the two pairings chosen correspond to the chose which minimizes m1^2+m2^2.</td>
  <td> double </td>
</tr>
<tr>
  <td> R^2 (dRazor) </td> 
  <td> The square of the ratio of mR and mT.</td>
  <td> double </td>
</tr>
</table>

<hr>
Running the code can be done by loading the Delphes library, compiling the treeSlimmer script
within the root interpreter, and passing the path to your input root file to the function <i>treeSlimmer()</i> :

<pre>
gSystem->Load("libDelphes")
.L DissectingJetsMetAnalysis/treeSlimmer.C+
treeSlimmer("../testData/example.root")
</pre>
