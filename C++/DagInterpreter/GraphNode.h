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

	bool ExtractNumber(int& number, const char*& line);
	bool ExtractIdentity(const char*& line);
	bool ExtractKids(const char*& line);
	bool ExtractNext(const char*& line);
	bool ExtractOperator(const char*& line);
	bool ExtractArguments(const char*& line);
	void ExtractComment(const char*& line);
	void SkipBlank(const char*& line);

public:
	explicit GraphNode(const char* line, bool& status);
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
	bool AddToNodes(std::string& line, bool& status);
};

class TextNodeChain;

class GraphNodeManager final
{
	bool m_stream;
	std::list<GraphNodeChain> m_chains;

public:
	explicit GraphNodeManager();
	bool ReadLine(std::string& line);
	void Set(std::vector<TextNodeChain>& rhs);
};