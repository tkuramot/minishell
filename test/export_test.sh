#!/bin/bash

func=$(find . -name "assert.sh")
source $func

echo
echo PIPE TEST

assert export aa=bb
assert export aa=
assert export aa=aa_
assert export aa=_aa
assert export aa=aa?
assert export aa=aa@
assert export aa=aa]
assert export aa=aa[
