#pragma once
#include <string>
#include <list>
#include <vector>

class TextBlock;

class GraphNode final
{
	int m_identity, m_next;
	std::pair<int, int> m_kids;
	std::string m_operator;
	std::string m_arguments;
	std::string m_comment;
	friend TextBlock;

	void PrintError(unsigned int row, long long column, const char* message);
	bool ExtractNumber(int& number, const char*& line, unsigned int row);
	bool ExtractIdentity(const char*& line, unsigned int row);
	bool ExtractKids(const char*& line, unsigned int row);
	bool ExtractNext(const char*& line, unsigned int row);
	bool ExtractOperator(const char*& line, unsigned int row);
	bool ExtractArguments(const char*& line, unsigned int row);
	void ExtractComment(const char*& line);
	void SkipBlank(const char*& line);

public:
	explicit GraphNode(const char* line, unsigned int row, bool& status);
	const int& Identity() const;
	const int& LeftKid() const;
	const int& RightKid() const;
	const int& Next() const;
};

struct GraphNodeChain final
{
	std::list<std::string> m_junk;
	std::vector<GraphNode> m_nodes;

	bool AddToJunk(std::string& line);
	bool AddToNodes(std::string& line, unsigned int row, bool& status);
};

class TextNodeChain;

class GraphNodeManager final
{
	bool m_stream;
	std::list<GraphNodeChain> m_chains;

public:
	explicit GraphNodeManager();
	bool ReadLine(std::string& line, unsigned int row);
	void Set(std::vector<TextNodeChain>& rhs);
};