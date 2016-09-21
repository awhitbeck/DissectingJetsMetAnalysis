CC=g++
CFLAGS=
LIBS=`root-config --cflags --glibs` -L $(ROOTSYS)/lib
INCLUDES=-I$(CMSSW_BASE)/src/AnalysisTools/src/ -I$(CMSSW_BASE)/src/
EXECS=genericPlotter projectTranTrees genericPlotter4Jets  projectTranTrees4Jets
genericPlotter genericPlotter4Jets : filterHighWeights.cc dissectingJetsMET.cc dissectingJetsMET.h tranTree.cc tranTree.h 
projectTranTrees projectTranTrees4Jets : tranTree.cc tranTree.h weightProducer.cc 
${EXECS} : helpers.h filterHighWeights.cc weightProducer.cc 
all:$(EXECS)
genericPlotter:
	$(CC) $(LIBS) $(INCLUDES) $(CFLAGS) genericPlotter.cc -o $@
projectTranTrees:
	$(CC) $(LIBS) $(INCLUDES) $(CFLAGS) projectTranTrees.cc -o $@
genericPlotter4Jets:
	$(CC) $(LIBS) $(INCLUDES) $(CFLAGS) genericPlotter4Jets.cc -o $@
projectTranTrees4Jets:
	$(CC) $(LIBS) $(INCLUDES) $(CFLAGS) projectTranTrees4Jets.cc -o $@
clean : 
	rm $(EXECS) 