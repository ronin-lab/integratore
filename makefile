 
SHELL=/bin/sh #Shell da utilizzare per l'esecuzione dei comandi

### Path to sources                 ###
INTEGRATORE  = $(PWD)
SRC_INTEGRATORE   = $(INTEGRATORE)/src
#UPDIR      = ../


### Compiler 
COMP       = gnu

include COMP.$(COMP)


##CC=cc #Compilatore da utilizzare

OBJECTS=BASIC.o METODI.o #File oggetto
SRCS=BASIC.c METODI.c #File sorgente

### Rules                           ###
all: lib integratore 

.SUFFIXES: .c .o 

##-I$(UPDIR)

lib:
	cd $(SRC_INTEGRATORE); $(CC) $(CFLAGS) -o BASIC.o -c BASIC.c; $(CC) $(CFLAGS) -o METODI.o -c METODI.c

integratore:
	cd $(SRC_INTEGRATORE); $(CC) -I$(UPDIR) $(CFLAGS) integratore.c $(OBJECTS) -o integratore


	@echo; if [ ! -d $(INTEGRATORE)/bin_$(COMP) ]; then mkdir $(INTEGRATORE)/bin_$(COMP); fi
	@echo; mv $(SRC_INTEGRATORE)/integratore $(INTEGRATORE)/bin_$(COMP)/.





#target "helloworld" richiede $(OBJECTS) per compilare
#helloworld: $(OBJECTS)
#        $(CC) -o $@ $<
 
##target "helloworld.o" richiede $(SRCS) per creare i file oggetto
#helloworld.o: $(SRCS)
#        $(CC) -c -o $@ $<

#target "clean" pulisce i file oggetto e il binario nella directory corrente 
#clean:
#        rm -f helloworld helloworld.o

#target "clean" non è un file!
#.PHONY: clean
