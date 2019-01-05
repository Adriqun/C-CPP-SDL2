#!/bin/bash

# Display the UID
echo "Your UID is ${UID}"

# Display the username
USER_NAME=$(id -un) #id -un / whoami / id --user --name
#USER_NAME=`id -un` # Older style syntax.
echo "Your username is $USER_NAME"

# Display if the user is the root user or not
if [[ "$UID" -eq 0 ]]
then
	echo "You are root."
else
	echo "You are not root."
fi

