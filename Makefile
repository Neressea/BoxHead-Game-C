all: create IA.o Map.o Character.o Building.o Spell.o Item.o Main.o Keybinds.o
	gcc ./bin/*.o -o ./Game -lSDL2-2.0 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
 
# Création du dossier bin (à condition que ce dernier n'existe pas déjà)
create:
	mkdir -p bin

############ Compilation de l'ensemble des fichiers ############

Main.o: ./src/Main.c ./header/*.h
	gcc -c ./src/Main.c -o ./bin/Main.o -lSDL2-2.0 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
 
Map.o: ./src/Map.c ./header/*.h
	gcc -c ./src/Map.c -o ./bin/Map.o -lSDL2-2.0 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

Character.o: ./src/Character.c ./header/*.h
	gcc -c ./src/Character.c -o ./bin/Character.o -lSDL2-2.0 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
 
Building.o: ./src/Building.c ./header/*.h
	gcc -Wall -c ./src/Building.c -o ./bin/Building.o -lSDL2-2.0 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

Spell.o: ./src/Spell.c ./header/*.h
	gcc -Wall -c ./src/Spell.c -o ./bin/Spell.o -lSDL2-2.0 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

Item.o: ./src/Item.c ./header/*.h
	gcc -Wall -c ./src/Item.c -o ./bin/Item.o -lSDL2-2.0 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

IA.o: ./src/IA.c ./header/*.h
	gcc -Wall -Werror -Wextra -c ./src/IA.c -o ./bin/IA.o -lSDL2-2.0 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

Keybinds.o: ./src/Keybinds.c ./header/*.h
	gcc -c ./src/Keybinds.c -o ./bin/Keybinds.o -lSDL2-2.0 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
 
# Suppression des fichiers temporaires
clean:
	rm -rf ./bin/*.o
