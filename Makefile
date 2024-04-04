CPPC=mpiCC
CPPFLAGS=-O2 -std=c++17

PROG=prog1

OBJS=$(PROG).o

$(PROG): $(OBJS)
	$(CPPC) -o $(PROG) $(OBJS) -lmpi

$(PROG).o: $(PROG).cpp
	$(CPPC) $(CPPFLAGS) -c $(PROG).cpp

clean:
	rm -f $(PROG) $(OBJS)
