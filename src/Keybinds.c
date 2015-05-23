#include "../header/Keybinds.h"

//Fonction remplissant le tableau a partir d'un fichier
void keybinds(FILE* fichier, int* keyBindings) {
	char chaine[LGR_MAX]="";
	int i=0;
	for (i=0; i<NB_TOUCHES; i++) {
		fgets(chaine, LGR_MAX, fichier);
		keyBindings[i]=atoi(chaine);
	}
}

//retourne 1 si la touche n'est pas déjà assignée
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

//Sous-fonction configurant une touche
void configureKeybind(int nb, int* keyBindings) {
	printf("Choississez la touche ");
	switch (nb){
		case 0:
			printf("pour quitter\n");
			break;
		case 1:
			printf("pour se déplacer vers le haut\n");
			break;
		case 2:
			printf("pour se déplacemer vers le bas\n");
			break;
		case 3:
			printf("pour se déplacer vers la gauche\n");
			break;
		case 4:
			printf("pour se déplacer vers la droite\n");
			break;
		case 5:
			printf("d'attaque\n");
			break;
		case 6:
			printf("pour choisir le feu\n");
			break;
		case 7:
			printf("pour choisir la glace\n");
			break;
		case 8:
			printf("pour choisir la tour\n");
			break;
	}
	SDL_Event event;
	SDL_WaitEvent(&event);
		if(event.type==SDL_KEYDOWN){
			if(isTaken(event.key.keysym.sym, nb, keyBindings)==0) {
				fprintf(stderr, "touche déjà liée à un raccourci clavier");
				return;
			}
				keyBindings[nb]=event.key.keysym.sym;
				FILE* fichier = NULL;
				fichier=fopen("./keybinds/CustomKeybinds", "w+");
				FILE* fichierTmp = NULL;
				fichierTmp=fopen("./keybinds/CustomKeybinds.tmp", "w+");
				int i;
				char chaine[LGR_MAX]="";
				for (i=0; i<nb; i++) {
					fgets(chaine, LGR_MAX, fichier);
					fputs(chaine, fichierTmp);
				}
				sprintf(chaine, "%d", keyBindings[nb]);
				fputs(chaine, fichierTmp);
				for (i=nb+1; i<NB_TOUCHES; i++) {
					fgets(chaine, LGR_MAX, fichier);
					fputs(chaine, fichierTmp);
				}
				fclose(fichier);
				fclose(fichierTmp);
				remove("./keybinds/CustomKeybinds");
				rename("./Keybinds/CustomKeybinds.tmp", "../Keybinds/CustomKeybinds");
		}
	}
	

//Fonction remplissant le tableau en fonction de l'utilisateur
void configureKeybinds (int* keyBindings) {
	int i;
	for (i=0; i<NB_TOUCHES; i++) {
		configureKeybind(i, keyBindings);
	}
}

//vérifie que les touches sont bien configurées
int isWellFormed(int* keyBindings) {
	int i=0;
	for (i=0; i<NB_TOUCHES; i++) {
		if (keyBindings[i]==0 || isTaken(keyBindings[i],i,keyBindings)==0) {
			return 0;
		}
	}
	return 1;
}

//Fonction créant le fichier de base si celui-ci est manquant ou corrompu
void createDefaultKeybinds() {
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

int test() {
	int keyBindings[NB_TOUCHES] = {0}; //On génère les raccourcis clavier
	initialise_keybinds(keyBindings);
	int j=0;
	for (j=0; j<NB_TOUCHES; j++) {
		printf("%d\n", keyBindings[j]);
	}
	return 0;
}




