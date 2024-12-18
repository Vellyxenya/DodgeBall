# Makefile

# Definitions de macros

CC     = g++
CFLAGS = -Wall -std=c++11 #evt rajouter -g avant -Wall
CFILES = ball.cc map.cc player.cc tools.cc projet.cc simulation.cc obstacle.cc actor.cc
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
	@/bin/rm -f *.o *.x *.c~ *.h~ *.h.gch prog

#
# -- Regles de dependances generees automatiquement
#
# DO NOT DELETE THIS LINE
ball.o: ball.cc ball.h tools.h actor.h error.h define.h
map.o: map.cc map.h actor.h tools.h error.h define.h player.h ball.h \
 obstacle.h
player.o: player.cc player.h tools.h actor.h error.h define.h
tools.o: tools.cc tools.h
projet.o: projet.cc simulation.h define.h tools.h map.h actor.h error.h \
 player.h ball.h obstacle.h
simulation.o: simulation.cc simulation.h define.h tools.h map.h actor.h \
 error.h player.h ball.h obstacle.h
obstacle.o: obstacle.cc obstacle.h tools.h actor.h error.h define.h
actor.o: actor.cc actor.h tools.h error.h define.h
