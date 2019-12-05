IDIR = header
CC = g++
CFLAGS = -I $(IDIR) -Wall -g -std=c++11
ODIR = obj

_DEPS = library.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o proxy.o inspector.o spyder.o dump.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

aracne: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
