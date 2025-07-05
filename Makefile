all: mapa

mapa: mapa.o graph.o utilities.o
	g++ mapa.o graph.o utilities.o -o mapa -lsfml-graphics -lsfml-window -lsfml-system

mapa.o: graph.hpp utilities.hpp
	g++ -c mapa.cpp

graph.o: graph.hpp
	g++ -c graph.cpp

utilities.o: utilities.hpp
	g++ -c utilities.cpp

clean:
	rm -f mapa *.o