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
# configurations store them in Makefile.$(PLATFORM).
-include ${CURDIR}/Makefile.$(PLATFORM)

# Project dirs.
SRC := src
BIN := bin
EXT := ext

# For ever $(SRC)/*.c the object file
# is $(SRC)/*.o
SOURCES := $(wildcard $(SRC)/*.c)
OBJECTS := $(SOURCES:.c=.o)

# Git submodule libs from $(EXT)/
CPPFLAGS += -I$(EXT)/linmath.h
DEPS += $(addsuffix /.git, $(addprefix $(EXT)/,\
							linmath.h))

$(TARGET): $(DEPS) $(OBJECTS) 
	$(CC) -o $(TARGET) $(OBJECTS) $(LDFLAGS)

# Windows requires *.dll in same
# dir as .exe
ifdef DLL
	cp $(addprefix $(DLL)/, $(DLLS)) .
endif

# Compile object files separately to prevent
# unnecessarily recompilation.
%.o: %.c %.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

# Some libs are downloaded through git submodules.
$(EXT)/%/.git: $(EXT)/%
	git submodule update --init $<

# Although $(DLLS) is platform specific, other
# platforms replace it with nothing as it is
# not defined.
.PHONY: clean
clean:
	rm -fr $(TARGET) $(OBJECTS) $(DLLS)

