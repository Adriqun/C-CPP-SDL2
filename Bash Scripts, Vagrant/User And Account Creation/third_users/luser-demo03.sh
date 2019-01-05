#!/bin/bash

# Display the UID
echo "Your UID is ${UID}"

# Only display if the UID != 1000
UID_TO_TEST_FOR='1000'
if [[ "$UID" -ne "$UID_TO_TEST_FOR" ]]
then
	echo "Your UID does not match: ${UID_TO_TEST_FOR}."
	exit 1
fi

# Set the username
USER_NAME=$(id -un)

# ${?} holds most recently exected command 
# Test if command succeeded
if [[ "${?}" -ne 0 ]]; then
	echo 'The id command did not execute succesfully'
	exit 1
fi

# Display the username
echo "Your username is ${USER_NAME}"

# String test conditional
# = equil, == looking for a pattern
USER_NAME_TO_TEST_FOR='vagrant'
if [[ "${USER_NAME}" = "${USER_NAME_TO_TEST_FOR}" ]]
then
	echo "Your username matches."
fi

# Display if the user is the vagrant user
if [[ "${USER_NAME}" != "${USER_NAME_TO_TEST_FOR}" ]]
then
	echo "Your username does not match."
	exit 1
fi

# Exit
exit 0