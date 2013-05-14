#include <stdio.h>
#include <stdlib.h>
#include "Agenda.h"
#include <string.h>

extern EVENEMENT *tete;
extern PERSONNE *teteListePers;

void chargerListePersonnes(char nom[100], char prenom[100], char email[100]){
	PERSONNE *pers = (PERSONNE *)malloc(sizeof(PERSONNE));
	
	strcpy(pers->nom,nom);
	strcpy(pers->prenom,prenom);
	strcpy(pers->email,email);

	pers->suivant = teteListePers;
	teteListePers = pers;
}

void lectureFichierParticipants(char *nomFichier){
	char *m_tP,nomP[100],prenomP[100],emailP[100],ligneP[200],carP;
	int nb1 = 0;
	FILE *f1 = fopen(nomFichier, "r");
	
	if(f1 != NULL){
		carP = fgetc(f1);
		
		while(carP != EOF){
			while (carP != '\n'){
				ligneP[nb1]=carP;
				nb1++;
				carP=fgetc(f1);
			}
			ligneP[nb1]='\0';
					
			if(strstr(ligneP, "Nom du participant") != NULL){
				m_tP = strtok(ligneP,":");
				strcpy(nomP , &ligneP[strlen(m_tP)+2]);
			}else if(strstr(ligneP, "Prénom du participant") != NULL){
				m_tP = strtok(ligneP,":");
				strcpy(prenomP , &ligneP[strlen(m_tP)+2]);
			}else if(strstr(ligneP, "Email du participant") != NULL){
				m_tP = strtok(ligneP,":");
				strcpy(emailP ,&ligneP[strlen(m_tP)+2]);
			}else if(strstr(ligneP, "-------------------------------") != NULL){
				chargerListePersonnes(nomP,prenomP,emailP);
			}
			nb1 = 0;
			carP = fgetc(f1); 
		}
		fclose(f1);
	}else
		printf("Fichier contenant les participants introuvable\n");
}

void chargerEvenement(char nom[100], char lieu[100], char desc[200], char dateDebut[50], char heureDebut[50], char dateFin[50], char heureFin[50],PERSONNE *p){
	EVENEMENT *e = (EVENEMENT *)malloc(sizeof(EVENEMENT));
	
	strcpy(e->nom,nom);
	strcpy(e->description,desc);
	strcpy(e->nomLieu,lieu);
	e->dateDebut = convertirStringToDate(dateDebut,heureDebut);	
	e->dateFin = convertirStringToDate(dateFin,heureFin);	
	e->participants = p;
	e->suivant = tete;
	tete = e;	
}

void lectureFichierEvenement(char *nomFichier){
	char *m_t,nom[100],lieu[100],desc[200],dateDeb[10],dateFin[10],heureDeb[5],heureFin[5],*participant,ligne[350],car;
	PERSONNE *temp;	
	PERSONNE *p = (PERSONNE *)malloc(sizeof(PERSONNE));
	p = NULL;
	int nb = 0,exit = 1;
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
					
			if(strstr(ligne, "Nom de l'événement") != NULL){
				m_t = strtok(ligne,":");
				strcpy(nom , &ligne[strlen(m_t)+2]);
			}else if(strstr(ligne, "Nom du lieu de l'événement") != NULL){
				m_t = strtok(ligne,":");
				strcpy(lieu , &ligne[strlen(m_t)+2]);
			}else if(strstr(ligne, "Description de l'événement") != NULL){
				m_t = strtok(ligne,":");
				strcpy(desc , &ligne[strlen(m_t)+2]);
			}else if(strstr(ligne, "Date de début de l'événement") != NULL){
				m_t = strtok(ligne,":");
				strcpy(dateDeb , &ligne[strlen(m_t)+2]);
			}else if(strstr(ligne, "Heure de début de l'événement") != NULL){
				m_t = strtok(ligne,":");
				strcpy(heureDeb , &ligne[strlen(m_t)+2]);
			}else if(strstr(ligne, "Date de fin de l'événement") != NULL){
				m_t = strtok(ligne,":");
				strcpy(dateFin , &ligne[strlen(m_t)+2]);
			}else if(strstr(ligne, "Heure de fin de l'événement") != NULL){
				m_t = strtok(ligne,":");
				strcpy(heureFin , &ligne[strlen(m_t)+2]);
			}else if(strstr(ligne, "Liste des participants de l'événement") != NULL){
				
				while(exit){											
					nb = 0;
					car = fgetc(f1); 
					while (car != '\n'){
						ligne[nb]=car;
						nb++;
						car=fgetc(f1);
					}
					ligne[nb]='\0';
					
					if(strstr(ligne, "-------------------------------") != NULL)
						exit = 0;
					else{
						m_t = strtok(ligne,")");
						participant = &ligne[strlen(m_t)+2];
						temp = testPersonneDejaExistente(participant);
						
						if(p != NULL){
							temp->suivant = p;
							p = temp;
						}else
							p = temp;

					}
				}
			}
			
		 if(strstr(ligne, "-------------------------------") != NULL){
				chargerEvenement(nom,lieu,desc,dateDeb,heureDeb,dateFin,heureFin,p);
				p = NULL;
			}
			nb = 0;
			exit = 1;
			car = fgetc(f1); 
		}
		fclose(f1);
		/*free(p); free(temp);*/
	}else
		printf("Fichier .txt contenant les événements introuvable \n");
}

void charger(char *nomFichier){
	char *temp = (char*)malloc((strlen(nomFichier)+1)*sizeof(char));
	char *part = (char*)malloc((strlen(nomFichier)+14)*sizeof(char));
	strcpy(temp,nomFichier);
	part = strtok(nomFichier,".");
	strcat(part,"_Participants.txt");

	lectureFichierParticipants(part);
	lectureFichierEvenement(temp);
}


