##Compiler
CXX = g++
#Options de compilation
CXXFLAGS = -Wall -Wextra -Werror -std=c++11

#Noms des fichiers sources
SRCS = Geometrie.cpp
#Noms des fichiers objets générés
OBJS = $(SRCS:.cpp=.o)
#Noms des fichiers headers
HEADERS = color.h SVGstream.h

#Nom de l'exécutable final
EXEC = index

run : $(EXEC)
	./$(EXEC)
	@make clean -s

#Règle par défaut : exécutable
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(EXEC)

#Règle de compilation des fichiers objets
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

#Nettoyage : suppression des fichiers objets et de l'exécutable
clean:
	rm -f $(OBJS) $(EXEC)