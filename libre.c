#include <stdio.h>
#include <stdlib.h>
#include "Agenda.h"
#include <string.h>

extern EVENEMENT *tete;

void libre(char date[10]){
	EVENEMENT *temp;
	temp = rechercherParJour(date);
	int *tableDebutHeure, *tableDebutMinute, *tableFinHeure, *tableFinMinute;
	int i,longueurTable;
	
	if(temp != NULL){
		/*Longueur des tableaux*/
		i = 0;
		temp = rechercherParJour(date);
		while(temp != NULL){
			i++;
			temp = temp->suivant;
		}
		longueurTable = i-1;

		tableDebutHeure = (int *)malloc(longueurTable*sizeof(int));
		tableDebutMinute = (int *)malloc(longueurTable*sizeof(int));
		tableFinHeure = (int *)malloc(longueurTable*sizeof(int));
		tableFinMinute = (int *)malloc(longueurTable*sizeof(int));
	
		/*Remplissage des tblx dhoraires en h et m*/
		while(temp != NULL){
			tableDebutHeure[i] = temp->dateDebut->tm_hour;
			tableDebutMinute[i] = temp->dateDebut->tm_min;
			tableFinHeure[i] = temp->dateFin->tm_hour;
			tableFinMinute[i] = temp->dateFin->tm_min;
			i++;
			temp = temp->suivant;
		}
		
		
		
		/*Tri des tableaux*/
		
		triTableau(tableDebutHeure,longueurTable);
		triTableau(tableDebutMinute,longueurTable);
		triTableau(tableFinHeure,longueurTable);
		triTableau(tableFinMinute,longueurTable);
		
		printf("\nles crénaux libres sont :\n");
		/*réinitialisation de temp*/
		temp = rechercherParJour(date);
		i = 0;
		int init = 0;
		
		/*Affichage des crenaux libres*/
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

EVENEMENT *rechercherParJour(char dateDebutEvenement[10]){
	EVENEMENT *temp = tete;
	EVENEMENT *res = (EVENEMENT *)malloc(sizeof(EVENEMENT));
	res = NULL;
	int indicTete = 0,i = 1;
	char date[256], dateTemp[256]; 
	strftime(date, sizeof(date), "%d/%m/%Y", tete->dateDebut);
	
	
	if(temp != NULL){
		strftime(dateTemp, sizeof(dateTemp), "%d/%m/%Y", temp->dateDebut); 
	}

	if(!strcmp(date,dateDebutEvenement)){
			res = tete;
			indicTete = 1;
	}
		
	while(temp != NULL ){
		
		if(strcmp(dateTemp,dateDebutEvenement)){
			if(indicTete == 0){
				res = temp;
				indicTete = 1;
			}
			else{
				res->suivant = res; 
				res = temp;
			}
		}
		
		i++; 
		temp = temp->suivant;
		
		if(temp != NULL)
			strftime(dateTemp, sizeof(dateTemp), "%d/%m/%Y", temp->dateDebut);		
	}
	
	if(indicTete == 0)
		printf("Il n'y a aucun évènement ce jour là, tous les créneaux sont libres\n");
	
	return res;
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

