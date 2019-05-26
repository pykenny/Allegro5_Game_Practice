# Compiler flags
CC=gcc
CFLAGS=-Wall
LIBS=`pkg-config --cflags --libs allegro-5 allegro_main-5 allegro_image-5 allegro_font-5 allegro_ttf-5 allegro_audio-5 allegro_acodec-5`

# Paths
ODIR_TOP=./bin
ODIR_RSR=./bin/resource
IDIR_TOP=./src/headers
IDIR_RSR=./src/resource
SDIR_TOP=./src/implement
SDIR_RSR=./src/resource

# Object files
_OBJ_MAINF=main.c
_OBJ_MAIN=$(SDIR_TOP)/$(_OBJ_MAINF)
_OBJ_TOPS=process.o control.o errcode.o
_OBJ_TOP=$(patsubst %,$(ODIR_TOP)/%,$(_OBJ_TOPS))
_OBJ_RSRS=resource_stage.o
_OBJ_RSR=$(patsubst %,$(ODIR_RSR)/%,$(_OBJ_RSRS))
OBJ=$(_OBJ_MAIN) $(_OBJ_TOP) $(_OBJ_RSR)

# Header files
_DEPS_TOPS=process.h control.h errcode.h resource.h statecodes.h process.h routine_info.h general_settings.h
_DEPS_TOP=$(patsubst %,$(IDIR_TOP)/%,$(_DEPS_TOPS))
_DEPS_RSRS=resource_stage.h
_DEPS_RSR=$(patsubst %,$(IDIR_RSR)/%,$(_DEPS_RSRS))
DEPS=$(_DEPS_TOP) $(_DEPS_RSR)

# Object file compiling
$(ODIR_TOP)/%.o: $(SDIR_TOP)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
$(ODIR_RSR)/%.o: $(SDIR_RSR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# Executable compiling
play.exe: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

# Phony operations
.PHONY: clean

# Clean-up
clean:
	rm -f $(ODIR_TOP)/*.o $(ODIR_RSR)/*.o ./play.exe *~ core
