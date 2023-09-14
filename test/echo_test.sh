#!/bin/bash

func=$(find . -name "assert.sh")
source $func

echo
echo ECHO TEST

# without option
assert echo
assert echo aaaaaaa
assert echo aaa bbb ccc
assert echo   aaa   bbb    ccc
assert echo -nnnnan
assert echo -a
assert echo ---------n
assert echo --
assert echo -

# with option
assert echo -n
assert echo -nnnnn
assert echo -nnnnnnnn -n
assert echo -nnnnnnnn -nnnnn
assert echo -nnnnnnnn -na
assert echo -nnnnnnnn -a
assert echo -n 123
assert echo -nnnnnnnn -n 1 2 3
assert echo -nnnnnnnn -nnnnn 1 2 3
assert echo -nnnnnnnn -na 1 2 3
assert echo -nnnnnnnn -a 1 2 3
