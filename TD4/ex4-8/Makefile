# NE PAS OUBLIER D'AJOUTER LA LISTE DES DEPENDANCES A LA FIN DU FICHIER

CIBLES = oui-ou-non
SRCS = executer-avant-delai.c  oui-ou-non.c
LIBS =  

PREFIX =  ../..
###########################################################

OBJS = $(SRCS:.c=.o)
INCDIR = $(PREFIX)/include
LIBDIR = $(PREFIX)/lib
BINDIR = $(PREFIX)/bin

# nom du compilateur
CC = gcc

#options du compilateur 
CFLAGS = -Wall -pedantic -g 

# option du preprocesseur
CPPFLAGS =  -I$(INCDIR) 

# options du linker et liste des biblioth�ques � charger
LDFLAGS =                         
LDLIBS = -L$(LIBDIR) $(LIBS)  

# cible par d�faut
$(CIBLES): $(OBJS)

.PHONY: all
all: $(CIBLES)


.PHONY: clean
clean:
	rm -f *.o *~ $(CIBLES)

.PHONY: dep
dep:
	gcc $(CPPFLAGS) -MM $(SRCS)

# liste des d�pendances g�n�r�e par 'make dep'

executer-avant-delai.o: executer-avant-delai.c executer-avant-delai.h
oui-ou-non.o: oui-ou-non.c executer-avant-delai.h
