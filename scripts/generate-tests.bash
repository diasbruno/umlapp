#!/bin/env bash

set -eu

ALL_TESTS=""
RUN_ALL_TESTS=""

LIB_TEST_PATH="./$1/t"
LIB_MAKEFILE_PATH="${LIB_TEST_PATH}/makefile"

echo $LIB_TEST_PATH
echo $LIB_MAKEFILE_PATH

echo "include definitions.mk" > $LIB_MAKEFILE_PATH

COMMAND="clang -g -o \$@ \$< \$(CFLAGS) \$(LDFLAGS)"

for f in $(find $LIB_TEST_PATH -name "*.c"); do
    TEST_NAME=`basename $f | sed 's/\.c//g'`

    cat <<EOF >> $LIB_MAKEFILE_PATH
${TEST_NAME}: ${TEST_NAME}.c
	${COMMAND}

run-${TEST_NAME}: ${TEST_NAME}
	./${TEST_NAME}

EOF

    ALL_TESTS="${ALL_TESTS} ${TEST_NAME}"
    RUN_ALL_TESTS="${RUN_ALL_TESTS} run-${TEST_NAME}"
done



cat <<EOF >> $LIB_MAKEFILE_PATH
all: ${ALL_TESTS}

test: all

run-test: ${RUN_ALL_TESTS}

clean:
	rm -rf ${ALL_TESTS}
EOF
