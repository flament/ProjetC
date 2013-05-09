#include <stdio.h>
#include <stdlib.h>
#include "Agenda.h"
#include <string.h>

extern EVENEMENT *tete;

void modifier(char nomEvenement[100],char dateDebutEvenement[10]){
	EVENEMENT *e = rechercher(nomEvenement,dateDebutEvenement);
	razTetePersonne();
	recuperationParticipantsEvt(e->participants);

	PERSONNE * p = (PERSONNE *)malloc(sizeof(PERSONNE));
	p = NULL;
	int modifier = 0,participant = 0, exit = 0, exit2;
	char *modifNom,*modifDesc,*modifLieu,*modifDateDeb,*modifDateFin,*modifHeureDeb,*modifHeureFin;
	char dateDebTemp[50], dateFinTemp[50],heureDebTemp[50],heureFinTemp[50],nomTemp[100],lieuTemp[100],descTemp[200],supprEmail[100];
	char heure[5],date[10];


	if(e == NULL){
		printf("Evenement inexistant\n");	
		return;
	}

	while(!exit){
		exit2 = 0;
		printf("Que voulez-vous modifier ?\n1) le nom\t2)le lieu\t3)la date de début\t4)l'heure de début\t5)la date de fin\t6)l'heure de fin\t7)la description\t8)les personnes participantes\n9)Quiter\n");
		scanf("%1d",&modifier);
		getchar();
		
		switch(modifier){
			case 1 :
				printf("Quel nom voulez vous donner ?");
				fgets(nomTemp, sizeof(nomTemp), stdin);
				modifNom = strtok(nomTemp,"\n");
				while(!stringValide(modifNom)){
					printf("Nom de l'évènement : ");
					fgets(nomTemp, sizeof(nomTemp), stdin);
					modifNom = strtok(nomTemp,"\n");
				}
				strcpy(e->nom,modifNom);
				break;
			case 2 :
				printf("Quel est le lieu ?");
				fgets(lieuTemp, sizeof(lieuTemp), stdin);
				modifLieu = strtok(lieuTemp,"\n");
				while(!stringValide(modifLieu)){
					printf("Lieu de l'évènement : ");
					fgets(lieuTemp, sizeof(lieuTemp), stdin);
					modifLieu = strtok(lieuTemp,"\n");
				}
				strcpy(e->nomLieu,modifLieu);
				break;
			case 3 :
				printf("Quelle est la date de début ?");
				fgets(dateDebTemp, sizeof(dateDebTemp), stdin);
				modifDateDeb = strtok(dateDebTemp,"\n");
				while(!formatDateValide(modifDateDeb)){
					printf("Date de début de l'évènement : ");
					fgets(dateDebTemp, sizeof(dateDebTemp), stdin);
					modifDateDeb = strtok(dateDebTemp,"\n");
				}
				strftime(heure, sizeof(heure), "%H:%M", e->dateDebut); 
				e->dateDebut = convertirStringToDate(modifDateDeb,heure);
				break;
			case 4 :
				printf("Quelle est l'heure de début ?");
				fgets(heureDebTemp, sizeof(heureDebTemp), stdin);
				modifHeureDeb = strtok(heureDebTemp,"\n");
				while(!formatHeureValide(modifHeureDeb)){
					printf("Heure de début de l'évènement : ");
					fgets(heureDebTemp, sizeof(heureDebTemp), stdin);
					modifHeureDeb = strtok(heureDebTemp,"\n");
				}
				strftime(date, sizeof(date), "%d/%m/%Y", e->dateDebut);
				e->dateDebut = convertirStringToDate(date,modifHeureDeb);
				break;
			case 5 :
				printf("Quelle est la date de fin ?");
				fgets(dateFinTemp, sizeof(dateFinTemp), stdin);
				modifDateFin = strtok(dateFinTemp,"\n");
				while(!formatDateValide(modifDateFin)){
					printf("Date de fin de l'évènement : ");
					fgets(dateFinTemp, sizeof(dateFinTemp), stdin);
					modifDateFin = strtok(dateFinTemp,"\n");
				}
				strftime(heure, sizeof(heure), "%H:%M", e->dateFin);
				e->dateFin = convertirStringToDate(modifDateFin,heure);
				break;
			case 6 :
				printf("Quelle est l'heure de fin ?");
				fgets(heureFinTemp, sizeof(heureFinTemp), stdin);
				modifHeureFin = strtok(heureFinTemp,"\n");
				while(!formatHeureValide(modifHeureFin)){
					printf("Heure de fin de l'évènement : ");
					fgets(heureFinTemp, sizeof(heureFinTemp), stdin);
					modifHeureFin = strtok(heureFinTemp,"\n");
				}
				strftime(date, sizeof(date), "%d/%m/%Y", e->dateFin);
				e->dateFin = convertirStringToDate(date,modifHeureFin);
				break;
			case 7 :
				printf("Quelle est la nouvelle description ?");
				fgets(descTemp, sizeof(descTemp), stdin);
				modifDesc = strtok(descTemp,"\n");
				while(!stringValide(modifDesc)){
					printf("Description de l'évènement : ");
					fgets(descTemp, sizeof(descTemp), stdin);
					modifDesc = strtok(descTemp,"\n");
				}
				strcpy(e->description,modifDesc);
				break;
			case 8 :
				while(!exit2){
					printf("voulez-vous inscrire ou supprimer un participant ?\n1)inscrire\t2)supprimer\t3)Quitter\n");
					scanf("%1d",&participant);
					getchar();
				
					switch(participant){
						case 1 :
							p = ajouterParticipant();
							break;
						case 2 :
							/* faire dérouler les personnes avec un numéro devant et supprimer la personne ainsi selectionnée*/
							printf("\n%s\n",afficherParticipants());
							if(e->participants == NULL){
								printf("Il n'y a aucun participant\n");
							}else{
								printf("\nQuel participant souhaitez-vous enlever de l'évènement? (rentrer son email)\n");
								scanf("%100s",supprEmail);
								getchar();
								supprimerParticipant(supprEmail);
							}
							break;
						case 3 :
							exit2 = 1;
							break;
						default :
							printf("Cette valeur n'est pas valide, veuillez rentrer une valeur valide");					
					}
				}
				e->participants = p;						
				break;
			case 9 :
					exit = 1;
					break;
			default :
				printf("Ceci n'est pas un choix valide, veuillez entrer un choix valide");
		}
	}	
}

