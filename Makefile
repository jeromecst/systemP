CC = gcc
CC = ${CC}
LIBS=-lsfml-graphics -lsfml-window -lsfml-system

t:
	@echo "**Compilation de la version terminal..."
	g++ -std=c++11 -c systemP.cpp systemPFonctions.cpp systemPFonctionsSFML.cpp
	g++ -std=c++11 systemP.o systemPFonctions.o systemPFonctionsSFML.o -o o -lsfml-graphics -lsfml-graphics -lsfml-window -lsfml-system


g:
	@echo "**Compilation de la version graphique..."
	g++ -std=c++11 -c systemPSFML.cpp systemPFonctions.cpp systemPFonctionsSFML.cpp
	g++ -std=c++11 -pthread systemPSFML.o systemPFonctions.o systemPFonctionsSFML.o -o o -lsfml-graphics -lsfml-window -lsfml-system


clean:
	rm *.o o