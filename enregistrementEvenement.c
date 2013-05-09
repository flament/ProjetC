#include <stdio.h>
#include <stdlib.h>
#include "Agenda.h"
#include <string.h>

extern EVENEMENT *tete;

void enregistrerFormatTxt(){
	char *fichier = "evt.txt";
	EVENEMENT *temp = tete;
	PERSONNE *pt;
	FILE *f;
	int count;
	char startDate[10] , endDate[10], startTime[10], endTime[10];
	
	f =  fopen(fichier,"w");
	if(f != NULL){				
		while(temp != NULL){
			strftime(startDate, sizeof(startDate), "%x", temp->dateDebut);
			strftime(endDate, sizeof(endDate), "%x", temp->dateFin);
			strftime(startTime, sizeof(startTime), "%H:%M", temp->dateDebut);
			strftime(endTime, sizeof(endTime), "%H:%M", temp->dateFin);

			fprintf(f,"Nom de l'évènement : %s\n",temp->nom);
			fprintf(f,"Nom du lieu de l'évènement : %s\n",temp->nomLieu);
			fprintf(f,"Description de l'évènement : %s\n",temp->description);
			fprintf(f,"Date de début de l'évènement : %s\n",startDate);
			fprintf(f,"Heure de début de l'évènement : %s\n",startTime);
			fprintf(f,"Date de fin de l'évènement : %s\n",endDate);
			fprintf(f,"Heure de fin de l'évènement : %s\n",endTime);
			fputs("Liste des participants de l'évènement :\n",f);

			count = 1;
			pt = temp->participants;
			while(pt != NULL){
				fprintf(f,"%d) : %s\n",count,pt->email);
				count++;
				pt = pt->suivant;	
			}
			
			
			fputs("------------------------------------------------------------------------------------\n",f);			
			temp = temp->suivant;
		}
	fclose(f);
	}
	else
		printf("Impossible d'ouvrir le fichier\n");
}
