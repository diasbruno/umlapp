include definitions.mk
test-select-command: test-select-command.c
	clang -g -o $@ $< $(CFLAGS) $(LDFLAGS)

run-test-select-command: test-select-command
	./test-select-command

test-create-command: test-create-command.c
	clang -g -o $@ $< $(CFLAGS) $(LDFLAGS)

run-test-create-command: test-create-command
	./test-create-command

all:  test-select-command test-create-command

test: all

run-test:  run-test-select-command run-test-create-command

clean:
	rm -rf  test-select-command test-create-command
