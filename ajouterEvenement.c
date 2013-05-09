#include <stdio.h>
#include <stdlib.h>
#include "Agenda.h"
#include <string.h>

EVENEMENT *tete = NULL;

void ajouterEvenement(){
	razTetePersonne();	

	EVENEMENT *e = (EVENEMENT *)malloc(sizeof(EVENEMENT));
	PERSONNE * p = (PERSONNE *)malloc(sizeof(PERSONNE));
	p = NULL;
	int participant = 0, exit = 0, choix;
	char *nom,*desc,*nomLieu,*dateDebut,*dateFin,*heureDebut,*heureFin;
	char dateDebTemp[50], dateFinTemp[50],heureDebTemp[50],heureFinTemp[50],nomTemp[100],lieuTemp[100],descTemp[200];
	
	printf("Nom de l'évènement : ");	
	fgets(nomTemp, sizeof(nomTemp), stdin);
	nom = strtok(nomTemp,"\n");
	while(!stringValide(nom)){
		printf("Nom de l'évènement : ");
		fgets(nomTemp, sizeof(nomTemp), stdin);
		nom = strtok(nomTemp,"\n");
	}

	printf("Description de l'évènement : ");
	fgets(descTemp, sizeof(descTemp), stdin);
	desc = strtok(descTemp,"\n");
	while(!stringValide(desc)){
		printf("Description de l'évènement : ");
		fgets(descTemp, sizeof(descTemp), stdin);
		desc = strtok(descTemp,"\n");
	}
	
	printf("Lieu de l'évènement :");
	fgets(lieuTemp, sizeof(lieuTemp), stdin);
	nomLieu = strtok(lieuTemp,"\n");
	while(!stringValide(nomLieu)){
		printf("Lieu de l'évènement : ");
		fgets(lieuTemp, sizeof(lieuTemp), stdin);
		nomLieu = strtok(lieuTemp,"\n");
	}

	printf("Date de début de l'évènement (format dd/mm/yyyy): ");
	fgets(dateDebTemp, sizeof(dateDebTemp), stdin);
	dateDebut = strtok(dateDebTemp,"\n");
	while(!formatDateValide(dateDebut)){
		printf("Date de début de l'évènement (format dd/mm/yyyy): ");
		fgets(dateDebTemp, sizeof(dateDebTemp), stdin);
		dateDebut = strtok(dateDebTemp,"\n");
	}

	printf("Heure de début de l'évènement (format HH:MM): ");
	fgets(heureDebTemp, sizeof(heureDebTemp), stdin);
	heureDebut = strtok(heureDebTemp,"\n");
	while(!formatHeureValide(heureDebut)){
		printf("Heure de début de l'évènement (format HH:MM): ");
		fgets(heureDebTemp, sizeof(heureDebTemp), stdin);
		heureDebut = strtok(heureDebTemp,"\n");
	}
	
	printf("Date de fin de l'évènement (format dd/mm/yyyy): ");
	fgets(dateFinTemp, sizeof(dateFinTemp), stdin);
	dateFin = strtok(dateFinTemp,"\n");
	while(!formatDateValide(dateFin)){
		printf("Date de fin de l'évènement (format dd/mm/yyyy): ");
		fgets(dateFinTemp, sizeof(dateFinTemp), stdin);
		dateFin = strtok(dateFinTemp,"\n");
	}

	printf("Heure de fin de l'évènement (format HH:MM): ");
	fgets(heureFinTemp, sizeof(heureFinTemp), stdin);
	heureFin = strtok(heureFinTemp,"\n");
	while(!formatHeureValide(heureFin)){
		printf("Heure de fin de l'évènement (format HH:MM): ");
		fgets(heureFinTemp, sizeof(heureFinTemp), stdin);
		heureFin = strtok(heureFinTemp,"\n");
	}

	/*vérification des dates+heures et une boucle demandant de changer l'une des deux si pas bon, et boucle jusqu'à ce que ce soit correct*/
	while(!dateFinValide(dateDebut,dateFin,heureDebut,heureFin) || !emplacementDispo(dateDebut,dateFin,heureDebut,heureFin)){
		printf("Que voulez-vous changer ? \n1)la date de début \n2) l'heure de début \n3) la date de fin \n4) l'heure de fin\n");
		scanf("%1d",&choix);
		getchar();

		switch(choix){
			case 1 :
				printf("Date de début de l'évènement (format dd/mm/yyyy): ");
				fgets(dateDebTemp, sizeof(dateDebTemp), stdin);
				dateDebut = strtok(dateDebTemp,"\n");
				while(!formatDateValide(dateDebut)){
					printf("Date de début de l'évènement (format dd/mm/yyyy): ");
					fgets(dateDebTemp, sizeof(dateDebTemp), stdin);
					dateDebut = strtok(dateDebTemp,"\n");
				}
				break;

			case 2 :
				printf("Heure de début de l'évènement (format HH:MM) ");
				fgets(heureDebTemp, sizeof(heureDebTemp), stdin);
				heureDebut = strtok(heureDebTemp,"\n");
				while(!formatHeureValide(heureDebut)){
					printf("Heure de début de l'évènement (format HH:MM): ");
					fgets(heureDebTemp, sizeof(heureDebTemp), stdin);
					heureDebut = strtok(heureDebTemp,"\n");
				}
				break;
			case 3 :
				printf("Date de fin de l'évènement (format dd/mm/yyyy): ");
				fgets(dateFinTemp, sizeof(dateFinTemp), stdin);
				dateFin = strtok(dateFinTemp,"\n");
				while(!formatDateValide(dateFin)){
					printf("Date de fin de l'évènement (format dd/mm/yyyy): ");
					fgets(dateFinTemp, sizeof(dateFinTemp), stdin);
					dateFin = strtok(dateFinTemp,"\n");
				}
				break;
			case 4 :
				printf("Heure de fin de l'évènement (format HH:MM) ");
				fgets(heureFinTemp, sizeof(heureFinTemp), stdin);
				heureFin = strtok(heureFinTemp,"\n");
				while(!formatHeureValide(heureFin)){
					printf("Heure de fin de l'évènement (format HH:MM): ");
					fgets(heureFinTemp, sizeof(heureFinTemp), stdin);
					heureFin = strtok(heureFinTemp,"\n");
				}
				break;
			default :
				printf("Cette valeur n'est pas valide, veuillez rentrer une valeur valide");					
		}									
	}
	
	while(!exit){
		printf("Voulez-vous ajouter un participant ?\n1) oui\t2) non\n");
		scanf("%1d",&participant);
		getchar();

		switch(participant){
			case 1 :
				p = ajouterParticipant();
				break;
			case 2 :
				exit = 1;
				break;
			default :
				printf("Cette valeur n'est pas valide, veuillez rentrer une valeur valide");					
		}											
	}
	
	strcpy(e->nom,nom);
	strcpy(e->description,desc);
	strcpy(e->nomLieu,nomLieu);
	e->dateDebut = convertirStringToDate(dateDebut,heureDebut);	
	e->dateFin = convertirStringToDate(dateFin,heureFin);	
	e->participants = p;	
	
	e->suivant = tete;
	tete = e;
}


