#ifndef __NODE_H__
#define __NODE_H__

#define MAX_WORD_LENGTH 1024

typedef struct Node
{
	unsigned char* pWord;
	int nTimes; // how many times word occured
	struct Node* next;
} Node;

void freeHeads(Node** ppHeads);
void freeBuffers(unsigned char** ppcInput, unsigned char** ppcOutput);

#endif