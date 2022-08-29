include definitions.mk
test-frame: test-frame.c
	clang -g -o $@ $< $(CFLAGS) $(LDFLAGS)

run-test-frame: test-frame
	./test-frame

all:  test-frame

test: all

run-test:  run-test-frame

clean:
	rm -rf  test-frame
