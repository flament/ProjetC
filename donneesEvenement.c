#include <stdio.h>
#include <stdlib.h>
#include "Agenda.h"
#include <string.h>

char *entreeNom(){
	char *nom = (char *)malloc(101*sizeof(char));
	char nomTemp[101];
	
	printf("Nom de l'évènement : ");	
	fgets(nomTemp, sizeof(nomTemp), stdin);
	/*Si l'utilisateur ne saisit pas de nom (tape sur Entrée), nom = Nouvel évènement par défaut*/	
	if(strcmp(nomTemp,"\n"))
		strcpy(nom ,strtok(nomTemp,"\n"));
	else
		strcpy(nom , "Nouvel évènement ");

	while(!stringValide(nom)){
		printf("Nom de l'évènement : ");
		fgets(nomTemp, sizeof(nomTemp), stdin);
		
		if(strcmp(nomTemp,"\n"))
			strcpy(nom ,strtok(nomTemp,"\n"));
		else
			strcpy(nom , "Nouvel évènement ");
	}

	return nom;
}

char *entreeDescription(){
	char *desc = (char *)malloc(201*sizeof(char));
	char descTemp[201];

	printf("Description de l'évènement : ");
	fgets(descTemp, sizeof(descTemp), stdin);
	
	if(strcmp(descTemp,"\n"))
		strcpy(desc , strtok(descTemp,"\n"));
	else
		strcpy(desc , "Inconnue");

	while(!stringValide(desc)){
		printf("Description de l'évènement : ");
		fgets(descTemp, sizeof(descTemp), stdin);
		
		if(strcmp(descTemp,"\n"))
			strcpy(desc , strtok(descTemp,"\n"));
		else
			strcpy(desc , "Inconnue");
	}

	return desc;
}

char *entreeLieu(){
	char *nomLieu = (char *)malloc(101*sizeof(char));
	char lieuTemp[101];
	
	printf("Lieu de l'évènement :");
	fgets(lieuTemp, sizeof(lieuTemp), stdin);
	
	if(strcmp(lieuTemp,"\n"))
		strcpy(nomLieu , strtok(lieuTemp,"\n"));
	else
		strcpy(nomLieu,"Inconnu");

	while(!stringValide(nomLieu)){
		printf("Lieu de l'évènement : ");
		fgets(lieuTemp, sizeof(lieuTemp), stdin);
		
		if(strcmp(lieuTemp,"\n"))
			strcpy(nomLieu , strtok(lieuTemp,"\n"));
		else
			strcpy(nomLieu,"Inconnu");
	}
	
	return nomLieu;
}

char *entreeDateDebut(){
	char *dateDebut = (char *)malloc(50*sizeof(char));	
	char dateDebTemp[50];

	printf("Date de début de l'évènement (format dd/mm/yyyy): ");
	fgets(dateDebTemp, sizeof(dateDebTemp), stdin);

	if(strcmp(dateDebTemp,"\n"))
		strcpy(dateDebut , strtok(dateDebTemp,"\n"));
	else
		strcpy(dateDebut , "Inconnue");

	while(!formatDateValide(dateDebut)){
		printf("Date de début de l'évènement (format dd/mm/yyyy): ");
		fgets(dateDebTemp, sizeof(dateDebTemp), stdin);
		
		if(strcmp(dateDebTemp,"\n"))
			strcpy(dateDebut , strtok(dateDebTemp,"\n"));
		else
			strcpy(dateDebut , "Inconnue");
	}

	return dateDebut;
}

char *entreeHeureDebut(){
	char *heureDebut = (char *)malloc(50*sizeof(char));
	char heureDebTemp[50];

	printf("Heure de début de l'évènement (format HH:MM): ");
	fgets(heureDebTemp, sizeof(heureDebTemp), stdin);

	if(strcmp(heureDebTemp,"\n"))
		strcpy(heureDebut , strtok(heureDebTemp,"\n"));
	else
		strcpy(heureDebut , "Inconnue");
	
	while(!formatHeureValide(heureDebut)){
		printf("Heure de début de l'évènement (format HH:MM): ");
		fgets(heureDebTemp, sizeof(heureDebTemp), stdin);

		if(strcmp(heureDebTemp,"\n"))
			strcpy(heureDebut , strtok(heureDebTemp,"\n"));
		else
			strcpy(heureDebut , "Inconnue");
	}

	return heureDebut;
}

char *entreeDateFin(){
	char *dateFin = (char *)malloc(50*sizeof(char));
	char dateFinTemp[50];

	printf("Date de fin de l'évènement (format dd/mm/yyyy): ");
	fgets(dateFinTemp, sizeof(dateFinTemp), stdin);

	if(strcmp(dateFinTemp,"\n"))
		strcpy(dateFin , strtok(dateFinTemp,"\n"));
	else
		strcpy(dateFin , "Inconnue");
	
	while(!formatDateValide(dateFin)){
		printf("Date de fin de l'évènement (format dd/mm/yyyy): ");
		fgets(dateFinTemp, sizeof(dateFinTemp), stdin);
		
		if(strcmp(dateFinTemp,"\n"))
			strcpy(dateFin , strtok(dateFinTemp,"\n"));
		else
			strcpy(dateFin , "Inconnue");
	}
	
	return dateFin;
}

char *entreeHeureFin(){
	char *heureFin = (char *)malloc(50*sizeof(char));
	char heureFinTemp[50];

	printf("Heure de fin de l'évènement (format HH:MM): ");
	fgets(heureFinTemp, sizeof(heureFinTemp), stdin);

	if(strcmp(heureFinTemp,"\n"))
		strcpy(heureFin , strtok(heureFinTemp,"\n"));
	else
		strcpy(heureFin , "Inconnue");
	
	while(!formatHeureValide(heureFin)){
		printf("Heure de fin de l'évènement (format HH:MM): ");
		fgets(heureFinTemp, sizeof(heureFinTemp), stdin);

		if(strcmp(heureFinTemp,"\n"))
			strcpy(heureFin , strtok(heureFinTemp,"\n"));
		else
			strcpy(heureFin , "Inconnue");
	}

	return heureFin;
}

