CFLAGS= -Wall -Werror
CFLAGS+= $(shell pkg-config --cflags gtk4 cglm cairo)
CFLAGS+= -I ../

LDFLAGS = $(shell pkg-config --libs gtk4 cglm cairo)
LDFLAGS+= $(foreach L,collections geometry commands render,-L../$(L) -l$(L))

SOURCES=$(wildcard *.c) $(wildcard commands/*.c)
OBJECTS=$(SOURCES:%.c=%.o)

%.o: %.c
	clang -g -c -o $@ $< $(CFLAGS)

umlapp: $(OBJECTS)
	clang -g -o $@ $(CFLAGS) $^ $(LDFLAGS)

all: umlapp

test:
	make -C ./t -k test

clean:
	rm -rf umlapp $(OBJECTS)
