CFLAGS= -Wall -Werror
CFLAGS+= $(shell pkg-config --cflags gtk4 cglm)
CFLAGS+= -I ../

LDFLAGS = $(shell pkg-config --libs gtk4 cglm)
LDFLAGS+= -L../sdk -lsdk

SOURCES=$(wildcard *.c) $(wildcard commands/*.c)
OBJECTS=$(SOURCES:%.c=%.o)

$(info $(SOURCES) $(OBJECTS))

%.o: %.c
	clang -g -c -o $@ $< $(CFLAGS)

umlapp: $(OBJECTS)
	clang -g -o $@ $(CFLAGS) $^ $(LDFLAGS)

all: umlapp

clean:
	rm -rf umlapp $(OBJECTS)
