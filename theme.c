#include <stdio.h>
#include <stdlib.h>
#include "Agenda.h"
#include <string.h>

THEME *teteTheme = NULL;

void ajouterTheme(){
	char nomTemp[100], *nom;
	THEME *theme = (THEME *)malloc(sizeof(THEME));
	THEME *test;
	test = NULL;

	printf("Nom du thème:");
	fgets(nomTemp, sizeof(nomTemp), stdin);
	if(strcmp(nomTemp,"\n"))
		nom = strtok(nomTemp,"\n");
	else
		nom = "";

	while((nom[0]<= 96 || nom[0] >= 123) && (nom[0]<= 64 || nom[0] >= 91)){
		printf("Nom invalide, le nom d'un thème doit commencer par une lettre!\n");
		printf("Veuillez resaisir un nom correcte:");
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
	char nomTemp[100], *nom;
	THEME *t = rechercherTheme(nomT);
	THEME *test;
	test = NULL;

	if(t !=NULL){
		printf("Nom du thème:");
		fgets(nomTemp, sizeof(nomTemp), stdin);
		if(strcmp(nomTemp,"\n"))
			nom = strtok(nomTemp,"\n");
		else
			nom = "";

		while((nom[0]<= 96 || nom[0] >= 123) && (nom[0]<= 64 || nom[0] >= 91)){
			printf("Nom invalide, le nom d'un thème doit commencer par une lettre!\n");
			printf("Veuillez resaisir un nom correcte:");
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
	
	/*if(!strcmp(teteTheme->nom, nom)){
		res = teteTheme;
		reussi = 1;
	}*/

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
