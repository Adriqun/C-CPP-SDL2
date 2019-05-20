#ifndef __IERRORS_H__
#define __IERRORS_H__

// errors
#define ERR_TOO_LITTLE_ARGS		"Error: There are too little arguments for the program\n"
#define ERR_TOO_MANY_ARGS		"Error: There are too many arguments for the program\n"

#define ERR_I_SWITCH_SPECIFIED	"Error: -i switch is already specified\n"
#define ERR_O_SWITCH_SPECIFIED	"Error: -o switch is already specified\n"
#define ERR_N_SWITCH_SPECIFIED	"Error: -n switch is already specified\n"
#define ERR_P_SWITCH_SPECIFIED	"Error: -p switch is already specified\n"

#define ERR_I_MISSING_FILENAME	"Error: missing <input file> for -i switch\n"
#define ERR_O_MISSING_FILENAME	"Error: missing <output file> for -o switch\n"
#define ERR_N_MISSING_NUMBER	"Error: missing <number> for -n switch\n"
#define ERR_N_SHOULD_CONTAIN	"Error: %s should contain only digits\n"

#define ERR_CANNOT_OPEN_FILE_R	"Error: Cannot open file %s in read mode\n"
#define ERR_CANNOT_OPEN_FILE_W	"Error: Cannot open file %s in write mode\n"
#define ERR_MAX_WORD_LENGTH		"Error: max length of the word is %d characters\n"

// messages
#define MSG_HINT_MANDATORY "Hint: switches -i and -o or -p (or both) are mandatory\n"
#define MSG_I_SWITCH_HELP "-i <input file> - sets the input file\n"
#define MSG_O_SWITCH_HELP "-o <output file> - sets the output to the file\n"
#define MSG_N_SWITCH_HELP "-n <number> - (optional), gives the most common words with <number> length in order\n"
#define MSG_P_SWITCH_HELP "-p - sets the output to the console\n"

#endif