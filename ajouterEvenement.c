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
	char dateDebTemp[50], dateFinTemp[50],heureDebTemp[50],heureFinTemp[50],nomTemp[101],lieuTemp[101],descTemp[201];
	
	printf("Nom de l'évènement : ");	
	fgets(nomTemp, sizeof(nomTemp), stdin);
	/*Si l'utilisateur ne saisit pas de nom (tape sur Entrée), nom = Nouvel évènement par défaut*/	
	if(strcmp(nomTemp,"\n"))
		nom = strtok(nomTemp,"\n");
	else
		nom = "Nouvel évènement ";

	while(!stringValide(nom)){
		printf("Nom de l'évènement : ");
		fgets(nomTemp, sizeof(nomTemp), stdin);
		
		if(strcmp(nomTemp,"\n"))
			nom = strtok(nomTemp,"\n");
		else
			nom = "Nouvel évènement ";
	}

	printf("Description de l'évènement : ");
	fgets(descTemp, sizeof(descTemp), stdin);
	
	if(strcmp(descTemp,"\n"))
		desc = strtok(descTemp,"\n");
	else
		desc = "Inconnue";
	while(!stringValide(desc)){
		printf("Description de l'évènement : ");
		fgets(descTemp, sizeof(descTemp), stdin);
		
		if(strcmp(descTemp,"\n"))
			desc = strtok(descTemp,"\n");
		else
			desc = "Inconnue";
	}
	
	printf("Lieu de l'évènement :");
	fgets(lieuTemp, sizeof(lieuTemp), stdin);
	
	if(strcmp(lieuTemp,"\n"))
		nomLieu = strtok(lieuTemp,"\n");
	else
		nomLieu = "Inconnu";

	while(!stringValide(nomLieu)){
		printf("Lieu de l'évènement : ");
		fgets(lieuTemp, sizeof(lieuTemp), stdin);
		
		if(strcmp(lieuTemp,"\n"))
			nomLieu = strtok(lieuTemp,"\n");
		else
			nomLieu = "Inconnu";
	}

	printf("Date de début de l'évènement (format dd/mm/yyyy): ");
	fgets(dateDebTemp, sizeof(dateDebTemp), stdin);
	if(strcmp(dateDebTemp,"\n"))
		dateDebut = strtok(dateDebTemp,"\n");
	else
		dateDebut = "Inconnue";

	while(!formatDateValide(dateDebut)){
		printf("Date de début de l'évènement (format dd/mm/yyyy): ");
		fgets(dateDebTemp, sizeof(dateDebTemp), stdin);
		
		if(strcmp(dateDebTemp,"\n"))
			dateDebut = strtok(dateDebTemp,"\n");
		else
			dateDebut = "Inconnue";
	}

	printf("Heure de début de l'évènement (format HH:MM): ");
	fgets(heureDebTemp, sizeof(heureDebTemp), stdin);
	if(strcmp(heureDebTemp,"\n"))
		heureDebut = strtok(heureDebTemp,"\n");
	else
		heureDebut = "Inconnue";
	
	while(!formatHeureValide(heureDebut)){
		printf("Heure de début de l'évènement (format HH:MM): ");
		fgets(heureDebTemp, sizeof(heureDebTemp), stdin);
		if(strcmp(heureDebTemp,"\n"))
			heureDebut = strtok(heureDebTemp,"\n");
		else
			heureDebut = "Inconnue";
	}
	
	printf("Date de fin de l'évènement (format dd/mm/yyyy): ");
	fgets(dateFinTemp, sizeof(dateFinTemp), stdin);
	if(strcmp(dateFinTemp,"\n"))
		dateFin = strtok(dateFinTemp,"\n");
	else
		dateFin = "Inconnue";
	
	while(!formatDateValide(dateFin)){
		printf("Date de fin de l'évènement (format dd/mm/yyyy): ");
		fgets(dateFinTemp, sizeof(dateFinTemp), stdin);
		
		if(strcmp(dateFinTemp,"\n"))
			dateFin = strtok(dateFinTemp,"\n");
		else
			dateFin = "Inconnue";
	}

	printf("Heure de fin de l'évènement (format HH:MM): ");
	fgets(heureFinTemp, sizeof(heureFinTemp), stdin);
	if(strcmp(heureFinTemp,"\n"))
		heureFin = strtok(heureFinTemp,"\n");
	else
		heureFin = "Inconnue";
	
	while(!formatHeureValide(heureFin)){
		printf("Heure de fin de l'évènement (format HH:MM): ");
		fgets(heureFinTemp, sizeof(heureFinTemp), stdin);
		if(strcmp(heureFinTemp,"\n"))
			heureFin = strtok(heureFinTemp,"\n");
		else
			heureFin = "Inconnue";
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
				if(strcmp(dateDebTemp,"\n"))
					dateDebut = strtok(dateDebTemp,"\n");
				else
					dateDebut = "Inconnue";

				while(!formatDateValide(dateDebut)){
					printf("Date de début de l'évènement (format dd/mm/yyyy): ");
					fgets(dateDebTemp, sizeof(dateDebTemp), stdin);
					if(strcmp(dateDebTemp,"\n"))
						dateDebut = strtok(dateDebTemp,"\n");
					else
						dateDebut = "Inconnue";
				}
				break;

			case 2 :
				printf("Heure de début de l'évènement (format HH:MM) ");
				fgets(heureDebTemp, sizeof(heureDebTemp), stdin);
				if(strcmp(heureDebTemp,"\n"))
					heureDebut = strtok(heureDebTemp,"\n");
				else
					heureDebut = "Inconnue";

				while(!formatHeureValide(heureDebut)){
					printf("Heure de début de l'évènement (format HH:MM): ");
					fgets(heureDebTemp, sizeof(heureDebTemp), stdin);
					
					if(strcmp(heureDebTemp,"\n"))
						heureDebut = strtok(heureDebTemp,"\n");
					else
						heureDebut = "Inconnue";
				}
				break;
			case 3 :
				printf("Date de fin de l'évènement (format dd/mm/yyyy): ");
				fgets(dateFinTemp, sizeof(dateFinTemp), stdin);
				if(strcmp(dateFinTemp,"\n"))
					dateFin = strtok(dateFinTemp,"\n");
				else
					dateFin = "Inconnue";
	
				while(!formatDateValide(dateFin)){
					printf("Date de fin de l'évènement (format dd/mm/yyyy): ");
					fgets(dateFinTemp, sizeof(dateFinTemp), stdin);
					
					if(strcmp(dateFinTemp,"\n"))
						dateFin = strtok(dateFinTemp,"\n");
					else
					dateFin = "Inconnue";
				}
				break;
			case 4 :
				printf("Heure de fin de l'évènement (format HH:MM) ");
				fgets(heureFinTemp, sizeof(heureFinTemp), stdin);
				
				if(strcmp(heureFinTemp,"\n"))
					heureFin = strtok(heureFinTemp,"\n");
				else
					heureFin = "Inconnue";

				while(!formatHeureValide(heureFin)){
					printf("Heure de fin de l'évènement (format HH:MM): ");
					fgets(heureFinTemp, sizeof(heureFinTemp), stdin);

					if(strcmp(heureFinTemp,"\n"))
						heureFin = strtok(heureFinTemp,"\n");
					else
						heureFin = "Inconnue";
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


