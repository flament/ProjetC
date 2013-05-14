#include <stdio.h>
#include <stdlib.h>
#include "Agenda.h"
#include <string.h>

char *entreeNomP(){
	char *nom = (char *)malloc(101*sizeof(char));
	char nomTemp[101];

	printf("Nom du participant:");
	fgets(nomTemp, sizeof(nomTemp), stdin);

	if(strcmp(nomTemp,"\n"))
		strcpy(nom , strtok(nomTemp,"\n"));
	else
		strcpy(nom , "Inconnu");

	return nom;
}

char *entreePrenomP(){
	char *prenom = (char *)malloc(101*sizeof(char));
	char prenomTemp[101];

	printf("Prénom du participant:");
	fgets(prenomTemp, sizeof(prenomTemp), stdin);

	if(strcmp(prenomTemp,"\n"))
		strcpy(prenom ,strtok(prenomTemp,"\n"));
	else
		strcpy(prenom , "Inconnu");

	return prenom;
}

char *entreeEmailP(){
	char *email = (char *)malloc(101*sizeof(char));
	char emailTemp[101];

	printf("Email du participant:");
	fgets(emailTemp, sizeof(emailTemp), stdin);

	if(strcmp(emailTemp,"\n"))
		strcpy(email,strtok(emailTemp,"\n"));
	else
		strcpy(email , "Inconnu");
	
	while(!emailValide(email)){
		printf("Email du participant: ");
		fgets(emailTemp, sizeof(emailTemp), stdin);

		if(strcmp(emailTemp,"\n"))
			strcpy(email,strtok(emailTemp,"\n"));
		else
			strcpy(email , "Inconnu");
	}

	return email;
}
