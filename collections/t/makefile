include definitions.mk
test-array: test-array.c
	clang -g -o $@ $< $(CFLAGS) $(LDFLAGS)

run-test-array: test-array
	./test-array

all:  test-array

test: all

run-test:  run-test-array

clean:
	rm -rf  test-array
