# Definitions de macros

CXX     = g++
CXXFLAGS = -g -Wall -std=c++11
CXXFILES = projet.cc simulation.cc base.cc message.cc geomod.cc
OFILES = projet.o simulation.o base.o message.o geomod.o
#remplacer la ligne 6 par la ligne 8 en cas de disfonctionnement
#OFILES = $(CXXFILES:.cc=.o)

# Definition de la premiere regle

projet: $(OFILES)
	$(CXX) $(OFILES) -o projet

# Definitions de cibles particulieres

depend:
	@echo " *** MISE A JOUR DES DEPENDANCES ***"
	@(sed '/^# DO NOT DELETE THIS LINE/q' Makefile && \
	  $(CXX) -MM $(CXXFLAGS) $(CXXFILES) | \
	  egrep -v "/usr/include" \
	 ) >Makefile.new
	@mv Makefile.new Makefile

clean:
	@echo " *** EFFACE MODULES OBJET ET EXECUTABLE ***"
	@/bin/rm -f *.o *.x *.cc~ *.h~ projet

#
# -- Regles de dependances generees automatiquement
#
# DO NOT DELETE THIS LINE
projet.o: projet.cc simulation.h gisement.h geomod.h constantes.h \
 message.h base.h robot.h
simulation.o: simulation.cc simulation.h gisement.h geomod.h constantes.h \
 message.h base.h robot.h
base.o: base.cc base.h geomod.h constantes.h message.h gisement.h robot.h
message.o: message.cc message.h
geomod.o: geomod.cc geomod.h
