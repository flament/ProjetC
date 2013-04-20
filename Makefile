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
$(PROG) :  verifs.o main.o
	$(CC) $(CFLAGS) verifs.o main.o  -o $(PROG) 

	
# compilation du fichier verifs
verifs.o : verifs.c Agenda.h
	$(CC) $(CFLAGS) -c verifs.c 

# compilation du fichier main
main.o : main.c Agenda.h
	$(CC) $(CFLAGS) -c main.c  

#destruction de tous les fichiers intermediaires crees
clean :
	-rm -f *.o

# suppression de tout ce qui peut etre regenere
mrproper : clean
	-rm -f $(PROG)
	
	
