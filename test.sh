#!/bin/bash
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
RESET="\033[0m"
OK=$GREEN"OK"$RESET
NG=$RED"NG"$RESET

cat <<EOF | gcc -xc -o a.out -
#include <stdio.h>
int main() { printf("hello from a.out\n"); }
EOF

cat <<EOF | gcc -xc -o print_args -
#include <stdio.h>
int main(int argc, char *argv[]) {
	for (int i = 0; argv[i]; i++)
		printf("argv[%d] = [%s]\n", i, argv[i]);
}
EOF

cat <<EOF | gcc -xc -o exit42 -
int main() { return 42; }
EOF

print_desc() {
	echo -e $YELLOW"$1"$RESET
}

cleanup() {
	rm -f cmp out a.out print_args exit42 infinite_loop no_exec_perm no_read_perm
}

assert() {
	COMMAND="$1"
	shift
	printf '%-70s:' "[$COMMAND]"
	# exit status
	echo -n -e "$COMMAND" | bash >cmp 2>&-
	expected=$?
	for arg in "$@"
	do
		mv "$arg" "$arg"".cmp"
	done
	echo -n -e "$COMMAND" | ./minishell >out 2>&-
	actual=$?
	for arg in "$@"
	do
		mv "$arg" "$arg"".out"
	done

	if diff out cmp > /dev/null; then
		echo -e -n "  diff $OK"
	else
		echo -e -n "  diff $NG"
		printf '%-70s:\n' "[$COMMAND]" >> error.log
		diff -U 1 out cmp >>error.log
	fi

	if [ "$actual" = "$expected" ]; then
		echo -e -n "  status $OK"
	else
		echo -e -n "  status $NG, expected $expected but got $actual"
		printf '%-70s:' "[$COMMAND]" >>error.log
		echo "status NG, expected $expected but got $actual" >>error.log
	fi
	for arg in "$@"
	do
		echo -n "  [$arg] "
		diff "$arg"".cmp" "$arg"".out" >/dev/null && echo -e -n "$OK" || echo -e -n "$NG"
		rm -f "$arg"".cmp" "$arg"".out"
	done
	echo
}

rm -f error.log

# Empty line (EOF)
assert ''

# Absolute path commands without args
assert '/bin/pwd'
assert '/bin/echo'
assert '/bin/ls'

# Search command path without args
assert 'pwd'
assert 'echo'
assert 'ls'
assert './a.out'

## no such command
assert 'a.out'
assert 'nosuchfile'

## command not found
assert '""'
# assert '.' # . is a builtin command in bash
assert '..'

## is a directory
assert './'
assert '/'
assert '/etc'
assert '/etc/'
assert '////'

## Permission denied
echo "int main() { }" | gcc -xc -o no_exec_perm -
chmod -x no_exec_perm
assert 'no_exec_perm'
assert './no_exec_perm'
echo "int main() { }" | gcc -xc -o no_read_perm -
chmod -r no_read_perm
assert 'no_read_perm'
assert './no_read_perm'

mkdir -p /tmp/a /tmp/b
echo "int main() { return 1; }" | gcc -xc -o /tmp/a/simple_test -
echo "int main() { return 2; }" | gcc -xc -o /tmp/b/simple_test -

print_desc "/tmp/a /tmp/b both with permission"

print_desc "/tmp/a /tmp/b both without permission"
chmod -x /tmp/a/simple_test; chmod -x /tmp/b/simple_test;

print_desc "a with permission, b without permission"
chmod +x /tmp/a/simple_test; chmod -x /tmp/b/simple_test;

print_desc "a without permission, b with permission"
chmod -x /tmp/a/simple_test; chmod +x /tmp/b/simple_test;

# Tokenize
## unquoted word
assert 'ls /'
assert 'echo hello    world     '

## single quote
assert "./print_args 'hello   world' '42Tokyo'"
assert "echo 'hello   world' '42Tokyo'"
assert "echo '\"hello   world\"' '42Tokyo'"

## double quote
assert './print_args "hello   world" "42Tokyo"'
assert 'echo "hello   world" "42Tokyo"'
assert "echo \"'hello   world'\" \"42Tokyo\""

## combination
assert "echo hello'      world'"
assert "echo hello'  world  '\"  42Tokyo  \""

# Redirect
## Redirecting output
assert 'echo hello >hello.txt' 'hello.txt'
assert 'echo hello >f1>f2>f3' 'f1' 'f2' 'f3'

## Redirecting input
assert 'cat <Makefile'
echo hello >f1
echo world >f2
echo 42Tokyo >f3
assert 'cat <f1<f2<f3'
rm -f f1 f2 f3
assert 'cat <hoge'

## Appending Redirected output
assert 'pwd >>pwd.txt' 'pwd.txt'

## Here Document
(
	print_desc 'export EOF="eof"'
	export EOF="eof"
)

# Pipe
assert 'cat Makefile | grep minishell'
assert 'cat | cat | ls\n\n'

# Expand Variable
assert 'echo $USER'
assert 'echo $USER$PATH$TERM'
assert 'echo "$USER  $PATH   $TERM"'

# Special Parameter $?
assert 'echo $?'

# Signal handling
echo "int main() { while (1) ; }" | gcc -xc -o infinite_loop -

## Signal to shell processes
print_desc "SIGTERM to SHELL"
(sleep 0.01; pkill -SIGTERM bash;
 sleep 0.01; pkill -SIGTERM minishell) &
assert './infinite_loop' 2>/dev/null # Redirect stderr to suppress signal terminated message

print_desc "SIGQUIT to SHELL"
(sleep 0.01; pkill -SIGQUIT bash; # SIGQUIT should not kill the shell
 sleep 0.01; pkill -SIGTERM bash;
 sleep 0.01; pkill -SIGQUIT minishell; # SIGQUIT should not kill the shell
 sleep 0.01; pkill -SIGTERM minishell) &
assert './infinite_loop' 2>/dev/null # Redirect stderr to suppress signal terminated message

print_desc "SIGINT to SHELL"
(sleep 0.01; pkill -SIGINT bash; # SIGINT should not kill the shell
 sleep 0.01; pkill -SIGTERM bash;
 sleep 0.01; pkill -SIGINT minishell; # SIGINT should not kill the shell
 sleep 0.01; pkill -SIGTERM minishell) &
assert './infinite_loop' 2>/dev/null # Redirect stderr to suppress signal terminated message

## Signal to child processes
print_desc "SIGTERM to child process"
(sleep 0.01; pkill -SIGTERM infinite_loop;
 sleep 0.01; pkill -SIGTERM infinite_loop) &
assert './infinite_loop'

print_desc "SIGINT to child process"
(sleep 0.01; pkill -SIGINT infinite_loop;
 sleep 0.01; pkill -SIGINT infinite_loop) &
assert './infinite_loop'

print_desc "SIGQUIT to child process"
(sleep 0.01; pkill -SIGQUIT infinite_loop;
 sleep 0.01; pkill -SIGQUIT infinite_loop) &
assert './infinite_loop'

print_desc "SIGUSR1 to child process"
(sleep 0.01; pkill -SIGUSR1 infinite_loop;
 sleep 0.01; pkill -SIGUSR1 infinite_loop) &
assert './infinite_loop'

# Manual Debug
# $ ./minishell
# $
# 1. Ctrl-\
# 2. Ctrl-C
# 3. Ctrl-D
#
# $ ./minishell
# $ hogehoge
# 1. Ctrl-\
# 2. Ctrl-C
# 3. Ctrl-D
#
# $ ./minishell
# $ cat <<EOF
# >
# 1. Ctrl-\
# 2. Ctrl-C
# 3. Ctrl-D
#
# $ ./minishell
# $ cat <<EOF
# > hoge
# > fuga
# 1. Ctrl-\
# 2. Ctrl-C
# 3. Ctrl-D

# Builtin
## exit
assert 'exit'
assert 'exit 42'
assert 'exit -42'
assert 'exit +42'
assert 'exit ""'
assert 'exit hello'
assert 'exit 42Tokyo'
assert 'exit 1 2'
assert 'exit a 2'
assert 'exit 9223372036854775806'
assert 'exit 9223372036854775807'
assert 'exit 9223372036854775808'
assert 'exit -9223372036854775807'
assert 'exit -9223372036854775808'
assert 'exit -9223372036854775809'
assert 'exit -92233720368fds'

## export
print_desc "Output of 'export' differs, but it's ok."
assert 'export' # order of variables, default variables differs...
assert 'export | grep nosuch | sort'
assert 'export [invalid]'

## unset
(
	print_desc 'export hoge fuga=fuga'
	export hoge fuga=fuga
	assert 'unset'
	assert 'unset hoge'
	assert 'unset fuga'
	assert 'unset nosuch'
	assert 'unset [invalid]'
	assert 'unset hoge fuga'
	assert 'unset hoge nosuch fuga'
)

## env
print_desc "Output of 'env' differs, but it's ok."
assert 'env' # order of variables, default variables differs...
assert 'env | grep hoge | sort'

## cd
assert 'cd'
assert 'cd .'
assert 'cd ..'
assert 'cd ///'
assert 'cd /tmp'
assert 'cd /tmp/'
assert 'cd /tmp///'
assert 'cd /../../../././.././'
assert 'cd src'

## echo
assert 'echo'
assert 'echo hello'
assert 'echo hello "    " world'
assert 'echo -n'
assert 'echo -n hello'
assert 'echo -n hello world'
assert 'echo hello -n'
assert 'echo -n-n-n'
assert 'echo ";|()"'

## pwd
assert 'pwd'

##edge cases
assert 'exit | exit'
assert 'exit 10 | exit 42'
assert 'exit 10 | exit 999'
assert 'exit -9223372036854775809 | exit 9223372036854775808'
assert 'cat < text'
assert 'cat > text'
assert 'echo "a" >> text'
assert 'cat >> text'
assert 'ls -la > text'
assert '< $A'
assert '> $A'
assert '>> $A'
assert '<< $A'
assert '$USER='
assert 'echo aaa > aaaa > aa > a'
assert 'echo $'
assert 'echo $a'
assert 'x=x'
assert 'echo '$?''
assert 'echo ''$?'''
assert 'echo '''$?''''
assert 'echo '$USER''
assert 'echo ''$USER'''
assert 'echo '''$USER''''
assert 'echo '''$A''''
assert 'echo '$A''
assert 'echo < none | ls'
assert 'cat < none | ls'
assert 'echo a=a'
print_desc "Output of 'export $a $b' differs, but it's ok."
assert 'export $a $b'
assert 'echo $a -n $b'
assert 'echo $a $USER -n'
assert 'echo $a -n $USER'
assert 'cat $a $b $c test'
assert 'cat $a $b $c'
assert 'cat $a $b $c text'

cleanup

if [ -f error.log ]; then
	echo -e $RED"Some tests have failed. Please review the error.log for more information."$RESET
fi


#a=a
#aa="echo hoge"
#aa=AA | echo $aa

#env -i ./minishell
#ls | 

#export $abc=fds
# $ARG=123
#echo ‘'''$A'''’
#echo ''$A''
#export B="echo a | $C"
#export B="echo a | ls -la > text | wc -l"
#export B="ls -la > text"
#a=a b="echo a" c="wc -l" d="ls -la"
