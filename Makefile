# Makefile

CC ?= gcc

TARGET := OpenGL-test

CFLAGS += -O3
CFLAGS += -Wall
CFLAGS += -Werror

# Non platform specific libs
LDFLAGS += -lSOIL
LDFLAGS += -lSDL2
LDFLAGS += -lm


# MinGW builds are default on windows on
# other platforms make must be called via:
# make $(TARGET).exe
ifeq ($(OS), Windows_NT)
	PLATFORM := MinGW
else
	ifeq ($(firstword $(MAKECMDGOALS)), $(TARGET).exe)
		PLATFORM := MinGW
	else
		CFLAGS += -fpic
		LDFLAGS += -lGL
		LDFLAGS += -lGLEW
	endif
endif

# If there are any platform specific
# configurations store them in Makefile.$(PLATFORM)
-include ${CURDIR}/Makefile.$(PLATFORM)

# Project dirs.
SRC := src
BIN := bin
EXT := ext

# For ever $(SRC)/*.c the object file
# is $(SRC)/*.o
SOURCES := $(wildcard $(SRC)/*.c)
OBJECTS := $(SOURCES:.c=.o)

DEPS += $(EXT)/gl-matrix.c/libgl-matrix
LDFLAGS += -l:$(EXT)/gl-matrix.c/libgl-matrix.a
CPPFLAGS += -I$(EXT)/gl-matrix.c

$(TARGET): $(DEPS) $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(LDFLAGS)

# Compile object files separately to prevent
# unnecessarily recompilation.
%.o: %.c %.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

# Windows requires *.dll in same
# dir as .exe
%.dll: $(DLL)/%.dll
	cp $(DLL)/$@ .

$(EXT)/gl-matrix.c/libgl-matrix:
	cd $(EXT)/gl-matrix.c && $(MAKE)

# Although $(DLLS) is platform specific, other
# platforms replace it with nothing as it is
# not defined.
.PHONY: clean
clean:
	rm -fr $(TARGET) $(OBJECTS)
	cd $(EXT)/gl-matrix.c && $(MAKE) clean

