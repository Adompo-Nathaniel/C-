CPPFLAGS= -std=c++17 -g -Wall -Wextra -Wconversion -O0
SRCs=Curve.cpp Figure.cpp GeomBase.cpp Surface.cpp SVG.cpp Interface.cpp main.cpp
OBJs=$(SRCs:.cpp=.o)
EXE=Projet
MAIN=main.o
CXX=g++
LIBRARY=libgraweditor.a

$(EXE): $(OBJs) $(LIBRARY)
	$(CXX) $(filter-out $(MAIN), $(OBJs)) $(MAIN) -o $@ $(LIBRARY)
	
$(LIBRARY): $(filter-out $(MAIN), $(OBJs))
	ar rcs $@ $^

clean:
	rm -f $(OBJs) $(EXE) $(LIBRARY)

clean_windows:
	del $(OBJs) $(EXE) $(LIBRARY)

Curve.o: SVG.h Curve.h GeomBase.h Array.h
Figure.o: Figure.h GeomBase.h SVG.h Array.h
GeomBase.o: GeomBase.h SVG.h
Interface.o: Interface.h GeomBase.h Surface.h Curve.h Figure.h
main.o: GeomBase.h SVG.h Surface.h Array.h Curve.h Figure.h Interface.h
Surface.o: SVG.h Surface.h GeomBase.h Array.h
SVG.o: SVG.h

