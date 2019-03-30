/*
	Purpose: 1. Counts words in requested file (basic functionality).
			 2. Prints words in order starting with the most common for requested n length word (-n switch option).
	Author: Adrian Michalek
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

typedef struct Node
{
	char* pWord;
	int nTimes; // how many times word occured
	struct Node* next;
} Node;

// switches
bool bInput = false; // -i <input file> = 2 (must be always specified)
bool bOutput = false; // -o <output file> = 2 (must be specified or -p)
bool bCommon = false; // -n <number> = 2 (optional)
bool bPrint = false; // -p = 1 (must be specified or -o)

// buffers
#define MAX_WORD_LENGTH 1024
char* cInput = NULL;
char* cOutput = NULL;
int iCommon = 0;
int iWhitespaces = 0;
int iStat[MAX_WORD_LENGTH];
Node* pHeads[MAX_WORD_LENGTH];

void freeGlobal()
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

	if (cInput)
		free(cInput);
	if (cOutput)
		free(cOutput);
}

void printHelp()
{
	printf("-i <input file> - sets the input file\n");
	printf("-o <output file> - sets the output file\n");
	printf("-n <number> - (optional), gives the most common words with <number> length in order\n");
	printf("-p - sets the output to the console\n");
}

bool parse(int* argc, char*** c_argv)
{
	int count = *argc;
	char** argv = *c_argv;
	if (count < 4)
	{
		printf("Error: There are too little arguments for the program\n");
		printf("Hint: switches -i and -o or -p (or both) are mandatory\n");
		printHelp();
		return false; // error
	}
	else if (count > 8)
	{
		printf("Error: There are too many arguments for the program\n");
		printHelp();
		return false; // error
	}
	
	for (int i = 1; i < count; ++i)
	{
		if (!strcmp(argv[i], "-i"))
		{
			if (bInput)
			{
				printf("Error: -i switch is already specified\n");
				return false;
			}
			bInput = true;
			++i;
			if (i >= count)
			{
				printf("Error: missing <input file> for -i switch\n");
				return false;
			}
			int iLength = strlen(argv[i]);
			cInput = (char*)malloc(iLength + 1);
			strncpy(cInput, argv[i], iLength + 1);
			cInput[iLength] = '\0';
		}
		else if (!strcmp(argv[i], "-o"))
		{
			if (bOutput)
			{
				printf("Error: -o switch is already specified\n");
				return false;
			}
			bOutput = true;
			++i;
			if (i >= count)
			{
				printf("Error: missing <output file> for -o switch\n");
				return false;
			}
			int iLength = strlen(argv[i]);
			cOutput = (char*)malloc(iLength + 1);
			strncpy(cOutput, argv[i], iLength + 1);
			cOutput[iLength] = '\0';
		}
		else if (!strcmp(argv[i], "-p"))
		{
			if (bPrint)
			{
				printf("Error: -p switch is already specified\n");
				return false;
			}
			bPrint = true;
		}
		else if (!strcmp(argv[i], "-n"))
		{
			if (bCommon)
			{
				printf("Error: -n switch is already specified\n");
				return false;
			}
			bCommon = true;
			++i;
			if (i >= count)
			{
				printf("Error: missing <number> for -n switch\n");
				return false;
			}

			int iLength = strlen(argv[i]);
			char* cTemp = (char*)malloc(iLength + 1);
			strncpy(cTemp, argv[i], iLength + 1);
			cTemp[iLength] = '\0';
			iCommon = atoi(cTemp);
			free(cTemp);
		}
	}

	return true; // success
}

bool loadFile()
{	
	FILE* pFile = fopen(cInput, "r");
	if (!pFile)
	{
		printf("Error: Cannot open file %s in read mode\n", cInput);
		return false; // error
	}

	for (int i = 0; i < MAX_WORD_LENGTH; ++i)
		iStat[i] = 0;

	char cBuffer[MAX_WORD_LENGTH];
	int iLen = 0;
	char ch;
	while (ch = fgetc(pFile))
	{
		if (ch < -1 || ch > 127)
			continue; // skip non ASCII

		if (isdigit(ch) || isalpha(ch))
		{
			cBuffer[iLen] = ch;
			++iLen;
			if (iLen >= MAX_WORD_LENGTH)
			{
				printf("Error: max length of the word is 1024 chars\n");
				fclose(pFile);
				return false;
			}
		}
		else
		{	// add to list
			char* pTemp = (char*)malloc(iLen + 1);
			for (int i = 0; i < iLen; ++i)
				pTemp[i] = cBuffer[i];
			pTemp[iLen] = '\0';
			++iStat[iLen];
			++iWhitespaces;

			Node** ptrNode = &pHeads[iLen];
			// search list
			while (*ptrNode)
			{
				if ((*ptrNode)->pWord && !strcmp(pTemp, (*ptrNode)->pWord))
					break;
				ptrNode = &(*ptrNode)->next;
			}

			iLen = 0;
			if (*ptrNode)
			{
				++(*ptrNode)->nTimes;
				free(pTemp);
			}
			else
			{	// the end of the list
				*ptrNode = malloc(sizeof(Node));
				(*ptrNode)->pWord = pTemp;
				(*ptrNode)->nTimes = 1;
				(*ptrNode)->next = NULL;
			}
		}

		if (ch == EOF)
			break;
	}

	return true; // success
}

int main(int argc, char** argv)
{
	if (parse(&argc, &argv))
	{
		if (loadFile())
		{
			if (bCommon && pHeads[iCommon])
			{	// sort
				for (Node* i = pHeads[iCommon]; i != NULL; i = i->next)
					for (Node* j = i->next; j != NULL; j = j->next)
					{
						if (i->nTimes > j->nTimes)
						{	// swap
							int iBuffer = i->nTimes;
							char* pcBuffer = i->pWord;
							i->nTimes = j->nTimes;
							j->nTimes = iBuffer;
							i->pWord = j->pWord;
							j->pWord = pcBuffer;
						}
					}
			}
			
			if (bPrint)
			{
				for (int i = 0; i < MAX_WORD_LENGTH; ++i)
					if (iStat[i])
						printf("%d words with length %d\n", iStat[i], i);
				if (bCommon)
				{
					printf("\n");
					if (pHeads[iCommon])
					{
						Node* ptrNode = pHeads[iCommon];
						while (ptrNode)
						{
							printf("Word \"%s\" has occured %d times\n", ptrNode->pWord, ptrNode->nTimes);
							ptrNode = ptrNode->next;
						}
					}
					else
						printf("There are no words with length %d\n", iCommon);
				}
				printf("\nWhitespaces (spaces, tabs, new lines...) occured %d times\n", iWhitespaces);
			}

			/*else*/ if (bOutput)
			{
				FILE* pFile = fopen(cOutput, "w");
				if (!pFile)
					printf("Error: Cannot open file %s in write mode\n", cInput);
				else
				{
					for (int i = 0; i < MAX_WORD_LENGTH; ++i)
						if (iStat[i])
							fprintf(pFile, "%d words with length %d\n", iStat[i], i);
					if (bCommon)
					{
						fprintf(pFile, "\n");
						if (pHeads[iCommon])
						{
							Node* ptrNode = pHeads[iCommon];
							while (ptrNode)
							{
								fprintf(pFile, "Word \"%s\" has occured %d times\n", ptrNode->pWord, ptrNode->nTimes);
								ptrNode = ptrNode->next;
							}
						}
						else
							fprintf(pFile, "There are no words with length %d\n", iCommon);
					}

					fprintf(pFile, "\nWhitespaces (spaces, tabs, new lines...) occured %d times\n", iWhitespaces);
					fclose(pFile);
				}
			}
		}
	}

	freeGlobal();
	printf("Press enter to continue...\n");
	{
		char c = 0;
		while (c != '\r' && c != '\n')
			c = getchar();
	}
	return 0;
}
