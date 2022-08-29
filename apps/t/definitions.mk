CFLAGS= -Wall -Werror
CFLAGS+= $(shell pkg-config --cflags gtk4 cglm cairo)
CFLAGS+= -I ../..

LDFLAGS = $(shell pkg-config --libs gtk4 cglm cairo)
LDFLAGS+= $(foreach L,collections geometry commands,-L../../$(L) -l$(L))
