# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    raise.py                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/15 21:20:10 by geonwkim          #+#    #+#              #
#    Updated: 2024/07/15 21:20:45 by geonwkim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/usr/local/bin/python3
import os
import sys

# For testing bash commands with cat
os.kill(os.getpid(), int(sys.argv[1]))

# bash-3.2$ cat << E""
# $HOME
# E
# $HOME


# bash-3.2$ cat << E"fe"
# $HOME
# Efe
# $HOME

# bash-3.2$ cat <<"a   a"
# a  a
# a   a
# a  a

# bash-3.2$ cat <<E
# $HOME
# E
# /Users/name

# bash-3.2$ cat <<"a   a"
# $HOME
# a    a
# a   a
# $HOME
# a    a

# Quoteがあれば、展開、Quoteがないなら展開しない

# bash-3.2$ cat <<'a   a'
# $HOME
# a
# $HOME

# bash-3.2$ cat << ''$PATH
# $PATH
# bash-3.2$ cat << ''$PATH
# aaaa
# $PATH
# aaaa
