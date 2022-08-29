PROJECT=render

OUTPUT=lib$(PROJECT).a

CFLAGS= -Wall -Werror
CFLAGS+= $(shell pkg-config --cflags cairo gtk4)
CFLAGS+= -I ../ -I ./

SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:%.c=%.o)

%.o: %.c
	clang -g -c -o $@ $< $(CFLAGS)

$(OUTPUT): $(OBJECTS)
	ar cr $@ $^

all: $(OUTPUT)

clean:
	rm -rf $(OUTPUT) $(OBJECTS)
