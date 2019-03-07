# Makefile

# Definitions de macros

CC     = g++
CFLAGS = -Wall -std=c++11 #evt rajouter -g avant -Wall
CFILES = ball.cc map.cc player.cc tools.cc projet.cc _errors_.cc simulation.cc obstacle.cc actor.cc
OFILES = $(CFILES:.cc=.o)

# Definition de la premiere regle

projet: $(OFILES)
	$(CC) $(OFILES) -o $@

# Definitions de cibles particulieres

depend:
	@echo " *** MISE A JOUR DES DEPENDANCES ***"
	@(sed '/^# DO NOT DELETE THIS LINE/q' Makefile && \
	  $(CC) -MM $(CFLAGS) $(CFILES) | \
	  egrep -v "/usr/include" \
	 ) >Makefile.new
	@mv Makefile.new Makefile

clean:
	@echo " *** EFFACE MODULES OBJET ET EXECUTABLE ***"
	@/bin/rm -f *.o *.x *.c~ *.h~ *.gch~ prog

#
# -- Regles de dependances generees automatiquement
#
# DO NOT DELETE THIS LINE
ball.o: ball.cc ball.h tools.h actor.h
map.o: map.cc map.h actor.h tools.h define.h
player.o: player.cc player.h tools.h actor.h
tools.o: tools.cc tools.h
projet.o: projet.cc simulation.h tools.h map.h actor.h define.h
_errors_.o: _errors_.cc
simulation.o: simulation.cc simulation.h tools.h map.h actor.h define.h
obstacle.o: obstacle.cc
actor.o: actor.cc actor.h tools.h
