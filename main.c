/* 
 * File:   main.c
 * Author: damien
 *
 * Created on 19 mars 2013, 17:06
 */

#include <stdio.h>
#include <stdlib.h>
#include "Agenda.h"
#include <string.h>

/*
 * 
 */
EVENEMENT *tete = NULL;
PERSONNE *pers = NULL;

struct tm* convertirStringToDate(char s[50], char h[50]){
	char *jour, *m_t, *mois, *annee,*heure,*minute;
	struct tm* tim;
	tim = (struct tm*)malloc(sizeof(struct tm));
	
 	jour = strtok(s,"/"); 
	m_t = &s[3];	 
	mois = strtok(m_t,"/");
	annee =  &m_t[3];
	heure = strtok(h,":");
	minute = &h[3];

	tim->tm_mday = atoi(jour);
	tim->tm_mon = atoi(mois)-1;
	tim->tm_year = atoi(annee) - 1900;
	tim->tm_hour = atoi(heure);
	tim->tm_min = atoi(minute);

	return tim;
}

EVENEMENT *rechercher(char *nomEvenement,char dateDebutEvenement[10]){
	EVENEMENT *temp = tete->suivant;
	char date[256], dateTemp[256];
	strftime(date, sizeof(date), "%d %B %Y", tete->dateDebut);
	
	if(temp != NULL)
		strftime(dateTemp, sizeof(dateTemp), "%d %B %Y", temp->dateDebut);


	if(strcmp(tete->nom,nomEvenement) && strcmp(date,dateDebutEvenement))	
			return tete;
	
	while(temp != NULL){
		if(strcmp(temp->nom,nomEvenement) && strcmp(dateTemp,dateDebutEvenement))
			return temp;
		
		temp = temp->suivant;
		if(temp != NULL)
			strftime(dateTemp, sizeof(dateTemp), "%d %B %Y", temp->dateDebut);		

	}
	printf("Aucun évènement ne correspond à ce nom et/ou cette date");
	return NULL;
}

void modifier(char *nomEvenement,char dateDebutEvenement[10]){
	EVENEMENT *e = rechercher(nomEvenement,dateDebutEvenement);
	int modifier = 0,participant = 0;
	char *modification = (char *)(malloc(sizeof(char)));


	if(e == NULL){
		printf("Evenement inexistant\n");	
		return;
	}
	
	while(modifier > 8 || modifier == 0){
		printf("Que voulez-vous modifier ?\n1) le nom\t2)le lieu\t3)la date de début\t4)l'heure de début\t5)la date de fin\t6)l'heure de fin\t7)la description\t8)les personnes participantes");
		scanf("%d",&modifier);
		switch(modifier){
			case 1 :
				printf("quel nom voulez vous donner ?");
				scanf("%s",modification);
				e->nom = modification;
				break;
			case 2 :
				printf("quel est le lieu ?");
				scanf("%s",modification);
				e->nomLieu = modification;
				break;
			case 3 :
				printf("quel est la date de début ?");
				scanf("%s",modification);
				/*e->dateDebut = convertirStringToDate(modification);*/
				break;
			case 4 :
				printf("quel est l'heure de début ?");
				scanf("%s",modification);
				/*e->heureDebut = convertirStringToDate(modification);*/
				break;
			case 5 :
				printf("quel est la date de fin ?");
				scanf("%s",modification);
				/*e->dateFin = convertirStringToDate(modification);*/
				break;
			case 6 :
				printf("quel est l'heure de fin ?");
				scanf("%s",modification);
				/*e->dateDebut = convertirStringToDate(modification);*/
				break;
			case 7 :
				printf("quel est la nouvelle description ?");
				scanf("%s",modification);
				e->description = modification;
				break;
			case 8 :
				while(participant == 0 || participant > 2){
				printf("voulez-vous inscrire ou supprimer un participant ?\n1)inscrire\t2)supprimer");
				scanf("%d",&participant);
				}
				switch(participant){
					case 1 :
						/*PERSONNE *personne = e->participants;
						PERSONNE *nouvellePersonne = (PERSONNE *)malloc(sizeof(PERSONNE));
						
						while(personne != NULL){
							personne = e->participants->suivant;
						}
						
						printf("Nom :");
						scanf("%s",nouvellePersonne->nom);
						printf("Prénom :");
						scanf("%s",nouvellePersonne->prenom);
						printf("email :");
						scanf("%s",nouvellePersonne->email);
						printf("Fonction :\t(élève ou professeur)");
						//scanf("%s",nouvellePersonne->fonction);
						//TACHES à faire

						personne->suivant = nouvellePersonne; */
						break;
					case 2 :
						/* faire dérouler les personnes avec un numéro devant et supprimer la personne ainsi selectionnée*/
					break;
					default :
						printf("Cette valeur n'est pas valide, veuillez rentrer une valeur valide");
						
						
				}
				break;
			default :
				printf("Ceci n'est pas un choix valide, veuillez entrer un choix valide");
		}
	}
	
}

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
		printf("impossible d'ouvrir le fichier");
}


void ajouterEvenement(){
	EVENEMENT *e = (EVENEMENT *)malloc(sizeof(EVENEMENT));	
	int capacite = 0;
	char *nom = (char *)(malloc(sizeof(char)));
	char *desc = (char *)(malloc(sizeof(char)));
	char *nomLieu = (char *)(malloc(sizeof(char)));
	char dateDebut[50], dateFin[50],heureDebut[50],heureFin[50];
	
	printf("Nom de l'évènement : ");	
	scanf("%s",nom);
	getchar();
	while(!stringValide(nom)){
		printf("Nom de l'évènement : ");
		scanf("%s",nom);
		getchar();
	}
	printf("Description de l'évènement : ");
	scanf("%s",desc);
	getchar();
	while(!stringValide(desc)){
		printf("Description de l'évènement : ");
		scanf("%s",desc);
		getchar();
	}
	
	printf("Lieu de l'évènement :");
	scanf("%s",nomLieu);
	getchar();
	while(!stringValide(nomLieu)){
		printf("Lieu de l'évènement : ");
		scanf("%s",nomLieu);
		getchar();
	}

	printf("Capacité du lieu : \t(pour ignorer appuyez sur Entrée)");
	scanf("%d",&capacite);
	getchar();

	printf("Date de début de l'évènement (format dd/mm/yyyy): ");
	scanf("%s",dateDebut);
	getchar();
	while(!formatDateValide(dateDebut)){
		printf("Date de début de l'évènement : ");
		scanf("%s",dateDebut);
		getchar();
	}

	printf("Heure de début de l'évènement (format HH:MM) ");
	scanf("%s",heureDebut);
	getchar();
	while(!formatHeureValide(heureDebut)){
		printf("Heure de début de l'évènement : ");
		scanf("%s",heureDebut);
		getchar();
	}
	
	printf("Date de fin de l'évènement (format dd/mm/yyyy): ");
	scanf("%s",dateFin);
	while(!formatDateValide(dateFin)){
		printf("Date de fin de l'évènement : ");
		scanf("%s",dateFin);
		getchar();
	}

	printf("Heure de fin de l'évènement (format HH:MM) ");
	scanf("%s",heureFin);
	getchar();
	while(!formatHeureValide(heureFin)){
		printf("Heure de fin de l'évènement : ");
		scanf("%s",heureFin);
		getchar();
	}
	
	/*if(capacite != 0)
		//e->capaciteLieu = capacite;*/
	
	e->nom = nom;
	e->description = desc;
	e->nomLieu = nomLieu;
	e->capaciteLieu = capacite;
	e->dateDebut = convertirStringToDate(dateDebut,heureDebut);	
	e->dateFin = convertirStringToDate(dateFin,heureFin);	

	e->suivant = tete;
	tete = e;	
}

int main(int argc, char** argv) {
    
	
	char buffer[256], buff2[256];

	ajouterEvenement();
	/*ajouterEvenement();*/

	printf("nom Evt: %s\n",tete->nom);	
	printf("nom Lieu: %s\n",tete->nomLieu);
	printf("Desc Evt: %s\n",tete->description);
	printf("capacite Lieu: %d\n",tete->capaciteLieu);
	strftime(buffer, sizeof(buffer), "%d %B %Y", tete->dateDebut);
	strftime(buff2, sizeof(buff2), "%d %B %Y", tete->dateFin);
	printf("%s\n",buffer);
	printf("%s\n",buff2);

	/*printf("nom Evt: %s\n",(tete->suivant)->nom);	
	printf("nom Lieu: %s\n",(tete->suivant)->nomLieu);
	printf("Desc Evt: %s\n",(tete->suivant)->description);
	printf("capacite Lieu: %d\n",(tete->suivant)->capaciteLieu);
	strftime(buffer, sizeof(buffer), "%d %B %Y", (tete->suivant)->dateDebut);
	strftime(buff2, sizeof(buff2), "%d %B %Y", (tete->suivant)->dateFin);
	printf("%s\n",buffer);
	printf("%s\n",buff2);*/

	ecriture();
    return (EXIT_SUCCESS);	
}

