CFLAGS= -Wall -Werror
CFLAGS+= $(shell pkg-config --cflags gtk4 cglm cairo)
CFLAGS+= -I ./

LDFLAGS = $(shell pkg-config --libs gtk4 cglm cairo)
LDFLAGS+= -L./sdk libsdk.a

libsdk.a:
	make -C sdk -k all

umlapp:
	make -C apps -k all

.DEFAULT_GOAL := all

all: libsdk.a umlapp

clean-apps:
	make -C apps -k clean

clean-sdk:
	make -C sdk -k clean

clean-all: clean-sdk clean-apps clean
