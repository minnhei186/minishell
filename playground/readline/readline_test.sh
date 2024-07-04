#!/bin/bash


assert(){
	
	printf '%-30s:' "\"$1\""

	echo -n -e "$1" | bash >cmp 

	echo -n -e "$1" |./minishell >out 
	


}

assert "echo helloefeafa"
