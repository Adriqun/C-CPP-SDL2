#pragma once
#include <vector>
#include <memory>
#include <list>
#include <string>

class GraphNode;

class TextBlock
{
	std::vector<std::string> m_rows;

protected:
	void PrintToConsole();

public:
	explicit TextBlock(GraphNode& rhs);
	const std::vector<std::string>& Get() const;
	size_t Height() const;
	size_t Width() const;
};

class TextNode : public TextBlock
{
	unsigned int m_referencesAsKid;
	unsigned int m_referencesAsNext;
	std::pair<TextNode*, TextNode*> m_kids;
	TextNode* m_next;

public:
	explicit TextNode(GraphNode& rhs) : TextBlock(rhs)
	{
		m_referencesAsKid = 0;
		m_referencesAsNext = 0;
		m_kids.first = m_kids.second = nullptr;
		m_next = nullptr;
	}

	void SetLeftKid(TextNode* lhs);
	void SetRightKid(TextNode* rhs);
	void SetNext(TextNode* next);
};

class TextNodeChain final
{
	std::list<std::string> m_junk;
	std::vector<TextNode*> m_nodes;
	void AddTextBlock(char*& where, const std::vector<std::string> block);

public:
	~TextNodeChain();
	void SetJunk(std::list<std::string>&& junk);
	void Set(std::vector<GraphNode>& nodes);
	bool CreateAndRedirectChart(std::fstream& file);
};

class TextBlockManager
{
	std::vector<TextNodeChain> m_chains;

public:
	explicit TextBlockManager(std::string pathToFile, bool&);
	bool RedirectToFile(std::string pathToFile);
};