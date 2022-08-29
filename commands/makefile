PROJECT=commands

OUTPUT=lib$(PROJECT).a

CFLAGS = -Wall -Werror
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
