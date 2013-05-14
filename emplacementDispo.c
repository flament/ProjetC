#include <stdio.h>
#include <stdlib.h>
#include "Agenda.h"
#include <string.h>

extern EVENEMENT *tete;

int emplacementDispo(char dateDeb[10],char dateFin[10], char heureDeb[5], char heureFin[5]){
	EVENEMENT *temp = tete;	
	int jourDeb, jourFin, moisDeb, moisFin, anneeDeb, anneeFin, heureD, heureF, minuteD, minuteF;
	char * m_t;
	int res = 1;

	jourDeb = atoi(strtok(dateDeb,"/")); 
	m_t = &dateDeb[3];	 
	moisDeb = atoi(strtok(m_t,"/"));
	anneeDeb =  atoi(&m_t[3]);
	heureD = atoi(strtok(heureDeb,":"));
	minuteD = atoi(&heureDeb[3]);

	jourFin = atoi(strtok(dateFin,"/")); 
	m_t = &dateFin[3];	 
	moisFin = atoi(strtok(m_t,"/"));
	anneeFin =  atoi(&m_t[3]);
	heureF = atoi(strtok(heureFin,":"));
	minuteF = atoi(&heureFin[3]);
	

	while(temp != NULL && res == 1){
		if((temp->dateDebut->tm_year+1900) == anneeDeb && anneeDeb == (temp->dateFin->tm_year+1900)){
			if((temp->dateDebut->tm_mon+1) == moisDeb && moisDeb == (temp->dateFin->tm_mon+1)){
				if(temp->dateDebut->tm_mday == jourDeb && jourDeb == temp->dateFin->tm_mday){
					if((temp->dateDebut->tm_hour == heureD && heureD == temp->dateFin->tm_hour && temp->dateDebut->tm_min <= minuteD && minuteD < temp->dateFin->tm_min)
					|| (temp->dateDebut->tm_hour == heureD && heureD < temp->dateFin->tm_hour && temp->dateDebut->tm_min <= minuteD)
					||	(temp->dateDebut->tm_hour < heureD && heureD < temp->dateFin->tm_hour) 
					|| (temp->dateDebut->tm_hour < heureD && heureD == temp->dateFin->tm_hour && minuteD < temp->dateFin->tm_min)){
								printf("L'événement ne peut commencer à cette heure-ci, un événement étant déjà en train de se dérouler à ce moment là.\n");
								res = 0;
					}else if(heureD < temp->dateDebut->tm_hour || (heureD == temp->dateDebut->tm_hour && minuteD < temp->dateDebut->tm_min)){
							if(heureF > temp->dateDebut->tm_hour || (heureF == temp->dateDebut->tm_hour && minuteF > temp->dateDebut->tm_min)){
								printf("L'événement ne peut se terminer à cette heure-ci, un événement étant déjà en train de se dérouler à ce moment là.\n");
								res = 0;
							}
					}
				}else if((temp->dateDebut->tm_mday < jourDeb && jourDeb < temp->dateFin->tm_mday)
						||(temp->dateDebut->tm_mday == jourDeb && temp->dateDebut->tm_hour < heureD && jourDeb < temp->dateFin->tm_mday)
						||(temp->dateDebut->tm_mday == jourDeb && temp->dateDebut->tm_hour == heureD && temp->dateDebut->tm_min <= minuteD && jourDeb < temp->dateFin->tm_mday)){
					printf("L'événement ne peut commencer ce jour là, un événement étant déjà en train de se dérouler à ce moment là.\n");
					res = 0;
				}else if((temp->dateDebut->tm_mday > jourDeb && temp->dateDebut->tm_mday < jourFin)
						||(temp->dateDebut->tm_mday == jourDeb && temp->dateDebut->tm_hour > heureD && temp->dateDebut->tm_mday < jourFin)
						||(temp->dateDebut->tm_mday == jourDeb && temp->dateDebut->tm_hour == heureD && temp->dateDebut->tm_min > minuteD && temp->dateDebut->tm_mday < jourFin)
						||(temp->dateDebut->tm_mday > jourDeb && temp->dateDebut->tm_mday == jourFin && temp->dateDebut->tm_hour < heureF) 
						||(temp->dateDebut->tm_mday > jourDeb && temp->dateDebut->tm_mday == jourFin && temp->dateDebut->tm_hour == heureF && temp->dateDebut->tm_min < minuteD)
						||(temp->dateDebut->tm_mday == jourDeb && temp->dateDebut->tm_hour > heureD && temp->dateDebut->tm_mday == jourFin && temp->dateDebut->tm_hour < heureF)
						||(temp->dateDebut->tm_mday == jourDeb && temp->dateDebut->tm_hour > heureD && temp->dateDebut->tm_mday == jourFin && temp->dateDebut->tm_hour == heureF && temp->dateDebut->tm_min < minuteF)
						||(temp->dateDebut->tm_mday == jourDeb && temp->dateDebut->tm_hour == heureD && temp->dateDebut->tm_min > minuteD && temp->dateDebut->tm_mday == jourFin && temp->dateDebut->tm_hour < heureF)
						||(temp->dateDebut->tm_mday == jourDeb && temp->dateDebut->tm_hour == heureD && temp->dateDebut->tm_min > minuteD && temp->dateDebut->tm_mday == jourFin && temp->dateDebut->tm_hour == heureF && temp->dateDebut->tm_min < minuteF)){
					printf("L'événement ne peut se terminer ce jour là, un événement étant déjà en train de se dérouler à ce moment là.\n");
					res = 0;
				}
			}else if(((temp->dateDebut->tm_mon+1) < moisDeb && moisDeb < (temp->dateFin->tm_mon+1)) 
						||((temp->dateDebut->tm_mon+1) == moisDeb && moisDeb < (temp->dateFin->tm_mon+1) && temp->dateDebut->tm_mday <= jourDeb) 
						|| ((temp->dateDebut->tm_mon+1) < moisDeb && moisDeb == (temp->dateFin->tm_mon+1) && temp->dateFin->tm_mday > jourDeb)){
							printf("L'événement ne peut commencer ce mois là, un événement étant déjà en train de se dérouler à ce moment là.\n");
							res = 0;
			}else if(((temp->dateDebut->tm_mon+1) > moisDeb	&& (temp->dateDebut->tm_mon+1) < moisFin)
						||((temp->dateDebut->tm_mon+1) > moisDeb	&& (temp->dateDebut->tm_mon+1) == moisFin && temp->dateDebut->tm_mday < jourFin)
						|| ((temp->dateDebut->tm_mon+1) == moisDeb && temp->dateDebut->tm_mday > jourDeb  && (temp->dateDebut->tm_mon+1) < moisFin)
						|| ((temp->dateDebut->tm_mon+1) == moisDeb && temp->dateDebut->tm_mday > jourDeb && (temp->dateDebut->tm_mon+1) == moisFin && temp->dateDebut->tm_mday < jourFin)){						
								printf("L'événement ne peut se terminer ce mois là, un événement étant déjà en train de se dérouler à ce moment là.\n");
								res = 0;						
			}
		}else if(((temp->dateDebut->tm_year+1900) < anneeDeb && anneeDeb < (temp->dateFin->tm_year+1900))
					||((temp->dateDebut->tm_year+1900)==anneeDeb && anneeDeb < (temp->dateFin->tm_year+1900) && (temp->dateDebut->tm_mon+1) < moisDeb)
					||((temp->dateDebut->tm_year+1900)==anneeDeb && anneeDeb < (temp->dateFin->tm_year+1900) && (temp->dateDebut->tm_mon+1)==moisDeb && temp->dateDebut->tm_mday <= jourDeb)
					||((temp->dateDebut->tm_year+1900)< anneeDeb && anneeDeb == (temp->dateFin->tm_year+1900) && (temp->dateFin->tm_mon+1) > moisDeb)
					||((temp->dateDebut->tm_year+1900)< anneeDeb && anneeDeb == (temp->dateFin->tm_year+1900) && (temp->dateFin->tm_mon+1)==moisDeb && temp->dateFin->tm_mday > jourDeb)){
				printf("L'événement ne peut commencer cette année là, un événement étant déjà en train de se dérouler à ce moment là.\n");
				res = 0;
		}else if(((temp->dateDebut->tm_year+1900) > anneeDeb && anneeFin > (temp->dateDebut->tm_year+1900))
					||((temp->dateDebut->tm_year+1900)==anneeDeb && (temp->dateDebut->tm_mon+1) > moisDeb && anneeFin > (temp->dateDebut->tm_year+1900))
					||((temp->dateDebut->tm_year+1900)==anneeDeb && (temp->dateDebut->tm_mon+1)==moisDeb && temp->dateDebut->tm_mday > jourDeb && anneeFin > (temp->dateDebut->tm_year+1900))
					||((temp->dateDebut->tm_year+1900)> anneeDeb && anneeFin == (temp->dateDebut->tm_year+1900) && (temp->dateDebut->tm_mon+1) < moisFin)
					||((temp->dateDebut->tm_year+1900)> anneeDeb && anneeFin == (temp->dateDebut->tm_year+1900) && (temp->dateDebut->tm_mon+1)==moisFin && temp->dateDebut->tm_mday < jourFin)
					||((temp->dateDebut->tm_year+1900)==anneeDeb && (temp->dateDebut->tm_mon+1)==moisDeb && temp->dateDebut->tm_mday > jourDeb && anneeFin == (temp->dateDebut->tm_year+1900) && (temp->dateDebut->tm_mon+1)==moisFin && temp->dateDebut->tm_mday < jourFin) ){
				printf("L'événement ne peut se terminer cette année là, un événement étant déjà en train de se dérouler à ce moment là.\n");
				res = 0;	
		}	
		temp = temp->suivant;
	}
	return res;
}

