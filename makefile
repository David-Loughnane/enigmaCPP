CPPFLAGS=-Wall -g
EXE=enigma
CXX=g++
OBJ=enigma.o components.o

$(EXE): $(OBJ)
	$(CXX) $(CPPFLAGS) $(OBJ) -o $(EXE)

%.o: %.cpp
	$(CXX) $(CPPFLAGS) -c $<

enigma.o: components.h

.PHONY: clean
clean:
	rm -f *.o $(EXE)
