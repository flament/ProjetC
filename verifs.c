#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Agenda.h"

int formatDateValide(char date[50]){
	char *jour, *m_t,*mois,*annee;
	char sep1,sep2;	
	int taille = (int)(strlen(date));
	int res = 1;
	
	sep1 = date[2];
	sep2 = date[5];
	 /*12/10/2012->12\010\02012*/
	jour = strtok(date,"/");/*La chaîne passée en argument est modifiée par la fonction : elle ajoute un caractère de fin de chaîne à la place du séparateur. */
	m_t = &date[3];
	mois = strtok(m_t,"/");
	annee =  &m_t[3];	
	
	if(taille != 10){
		printf("la date ne doit pas contenir plus de 10 caractères!\n");
		res = 0;
	}else if(atoi(mois) < 0 || atoi(mois) > 12){
		printf("mois invalide\n");
		res = 0;
	}else if((int)(strlen(annee)) != 4){
		printf("Année invalide!\n");
		res = 0;
	}else if(sep1 != '/' || sep2 != '/'){
		printf("format invalide\n");
		res = 0;
	}			
	/*strcmp renvoie 0 si égaux*/
	else if(!strcmp(mois,"02")){
		if(atoi(jour) < 0 || atoi(jour) > 28){
			printf("Le mois de février doit contenir entre 1 et 28 jours!\n");
			res = 0;
		}
	}else if(!strcmp(mois,"01") || !strcmp(mois,"03") || !strcmp(mois,"05") || !strcmp(mois,"07") || !strcmp(mois,"08") || !strcmp(mois,"10") || !strcmp(mois,"12")){
		if(atoi(jour) < 0 || atoi(jour) > 31){
			printf("Ces mois ne contiennent que 31 jours!\n");
			res = 0;
		}
	}else if(!strcmp(mois,"04") || !strcmp(mois,"06") || !strcmp(mois,"09") || !strcmp(mois,"11")){
		if(atoi(jour) < 0 || atoi(jour) > 30){
			printf("Ces mois ne contiennent que 30 jours!\n");
			res = 0;
		}					
	}else{
		printf("Jour entré invalide!\n");
		res = 0;
	}

	return res;
}

int formatHeureValide(char h[50]){
	char *heure, *minute;
	char sep = h[2];
	int taille = (int)(strlen(h));
	int res = 1;
	
	heure = strtok(h,":");
	minute = &h[3];

	if(taille != 5){
		printf("l'heure ne doit pas contenir plus de 5 caractères!\n");
		res = 0;
	}else if(sep != ':'){
		printf("Format heure invalide!\n");
		res = 0;
	}else if(atoi(heure) < 0 || atoi(heure) >= 24){
		printf("Heure invalide!\n");
		res = 0;
	}else if(atoi(minute) < 0 || atoi(minute) > 59){
		printf("Minute invalide!\n");
		res = 0;
	}
	return res;
}
int stringValide(char *s){
   int res = 1;
	int i;

	for(i = 0; i < (int)strlen(s); i++){
		if(s[i] == ','){
			res = 0;
			break;
		}
	}
	if(res == 0)
		printf("Il ne doit pas y avoir de virgule(s)!\n");
	return res;
}

/*int main(int argc, char** argv) {
	char d[25]= "29/02/2013";
	//int test1 = formatDateValide(d);//OK
	char d1[25] = "04/02/2013";
	//int test2 = formatDateValide(d1);//OK
	char d2[25] = "32/12/2013";
	//int test3 = formatDateValide(d2);//OK
	char d3[25] = "29/12/2013"; 
	//int test4 = formatDateValide(d3);//OK
	char d4[25] = "31/06/2013";
	//int test5  = formatDateValide(d4);//OK
	char d5[25] = "05/04/2013";
	//int test6 = formatDateValide(d5); //OK
	char d6[25] = "29,02/2013";
	//int test7 = formatDateValide(d6);//OK
	char d7[25] = "12/12/12365";
	//int test8 = formatDateValide(d7); //OK
	char d8[25] = "12/13/1999";
	//int test9 = formatDateValide(d8);//OK
	char d9[25] = "28,02/2013";
	int test10 = formatDateValide(d9);
	//printf("test1 %d\n",test1);
	//printf("test2 %d\n",test2);
	//printf("test3 %d\n",test3);
	//printf("test4 %d\n",test4);
	//printf("test5 %d\n",test5);
	//printf("test6 %d\n",test6);
	//printf("test7 %d\n",test7);
	//printf("test8 %d\n",test8);
	//printf("test9 %d\n",test9);
	printf("test10 %d\n",test10);

	int t = stringValide(d9);
	printf("%d\n",t);
	char * gg = "salut";
	int t2 = stringValide(gg);
	printf("%d\n",t2);
	char h[50] = "10:50";
	char h1[50] = "10:60";
	char h2[50]= "24:30";
	char h3[50] = "10h50";
	char h4[50] = "10:020";
	//int test1 = formatHeureValide(h); //OK
	//int test2 = formatHeureValide(h1);//OK
	//int test3 = formatHeureValide(h2);//OK
	//int test4 = formatHeureValide(h3);//OK
	//int test5 = formatHeureValide(h4);//OK
	//printf("test10 %d\n",test1);
	//printf("test2 %d\n",test2);
	//printf("test3 %d\n",test3);
	//printf("test4 %d\n",test4);
	//printf("test5 %d\n",test5);
	
	return (EXIT_SUCCESS);
}*/
