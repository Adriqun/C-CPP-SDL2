#ifndef __NODE_H__
#define __NODE_H__

typedef struct Node
{
	char* pWord;
	int nTimes; // how many times word occured
	struct Node* next;
} Node;

#endif