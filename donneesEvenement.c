#include <stdio.h>
#include <stdlib.h>
#include "Agenda.h"
#include <string.h>

/*retourne le nom de l'événement rentré par l'utilisateur*/
char *entreeNom(){
	char *nom = (char *)malloc(101*sizeof(char));
	char nomTemp[101];
		
	printf("Nom de l'événement : ");	
	fflush(stdin);
	fgets(nomTemp, sizeof(nomTemp), stdin);
	/*Si l'utilisateur ne saisit pas de nom (tape sur Entrée), nom = Nouvel évènement par défaut*/	
	if(strcmp(nomTemp,"\n"))
		strcpy(nom ,strtok(nomTemp,"\n"));
	else
		strcpy(nom , "Nouvel événement ");

	while(!stringValide(nom)){
		printf("Nom de l'événement : ");
		fflush(stdin);
		fgets(nomTemp, sizeof(nomTemp), stdin);
		
		if(strcmp(nomTemp,"\n"))
			strcpy(nom ,strtok(nomTemp,"\n"));
		else
			strcpy(nom , "Nouvel événement ");
	}

	return nom;
}

/*retourne la description de l'événement rentrée par l'utilisateur*/
char *entreeDescription(){
	char *desc = (char *)malloc(201*sizeof(char));
	char descTemp[201];

	printf("Description de l'événement : ");
	fflush(stdin);
	fgets(descTemp, sizeof(descTemp), stdin);
	
	if(strcmp(descTemp,"\n"))
		strcpy(desc , strtok(descTemp,"\n"));
	else
		strcpy(desc , "Inconnue");

	while(!stringValide(desc)){
		printf("Description de l'événement : ");
		fflush(stdin);
		fgets(descTemp, sizeof(descTemp), stdin);
		
		if(strcmp(descTemp,"\n"))
			strcpy(desc , strtok(descTemp,"\n"));
		else
			strcpy(desc , "Inconnue");
	}

	return desc;
}

/*retourne le nom du lieu de l'événement rentré par l'utilisateur*/
char *entreeLieu(){
	char *nomLieu = (char *)malloc(101*sizeof(char));
	char lieuTemp[101];
	
	printf("Lieu de l'événement :");
	fflush(stdin);
	fgets(lieuTemp, sizeof(lieuTemp), stdin);
	
	if(strcmp(lieuTemp,"\n"))
		strcpy(nomLieu , strtok(lieuTemp,"\n"));
	else
		strcpy(nomLieu,"Inconnu");

	while(!stringValide(nomLieu)){
		printf("Lieu de l'événement : ");
		fflush(stdin);
		fgets(lieuTemp, sizeof(lieuTemp), stdin);
		
		if(strcmp(lieuTemp,"\n"))
			strcpy(nomLieu , strtok(lieuTemp,"\n"));
		else
			strcpy(nomLieu,"Inconnu");
	}
	
	return nomLieu;
}

/*retourne la date de début de l'événement rentrée par l'utilisateur*/
char *entreeDateDebut(){
	char *dateDebut = (char *)malloc(50*sizeof(char));	
	char dateDebTemp[50];

	printf("Date de début de l'événement (format dd/mm/yyyy): ");
	fflush(stdin);
	fgets(dateDebTemp, sizeof(dateDebTemp), stdin);

	if(strcmp(dateDebTemp,"\n"))
		strcpy(dateDebut , strtok(dateDebTemp,"\n"));
	else
		strcpy(dateDebut , "Inconnue");

	while(!formatDateValide(dateDebut)){
		printf("Date de début de l'événement (format dd/mm/yyyy): ");
		fflush(stdin);
		fgets(dateDebTemp, sizeof(dateDebTemp), stdin);
		
		if(strcmp(dateDebTemp,"\n"))
			strcpy(dateDebut , strtok(dateDebTemp,"\n"));
		else
			strcpy(dateDebut , "Inconnue");
	}

	return dateDebut;
}

/*retourne l'horaire de début de l'événement rentré par l'utilisateur*/
char *entreeHeureDebut(){
	char *heureDebut = (char *)malloc(50*sizeof(char));
	char heureDebTemp[50];

	printf("Heure de début de l'événement (format HH:MM): ");
	fflush(stdin);
	fgets(heureDebTemp, sizeof(heureDebTemp), stdin);

	if(strcmp(heureDebTemp,"\n"))
		strcpy(heureDebut , strtok(heureDebTemp,"\n"));
	else
		strcpy(heureDebut , "Inconnue");
	
	while(!formatHeureValide(heureDebut)){
		printf("Heure de début de l'événement (format HH:MM): ");
		fflush(stdin);
		fgets(heureDebTemp, sizeof(heureDebTemp), stdin);

		if(strcmp(heureDebTemp,"\n"))
			strcpy(heureDebut , strtok(heureDebTemp,"\n"));
		else
			strcpy(heureDebut , "Inconnue");
	}

	return heureDebut;
}

/*retourne la date de fin de l'événement rentrée par l'utilisateur*/
char *entreeDateFin(){
	char *dateFin = (char *)malloc(50*sizeof(char));
	char dateFinTemp[50];

	printf("Date de fin de l'événement (format dd/mm/yyyy): ");
	fflush(stdin);
	fgets(dateFinTemp, sizeof(dateFinTemp), stdin);

	if(strcmp(dateFinTemp,"\n"))
		strcpy(dateFin , strtok(dateFinTemp,"\n"));
	else
		strcpy(dateFin , "Inconnue");
	
	while(!formatDateValide(dateFin)){
		printf("Date de fin de l'événement (format dd/mm/yyyy): ");
		fflush(stdin);
		fgets(dateFinTemp, sizeof(dateFinTemp), stdin);
		
		if(strcmp(dateFinTemp,"\n"))
			strcpy(dateFin , strtok(dateFinTemp,"\n"));
		else
			strcpy(dateFin , "Inconnue");
	}
	
	return dateFin;
}

/*retourne l'horaire de fin de l'événement rentré par l'utilisateur*/
char *entreeHeureFin(){
	char *heureFin = (char *)malloc(50*sizeof(char));
	char heureFinTemp[50];

	printf("Heure de fin de l'événement (format HH:MM): ");
	fflush(stdin);
	fgets(heureFinTemp, sizeof(heureFinTemp), stdin);

	if(strcmp(heureFinTemp,"\n"))
		strcpy(heureFin , strtok(heureFinTemp,"\n"));
	else
		strcpy(heureFin , "Inconnue");
	
	while(!formatHeureValide(heureFin)){
		printf("Heure de fin de l'événement (format HH:MM): ");
		fflush(stdin);
		fgets(heureFinTemp, sizeof(heureFinTemp), stdin);

		if(strcmp(heureFinTemp,"\n"))
			strcpy(heureFin , strtok(heureFinTemp,"\n"));
		else
			strcpy(heureFin , "Inconnue");
	}

	return heureFin;
}

