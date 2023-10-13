#!/bin/bash

func=$(find . -name "assert.sh")
source $func

echo
echo REDIRECT TEST

assert "cat Makefile < none | cat"
assert "cat Makefile < Makefile > /tmp/file"
assert "cat Makefile < none"
assert "cat Makefile < src"
assert "cat Makefile > src"
assert "cat Makefile >> src"
assert "cat Makefile >> src << a"
assert "cat << a < Makefile"
