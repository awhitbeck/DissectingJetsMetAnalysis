CC=g++
CFLAGS=
LIBS=`root-config --cflags --glibs` -L $(ROOTSYS)/lib
EXECS=compareSignals makeStack
all:$(EXECS)
compareSignals:
	$(CC) $(LIBS) $(CFLAGS) compareSignals.cc -o $@
makeStack:
	$(CC) $(LIBS) $(CFLAGS) makeStack.cc -o $@
clean : 
	rm $(EXECS) 