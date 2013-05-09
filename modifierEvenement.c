#include <stdio.h>
#include <stdlib.h>
#include "Agenda.h"
#include <string.h>

extern EVENEMENT *tete;

void modifier(char nomEvenement[100],char dateDebutEvenement[10]){
	EVENEMENT *e = rechercher(nomEvenement,dateDebutEvenement);
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

	razTetePersonne();
	recuperationParticipantsEvt(e->participants);

	while(!exit){
		exit2 = 0;
		printf("Que voulez-vous modifier ?\n1) le nom\t2)le lieu\t3)la date de début\t4)l'heure de début\t5)la date de fin\t6)l'heure de fin\t7)la description\t8)les personnes participantes\n9)Quiter\n");
		scanf("%1d",&modifier);
		getchar();
		
		switch(modifier){
			case 1 :
				printf("Quel nom voulez vous donner ?");
				fgets(nomTemp, sizeof(nomTemp), stdin);
				
				if(strcmp(nomTemp,"\n"))
					modifNom = strtok(nomTemp,"\n");
				else
					modifNom = "Nouvel évènement ";

				while(!stringValide(modifNom)){
					printf("Nom de l'évènement : ");
					fgets(nomTemp, sizeof(nomTemp), stdin);
					
					if(strcmp(nomTemp,"\n"))
						modifNom = strtok(nomTemp,"\n");
					else
						modifNom = "Nouvel évènement ";
				}
				strcpy(e->nom,modifNom);
				break;
			case 2 :
				printf("Quel est le lieu ?");
				fgets(lieuTemp, sizeof(lieuTemp), stdin);
				
				if(strcmp(lieuTemp,"\n"))
					modifLieu = strtok(lieuTemp,"\n");
				else
					modifLieu = "Inconnu";

				while(!stringValide(modifLieu)){
					printf("Lieu de l'évènement : ");
					fgets(lieuTemp, sizeof(lieuTemp), stdin);
					if(strcmp(lieuTemp,"\n"))
						modifLieu = strtok(lieuTemp,"\n");
					else
						modifLieu = "Inconnu";
				}
				strcpy(e->nomLieu,modifLieu);
				break;
			case 3 :
				printf("Quelle est la date de début ?");
				fgets(dateDebTemp, sizeof(dateDebTemp), stdin);
				if(strcmp(dateDebTemp,"\n"))
					modifDateDeb = strtok(dateDebTemp,"\n");
				else
					modifDateDeb = "Inconnue";
				while(!formatDateValide(modifDateDeb)){
					printf("Date de début de l'évènement : ");
					fgets(dateDebTemp, sizeof(dateDebTemp), stdin);
					
					if(strcmp(dateDebTemp,"\n"))
						modifDateDeb = strtok(dateDebTemp,"\n");
					else
						modifDateDeb = "Inconnue";
				}
				strftime(heure, sizeof(heure), "%H:%M", e->dateDebut); 
				e->dateDebut = convertirStringToDate(modifDateDeb,heure);
				break;
			case 4 :
				printf("Quelle est l'heure de début ?");
				fgets(heureDebTemp, sizeof(heureDebTemp), stdin);
				
				if(strcmp(heureDebTemp,"\n"))
					modifHeureDeb = strtok(heureDebTemp,"\n");
				else
					modifHeureDeb = "Inconnue";
				
				while(!formatHeureValide(modifHeureDeb)){
					printf("Heure de début de l'évènement : ");
					fgets(heureDebTemp, sizeof(heureDebTemp), stdin);
					
					if(strcmp(heureDebTemp,"\n"))
						modifHeureDeb = strtok(heureDebTemp,"\n");
					else
						modifHeureDeb = "Inconnue";
				}
				strftime(date, sizeof(date), "%d/%m/%Y", e->dateDebut);
				e->dateDebut = convertirStringToDate(date,modifHeureDeb);
				break;
			case 5 :
				printf("Quelle est la date de fin ?");
				fgets(dateFinTemp, sizeof(dateFinTemp), stdin);
				if(strcmp(dateFinTemp,"\n"))
					modifDateFin = strtok(dateFinTemp,"\n");
				else
					modifDateFin = "Inconnue";
				
				while(!formatDateValide(modifDateFin)){
					printf("Date de fin de l'évènement : ");
					fgets(dateFinTemp, sizeof(dateFinTemp), stdin);
					if(strcmp(dateFinTemp,"\n"))
						modifDateFin = strtok(dateFinTemp,"\n");
					else
						modifDateFin = "Inconnue";
				}
				strftime(heure, sizeof(heure), "%H:%M", e->dateFin);
				e->dateFin = convertirStringToDate(modifDateFin,heure);
				break;
			case 6 :
				printf("Quelle est l'heure de fin ?");
				fgets(heureFinTemp, sizeof(heureFinTemp), stdin);
				if(strcmp(heureFinTemp,"\n"))
					modifHeureFin = strtok(heureFinTemp,"\n");
				else
					modifHeureFin = "Inconnue";
				
				while(!formatHeureValide(modifHeureFin)){
					printf("Heure de fin de l'évènement : ");
					fgets(heureFinTemp, sizeof(heureFinTemp), stdin);
					if(strcmp(heureFinTemp,"\n"))
						modifHeureFin = strtok(heureFinTemp,"\n");
					else
						modifHeureFin = "Inconnue";
				}
				strftime(date, sizeof(date), "%d/%m/%Y", e->dateFin);
				e->dateFin = convertirStringToDate(date,modifHeureFin);
				break;
			case 7 :
				printf("Quelle est la nouvelle description ?");
				fgets(descTemp, sizeof(descTemp), stdin);
				
				if(strcmp(descTemp,"\n"))
					modifDesc = strtok(descTemp,"\n");
				else
					modifDesc = "Inconnue";
				while(!stringValide(modifDesc)){
					printf("Description de l'évènement : ");
					fgets(descTemp, sizeof(descTemp), stdin);
					
					if(strcmp(descTemp,"\n"))
						modifDesc = strtok(descTemp,"\n");
					else
						modifDesc = "Inconnue";
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
								supprimerParticipantEvt(supprEmail);
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

