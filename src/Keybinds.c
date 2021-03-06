#include "../header/Keybinds.h"

void keybinds(FILE* fichier, int* keyBindings) {
	char chaine[LGR_MAX]="";
	int i=0;

	//Fill the array with the content of the file
	for (i=0; i<NB_TOUCHES; i++) {
		fgets(chaine, LGR_MAX, fichier);
		keyBindings[i]=atoi(chaine);
	}
}

int isTaken(int new, int pos, int* keyBindings) {
	int i=0;
	for (i=0; i<pos; i++) {
		if (keyBindings[i]==new) {
			return 0;
		}
	}
	for (i=pos+1; i<NB_TOUCHES; i++) {
		if (keyBindings[i]==new) {
			return 0;
		}
	}
	return 1;
}

int configureKeybind(int nb, int* keyBindings, int key) {
	//We check that the key is free.
	if(isTaken(key, nb, keyBindings)==0) {
		return 1;
	}
	//We delete the file.
	remove("./keybinds/CustomKeybinds");
	keyBindings[nb]=key;
	FILE* fichierTmp = NULL;

	//We rewrite the file.
	fichierTmp=fopen("./keybinds/CustomKeybinds", "w+");
	int i;
	char chaine[LGR_MAX]="";

	for (i=0; i<NB_TOUCHES; i++) {
		sprintf(chaine, "%d\n", keyBindings[i]);
		fputs(chaine, fichierTmp);
	}

	fclose(fichierTmp);
	return 0;
}

int isWellFormed(int* keyBindings) {
	int i=0;

	//If there is one key not well-formed, we return 0.
	for (i=0; i<NB_TOUCHES; i++) {
		if (keyBindings[i]==0 || isTaken(keyBindings[i],i,keyBindings)==0) {
			return 0;
		}
	}
	return 1;
}

void createDefaultKeybinds() {
	//Create a default configuration.
	FILE* fichier = NULL;
	remove("./keybinds/DefaultKeybinds");
	fichier=fopen("./keybinds/DefaultKeybinds", "w+");
	char chaine[LGR_MAX]="";
	sprintf(chaine, "%d\n", SDLK_ESCAPE);
	fputs(chaine, fichier);
	sprintf(chaine, "%d\n", SDLK_UP);
	fputs(chaine, fichier);
	sprintf(chaine, "%d\n", SDLK_DOWN);
	fputs(chaine, fichier);
	sprintf(chaine, "%d\n", SDLK_LEFT);
	fputs(chaine, fichier);
	sprintf(chaine, "%d\n", SDLK_RIGHT);
	fputs(chaine, fichier);
	sprintf(chaine, "%d\n", SDLK_SPACE);
	fputs(chaine, fichier);
	sprintf(chaine, "%d\n", SDLK_a);
	fputs(chaine, fichier);
	sprintf(chaine, "%d\n", SDLK_z);
	fputs(chaine, fichier);
	sprintf(chaine, "%d\n", SDLK_e);
	fputs(chaine, fichier);
	fclose(fichier);
}

void createCustomKeybinds() {
	//Create a new basic custom file.
	FILE* fichier = NULL;
	remove("./keybinds/CustomKeybinds");
	fichier=fopen("./keybinds/CustomKeybinds", "w+");
	char chaine[LGR_MAX]="";
	sprintf(chaine, "%d\n", SDLK_ESCAPE);
	fputs(chaine, fichier);
	sprintf(chaine, "%d\n", SDLK_UP);
	fputs(chaine, fichier);
	sprintf(chaine, "%d\n", SDLK_DOWN);
	fputs(chaine, fichier);
	sprintf(chaine, "%d\n", SDLK_LEFT);
	fputs(chaine, fichier);
	sprintf(chaine, "%d\n", SDLK_RIGHT);
	fputs(chaine, fichier);
	sprintf(chaine, "%d\n", SDLK_SPACE);
	fputs(chaine, fichier);
	sprintf(chaine, "%d\n", SDLK_a);
	fputs(chaine, fichier);
	sprintf(chaine, "%d\n", SDLK_z);
	fputs(chaine, fichier);
	sprintf(chaine, "%d\n", SDLK_e);
	fputs(chaine, fichier);
	fclose(fichier);
}


// A l'initialisation, on remplis les raccourcis calvier.
int initialise_keybinds(int* keyBindings) {
	FILE* fichier = NULL;
	//on essaye de charger les raccourcis clavier personnalisés
	fichier=fopen("./keybinds/CustomKeybinds", "r"); 
	if (fichier!=NULL) {
		keybinds(fichier,keyBindings);
	//si ça ne marche pas, on essaye de charger les raccourcis claviers par défaut
	} else {
		fclose(fichier);
		fichier=fopen("./keybinds/DefaultKeybinds", "r");
		//si ça ne marche toujours pas, on recréé les fichier par défaut
		if(fichier==NULL) {
			fclose(fichier);
			createDefaultKeybinds();
			fichier=fopen("./keybinds/DefaultKeybinds", "r");
		}
		keybinds(fichier, keyBindings);
	}
	fclose(fichier);
	//si les touches sont mal configurées, on repars de 0
	if (isWellFormed(keyBindings)==0) {
			createDefaultKeybinds();
			fichier=fopen("./keybinds/DefaultKeybinds", "r");
			keybinds(fichier, keyBindings);
			fclose(fichier);
		} 
return 0;

}




