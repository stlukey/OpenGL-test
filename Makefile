# Makefile

CC = gcc

CFLAGS += -O3
CFLAGS += -Wall
CFLAGS += -Werror 

CPPFLAGS += -Iext/linmath.h

LDFLAGS += -lSDL2
LDFLAGS += -lSOIL
LDFLAGS += -lGL
LDFLAGS += -lm
LDFLAGS += -lGLEW

TARGET = OpenGL-test

SRC = src
BIN = bin
EXT = ext
SHADERDIR = $(SRC)/shaders

SOURCES := $(wildcard $(SRC)/*.c)
OBJECTS := $(SOURCES:.c=.o)

#SHADERS := $(wildcard $(SHADERDIR)/*.glsl)
#SHADERS_H := $(SHADERS:.glsl=.glsl.h)


DEPS += linmath.h
DEPS := $(addprefix $(EXT)/, $(DEPS))

$(TARGET): $(DEPS) $(OBJECTS)
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $(TARGET) $(OBJECTS) $(LDFLAGS)

%.o: %.c %.h
	$(CC) -fpic $(CFLAGS) -c -o $@ $<

#%.glsl.h: %.glsl
#	sed -e 's/\\/\\\\/g;s/"/\\"/g;s/ /\\t/g;s/^/"/;s/$$/\\n"/' $< > $@

ext/%:
	git submodule update --init --recursive $@

clean:
	rm -fr $(TARGET) $(OBJECTS) $(SHADERS_H) $(BIN)

