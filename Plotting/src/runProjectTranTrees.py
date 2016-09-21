import os

bkgsamples = ["QCD","znunu","Wjets","ttbar"]
sigsamples = ["GjN1_GjN1","GjN1_GjjN1",
              "GjjN1_GjjN1","GjjN1_GjjjN1",
              "GjjjN1_GjjjN1","GjjjN1_GjjjjN1",
              "GjjjjN1_GjjjjN1"]
              

for b in bkgsamples : 
    print b
    os.system("./projectTranTrees {0}".format(b))
for s in sigsamples :
    print "{0}_500 compressed".format(s)
    os.system("./projectTranTrees {0}_500 compressed".format(s))
    print "{0}_500 uncompressed".format(s)
    os.system("./projectTranTrees {0}_500 uncompressed".format(s))
    print "{0}_1000 compressed".format(s)
    os.system("./projectTranTrees {0}_1000 compressed".format(s))
    print "{0}_1000 uncompressed".format(s)
    os.system("./projectTranTrees {0}_1000 uncompressed".format(s))
    print "{0}_1500 compressed".format(s)
    os.system("./projectTranTrees {0}_1500 compressed".format(s))
    print "{0}_1500 uncompressed".format(s)
    os.system("./projectTranTrees {0}_1500 uncompressed".format(s))
