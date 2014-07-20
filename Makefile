
# Makefile

CC = gcc

CFLAGS += -O3
CFLAGS += -Wall
CFLAGS += -Werror 

LDFLAGS += -lSDL2
LDFLAGS += -lGL
LDFLAGS += -lm
LDFLAGS += -lGLEW

TARGET = OpenGL-test

SRC = src
SHADERDIR = $(SRC)/shaders

SOURCES = $(wildcard $(SRC)/*.c)
OBJECTS = $(SOURCES:.c=.o)

SHADERS = $(wildcard $(SHADERDIR)/*.glsl)
SHADERS_H = $(SHADERS:.glsl=.glsl.h)


$(TARGET): $(SHADERS_H) $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) $(LDFLAGS)

%.o: %.c %.h $(SHADERS_H)
	$(CC) -fPIC $(CFLAGS) -c -o $@ $<

%.glsl.h: %.glsl
	sed -e 's/\\/\\\\/g;s/"/\\"/g;s/ /\\t/g;s/^/"/;s/$$/\\n"/' $< > $@
clean:
	rm -f $(TARGET) $(OBJECTS) $(SHADERS_H)

