#!/bin/bash

# This script displays various information to the screen.
# Display 'Hello'
echo 'Hello'

# To check if command is build in, type in terminal.
# "type echo"
# More info.
# "type -a echo"

# You can type in the terminal also:
# /usr/bin/echo 'Hello'

# If command is not build in shell then type.
# "man uptime" instead of "help uptime"
# man means manual
# "uptime" is not build in

# Assign value to variable.
word='script'
# word0 <- valid
# _word <- valid
# 1word <- not valid

# Display the value.
echo "$word"

# Display exactly what you specified.
echo '$word'

# Alternative syntax.
echo "This is a shell ${word}."
# Append text to the variable. The usage of {}
echo "${word}ing is fun."