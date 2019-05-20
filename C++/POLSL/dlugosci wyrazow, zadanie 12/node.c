#include "node.h"
#include <stdlib.h> // free()

void freeHeads(Node** pHeads)
{
	for (int i = 0; i < MAX_WORD_LENGTH; ++i)
	{
		if (pHeads[i])
		{
			Node* ptrNode = pHeads[i];
			while (ptrNode)
			{
				Node* delNode = ptrNode;
				ptrNode = ptrNode->next;
				free(delNode->pWord);
				free(delNode);
			}
		}
	}
}

void freeBuffers(unsigned char** ppcInput, unsigned char** ppcOutput)
{
	unsigned char* pcInput = *ppcInput;
	if (pcInput)
		free(pcInput);

	unsigned char* pcOutput = *ppcOutput;
	if (pcOutput)
		free(pcOutput);
}