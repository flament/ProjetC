#include <stdio.h>
#include <stdlib.h>
#include "Agenda.h"
#include <string.h>

extern EVENEMENT *tete;

EVENEMENT *rechercher(char nomEvenement[100],char dateDebutEvenement[10]){
	EVENEMENT *temp = tete->suivant;
	EVENEMENT *res = (EVENEMENT *)malloc(sizeof(EVENEMENT));
	res = NULL;
	int reussi = 0;
	char date[256], dateTemp[256]; 
	strftime(date, sizeof(date), "%d/%m/%Y", tete->dateDebut);
	
	if(temp != NULL)
		strftime(dateTemp, sizeof(dateTemp), "%d/%m/%Y", temp->dateDebut);

	if(!strcmp(tete->nom,nomEvenement) && !strcmp(date,dateDebutEvenement)){
			res = tete;
			reussi = 1;
	}
		
	while(temp != NULL && reussi == 0){
		if(!strcmp(temp->nom,nomEvenement) && !strcmp(dateTemp,dateDebutEvenement)){
			res = temp;
			reussi = 1;
		}
		
		temp = temp->suivant;
		if(temp != NULL)
			strftime(dateTemp, sizeof(dateTemp), "%d/%m/%Y", temp->dateDebut);		
	}

	if(reussi ==0)
		printf("Aucun évènement ne correspond à ce nom et/ou cette date\n");
	
	return res;
}

void supprimer(char nomEvenement[100],char dateDebutEvenement[10]){ 
	EVENEMENT *e = rechercher(nomEvenement,dateDebutEvenement); 
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
	}else
		printf("Evènement inexistant!\n");	
}

