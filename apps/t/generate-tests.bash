#!/bin/env bash

set -eu

echo "include definitions.mk" > makefile

COMMAND="clang -g -o \$@ \$< \$(CFLAGS) \$(LDFLAGS)"

ALL_TESTS=""

for f in $(find ./ -name "*.c" | sed 's/\.c//g'); do
    cat <<EOF >>makefile
.PHONY = ${f}
${f}: ${f}.c
	${COMMAND}

EOF

    ALL_TESTS="${ALL_TESTS} ${f}"
done

cat <<EOF >>makefile
all: ${ALL_TESTS}

clean:
	rm -rf ${ALL_TESTS}
EOF

