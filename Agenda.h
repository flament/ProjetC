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

struct Theme{
    char nom[100];
	 struct Theme *suivant;
};
typedef struct Theme THEME;

struct Personne{
    char nom[100];
    char prenom[100];
    char email[100];
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


void ajouterTheme();
void supprimerTheme(char nom[100]);
void modifierTheme(char nom[100]);
THEME *rechercherTheme(char nom[100]);
char *afficherThemes();

void libererEvenement(EVENEMENT* e);
void libererPersonne(PERSONNE* p);
void libererTheme(THEME* t);

int formatDateValide(char date[25]);
int formatHeureValide(char h[50]);
int stringValide(char *s);
int dateFinValide(char dateDeb[10],char dateFin[10], char heureDeb[5], char heureFin[5]);
int emailValide(char email[100]);
int nomFichierValide(char *nom);
int chargementValide(char *nom, char *theme);

void chargerListePersonnes(char *nom, char *prenom, char *email);
void lectureFichierParticipants(char *nomFichier);
void chargerEvenement(char nom[100], char lieu[100], char desc[200], char dateDebut[50], char heureDebut[50], char dateFin[50], char heureFin[50],PERSONNE *p);
void lectureFichierEvenement(char *nomFichier);
void charger(char *nomFichier);
void lectureFichierThemes(char *nomFichier);
void chargerTheme(char *nom);
void confirmation(char *nom);

void ecrireUnEvenement(FILE* c,EVENEMENT *e);
void ecritureCSV(char *fichier);
void enregistrerFormatTxt(char *fichier);
void enregistrerParticipants(char *fichier);
void enregistrer(char *nomFichier, char nomTheme[100]);
void enregistrerTheme(char *nomFichier);


char *entreeNomP();
char *entreePrenomP();
char *entreeEmailP();

PERSONNE *ajouterParticipant();
PERSONNE *rechercherParticipant(char email[100]);
PERSONNE *supprimerParticipantEvt(char email[100]);
PERSONNE *modifierParticipant(char email[100]);
char *afficherParticipants();
void recuperationParticipantsEvt(PERSONNE *p);
void razTetePersonne();
PERSONNE *testPersonneDejaExistente(char email[100]);

struct tm* convertirStringToDate(char s[50], char h[50]);
int emplacementDispo(char dateDeb[10],char dateFin[10], char heureDeb[5], char heureFin[5]);
void libre(char date[10]);
EVENEMENT *rechercherParJour(char dateDebutEvenement[10]);
void triTableau(int *t,int n);

char *entreeNom();
char *entreeDescription();
char *entreeLieu();
char *entreeDateDebut();
char *entreeHeureDebut();
char *entreeDateFin();
char *entreeHeureFin();
EVENEMENT *rechercherEvenement(char nomEvenement[100],char dateDebutEvenement[10],char heureDeb[5]);
void supprimerEvenement(char nomEvenement[100],char dateDebutEvenement[10],char heureDeb[5]);
void modifierEvenement(char nomEvenement[100],char dateDebutEvenement[10],char heureDeb[5]);
void ajouterEvenement();
char *afficherEvenements();
#endif	/* AGENDA_H */

