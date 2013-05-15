#include <stdio.h>
#include <stdlib.h>
#include "Agenda.h"
#include <string.h>

extern EVENEMENT *tete;

void modifierEvenement(char nomEvenement[100],char dateDebutEvenement[10],char heureDeb[5]){
	EVENEMENT *e = rechercherEvenement(nomEvenement,dateDebutEvenement,heureDeb);
	PERSONNE * p = (PERSONNE *)malloc(sizeof(PERSONNE));
	p = NULL;
	int modifier = 0,participant = 0, exit = 0, exit2;
	char *modifDateDeb,*modifDateFin,*modifHeureDeb,*modifHeureFin;
	char heureD[256],heureF[256],dateD[256],dateF[256],supprEmail[101];

	if(e == NULL){
		printf("Evénement inexistant\n");	
		return;
	}

	razTetePersonne();
	recuperationParticipantsEvt(e->participants);

	while(!exit){
		exit2 = 0;
		printf("Que voulez-vous modifier ?\n1) le nom\t2)le lieu\t3)la date de début\t4)l'heure de début\t5)la date de fin\t6)l'heure de fin\t7)la description\t8)les personnes participantes\n9)Quitter\n");
		scanf("%d",&modifier);
		getchar();
		
		switch(modifier){
			case 1 :
				strcpy(e->nom,entreeNom());
				break;
			case 2 :
				strcpy(e->nomLieu,entreeLieu());
				break;
			case 3 :
				modifDateDeb = entreeDateDebut();			
				strftime(heureD, sizeof(heureD), "%H:%M", e->dateDebut);
				strftime(heureF, sizeof(heureF), "%H:%M", e->dateFin);
				strftime(dateF, sizeof(dateF), "%d/%m/%Y", e->dateFin);

				if(dateFinValide(modifDateDeb,dateF,heureD,heureF) && emplacementDispo(modifDateDeb,dateF,heureD,heureF))
					e->dateDebut = convertirStringToDate(modifDateDeb,heureD);
				else
					printf("Modification non prise en compte\n");
				
				break;
			case 4 :
				modifHeureDeb = entreeHeureDebut();			
				strftime(dateD, sizeof(dateD), "%d/%m/%Y", e->dateDebut);
				strftime(heureF, sizeof(heureF), "%H:%M", e->dateFin);
				strftime(dateF, sizeof(dateF), "%d/%m/%Y", e->dateFin);
				
				if(dateFinValide(dateD,dateF,modifHeureDeb,heureF))
					e->dateDebut = convertirStringToDate(dateD,modifHeureDeb);
				else
					printf("Modification non prise en compte\n");
				break;
			case 5 :
				modifDateFin = entreeDateFin();
				strftime(heureF, sizeof(heureF), "%H:%M", e->dateFin);
				strftime(dateD, sizeof(dateD), "%d/%m/%Y", e->dateDebut);
				strftime(heureD, sizeof(heureD), "%H:%M", e->dateDebut);

				if(dateFinValide(dateD,modifDateFin,heureD,heureF) && emplacementDispo(dateD,modifDateFin,heureD,heureF))		
					e->dateFin = convertirStringToDate(modifDateFin,heureF);
				else
					printf("Modification non prise en compte\n");

				break;
			case 6 :
				modifHeureFin = entreeHeureFin();
				strftime(dateF, sizeof(dateF), "%d/%m/%Y", e->dateFin);	
				strftime(dateD, sizeof(dateD), "%d/%m/%Y", e->dateDebut);
				strftime(heureD, sizeof(heureD), "%H:%M", e->dateDebut);
		
				if(dateFinValide(dateD,dateF,heureD,modifHeureFin))
					e->dateFin = convertirStringToDate(dateF,modifHeureFin);
				else
					printf("Modification non prise en compte\n");
				break;
			case 7 :
				strcpy(e->description,entreeDescription());
				break;
			case 8 :
				while(!exit2){
					printf("Voulez-vous inscrire, modifier ou supprimer un participant ?\n1)inscrire\t2)modifier 3)supprimer\t4)Quitter\n");
					scanf("%d",&participant);
					getchar();
				
					switch(participant){
						case 1 :
							p = ajouterParticipant();
							e->participants = p;	
							break;
						case 2:
							if(e->participants == NULL){
								printf("Il n'y a aucun participant\n");
							}else{
								printf("\n%s\n",afficherParticipants());
								printf("\nQuel participant souhaitez-vous modifier? (rentrer son email)\n");
								scanf("%100s",supprEmail);
								getchar();
								p = modifierParticipant(supprEmail);
								e->participants = p;
							}
							/*free(afficherParticipants());*/
							break;
						case 3 :
							/* faire dérouler les personnes avec un numéro devant et supprimer la personne ainsi selectionnée*/
							if(e->participants == NULL){
								printf("Il n'y a aucun participant\n");
							}else{
								printf("\n%s\n",afficherParticipants());
								printf("\nQuel participant souhaitez-vous enlever de l'événement? (rentrer son email)\n");
								scanf("%100s",supprEmail);
								getchar();
								p = supprimerParticipantEvt(supprEmail);
								e->participants = p;
							}
							/*free(afficherParticipants());*/
							break;
						case 4 :
							exit2 = 1;
							break;
						default :
							printf("Cette valeur n'est pas valide, veuillez rentrer une valeur valide");					
					}
				}								
				break;
			case 9 :
					exit = 1;
					break;
			default :
				printf("Ceci n'est pas un choix valide, veuillez entrer un choix valide");
		}
	}	
}

