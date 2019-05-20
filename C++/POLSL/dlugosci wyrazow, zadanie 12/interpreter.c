#include "interpreter.h"
#include "ierrors.h"
#include <stdio.h>	// printf(), FILE, fopen(), fclose(), fgetc(), EOF
#include <stdlib.h> // malloc(), free(), atoi(), 
#include <string.h> // strcmp(), strlen(), strncpy(), 
#include <ctype.h>	// isdigit(), isalpha()

void init(Interpreter *pInter)
{
	pInter->bInput = false;
	pInter->bOutput = false;
	pInter->bCommon = false;
	pInter->bPrint = false;

	pInter->pcInput = NULL;
	pInter->pcOutput = NULL;
	pInter->iCommon = -1;

	int i = 0;
	for (; i < MAX_WORD_LENGTH; ++i)
	{
		pInter->iStat[i] = 0;
		pInter->pHeads[i] = NULL;
	}
}

void printHelp()
{
	printf(MSG_I_SWITCH_HELP);
	printf(MSG_O_SWITCH_HELP);
	printf(MSG_N_SWITCH_HELP);
	printf(MSG_P_SWITCH_HELP);
}

bool parse(int* argc, char*** c_argv, Interpreter* pInter)
{
	int count = *argc;
	char** argv = *c_argv;
	if (count < 4)
	{
		printf(ERR_TOO_LITTLE_ARGS);
		printf(MSG_HINT_MANDATORY);
		printHelp();
		return false;
	}
	else if (count > 8)
	{
		printf(ERR_TOO_MANY_ARGS);
		printHelp();
		return false;
	}

	int i = 1;
	for (; i < count; ++i)
	{
		if (!strcmp(argv[i], "-i"))
		{
			if (pInter->bInput)
			{
				printf(ERR_I_SWITCH_SPECIFIED);
				return false;
			}
			pInter->bInput = true;
			if (++i >= count)
			{
				printf(ERR_I_MISSING_FILENAME);
				return false;
			}
			int len = strlen(argv[i]);
			pInter->pcInput = (char*)malloc(len + 1);
			strncpy(pInter->pcInput, argv[i], len);
			pInter->pcInput[len] = '\0';
		}
		else if (!strcmp(argv[i], "-o"))
		{
			if (pInter->bOutput)
			{
				printf(ERR_O_SWITCH_SPECIFIED);
				return false;
			}
			pInter->bOutput = true;
			if (++i >= count)
			{
				printf(ERR_O_MISSING_FILENAME);
				return false;
			}
			int len = strlen(argv[i]);
			pInter->pcOutput = (char*)malloc(len + 1);
			strncpy(pInter->pcOutput, argv[i], len);
			pInter->pcOutput[len] = '\0';
		}
		else if (!strcmp(argv[i], "-p"))
		{
			if (pInter->bPrint)
			{
				printf(ERR_P_SWITCH_SPECIFIED);
				return false;
			}
			pInter->bPrint = true;
		}
		else if (!strcmp(argv[i], "-n"))
		{
			if (pInter->bCommon)
			{
				printf(ERR_N_SWITCH_SPECIFIED);
				return false;
			}
			pInter->bCommon = true;
			if (++i >= count)
			{
				printf(ERR_N_MISSING_NUMBER);
				return false;
			}

			int len = strlen(argv[i]);
			char* cTemp = (char*)malloc(len + 1);
			strncpy(cTemp, argv[i], len);
			cTemp[len] = '\0';

			int j = 0;
			for (; j < len; ++j)
			{
				if (!isdigit(cTemp[j]))
					break;
			}

			if (len != j)
			{
				printf(ERR_N_SHOULD_CONTAIN, cTemp);
				free(cTemp);
				return false;
			}

			pInter->iCommon = atoi(cTemp);
			free(cTemp);
		}
	}

	return true;
}

bool loadFile(Interpreter* pInter)
{
	FILE* pFile = fopen(pInter->pcInput, "r");
	if (!pFile)
	{
		printf(ERR_CANNOT_OPEN_FILE_R, pInter->pcInput);
		return false;
	}

	for (int i = 0; i < MAX_WORD_LENGTH; ++i)
		pInter->iStat[i] = 0;
	
	int iLen = 0;
	unsigned char ch;
	unsigned char cBuffer[MAX_WORD_LENGTH];
	while (ch = fgetc(pFile))
	{
		if ((ch > 0xFF / 2 && ch != 0xFF) || isdigit(ch) || isalpha(ch))
		{
			cBuffer[iLen] = ch;
			++iLen;
			if (iLen >= MAX_WORD_LENGTH)
			{
				printf(ERR_MAX_WORD_LENGTH, MAX_WORD_LENGTH);
				fclose(pFile);
				return false;
			}
		}
		else
		{
			// add 0 length word: space, dot etc.
			unsigned char* pTemp = (unsigned char*)malloc(2);
			pTemp[0] = ch;
			pTemp[1] = '\0';
			++pInter->iStat[0];

			// search list
			Node** ptrNode = &pInter->pHeads[0];
			while (*ptrNode)
			{
				if ((*ptrNode)->pWord && !strcmp(pTemp, (*ptrNode)->pWord))
					break;
				ptrNode = &(*ptrNode)->next;
			}
			if (*ptrNode)
			{
				++(*ptrNode)->nTimes;
				free(pTemp);
			}
			else
			{	// the end of the list
				*ptrNode = (Node*)malloc(sizeof(Node));
				(*ptrNode)->pWord = pTemp;
				(*ptrNode)->nTimes = 1;
				(*ptrNode)->next = NULL;
			}

			if (iLen)
			{
				// add to list
				unsigned char* pTemp = (unsigned char*)malloc(iLen + 1);
				for (int i = 0; i < iLen; ++i)
					pTemp[i] = cBuffer[i];
				pTemp[iLen] = '\0';
				++pInter->iStat[iLen];

				Node** ptrNode = &pInter->pHeads[iLen];
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
					*ptrNode = (Node*)malloc(sizeof(Node));
					(*ptrNode)->pWord = pTemp;
					(*ptrNode)->nTimes = 1;
					(*ptrNode)->next = NULL;
				}
			}
		}

		if (ch == EOF || ch == 0xFF)
			break;
	}

	fclose(pFile);
	return true;
}

void evaluate(Interpreter* pInter)
{
	if (pInter->bCommon && pInter->pHeads[pInter->iCommon])
	{	// sort
		for (Node* i = pInter->pHeads[pInter->iCommon]; i != NULL; i = i->next)
			for (Node* j = i->next; j != NULL; j = j->next)
			{
				if (i->nTimes < j->nTimes)
				{	// swap
					int iBuffer = i->nTimes;
					unsigned char* pcBuffer = i->pWord;
					i->nTimes = j->nTimes;
					j->nTimes = iBuffer;
					i->pWord = j->pWord;
					j->pWord = pcBuffer;
				}
			}
	}

	if (pInter->bPrint)
	{
		int i = 0;
		for (; i < MAX_WORD_LENGTH; ++i)
			if (pInter->iStat[i])
				printf("%d words with length %d\n", pInter->iStat[i], i);
		if (pInter->bCommon)
		{
			printf("\n");
			if (pInter->pHeads[pInter->iCommon])
			{
				Node* ptrNode = pInter->pHeads[pInter->iCommon];
				while (ptrNode)
				{
					printf("Word \"%s\" has occured %d times\n", ptrNode->pWord, ptrNode->nTimes);
					ptrNode = ptrNode->next;
				}
			}
			else
				printf("There are no words with length %d\n", pInter->iCommon);
		}
	}

	if (pInter->bOutput)
	{
		FILE* pFile = fopen(pInter->pcOutput, "w");
		if (!pFile)
			printf(ERR_CANNOT_OPEN_FILE_W, pInter->pcInput);
		else
		{
			int i = 0;
			for (; i < MAX_WORD_LENGTH; ++i)
				if (pInter->iStat[i])
					fprintf(pFile, "%d words with length %d\n", pInter->iStat[i], i);
			if (pInter->bCommon)
			{
				fprintf(pFile, "\n");
				if (pInter->pHeads[pInter->iCommon])
				{
					Node* ptrNode = pInter->pHeads[pInter->iCommon];
					while (ptrNode)
					{
						fprintf(pFile, "Word \"%s\" has occured %d times\n", ptrNode->pWord, ptrNode->nTimes);
						ptrNode = ptrNode->next;
					}
				}
				else
					fprintf(pFile, "There are no words with length %d\n", pInter->iCommon);
			}

			fclose(pFile);
		}
	}
}