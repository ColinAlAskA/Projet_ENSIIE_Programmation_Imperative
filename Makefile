CC=gcc
CFLAGS=-Wall -Wextra -Werror
LFLAGS=-lm

projet_ppm: projet.o pixel.o opacite.o couleur.o pile.o machine.o
	$(CC) -o $@ $^ $(LFLAGS)

projet.o: projet.c machine.h
	$(CC) $(CFLAGS) -o $@ -c $<

pixel.o: pixel.c pixel.h
	$(CC) $(CFLAGS) -o $@ -c $<

opacite.o: opacite.c opacite.h pixel.h
	$(CC) $(CFLAGS) -o $@ -c $<

couleur.o: couleur.c couleur.h pixel.h
	$(CC) $(CFLAGS) -o $@ -c $<

pile.o: pile.c pile.h pixel.h
	$(CC) $(CFLAGS) -o $@ -c $<

machine.o: machine.c machine.h couleur.h opacite.h pile.h pixel.h
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f ./*.o