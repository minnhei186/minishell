#!/bin/bash


assert(){
	printf '%-30s:' "\"$1\""

	eval "$1"

	if [ $? -eq 0 ]; then
		echo "PASS"
	else
		echo "FAIL"
	fi
}

assert "[ 1 -eq 1 ]"
assert "ls /tmp"
