#include <stdio.h>
#include <stdlib.h>
#include "Agenda.h"
#include <string.h>

struct tm* convertirStringToDate(char s[50], char h[50]){
	char *jour, *m_t, *mois, *annee,*heure,*minute;
	struct tm* tim;
	tim = (struct tm*)malloc(sizeof(struct tm));
	
 	jour = strtok(s,"/"); 
	m_t = &s[3];	 
	mois = strtok(m_t,"/");
	annee =  &m_t[3];
	heure = strtok(h,":");
	minute = &h[3];

	tim->tm_mday = atoi(jour);
	tim->tm_mon = atoi(mois)-1;
	tim->tm_year = atoi(annee) - 1900;
	tim->tm_hour = atoi(heure);
	tim->tm_min = atoi(minute);

	return tim;
}
