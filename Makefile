CC=gcc
CFLAGS=-Wall
LIBS=`pkg-config --cflags --libs allegro-5 allegro_main-5 allegro_image-5 allegro_font-5 allegro_ttf-5 allegro_audio-5 allegro_acodec-5`

ODIR=./
IDIR=./
_OBJ = main.c process.o resource.o control.o errcode.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))
_DEPS = process.h control.h errcode.h resource.h statecodes.h process.h routine_info.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

# Object file compiling
$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# Executable compiling
play.exe: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

# Phony operations
.PHONY: clean

# Clean-up
clean:
	rm -f $(ODIR)/*.o *.exe *~ core
