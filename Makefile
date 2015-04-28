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


#clean:	
#	rm -fr *.o

#mrproper: clean
#	rm -fr ${EXEC}

# Création de l'exécutable 'Light'
all: create Map.o Building.o Character.o Game.o Spell.o Main.o
 
# Création du dossier bin (à condition que ce dernier n'existe pas déjà)
create:
	mkdir -p bin

############ Compilation de l'ensemble des fichiers ############
Main.o: ./src/Main.c ./header/*.h
	gcc -Wall -Werror -Wextra -c ./src/Main.c -o ./bin/Main.o -lSDL2-2.0 -lSDL2_image
 
Map.o: ./src/Map.c ./header/*.h
	gcc -Wall -Werror -Wextra -c ./src/Map.c -o ./bin/Map.o -lSDL2-2.0 -lSDL2_image
 
Building.o: ./src/Building.c ./header/*.h
	gcc -Wall -c ./src/Building.c -o ./bin/Building.o -lSDL2-2.0 -lSDL2_image
 
Character.o: ./src/Character.c ./header/*.h
	gcc -Wall -c ./src/Character.c -o ./bin/Character.o -lSDL2-2.0 -lSDL2_image
 
Game.o: ./src/Game.c ./header/*.h
	gcc -Wall -c ./src/Game.c -o ./bin/Game.o  -lSDL2-2.0 -lSDL2_image

Spell.o: ./src/Spell.c ./header/*.h
	gcc -Wall -c ./src/Spell.c -o ./bin/Spell.o -lSDL2-2.0 -lSDL2_image
 
# Suppression des fichiers temporaires
clean:
	rm -rf ./bin/*.o
