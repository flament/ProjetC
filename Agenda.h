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

struct Tache{
    char *nom;
    time_t deadline;
    /*PERSONNE personne;*/
};
typedef struct Tache TACHE;

struct Personne{
    char *nom;
    char *prenom;
    char *email;
    char *mdp;
    Fonction fonction;
	struct Personne *suivant;
    TACHE taches[] ;
};
typedef struct Personne PERSONNE;

struct Evenement{
    char *nom;
    char *nomLieu;
	int capaciteLieu;
    char *description;
    struct tm* dateDebut;
    struct tm* dateFin; 
    PERSONNE *participants;
	struct Evenement *suivant;
};
typedef struct Evenement EVENEMENT;

int formatDateValide(char date[25]);
int formatHeureValide(char h[50]);
int stringValide(char *s);

#endif	/* AGENDA_H */

