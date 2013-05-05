#include <stdio.h>
#include <stdlib.h>
#include "Agenda.h"
#include <string.h>

PERSONNE *tetePers = NULL;

PERSONNE *ajouterParticipant(){
	PERSONNE *pers = (PERSONNE *)malloc(sizeof(PERSONNE));
	char *prenom, *nom, *email;
	char prenomTemp[80], nomTemp[80],emailTemp[80];
	/* mdp fct */
	printf("Nom :");
	fgets(nomTemp, sizeof(nomTemp), stdin);
	nom = strtok(nomTemp,"\n");
	
	printf("Prénom :");
	fgets(prenomTemp, sizeof(prenomTemp), stdin);
	prenom = strtok(prenomTemp,"\n");
	
	printf("Email :");
	fgets(emailTemp, sizeof(emailTemp), stdin);
	email = strtok(emailTemp,"\n");
	
	while(!emailValide(email)){
		printf("Email: ");
		fgets(emailTemp, sizeof(emailTemp), stdin);
		email = strtok(emailTemp,"\n");
	}
	strcpy(pers->nom,nom);
	strcpy(pers->prenom,prenom);
	strcpy(pers->email,email);
	
	pers->suivant = tetePers;
	tetePers = pers;
	return tetePers;
}

PERSONNE *rechercherParticipant(char email[100]){
	PERSONNE *temp = tetePers->suivant;
	PERSONNE *res = (PERSONNE *)malloc(sizeof(PERSONNE));
	res = NULL;
	int reussi = 0;
	
	if(!strcmp(tetePers->email, email)){
		res = tetePers;
		reussi = 1;
	}

	while(temp != NULL && reussi == 0){
		if(!strcmp(temp->email,email)){
				reussi = 1;
				res = temp;
		}
		temp = temp->suivant;
	}
	return res;
}

void supprimerParticipant(char email[100]){
	PERSONNE *p = rechercherParticipant(email);
	PERSONNE* temp = tetePers;
	if(p != NULL){
		if(tetePers == p)
			tetePers = tetePers->suivant;
		else{
			while(temp->suivant != p){ 
				temp = temp->suivant;
			}
			if(temp->suivant->suivant !=NULL)
				temp->suivant = temp->suivant->suivant;
			else
				temp->suivant = NULL;
		}
	}else
		printf("\nParticipant inexistant\n\n");
}


void modifierParticipant(char email[100]){
	PERSONNE *p = rechercherParticipant(email);
	char *modifPrenom, *modifNom, *modifEmail;
	char prenomTemp[80], nomTemp[80],emailTemp[80];
	int modifier = 0, exit = 0;

	if(p != NULL){
		while(!exit){
			printf("Que voulez-vous modifier ?\n1) le nom\t2)le prénom\t3)l'email\t 4)Quiter\n");
			scanf("%1d",&modifier);
			getchar();

			switch(modifier){
				case 1 :
					printf("Quel nom voulez vous donner ?");
					fgets(nomTemp, sizeof(nomTemp), stdin);
					modifNom = strtok(nomTemp,"\n");
					strcpy(p->nom,modifNom);
					break;
				case 2 :
					printf("Quel prénom voulez vous donner ?");
					fgets(prenomTemp, sizeof(prenomTemp), stdin);
					modifPrenom = strtok(prenomTemp,"\n");
					strcpy(p->prenom,modifPrenom);
					break;
				case 3 :
					printf("Quel est le nouvel email ?");
					fgets(emailTemp, sizeof(emailTemp), stdin);
					modifEmail = strtok(emailTemp,"\n");
					
					while(!emailValide(modifEmail)){
						printf("Quel est le nouvel email ?");
						fgets(emailTemp, sizeof(emailTemp), stdin);
						modifEmail = strtok(emailTemp,"\n");
					}
					strcpy(p->email,modifEmail);
					break;		
				case 4 :
					exit = 1;
					break;
				default :
					printf("Ceci n'est pas un choix valide, veuillez entrer un choix valide");
			}
		}
	}else
		printf("Participant inexistant");
}

char *afficherParticipants(){
	char *res = (char*)malloc(sizeof(char));
	char nb[1],nomTemp[100],prenomTemp[100],emailTemp[100];
	PERSONNE *temp = tetePers->suivant;
	int count = 1;
	
	strcpy(res,"1)");
	strcat(res,tetePers->nom);
	strcat(res,"  ");
	strcat(res,tetePers->prenom);
	strcat(res,"  (");
	strcat(res,tetePers->email);
	strcat(res,")\n");	
	
	while(temp != NULL){
		count++;
		sprintf(nb,"%d",count);
		strcat(res,nb);
		strcat(res,")");
		strcpy(nomTemp,temp->nom);
		strcat(res,nomTemp);
		strcat(res, "  ");
		strcpy(prenomTemp,temp->prenom);
		strcat(res,prenomTemp);
		strcat(res, "  (");
		strcpy(emailTemp,temp->email);
		strcat(res,emailTemp);
		strcat(res,")\n");
		temp = temp->suivant;
	}
	return res;
}

