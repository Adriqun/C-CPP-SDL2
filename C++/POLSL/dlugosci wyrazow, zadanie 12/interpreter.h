#ifndef __INTERPRETER_H__
#define __INTERPRETER_H__

#include "node.h"
#include <stdbool.h> // bool

typedef struct Interpreter
{
	// Switches.
	bool bInput;	// -i <input file> = 2 (must be always specified)
	bool bOutput;	// -o <output file> = 2 (must be specified or -p)
	bool bCommon;	// -n <number> = 2 (optional)
	bool bPrint;	// -p = 1 (must be specified or -o)

	// Buffers.
	unsigned char* pcInput;
	unsigned char* pcOutput;
	int iCommon;
	int iStat[MAX_WORD_LENGTH];
	Node* pHeads[MAX_WORD_LENGTH];
} Interpreter;

void init(Interpreter *pInter);
void printHelp();
bool parse(int* argc, char*** c_argv, Interpreter* pInter);
bool loadFile(Interpreter* pInter);
void evaluate(Interpreter* pInter);

#endif