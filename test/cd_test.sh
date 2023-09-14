#!/bin/bash

func=$(find . -name "assert.sh")
source $func

echo
echo ====== CD TEST

assert cd
