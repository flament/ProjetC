#include <stdio.h>
#include <stdlib.h>
#include "Agenda.h"
#include <string.h>

PERSONNE *tetePers = NULL;
PERSONNE *teteListePers = NULL;

void razTetePersonne(){
	tetePers = NULL;
}

void recuperationParticipantsEvt(PERSONNE *p){
	tetePers = p;
}

PERSONNE *ajouterParticipant(){
	PERSONNE *pers = (PERSONNE *)malloc(sizeof(PERSONNE));
	/*temp permettra d'insérer la nouvelle Personne dans la liste de tous les participants de tous les évènements*/
	PERSONNE * temp = (PERSONNE *)malloc(sizeof(PERSONNE));
	PERSONNE *test = (PERSONNE *)malloc(sizeof(PERSONNE));
	test = NULL;

	char *prenom, *nom, *email;
	char prenomTemp[101], nomTemp[101],emailTemp[101];
	/* mdp fct */
	printf("Nom :");
	fgets(nomTemp, sizeof(nomTemp), stdin);
	if(strcmp(nomTemp,"\n"))
		nom = strtok(nomTemp,"\n");
	else
		nom = "Inconnu ";
	
	printf("Prénom :");
	fgets(prenomTemp, sizeof(prenomTemp), stdin);
	if(strcmp(prenomTemp,"\n"))
		prenom = strtok(prenomTemp,"\n");
	else
		prenom = "Inconnu ";
		
	printf("Email :");
	fgets(emailTemp, sizeof(emailTemp), stdin);
	if(strcmp(emailTemp,"\n"))
		email = strtok(emailTemp,"\n");
	else
		email = "Inconnu ";
	
	while(!emailValide(email)){
		printf("Email: ");
		fgets(emailTemp, sizeof(emailTemp), stdin);
		if(strcmp(emailTemp,"\n"))
			email = strtok(emailTemp,"\n");
		else
			email = "Inconnu ";
	}
	
	if(tetePers != NULL)
		test = rechercherParticipant(email);

	if(test != NULL){
		printf("Participant déjà présent!\n");
	}else{
		if(teteListePers != NULL)
			test = testPersonneDejaExistente(email);

		/*email existe mais ne correspond pas au nom et prénom rentrés*/
		if(test != NULL && (strcmp(test->nom,nom) || strcmp(test->prenom,prenom)))
			printf("Erreur, email déjà utilisé par quelqu'un d'autre!\n");
		else if(test != NULL){
			strcpy(pers->nom,nom);
			strcpy(pers->prenom,prenom);
			strcpy(pers->email,email);	
			pers->suivant = tetePers;
			tetePers = pers;
		}else{
			strcpy(pers->nom,nom);
			strcpy(pers->prenom,prenom);
			strcpy(pers->email,email);	
			pers->suivant = tetePers;
			tetePers = pers;		
			
			strcpy(temp->nom,pers->nom);
			strcpy(temp->prenom,pers->prenom);
			strcpy(temp->email,pers->email);
			temp->suivant = teteListePers;
			teteListePers = temp;
		}		
	}
	return tetePers;
}

PERSONNE *testPersonneDejaExistente(char email[100]){
	PERSONNE *temp = teteListePers;
	PERSONNE *res = (PERSONNE *)malloc(sizeof(PERSONNE));
	res = NULL;
	int reussi = 0;
	
	/*if(!strcmp(teteListePers->email, email)){
		res = teteListePers;
		reussi = 1;
	}*/

	while(temp != NULL && reussi == 0){
		if(!strcmp(temp->email,email)){
				reussi = 1;
				res = temp;
		}
		temp = temp->suivant;
	}
	return res;
}

PERSONNE *rechercherParticipant(char email[100]){
	PERSONNE *temp = tetePers;
	PERSONNE *res = (PERSONNE *)malloc(sizeof(PERSONNE));
	res = NULL;
	int reussi = 0;
	
	/*if(!strcmp(tetePers->email, email)){
		res = tetePers;
		reussi = 1;
	}*/

	while(temp != NULL && reussi == 0){
		if(!strcmp(temp->email,email)){
				reussi = 1;
				res = temp;
		}
		temp = temp->suivant;
	}
	return res;
}

/*Suprime un participant d'un evt donné*/
PERSONNE * supprimerParticipantEvt(char email[100]){
	PERSONNE *p = rechercherParticipant(email);
	PERSONNE* temp = tetePers;
	if(p != NULL){
		if(temp == p)
			temp = temp->suivant;
		else{
			while(temp->suivant != p){ 
				temp = temp->suivant;
			}
			if(temp->suivant->suivant !=NULL)
				temp->suivant = temp->suivant->suivant;
			else
				temp->suivant = NULL;
		}
		free(p);
	}else
		printf("\nParticipant inexistant\n\n");
		
	
	return temp;
}


void modifierParticipant(char email[100]){
	PERSONNE *p = rechercherParticipant(email);
	PERSONNE *test = testPersonneDejaExistente(email);

	char *modifPrenom, *modifNom, *modifEmail;
	char prenomTemp[101], nomTemp[101],emailTemp[101];
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
					
					if(strcmp(nomTemp,"\n"))
						modifNom = strtok(nomTemp,"\n");
					else
						modifNom = "Inconnu ";
					
					strcpy(p->nom,modifNom);
					strcpy(test->nom,modifNom);
					break;
				case 2 :
					printf("Quel prénom voulez vous donner ?");
					fgets(prenomTemp, sizeof(prenomTemp), stdin);
					
					if(strcmp(prenomTemp,"\n"))
						modifPrenom = strtok(prenomTemp,"\n");
					else
						modifPrenom = "Inconnu ";
					
					strcpy(p->prenom,modifPrenom);
					strcpy(test->prenom,modifPrenom);
					break;
				case 3 :
					printf("Quel est le nouvel email ?");
					fgets(emailTemp, sizeof(emailTemp), stdin);
					
					if(strcmp(emailTemp,"\n"))
						modifEmail = strtok(emailTemp,"\n");
					else
						modifEmail = "Inconnu ";
									
					while(!emailValide(modifEmail)){
						printf("Quel est le nouvel email ?");
						fgets(emailTemp, sizeof(emailTemp), stdin);
						
						if(strcmp(emailTemp,"\n"))
							modifEmail = strtok(emailTemp,"\n");
						else
							modifEmail = "Inconnu ";
					}

					/*email existe mais ne correspond pas au nom et prénom rentrés*/
					if(test != NULL && (strcmp(test->nom,p->nom) || strcmp(test->prenom,p->prenom)))
						printf("Erreur, email déjà utilisé par quelqu'un d'autre!\n");
					else{		
						strcpy(p->email,modifEmail);
						strcpy(test->email,modifEmail);
					}
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

/*Supprime un participant de la liste des inscrits et de la liste des participants des évènements auxquels il était inscrit*/
void supprimerParticipant(char email[100]){



}

char *afficherParticipants(){
	char *res = (char*)malloc(310*sizeof(char));
	char nb[1],nomTemp[100],prenomTemp[100],emailTemp[100];
	PERSONNE *temp = tetePers->suivant;
	int count = 1;
	int taille;

	strcpy(res,"1)");
	strcat(res,tetePers->nom);
	strcat(res,"  ");
	strcat(res,tetePers->prenom);
	strcat(res,"  (");
	strcat(res,tetePers->email);
	strcat(res,")\n");	
	taille = strlen(res);

	while(temp != NULL){
		res = realloc(res, (taille+310)*sizeof(char)); 
		taille = strlen(res); 
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

