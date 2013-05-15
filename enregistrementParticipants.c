#include <stdio.h>
#include <stdlib.h>
#include "Agenda.h"
#include <string.h>

extern PERSONNE *teteListePers;

void enregistrerParticipants(char *fichier){
	/*char *fichier = "participants.txt";*/
	PERSONNE *temp = teteListePers;
	FILE *f;
	
	f =  fopen(fichier,"w");
	if(f != NULL){				
		while(temp != NULL){

			fprintf(f,"Nom du participant : %s\n",temp->nom);
			fprintf(f,"Prénom du participant : %s\n",temp->prenom);
			fprintf(f,"Email du participant : %s\n",temp->email);
			
			fputs("------------------------------------------------------------------------------------\n",f);			
			temp = temp->suivant;
		}
	printf("Les données concernant les participants ont bien été sauvegardées\n");
	fclose(f);
	}
	else
		printf("Impossible d'ouvrir le fichier\n");
}

void enregistrer(char *fichier, char nomTheme[100]){
		char *csv = (char *)malloc((strlen(nomTheme)+strlen(fichier)+6)*sizeof(char)); 
		strcpy(csv,fichier);
		strcat(csv,"_");
		strcat(csv,nomTheme);
		strcat(csv,".csv");
	
		char *txt = (char *)malloc((strlen(nomTheme)+strlen(fichier)+6)*sizeof(char)); 
		strcpy(txt,fichier);
		strcat(txt,"_");
		strcat(txt,nomTheme);
		strcat(txt,".txt");

		char *pers = (char *)malloc((strlen(nomTheme)+strlen(fichier)+19)*sizeof(char)); 
		strcpy(pers,fichier);
		strcat(pers,"_");
		strcat(pers,nomTheme);
		strcat(pers,"_Participants.txt");
	
		ecritureCSV(csv);
		enregistrerFormatTxt(txt);
		enregistrerParticipants(pers);
}
