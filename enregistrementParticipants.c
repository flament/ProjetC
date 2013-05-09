#include <stdio.h>
#include <stdlib.h>
#include "Agenda.h"
#include <string.h>

extern PERSONNE *teteListePers;

void enregistrerParticipants(){
	char *fichier = "participants.txt";
	PERSONNE *temp = teteListePers;
	FILE *f;
	
	f =  fopen(fichier,"w");
	if(f != NULL){				
		while(temp != NULL){

			fprintf(f,"Nom du participant : %s\n",temp->nom);
			fprintf(f,"Prénom du participant : %s\n",temp->prenom);
			fprintf(f,"Email du participant : %s\n",temp->email);
			/*fprintf(f,"Fonction du participant : %s\n",temp->fonction);*/
			
			fputs("------------------------------------------------------------------------------------\n",f);			
			temp = temp->suivant;
		}
	fclose(f);
	}
	else
		printf("Impossible d'ouvrir le fichier\n");
}
