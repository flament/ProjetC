#include <stdio.h>
#include <stdlib.h>
#include "Agenda.h"
#include <string.h>

extern EVENEMENT *tete;

/*indique les créneaux libres d'une journée*/
void libre(char date[10]){
	EVENEMENT *temp;
	EVENEMENT *e= (EVENEMENT *)malloc(sizeof(EVENEMENT));
	temp = rechercherParJour(date);
	e = temp;
	int *tableDebutHeure = (int *)malloc(100*sizeof(int));
	int *tableDebutMinute = (int *)malloc(100*sizeof(int));
	int *tableFinHeure = (int *)malloc(100*sizeof(int));
	int *tableFinMinute = (int *)malloc(100*sizeof(int));
	int i, longueurTable,init;
	
	if(temp != NULL){
		i = 0;
		/*Remplissage des tableaux d'horaires en heures et minutes*/
		while(temp != NULL){
			tableDebutHeure[i] = temp->dateDebut->tm_hour;
			tableDebutMinute[i] = temp->dateDebut->tm_min;
			tableFinHeure[i] = temp->dateFin->tm_hour;
			tableFinMinute[i] = temp->dateFin->tm_min;
			i++;
			temp = temp->suivant;
		}
	
		/*Longueur des tableaux*/
		i = 0;
		temp = e;
		while(temp != NULL){
			i++;
			temp = temp->suivant;
		}
		
		 longueurTable = i-1;
		
		/*Tri des tableaux*/	
		triTableau(tableDebutHeure,longueurTable);
		triTableau(tableDebutMinute,longueurTable);
		triTableau(tableFinHeure,longueurTable);
		triTableau(tableFinMinute,longueurTable);
		
		printf("\nles crénaux libres sont :\n");
		/*réinitialisation de temp*/
		temp = e;
		i = 0;
	   init = 0;
		
		/*Affichage des créneaux libres*/
		while(temp != NULL){
			if((init == 0)){
				if(tableDebutMinute[i] < 10){
					printf("\tde 00h00 à %dh0%d\n",tableDebutHeure[i],tableDebutMinute[i]);
				}
				else{
					printf("\tde 00h00 à %dh%d\n",tableDebutHeure[i],tableDebutMinute[i]);
				}
				init = 1;
			}
			if(temp->suivant != NULL){
				if(tableDebutMinute[i+1] < 10 && !tableFinMinute[i] < 10){
					printf("\tde %dh%d à %dh0%d\n",tableFinHeure[i],tableFinMinute[i],tableDebutHeure[i+1],tableDebutMinute[i+1]);
				}
				else if(tableFinMinute[i] < 10 && !tableDebutMinute[i+1] < 10){
					printf("\tde %dh0%d à %dh%d\n",tableFinHeure[i],tableFinMinute[i],tableDebutHeure[i+1],tableDebutMinute[i+1]);
				}
				else if(tableDebutMinute[i+1] < 10 && tableFinMinute[i] < 10){
					printf("\tde %dh0%d à %dh0%d\n",tableFinHeure[i],tableFinMinute[i],tableDebutHeure[i+1],tableDebutMinute[i+1]);
				}
				else{
					printf("\tde %dh%d à %dh%d\n",tableFinHeure[i],tableFinMinute[i],tableDebutHeure[i+1],tableDebutMinute[i+1]);
				}
			}
			if(temp->suivant == NULL){
				if(tableFinMinute[i] < 10){
					printf("\tde %dh0%d à 23h59\n",tableFinHeure[i],tableFinMinute[i]);
				}
				else{
					printf("\tde %dh%d à 23h59\n",tableFinHeure[i],tableFinMinute[i]);
				}
			}
			
			i++;
			temp = temp->suivant;
		}
	}
}

/*retourne les événements d'une journée*/
EVENEMENT *rechercherParJour(char dateDebutEvenement[10]){
	EVENEMENT *tem = tete;
	EVENEMENT *res1 = (EVENEMENT *)malloc(sizeof(EVENEMENT));
	EVENEMENT *res;
	res1 = NULL;
	res = NULL;
	int indicTete = 0,i = 0;
	char dateTemp[256]; 
	
	
	if(tem != NULL)
		strftime(dateTemp, sizeof(dateTemp), "%d/%m/%Y", tem->dateDebut);

	while(tem != NULL){
		if(!strcmp(dateTemp,dateDebutEvenement)){
			if(indicTete == 0){
				res = tem;
				indicTete = 1;
			}
			else{
				if(res1 != NULL)
					res1->suivant = res1;
				res1 = res;
				res = tem;
			}
		}	
		i++; 
		tem = tem->suivant;

		if(tem != NULL)
			strftime(dateTemp, sizeof(dateTemp), "%d/%m/%Y", tem->dateDebut);		
	}
	
	if(i == 1)
		res1 = res;
	if(indicTete == 0)
		printf("Il n'y a aucun évènement ce jour là, tous les créneaux sont libres\n");
	
	return res1;
}

/*tri d'un tableau dans l'ordre croissant -> table[0] est le plus petit*/
void triTableau(int *t,int n){ 
	int j = 0,tmp = 0, enDesordre = 1;
	while(enDesordre){
		enDesordre = 0; 
		for(j =0; j < n; j++){ 
			if(t[j] > t[j+1]){
				tmp = t[j+1];
				t[j+1] = t[j];
				t[j] = tmp;
				enDesordre = 1;
			}
		}
	}
}

