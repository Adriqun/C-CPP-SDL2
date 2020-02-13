#pragma once
#include <string>
#include <list>

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

	Identifier lastIdentifier;
	unsigned int m_maxCommentLength;
	unsigned int m_maxArgumentsLength;
	unsigned int m_TopMostUsed;
	unsigned long long m_data;
	std::list<std::string> m_files;

	void PrintHelp();
	bool Compare(char* argument);
public:
	explicit Options(int argc, char** argv, bool& status);
	~Options();
	std::list<std::string>::iterator Begin();
	std::list<std::string>::iterator End();
};