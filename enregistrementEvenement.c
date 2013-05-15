#include <stdio.h>
#include <stdlib.h>
#include "Agenda.h"
#include <string.h>

extern EVENEMENT *tete;

/*enregistre les données concernant les événements dans un fichier texte*/
void enregistrerFormatTxt(char *fichier){
	EVENEMENT *temp = tete;
	PERSONNE *pt;
	FILE *f;
	int count;
	char startDate[256] , endDate[256], startTime[10], endTime[10];
	
	f =  fopen(fichier,"w");
	if(f != NULL){				
		while(temp != NULL){
			strftime(startDate, sizeof(startDate), "%d/%m/%Y", temp->dateDebut);
			strftime(endDate, sizeof(endDate), "%d/%m/%Y", temp->dateFin);
			strftime(startTime, sizeof(startTime), "%H:%M", temp->dateDebut);
			strftime(endTime, sizeof(endTime), "%H:%M", temp->dateFin);

			fprintf(f,"Nom de l'événement : %s\n",temp->nom);
			fprintf(f,"Nom du lieu de l'événement : %s\n",temp->nomLieu);
			fprintf(f,"Description de l'événement : %s\n",temp->description);
			fprintf(f,"Date de début de l'événement : %s\n",startDate);
			fprintf(f,"Heure de début de l'événement : %s\n",startTime);
			fprintf(f,"Date de fin de l'événement : %s\n",endDate);
			fprintf(f,"Heure de fin de l'événement : %s\n",endTime);
			if(temp->participants != NULL){
				fputs("Liste des participants de l'événement :\n",f);
				count = 1;
				pt = temp->participants;
				
				while(pt != NULL){
					fprintf(f,"%d) %s\n",count,pt->email);
					count++;
					pt = pt->suivant;	
				}
			}
			
			fputs("------------------------------------------------------------------------------------\n",f);			
			temp = temp->suivant;
		}
	printf("Les données concernant les événements ont bien été sauvegardées\n");
	fclose(f);
	}
	else
		printf("Impossible d'ouvrir le fichier\n");
}
