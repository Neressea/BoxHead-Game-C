#CPP=gcc    #Commande du compilateur
#CFLAGS=-O3 #Option d'optimisation du programme
#LDFLAGS=-lSDL -lSDL_mixer #Linker
#EXEC=nomProgramme  #Nom du programme à modifier

# Création du dossier bin (à condition que ce dernier n'existe pas déjà)

#all: ${EXEC}

#${EXEC}: ${EXEC}.o
#	${CPP} $(CFLAGS) -o ${EXEC} ${EXEC}.o ${LDFLAGS}

#${EXEC}.o: ${EXEC}.c
#	${CPP} $(CFLAGS) -o ${EXEC}.o -c ${EXEC}.c


# Création de l'exécutable 'Light'

all: create IA.o Map.o Character.o Building.o Game.o Spell.o Item.o Main.o
	gcc ./bin/*.o -o ./Game -lSDL2-2.0 -lSDL2_image -lSDL2_ttf
 
# Création du dossier bin (à condition que ce dernier n'existe pas déjà)
create:
	mkdir -p bin

############ Compilation de l'ensemble des fichiers ############

Main.o: ./src/Main.c ./header/*.h
	gcc -c ./src/Main.c -o ./bin/Main.o -lSDL2-2.0 -lSDL2_image -lSDL2_ttf
 
Map.o: ./src/Map.c ./header/*.h
	gcc -c ./src/Map.c -o ./bin/Map.o -lSDL2-2.0 -lSDL2_image -lSDL2_ttf

Character.o: ./src/Character.c ./header/*.h
	gcc -c ./src/Character.c -o ./bin/Character.o -lSDL2-2.0 -lSDL2_image -lSDL2_ttf
 
Building.o: ./src/Building.c ./header/*.h
	gcc -Wall -c ./src/Building.c -o ./bin/Building.o -lSDL2-2.0 -lSDL2_image -lSDL2_ttf
 
Game.o: ./src/Game.c ./header/*.h
	gcc -Wall -c ./src/Game.c -o ./bin/Game.o  -lSDL2-2.0 -lSDL2_image -lSDL2_ttf

Spell.o: ./src/Spell.c ./header/*.h
	gcc -Wall -c ./src/Spell.c -o ./bin/Spell.o -lSDL2-2.0 -lSDL2_image -lSDL2_ttf

Item.o: ./src/Item.c ./header/*.h
	gcc -Wall -c ./src/Item.c -o ./bin/Item.o -lSDL2-2.0 -lSDL2_image -lSDL2_ttf

IA.o: ./src/IA.c ./header/*.h
	gcc -Wall -Werror -Wextra -c ./src/IA.c -o ./bin/IA.o -lSDL2-2.0 -lSDL2_image -lSDL2_ttf
 
# Suppression des fichiers temporaires
clean:
	rm -rf ./bin/*.o
