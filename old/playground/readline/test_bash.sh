#!/bin/bash

assert()
{
	printf '%-30s\n' "$1"

	eval "$1"

}

gcc readline_test.c -lreadline 
./a.out



ls -la

