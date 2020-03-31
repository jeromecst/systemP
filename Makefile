CC = gcc
CC = ${CC}
LIBS=-lsfml-graphics -lsfml-window -lsfml-system

t:
	@echo "**Compilation de la version terminal..."
	g++ -std=c++11 systemP.cpp systemPFonctions.cpp -o t

clean:
	rm t
