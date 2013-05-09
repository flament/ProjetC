/* 
 * File:   Agenda.h
 * Author: damien
 *
 * Created on 19 mars 2013, 17:07
 */

#ifndef AGENDA_H
#define	AGENDA_H
#include <time.h>
#include <stdio.h>
#include <string.h>

enum Fonc {eleve,professeur};
typedef enum Fonc Fonction;

struct Personne{
    char nom[100];
    char prenom[100];
    char email[100];
    char mdp[100];
    Fonction fonction;
	 struct Personne *suivant;
};
typedef struct Personne PERSONNE;

struct Evenement{
    char nom[100];
    char nomLieu[100];
    char description[200];
    struct tm* dateDebut;
    struct tm* dateFin; 
    PERSONNE *participants;
	struct Evenement *suivant;
};
typedef struct Evenement EVENEMENT;

int formatDateValide(char date[25]);
int formatHeureValide(char h[50]);
int stringValide(char *s);
int dateFinValide(char dateDeb[10],char dateFin[10], char heureDeb[5], char heureFin[5]);
int emailValide(char email[100]);


void chargerEvenement(char nom[100], char lieu[100], char desc[200], char dateDebut[50], char heureDebut[50], char dateFin[50], char heureFin[50]);
void charger(char *nomFichier);
void ecrireUnEvenement(FILE* c,EVENEMENT *e);
void ecritureCSV();
void enregistrerFormatTxt();
void enregistrerParticipants();

PERSONNE *ajouterParticipant();
PERSONNE *rechercherParticipant(char email[100]);
void supprimerParticipantEvt(char email[100]);
void modifierParticipant(char email[100]);
char *afficherParticipants();
void recuperationParticipantsEvt(PERSONNE *p);
void razTetePersonne();
PERSONNE *testPersonneDejaExistente(char email[100]);

struct tm* convertirStringToDate(char s[50], char h[50]);
int emplacementDispo(char dateDeb[10],char dateFin[10], char heureDeb[5], char heureFin[5]);

EVENEMENT *rechercher(char nomEvenement[100],char dateDebutEvenement[10]);
void supprimer(char nomEvenement[100],char dateDebutEvenement[10]);
void modifier(char nomEvenement[100],char dateDebutEvenement[10]);
void ajouterEvenement();
#endif	/* AGENDA_H */

