#definition du compilateur
CC = gcc

# specification des options du compilateur
CFLAGS = -ansi -Wall

#inclusion de la glib
#GLIBFLAGS = -I /usr/include/glib-2.0 -I /usr/lib/glib-2.0/include
#LIENFLAGS = -lglib-2.0

# nom de l'executable
PROG = agenda

# defintion de la cible a reconstruire
all : $(PROG)

#edition de liens et production de l'executable
$(PROG) :  verifs.o charger.o enregistrementFormatCSV.o enregistrementEvenement.o enregistrementParticipants.o conversion.o emplacementDispo.o participants.o  ajouterEvenement.o modifierEvenement.o supprimerEvenement.o main.o
	$(CC) $(CFLAGS) verifs.o charger.o enregistrementFormatCSV.o enregistrementEvenement.o enregistrementParticipants.o conversion.o emplacementDispo.o participants.o ajouterEvenement.o modifierEvenement.o main.o  supprimerEvenement.o -o $(PROG) 

	
# compilation du fichier verifs
verifs.o : verifs.c Agenda.h
	$(CC) $(CFLAGS) -c verifs.c 

# compilation du fichier charger
charger.o : charger.c Agenda.h
	$(CC) $(CFLAGS) -c charger.c 

# compilation du fichier enregistrementFormatCSV
enregistrementFormatCSV.o : enregistrementFormatCSV.c Agenda.h
	$(CC) $(CFLAGS) -c enregistrementFormatCSV.c 

# compilation du fichier enregistrementEvenement
enregistrementEvenement.o : enregistrementEvenement.c Agenda.h
	$(CC) $(CFLAGS) -c enregistrementEvenement.c 

# compilation du fichier enregistrementParticipants
enregistrementParticipants.o : enregistrementParticipants.c Agenda.h
	$(CC) $(CFLAGS) -c enregistrementParticipants.c 

# compilation du fichier conversion
conversion.o : conversion.c Agenda.h
	$(CC) $(CFLAGS) -c conversion.c 

# compilation du fichier emplacementDispo
emplacementDispo.o : emplacementDispo.c Agenda.h
	$(CC) $(CFLAGS) -c emplacementDispo.c 

# compilation du fichier participants
participants.o : participants.c Agenda.h
	$(CC) $(CFLAGS) -c participants.c  

# compilation du fichier ajouterEvenement
ajouterEvenement.o : ajouterEvenement.c Agenda.h
	$(CC) $(CFLAGS) -c ajouterEvenement.c  

# compilation du fichier modifierEvenement
modifierEvenement.o : modifierEvenement.c Agenda.h
	$(CC) $(CFLAGS) -c modifierEvenement.c  

# compilation du fichier supprimerEvenement
supprimerEvenement.o : supprimerEvenement.c Agenda.h
	$(CC) $(CFLAGS) -c supprimerEvenement.c  

# compilation du fichier main
main.o : main.c Agenda.h
	$(CC) $(CFLAGS) -c main.c  

#destruction de tous les fichiers intermediaires crees
clean :
	-rm -f *.o

# suppression de tout ce qui peut etre regenere
mrproper : clean
	-rm -f $(PROG)
	
	
