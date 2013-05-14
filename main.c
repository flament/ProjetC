#include <stdio.h>
#include <stdlib.h>
#include "Agenda.h"
#include <string.h>

extern EVENEMENT *tete;
extern PERSONNE *teteListePers;
extern THEME *teteTheme;

void libererEvenement(EVENEMENT* e){
	if(e->suivant != NULL){
		libererEvenement(e->suivant);
	}
	/*if(e->participants != NULL)
		libererPersonne(e->participants);*/
	free(e->dateDebut);
	free(e->dateFin);
	free(e);
}

void libererPersonne(PERSONNE* p){
	if(p->suivant != NULL){
		libererPersonne(p->suivant);
	}
	free(p);
}

void libererTheme(THEME* t){
	if(t->suivant != NULL){
		libererTheme(t->suivant);
	}
	free(t);
}
void menuGestion(char theme[100]){
	char nomTemp[100], *nom,dateTemp[12], *date,heureTemp[6],*heure,dateDebut[100],dateFin[100];
	char * msg = (char *)malloc((strlen(theme)+54)*sizeof(char)); 
	EVENEMENT *e;
	int choix, arret;
 	arret = 1;	
	strcpy(msg,"\n-------------------Gestion de ");
	strcat(msg,theme);
	strcat(msg,"-------------------\n\n");

	while(arret){
		printf("%s",msg);
		printf("Que voulez-vous faire?\n");
		printf("\t1)Créer un événement\n");
		printf("\t2)Modifier un événement\n");
		printf("\t3)Supprimer un événement\n");
		printf("\t4)Rechercher des infos sur un événement\n");
		printf("\t5)Consulter les créneaux disponibles d'un jour donné\n");
		printf("\t6)Sauvegarder le(s) événement(s) créé(s)\n");
		printf("\t7)Charger des événements\n");
		printf("\t8)Quitter\n");
		printf("Votre choix :\n");
		
		scanf("%1d",&choix);
		getchar();

		switch(choix){
			case 1:
				ajouterEvenement();
				break;
			case 2:
				if(tete == NULL)
					printf("Il n'y a aucun évènement de créé\n");
				else{
					printf("\n%s\n",afficherEvenements());
					printf("Saisissez le nom de l'évènement à modifier:");
					fgets(nomTemp, sizeof(nomTemp), stdin);				
					if(strcmp(nomTemp,"\n"))
						nom = strtok(nomTemp,"\n");
					else
						nom = "";
				
					printf("Saisissez la date de début de l'évènement à modifier:");
					fgets(dateTemp, sizeof(dateTemp), stdin);
					if(strcmp(dateTemp,"\n"))
						date = strtok(dateTemp,"\n");
					else
						date = "";

					printf("Saisissez l'heure de début de l'évènement à modifier:");
					fgets(heureTemp, sizeof(heureTemp), stdin);
					if(strcmp(heureTemp,"\n"))
						heure = strtok(heureTemp,"\n");
					else
						heure = "";

					modifierEvenement(nom,date,heure);
				}
				break;
			case 3:
				if(tete == NULL)
					printf("Il n'y a aucun évènement de créé\n");
				else{
					printf("\n%s\n",afficherEvenements());
					
					printf("Saisissez le nom de l'évènement à supprimer:");
					fgets(nomTemp, sizeof(nomTemp), stdin);
					if(strcmp(nomTemp,"\n"))
						nom = strtok(nomTemp,"\n");
					else
						nom = "";
				
					printf("Saisissez la date de début de l'évènement à supprimer:");
					fgets(dateTemp, sizeof(dateTemp), stdin);
					if(strcmp(dateTemp,"\n"))
						date = strtok(dateTemp,"\n");
					else
						date = "";

					printf("Saisissez l'heure de début de l'évènement à supprimer:");
					fgets(heureTemp, sizeof(heureTemp), stdin);
					if(strcmp(heureTemp,"\n"))
						heure = strtok(heureTemp,"\n");
					else
						heure = "";

					supprimerEvenement(nom,date,heure);
				}
				break;
			case 4:
				if(tete == NULL)
					printf("Il n'y a aucun évènement de créé\n");
				else{
					printf("\n%s\n",afficherEvenements());
					printf("Saisissez le nom de l'évènement à consulter:");
					fgets(nomTemp, sizeof(nomTemp), stdin);				
					if(strcmp(nomTemp,"\n"))
						nom = strtok(nomTemp,"\n");
					else
						nom = "";
				
					printf("Saisissez la date de début de l'évènement à consulter:");
					fgets(dateTemp, sizeof(dateTemp), stdin);
					if(strcmp(dateTemp,"\n"))
						date = strtok(dateTemp,"\n");
					else
						date = "";

					printf("Saisissez l'heure de début de l'évènement à consulter:");
					fgets(heureTemp, sizeof(heureTemp), stdin);
					if(strcmp(heureTemp,"\n"))
						heure = strtok(heureTemp,"\n");
					else
						heure = "";

					e = rechercherEvenement(nom,date,heure);
					if(e != NULL){
						printf("Nom : %s\nDescription : %s\nLieu : %s\n",e->nom,e->description,e->nomLieu);
						strftime(dateDebut, sizeof(dateDebut), "%d/%m/%Y à %H:%M", e->dateDebut);
						strftime(dateFin, sizeof(dateFin), "%d/%m/%Y à %H:%M", e->dateFin);
						printf("Date de début : %s\nDate de fin : %s\n",dateDebut,dateFin);
						recuperationParticipantsEvt(e->participants);
						if(e->participants != NULL){
							printf("Ses participants sont :\n");
							printf("\t%s\n",afficherParticipants());
						}
					}
				}

				break;
			case 5:
				break;
			case 6:
				printf("Saisissez le nom du fichier à sauvegarder:");
				fgets(nomTemp, sizeof(nomTemp), stdin);
				if(strcmp(nomTemp,"\n"))
					nom = strtok(nomTemp,"\n");
				else
					nom = "fichier";
				
				if(nomFichierValide(nom))
					enregistrer(nom,theme);

				break;
			case 7:
				printf("Saisissez le nom du fichier à charger:");
				fgets(nomTemp, sizeof(nomTemp), stdin);
				if(strcmp(nomTemp,"\n"))
					nom = strtok(nomTemp,"\n");
				else
					nom = "";	
			
				if(chargementValide(nom,theme))
					charger(nom);
				break;
			case 8:
				arret = 0;
				free(msg);
				break;
			default :
				printf("Ceci n'est pas un choix valide, veuillez entrer un chiffre entre 1 et 8\n");
		}
	}

}

int main(int argc, char** argv) {
	THEME *test;
	char nomTemp[100], *nom;
   int choix, arret;
 	arret = 1;

	while(arret){
		printf("\n-------------------Accueil-------------------\n\n");
		printf("Que voulez-vous faire?\n");
		printf("\t1)Créer un thème\n");
		printf("\t2)Modifier un thème\n");
		printf("\t3)Supprimer un thème\n");
		printf("\t4)Gérer un thème\n");
		printf("\t5)Sauvegarder le(s) thème(s) créé(s)\n");
		printf("\t6)Charger des thèmes\n");
		printf("\t7)Quitter\n");
		printf("Votre choix :\n");
		
		scanf("%1d",&choix);
		getchar();

		switch(choix){
			case 1:
				ajouterTheme();
				break;
			case 2:
				if(teteTheme == NULL)
					printf("Il n'y a aucun thème de créé\n");
				else{
					printf("\n%s\n",afficherThemes());
					printf("Saisissez le nom du thème à modifier:");
					fgets(nomTemp, sizeof(nomTemp), stdin);
					if(strcmp(nomTemp,"\n"))
						nom = strtok(nomTemp,"\n");
					else
						nom = "";
					modifierTheme(nom);
				}
				break;
			case 3:
				if(teteTheme == NULL)
					printf("Il n'y a aucun thème de créé\n");
				else{
					printf("\n%s\n",afficherThemes());
					printf("Saisissez le nom du thème à supprimer:");
					fgets(nomTemp, sizeof(nomTemp), stdin);
					if(strcmp(nomTemp,"\n"))
						nom = strtok(nomTemp,"\n");
					else
						nom = "";
					supprimerTheme(nom);
				}
				break;
			case 4:
				if(teteTheme == NULL)
					printf("Il n'y a aucun thème de créé\n");
				else{
					printf("\n%s\n",afficherThemes());
					printf("\nSaisissez le nom du thème que vous voulez gérer :");
					fgets(nomTemp, sizeof(nomTemp), stdin);
					
					if(strcmp(nomTemp,"\n"))
						nom = strtok(nomTemp,"\n");
					else
						nom = "";
					
					test = rechercherTheme(nom);
					
					if(test != NULL)
						menuGestion(nom);
					else
						printf("\nThème inexistant\n\n");
				}
				break;
			case 5:
				printf("Saisissez le nom du fichier à sauvegarder:");
				fgets(nomTemp, sizeof(nomTemp), stdin);
				if(strcmp(nomTemp,"\n"))
					nom = strtok(nomTemp,"\n");
				else
					nom = "";
				
				if(nomFichierValide(nom))
					enregistrerTheme(nom);
				break;
			case 6:
				printf("Saisissez le nom du fichier à charger:");
				fgets(nomTemp, sizeof(nomTemp), stdin);
				if(strcmp(nomTemp,"\n"))
					nom = strtok(nomTemp,"\n");
				else
					nom = "";		
				
					lectureFichierThemes(nom);
				break;
			case 7:
				arret = 0;
				break;
			default :
				printf("Ceci n'est pas un choix valide, veuillez entrer un chiffre entre 1 et 7\n");
		}
	}
		
	
	/*char buffer[256], buff2[256];*/
	
	/*charger("Calendrier.csv");*/
	/*char d[10] = "18/04/2013";
	char d1[10] = "18/04/2013";
	char h[5] = "15:00";
	char h1[5] = "16:00";
	
	ajouterEvenement();
	
	int test = emplacementDispo(d,d1,h,h1);
	printf("%d\n",test);	*/

	/*ajouterEvenement();
	ajouterEvenement();*/
	
	/*printf("\n\n---------------------------------------------------\n");*/
	/*modifier("evt1","18/04/2013");*/	

	/*EVENEMENT *temp = tete;
	while(temp != NULL){
		printf("\n%s\n",temp->nom);
		temp= temp->suivant;
	}
	PERSONNE *tem = teteListePers;
	while(tem != NULL){
		printf("\n%s\n",tem->nom);
		tem = tem->suivant;
	}*/
	
	
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
	printf("%s\n",buff2);*/
	/*printf("\n\n\nnom Evt: %s\n",tete->nom);
	printf("nom1 : %s\n",tete->participants->nom);
	printf("prenom: %s\n",tete->participants->prenom);
	printf(",,,,,,,,,,,,,,,,,,,nom2 : %s\n",tete->participants->suivant->nom);
	printf("prenom: %s\n",tete->participants->suivant->prenom);*
	

	printf("\n\nnom Evt: %s\n",(tete->suivant)->nom);	
	printf("nom Lieu: %s\n",(tete->suivant)->nomLieu);
	printf("Desc Evt: %s\n",(tete->suivant)->description);
	printf("nom1 : %s\n",(tete->suivant)->participants->nom);
	printf("prenom: %s\n",(tete->suivant)->participants->prenom);
	printf(",,,,,,,,,,,,,,,,,,,nom2 : %s\n",(tete->suivant)->participants->suivant->nom);
	printf("prenom: %s\n",(tete->suivant)->participants->suivant->prenom);*/
	/*strftime(buffer, sizeof(buffer), "%x %H:%M", (tete->suivant)->dateDebut);
	strftime(buff2, sizeof(buff2), "%x %H:%M", (tete->suivant)->dateFin);
	printf("%s\n",buffer);
	printf("%s\n",buff2);*/

	/*ecritureCSV();
	enregistrerParticipants();
	enregistrerFormatTxt();
*/
	if(tete != NULL)
		libererEvenement(tete);

	if(teteListePers != NULL)
		libererPersonne(teteListePers);
	
	if(teteTheme != NULL)
		libererTheme(teteTheme);

    return (EXIT_SUCCESS);	
}

