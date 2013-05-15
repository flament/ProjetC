#include <stdio.h>
#include <stdlib.h>
#include "Agenda.h"
#include <string.h>

/*liste chaînée contenant les événements*/
EVENEMENT *tete = NULL;

/*ajoute un événement*/
void ajouterEvenement(){
	razTetePersonne();	

	EVENEMENT *e = (EVENEMENT *)malloc(sizeof(EVENEMENT));
	PERSONNE * p = (PERSONNE *)malloc(sizeof(PERSONNE));
	p = NULL;
	int participant, exit = 0, choix;
	char *dateDebut,*dateFin,*heureDebut,*heureFin;
	
	strcpy(e->nom,entreeNom());
	strcpy(e->description,entreeDescription());
	strcpy(e->nomLieu,entreeLieu());
	dateDebut = entreeDateDebut();	
	heureDebut = entreeHeureDebut();
	dateFin = entreeDateFin();
	heureFin = entreeHeureFin();
	
	/*vérification des dates+heures et une boucle demandant de changer l'une des deux si c'est pas bon, et boucle jusqu'à ce que ce soit correct*/
	while(!dateFinValide(dateDebut,dateFin,heureDebut,heureFin) || !emplacementDispo(dateDebut,dateFin,heureDebut,heureFin)){
		printf("Que voulez-vous changer ? \n1)la date de début \n2) l'heure de début \n3) la date de fin \n4) l'heure de fin\n");
		choix = 0;
		scanf("%d",&choix);
		getchar();

		switch(choix){
			case 1 :
				dateDebut = entreeDateDebut();
				break;
			case 2 :
				heureDebut = entreeHeureDebut();
				break;
			case 3 :
				dateFin = entreeDateFin();
				break;
			case 4 :
				heureFin = entreeHeureFin();
				break;
			default :
				printf("Cette valeur n'est pas valide, veuillez rentrer une valeur valide");					
		}									
	}
	
	while(!exit){
		printf("Voulez-vous ajouter un participant ?\n1) oui\t2) non\n");
		fflush(stdin);
		participant = 0;
		scanf("%d",&participant);
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
		
	e->dateDebut = convertirStringToDate(dateDebut,heureDebut);	
	e->dateFin = convertirStringToDate(dateFin,heureFin);	
	e->participants = p;	
	
	e->suivant = tete;
	tete = e;
}


