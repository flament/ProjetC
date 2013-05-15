#include <stdio.h>
#include <stdlib.h>
#include "Agenda.h"
#include <string.h>

THEME *teteTheme = NULL;

void ajouterTheme(){
	char nomTemp[101], *nom;
	THEME *theme = (THEME *)malloc(sizeof(THEME));
	THEME *test;
	test = NULL;

	printf("Nom du thème:");
	fflush(stdin);
	fgets(nomTemp, sizeof(nomTemp), stdin);
	if(strcmp(nomTemp,"\n"))
		nom = strtok(nomTemp,"\n");
	else
		nom = "";

	while((nom[0]<= 96 || nom[0] >= 123) && (nom[0]<= 64 || nom[0] >= 91)){
		printf("Nom invalide, le nom d'un thème doit commencer par une lettre!\n");
		printf("Veuillez resaisir un nom correct:");
		fflush(stdin);
		fgets(nomTemp, sizeof(nomTemp), stdin);	
		if(strcmp(nomTemp,"\n"))
			nom = strtok(nomTemp,"\n");
		else
			nom = "";
	}

	if(teteTheme != NULL)
		test = rechercherTheme(nom);

	if(test != NULL){
		printf("Thème déjà présent!\n");
	}else{
		strcpy(theme->nom,nom);
		theme->suivant = teteTheme;
		teteTheme = theme;
	}	

}

void supprimerTheme(char nom[100]){
	THEME *t = rechercherTheme(nom);
	THEME* temp = teteTheme;

	if(t != NULL){
		if(teteTheme == t)
			teteTheme = teteTheme->suivant;
		else{
			while(temp->suivant != t){ 
				temp = temp->suivant;
			}
			if(temp->suivant->suivant !=NULL)
				temp->suivant = temp->suivant->suivant;
			else
				temp->suivant = NULL;
		}
	}else
		printf("\nThème inexistant\n\n");
}

void modifierTheme(char nomT[100]){
	char nomTemp[101], *nom;
	THEME *t = rechercherTheme(nomT);
	THEME *test;
	test = NULL;

	if(t !=NULL){
		printf("Nom du thème:");
		fflush(stdin);
		fgets(nomTemp, sizeof(nomTemp), stdin);
		if(strcmp(nomTemp,"\n"))
			nom = strtok(nomTemp,"\n");
		else
			nom = "";

		while((nom[0]<= 96 || nom[0] >= 123) && (nom[0]<= 64 || nom[0] >= 91)){
			printf("Nom invalide, le nom d'un thème doit commencer par une lettre!\n");
			printf("Veuillez resaisir un nom correcte:");
			fflush(stdin);
			fgets(nomTemp, sizeof(nomTemp), stdin);	
			if(strcmp(nomTemp,"\n"))
				nom = strtok(nomTemp,"\n");
			else
				nom = "";
		}

		test = rechercherTheme(nom);

		if(test != NULL){
			printf("Thème déjà présent!\n");
		}else
			strcpy(t->nom,nom);

	}else
		printf("\nThème inexistant\n\n");
}

THEME *rechercherTheme(char nom[100]){
	THEME *temp = teteTheme;
	THEME *res = (THEME *)malloc(sizeof(THEME));
	res = NULL;
	int reussi = 0;
	
	while(temp != NULL && reussi == 0){
		if(!strcmp(temp->nom,nom)){
				reussi = 1;
				res = temp;
		}
		temp = temp->suivant;
	}
	return res;
}

char *afficherThemes(){
	char *res = (char*)malloc(105*sizeof(char));
	char nb[1],nomTemp[100];
	THEME *temp = teteTheme->suivant;
	int count = 1;
	int taille;

	strcpy(res,"1)");
	strcat(res,teteTheme->nom);
	strcat(res,"\n");	
	taille = strlen(res);

	while(temp != NULL){
		res = realloc(res, (taille+105)*sizeof(char)); 
		taille = strlen(res); 
		count++;
		sprintf(nb,"%d",count);
		strcat(res,nb);
		strcat(res,")");
		strcpy(nomTemp,temp->nom);
		strcat(res,nomTemp);
		strcat(res,"\n");
		temp = temp->suivant;
	}
	return res;
}

void enregistrerTheme(char *nomFichier){
	THEME *temp = teteTheme;
	FILE *f;
	char *fichier = (char *)malloc((strlen(nomFichier)+5)*sizeof(char)); 
	strcpy(fichier,nomFichier);
	strcat(fichier,".txt");	

	f =  fopen(fichier,"w");
	if(f != NULL){				
		while(temp != NULL){
			fprintf(f,"Nom du thème : %s\n",temp->nom);
			temp = temp->suivant;
		}
	fclose(f);
	printf("Enregistrement des thèmes réussi\n");
	}
	else
		printf("Impossible d'ouvrir le fichier\n");
}

void chargerTheme(char *nom){
	THEME *t = (THEME *)malloc(sizeof(THEME));
	
	strcpy(t->nom,nom);
	t->suivant = teteTheme;
	teteTheme = t;
}

void confirmation(char *nom){
	int chargement = 1;
	int choix = 0;

	if(teteTheme != NULL){
		printf("Attention, en chargeant les données d'un fichier vous allez perdre les données actuelles! Voulez vous continuer? 1)Oui 2)Non\n");
		scanf("%d",&choix);
		getchar();

		switch(choix){
			case 1:
				break;
			case 2:
				chargement = 0;
				break;	
			default :
				printf("Ceci n'est pas un choix valide, veuillez entrer soit 1 soit 2\n");
		}
	}

	if(chargement)
		lectureFichierThemes(nom);
	
}

void lectureFichierThemes(char *nomFichier){
	char *m_t,nom[100],ligne[200],car;
	int nb = 0;

	FILE *f1 = fopen(nomFichier, "r");
	
	if(f1 != NULL){
		car = fgetc(f1);
		
		while(car != EOF){
			while (car != '\n'){
				ligne[nb]=car;
				nb++;
				car=fgetc(f1);
			}
			ligne[nb]='\0';
					
			if(strstr(ligne, "Nom du thème") != NULL){
				m_t = strtok(ligne,":");
				strcpy(nom , &ligne[strlen(m_t)+2]);
				chargerTheme(nom);
			}
			nb = 0;
			car = fgetc(f1); 
		}
		fclose(f1);
		printf("Chargement des thèmes réussi\n");
	}else
		printf("Fichier introuvable\n");
}
