/* 
 * File:   main.c
 * Author: damien
 *
 * Created on 19 mars 2013, 17:06
 */

#include <stdio.h>
#include <stdlib.h>
#include "Agenda.h"
#include <string.h>

/*vaut mieux mettre strcpy pour les string que = car sinon le string en question n'a pas vraiment de valeur affecté...fucking C*/

extern EVENEMENT *tete;

int main(int argc, char** argv) {
    
	
	char buffer[256], buff2[256];
	
	/*charger("Calendrier.csv");*/
	/*char d[10] = "18/04/2013";
	char d1[10] = "18/04/2013";
	char h[5] = "15:00";
	char h1[5] = "16:00";
	
	ajouterEvenement();
	
	int test = emplacementDispo(d,d1,h,h1);
	printf("%d\n",test);	*/
	/*printf("nom Evt: %s\n",tete->nom);
	printf("nom1 : %s\n",tete->participants->nom);
	printf("prenom: %s\n",tete->participants->prenom);
	printf(",,,,,,,,,,,,,,,,,,,nom2 : %s\n",tete->participants->suivant->nom);
	printf("prenom: %s\n",tete->participants->suivant->prenom);
	modifier("test3","18/04/2013");*/
	
	ajouterEvenement();
	ajouterEvenement();
	ajouterEvenement();
	/*printf("\n\n%s\n",afficherParticipants());*/
	modifier("evt2","18/04/2013");
	printf("\n\n---------------------------------------------------\n");
	modifier("evt1","18/04/2013");
	/*printf("\n\n%s\n",afficherParticipants());*/
	/*ajouterEvenement();
	ajouterEvenement();*/
	/*EVENEMENT *ev = (EVENEMENT *)malloc(sizeof(EVENEMENT));
	ev = rechercher("test3","18/04/2013");
	printf("nom Evt: %s\n",ev->nom);
	printf("nom Lieu: %s\n",ev->nomLieu);
	strftime(buffer, sizeof(buffer), "%d %B %Y", ev->dateDebut);
	printf("%s\n",buffer);
	supprimer("test3","18/04/2013");*/
	/*printf("nom Evt: %s\n",tete->nom);	
	printf("nom Lieu: %s\n",tete->nomLieu);
	printf("Desc Evt: %s\n",tete->description);
	strftime(buffer, sizeof(buffer), "%x %H:%M", tete->dateDebut);
	strftime(buff2, sizeof(buff2), "%x %H:%M", tete->dateFin);
	printf("%s\n",buffer);
	printf("%s\n",buff2);

	printf("nom Evt: %s\n",(tete->suivant)->nom);	
	printf("nom Lieu: %s\n",(tete->suivant)->nomLieu);
	printf("Desc Evt: %s\n",(tete->suivant)->description);
	strftime(buffer, sizeof(buffer), "%x %H:%M", (tete->suivant)->dateDebut);
	strftime(buff2, sizeof(buff2), "%x %H:%M", (tete->suivant)->dateFin);
	printf("%s\n",buffer);
	printf("%s\n",buff2);*/

	ecriture();
    return (EXIT_SUCCESS);	
}

