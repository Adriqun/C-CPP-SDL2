# Check if user is super user.
UID_TO_TEST='1000'
if [[ "${UID}" -eq "${UID_TO_TEST}" ]]
then
	echo 'You need to have super user priviliges'
	echo 'Your UID does not match' ${UID_TO_TEST}
	exit 1
fi

# Read/set data
HOSTNAME=$(hostname)
read -p 'Enter the username to create: ' USERNAME
read -p 'Enter the name of the person who this account is for: ' COMMENT
read -p 'Enter the password to use for the account: ' PASSWORD

# Creates account
useradd -c "${COMMENT}" -m ${USERNAME}

if [[ "${?}" -ne "0" ]]
then
	echo 'Cannot create an account...'
	exit 1
fi

# Set account password
echo ${PASSWORD} | passwd --stdin ${USERNAME}

if [[ "${?}" -ne "0" ]]
then
	echo 'Cannot set password for account...'
	exit 1
fi

# Force password change while first logging
passwd -e ${USERNAME}

# Display added data
echo 'Added user with username:' ${USERNAME} 'and password:' ${PASSWORD} 'on host:' ${HOSTNAME}