#include <stdio.h>
#include <stdlib.h>
#include "Agenda.h"
#include <string.h>

extern EVENEMENT *tete;

void ecrireUnEvenement(FILE* c,EVENEMENT *e){
	/*FORMAT date jj/mm/aaaa ; heure hh:mm*/
	char startDate[10] , endDate[10], startTime[10], endTime[10];
	strftime(startDate, sizeof(startDate), "%x", e->dateDebut);
	strftime(endDate, sizeof(endDate), "%x", e->dateFin);
	strftime(startTime, sizeof(startTime), "%H:%M", e->dateDebut);
	strftime(endTime, sizeof(endTime), "%H:%M", e->dateFin);
	
	fprintf(c,"%s, %s, %s, %s, %s, false, %s, %s\n",e->nom,startDate,startTime,endDate,endTime,e->nomLieu,e->description);		
}

void ecriture(){
	FILE *calendrier;
	EVENEMENT *temp = tete;
	
	calendrier =  fopen("Calendrier.csv","w");
	if(calendrier != NULL){		
		fputs("Subject, Start Date, Start Time, End Date, End Time, All Day, Location,  Description\n",calendrier);	
		
		while(temp != NULL){
			ecrireUnEvenement(calendrier,temp);
			temp = temp->suivant;
		}
	fclose(calendrier);
	}
	else
		printf("Impossible d'ouvrir le fichier\n");
}