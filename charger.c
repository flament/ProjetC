#include <stdio.h>
#include <stdlib.h>
#include "Agenda.h"
#include <string.h>

extern EVENEMENT *tete;

void chargerEvenement(char nom[100], char lieu[100], char desc[200], char dateDebut[50], char heureDebut[50], char dateFin[50], char heureFin[50]){
	EVENEMENT *e = (EVENEMENT *)malloc(sizeof(EVENEMENT));
	
	strcpy(e->nom,nom);
	strcpy(e->description,desc);
	strcpy(e->nomLieu,lieu);
	e->dateDebut = convertirStringToDate(dateDebut,heureDebut);	
	e->dateFin = convertirStringToDate(dateFin,heureFin);	
	/*e->participants = p;*/	
	e->suivant = tete;
	tete = e;	
}

void charger(char *nomFichier){
	
	char *nom,*lieu,*desc,*dateDeb,*dateFin,*heureDeb,*heureFin,*allDay,ligne[350],car;
	char *m_t,*m_t2,*m_t3,*m_t4,*m_t5,*m_t6;
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
			nb = 0;
			car = fgetc(f1); 
	
			if(strcmp(ligne,"Subject, Start Date, Start Time, End Date, End Time, All Day, Location,  Description")){
				nom = strtok(ligne,", ");		
				m_t = &ligne[(int)(strlen(nom))+2];
				dateDeb = strtok(m_t,", ");			
				m_t2 = &m_t[(int)(strlen(dateDeb))+2];	
				heureDeb = strtok(m_t2,", ");
				m_t3 = &m_t2[strlen(heureDeb)+2];
				dateFin = strtok(m_t3,", ");
				m_t4 = &m_t3[strlen(dateFin)+2];
				heureFin = strtok(m_t4,", ");
				m_t5 = &m_t4[strlen(heureFin)+2];
				allDay = strtok(m_t5,", ");
				m_t6 = &m_t5[strlen(allDay)+2];
				lieu = strtok(m_t6,", ");
				desc = &m_t6[strlen(lieu)+2];
					 
  				chargerEvenement(nom,lieu,desc,dateDeb,heureDeb,dateFin,heureFin);
		/*printf("nom Evt: %s\n",nom);
		printf("dd: %s\n",dateDeb);
		printf("hd: %s\n",heureDeb);
		printf("Lieu: %s\n",lieu);
		printf("desc: %s\n",desc);
		printf("hf: %s\n",heureFin);
		printf("df: %s\n",dateFin);*/
			}
		}
	}else
		printf("Fichier introuvable\n");
	fclose(f1);
}


