#CPP=gcc    #Commande du compilateur
#FLAGS=-O3 #Option d'optimisation du programme
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
 
all: create Main.o Map.o Building.o Character.o Game.o Weapon.o
	gcc ./bin/*.o -o Game `sdl-config --libs`
 
# Création du dossier bin (à condition que ce dernier n'existe pas déjà)
 
create:
	mkdir -p bin
 
 
############ Compilation de l'ensemble des fichiers ############
Main.o: ./src/Main.c ./header/*.h
	gcc ./src/Main.c -o ./bin/Main.o `sdl-config --cflags`
 
Map.o: ./src/Map.c ./header/*.h
	gcc ./src/Map.c -o ./bin/Map.o
 
Building.o: ./src/Building.c ./header/*.h
	gcc ./src/Building.c -o ./bin/Building.o
 
Character.o: ./src/Character.c ./header/*.h
	gcc ./src/Character.c -o ./bin/Character.o
 
Game.o: ./src/Game.c ./header/*.h
	gcc ./src/Game.c -o ./bin/Game.o

Weapon.o: ./src/Weapon.c ./header/*.h
	gcc ./src/Weapon.c -o ./bin/Weapon.o
 
# Suppression des fichiers temporaires
clean:
	rm -rf ./bin/*.o