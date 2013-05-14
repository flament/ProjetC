#include <stdio.h>
#include <stdlib.h>
#include "Agenda.h"
#include <string.h>

extern EVENEMENT *tete;

EVENEMENT *rechercherEvenement(char nomEvenement[100],char dateDebutEvenement[10], char heureDeb[5]){
	EVENEMENT *temp = tete;
	EVENEMENT *res = (EVENEMENT *)malloc(sizeof(EVENEMENT));
	res = NULL;
	int reussi = 0;
	char dateTemp[256],heureTemp[256]; 
	
	if(temp != NULL){
		strftime(dateTemp, sizeof(dateTemp), "%d/%m/%Y", temp->dateDebut);
		strftime(heureTemp, sizeof(heureTemp), "%H:%M", temp->dateDebut);
	}

	while(temp != NULL && reussi == 0){
		if(!strcmp(temp->nom,nomEvenement) && !strcmp(dateTemp,dateDebutEvenement) && !strcmp(heureTemp,heureDeb)){
			res = temp;
			reussi = 1;
		}
		
		temp = temp->suivant;
		if(temp != NULL){
			strftime(dateTemp, sizeof(dateTemp), "%d/%m/%Y", temp->dateDebut);	
			strftime(heureTemp, sizeof(heureTemp), "%H:%M", temp->dateDebut);
		}	
	}

	if(reussi ==0)
		printf("Aucun événement ne correspond à ce nom et/ou cette date\n");
	
	return res;
}

void supprimerEvenement(char nomEvenement[100],char dateDebutEvenement[10],char heureDeb[5]){ 
	EVENEMENT *e = rechercherEvenement(nomEvenement,dateDebutEvenement,heureDeb); 
	EVENEMENT *temp = tete;
	if(e != NULL){	
		if(tete == e){
			tete = tete->suivant;
		}else{
			while(temp->suivant != e){
				temp = temp->suivant;
			} 
			if(temp->suivant->suivant != NULL)
				temp->suivant = temp->suivant->suivant;		
			else
				temp->suivant = NULL;
		}

		free(e->dateDebut);
		free(e->dateFin);
		/*if(e->participants != NULL)
			libererPersonne(e->participants);*/
		free(e);
	}else
		printf("Evénement inexistant!\n");	
}

char *afficherEvenements(){
	char *res = (char*)malloc(210*sizeof(char));
	char nb[1],nomTemp[100],dateTemp[100];
	EVENEMENT *temp = tete->suivant;
	int count = 1;
	int taille;

	strftime(dateTemp, sizeof(dateTemp), "%d/%m/%Y à %H:%M", tete->dateDebut);
	strcpy(res,"1)");
	strcat(res,tete->nom);
	strcat(res,"  ");
	strcat(res,"  (");
	strcat(res,dateTemp);
	strcat(res,")\n");	
	taille = strlen(res);

	while(temp != NULL){
		res = realloc(res, (taille+210)*sizeof(char)); 
		taille = strlen(res); 
		count++;
		sprintf(nb,"%d",count);
		strcat(res,nb);
		strcat(res,")");
		strcpy(nomTemp,temp->nom);
		strcat(res,nomTemp);
		strcat(res, "  ");
		strcat(res, "  (");
		strftime(dateTemp, sizeof(dateTemp), "%d/%m/%Y à %H:%M", temp->dateDebut);
		strcat(res,dateTemp);
		strcat(res,")\n");
		temp = temp->suivant;
	}
	return res;
}

