#pragma once
#include <string>
#include <list>

class TextBlock;

class Options final
{
	enum Identifier
	{
		Help = 0,
		RemoveComments,
		RemoveArguments,
		ReduceComments,
		ReduceArguments,
		SetLeftAlignment,
		SetRightAlignment,
		SetCenterAlignment,
		PrintNodeNumberInsideEdge,
		PrintMostUsed,
		SpecifyFile,
		None
	};

	friend TextBlock;

	static Identifier m_lastIdentifier;
	static unsigned int m_maxCommentLength;
	static unsigned int m_maxArgumentsLength;
	static unsigned int m_TopMostUsed;
	static unsigned long long m_data;
	static std::list<std::string> m_files;

	static void PrintHelp();
	static bool Compare(char* argument);
public:
	static bool Parse(int argc, char** argv);
	static std::list<std::string>::iterator Begin();
	static std::list<std::string>::iterator End();
};