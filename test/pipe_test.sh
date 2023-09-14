#!/bin/bash

func=$(find . -name "assert.sh")
source $func

echo
echo PIPE TEST

assert "cat Makefile | grep SRC"
assert "cat Makefile | grep SRC | wc"
assert "cat Makefile | grep SRC | wc"
assert "cat | cat | ls"
assert "cat | cat | grep"
assert "ls | cat | grep Makefile"
assert "echo hi | cat"
assert "echo hi | cat | wc"
assert "echo hi | cat | wc"
