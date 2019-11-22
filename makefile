IDIR =./headers
CC=gcc
CFLAGS=-I$(IDIR) -Wall

ODIR=build

LIBS=-lwiringPi -lncurses

_DEPS = adcCrudo.h apilada.h auto.h carrera.h choque.h contador.h controlVelocidad.h deteccionTecla.h explosion.h logueo.h loteria.h policia.h rs232.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = adcCrudo.o apilada.o auto.o carrera.o choque.o contador.o controlVelocidad.o deteccionTecla.o explosion.o logueo.o loteria.o main.o policia.o rs232.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: ./fuentes/%.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

ejecutable: $(OBJ)
		$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ ejecutable
