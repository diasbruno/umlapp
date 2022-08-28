CFLAGS= -Wall -Werror
CFLAGS+= $(shell pkg-config --cflags gtk4 cglm cairo)
CFLAGS+= -I ../

SOURCES=$(wildcard *.c) $(wildcard commands/*.c)
OBJECTS=$(SOURCES:%.c=%.o)

$(info $(SOURCES) $(OBJECTS))

%.o: %.c
	clang -g -c -o $@ $< $(CFLAGS)

libsdk.a: $(OBJECTS)
	ar cr $@ $^

all: libsdk.a

clean:
	rm -rf libsdk.a $(OBJECTS)
