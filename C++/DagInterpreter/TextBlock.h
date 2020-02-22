#pragma once
#include <vector>
#include <memory>
#include <list>
#include <string>
#include <unordered_map>

class GraphNode;
class TextNode;

class TextBlock
{
protected:
	struct Handle {
		size_t x, y;
	} m_handle;

	std::vector<std::string> m_rows;

	void PrintToConsole();

public:
	explicit TextBlock(GraphNode& rhs);
	explicit TextBlock(TextNode* rhs);
	const std::vector<std::string>& Get() const;
	size_t Width();
	size_t Height();
	void AddOrphan(TextBlock*);
};

class TextNode : public TextBlock
{
	bool m_alreadyVisited;
	unsigned int m_index;
	unsigned int m_referencesAsKid;
	unsigned int m_referencesAsNext;
	std::pair<TextNode*, TextNode*> m_kids;
	TextNode* m_next;

public:
	explicit TextNode(GraphNode& rhs, unsigned int index) : TextBlock(rhs)
	{
		m_alreadyVisited = false;
		m_index = index;
		m_referencesAsKid = 0;
		m_referencesAsNext = 0;
		m_kids.first = m_kids.second = nullptr;
		m_next = nullptr;
	}

	void SetVisited();
	bool AlreadVisited();
	void SetLeftKid(TextNode* lhs);
	void SetRightKid(TextNode* rhs);
	void SetNext(TextNode* next);

	unsigned int GetIndex();
	TextNode* GetLeftKid();
	TextNode* GetRightKid();
	TextNode* GetNext();
};

class LinearNode : public TextBlock
{
	unsigned int m_index;
	long long m_next;

public:
	explicit LinearNode(TextNode* rhs, unsigned int index) : TextBlock(rhs)
	{
		m_next = -1;
		m_index = index;
	}

	void SetNext(long long next);
	unsigned int GetIndex();
	const long long GetNext() const;
};

class TextNodeChain final
{
	std::list<std::string> m_junk;
	std::vector<LinearNode*> m_nodes;
	void Linearise(TextNode* current, std::unordered_map<size_t, TextNode*>&);

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