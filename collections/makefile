PROJECT=collections

OUTPUT=lib$(PROJECT).a

CFLAGS= -Wall -Werror
CFLAGS+= -I ./ -I ./..

SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:%.c=%.o)

%.o: %.c
	clang -g -c -o $@ $< $(CFLAGS)

$(OUTPUT): $(OBJECTS)
	ar cr $@ $^

all: $(OUTPUT)

.PHONY: test
test: all
	make -C ./t -k test

.PHONY: run-test
run-test: test
	make -C ./t -k run-test

clean:
	rm -rf $(OUTPUT) $(OBJECTS)
