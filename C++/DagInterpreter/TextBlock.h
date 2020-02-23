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
	size_t m_leftKidX, m_rightKidX, m_KidY;
	size_t m_nextX, m_nextY;
	std::vector<std::string> m_rows;
	void PrintToConsole();

public:
	explicit TextBlock(GraphNode& rhs);
	explicit TextBlock(TextNode* rhs);
	const std::vector<std::string>& Get() const;
	size_t Width();
	size_t Height();
	size_t GetLeftKidX();
	size_t GetRightKidX();
	size_t GetKidY();
	size_t GetNextX();
	size_t GetNextY();
};

struct Reference
{
	unsigned int asLeftKid;
	unsigned int asRightKid;
	unsigned int asNext;
	explicit Reference()
	{
		asLeftKid = asRightKid = asNext = 0;
	}
	explicit Reference(const Reference& rhs) noexcept
	{
		asLeftKid = rhs.asLeftKid;
		asRightKid = rhs.asRightKid;
		asNext = rhs.asNext;
	}
};

class TextNode : public TextBlock
{
	bool m_alreadyVisited;
	unsigned int m_index;
	Reference m_reference;
	std::pair<TextNode*, TextNode*> m_kids;
	TextNode* m_next;

public:
	explicit TextNode(GraphNode& rhs, unsigned int index) : TextBlock(rhs)
	{
		m_alreadyVisited = false;
		m_index = index;
		m_kids.first = m_kids.second = nullptr;
		m_next = nullptr;
	}

	void SetVisited();
	bool AlreadyVisited();
	const Reference& GetReference() const;
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
	Reference m_reference;
	std::pair<long long, long long> m_kids;
	long long m_next;

public:
	explicit LinearNode(TextNode* rhs, unsigned int index, const Reference& reference) : TextBlock(rhs), m_reference(reference)
	{
		m_index = index;
		m_kids.first = m_kids.second = -1;
		m_next = -1;
	}

	void SetLeftKid(long long kid);
	void SetRightKid(long long kid);
	void SetNext(long long next);
	unsigned int GetIndex();
	unsigned int GetReferencesAsLeftKid();
	unsigned int GetReferencesAsRightKid();
	unsigned int GetReferencesAsNext();
	const long long GetLeftKid() const;
	const long long GetRightKid() const;
	const long long GetNext() const;
	bool HasLeftKid();
	bool HasRightKid();
	bool HasNext();
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