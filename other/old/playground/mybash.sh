#!/bin/bash

assert(){

	printf '%-30s' "$1"

	eval "$1"
}

assert " ls /tmp "

