#include "TextBlock.h"
#include "GraphNode.h"
#include <iostream>
#include <fstream>

void TextBlock::PrintToConsole()
{
	for (auto &i : m_rows)
		std::cout << i << std::endl;
}

TextBlock::TextBlock(GraphNode& rhs)
{
	// |------| |--------| |-------| |-------------|
	// | #0 A | | #0 ABC | | #0 AB | | #0 OPERATOR |
	// |------| | "args" | | ;comm | | "arguments" |
	//          |--------| |-------| |    ;comm    |
	//                               |-------------|

	std::string id = "#" + std::to_string(rhs.m_identity);
	std::string& op = rhs.m_operator;
	std::string& args = rhs.m_arguments;
	std::string& comment = rhs.m_comment;

	// Calculate height
	size_t height = 3;
	if (!args.empty())
		++height;
	if (!comment.empty())
		++height;
	m_rows.resize(height);

	// Calculate width
	size_t width = id.size() + op.size() + 1;
	if (width < args.size())
		width = args.size();
	if (width < comment.size())
		width = comment.size();
	width += 4; // "| " + " |"

	// Set top and bottom
	m_rows[0].resize(width, '-');
	m_rows[0].back() = m_rows[0].front() = '|';
	m_rows[height - 1].resize(width, '-');
	m_rows[height - 1].back() = m_rows[height - 1].front() = '|';

	// Set identity
	m_rows[1].resize(width, ' ');
	m_rows[1].back() = m_rows[1].front() = '|';
	size_t position = 2;
	for (size_t i = 0; i < id.size(); ++i)
		m_rows[1][position++] = id[i];

	// Set operator
	position = (width - op.size()) / 2;
	if (position <= id.size() + 2)
		position = id.size() + 3;
	for (size_t i = 0; i < op.size(); ++i)
		m_rows[1][position++] = op[i];

	// Set arguments
	if (!args.empty())
	{
		m_rows[2].resize(width, ' ');
		m_rows[2].back() = m_rows[2].front() = '|';
		position = (width - args.size()) / 2;
		for (size_t i = 0; i < args.size(); ++i)
			m_rows[2][position++] = args[i];
	}

	// Set comment
	if (!comment.empty())
	{
		m_rows[height - 2].resize(width, ' ');
		m_rows[height - 2].back() = m_rows[height - 2].front() = '|';

		position = (width - comment.size()) / 2;
		for (size_t i = 0; i < comment.size(); ++i)
			m_rows[3][position++] = comment[i];
	}
}

const std::vector<std::string>& TextBlock::Get() const
{
	return m_rows;
}

size_t TextBlock::Height() const
{
	return m_rows.size();
}

size_t TextBlock::Width() const
{
	return m_rows[0].size();
}

void TextNode::SetLeftKid(TextNode* lhs)
{
	m_kids.first = lhs;
	++lhs->m_referencesAsKid;
}

void TextNode::SetRightKid(TextNode* rhs)
{
	m_kids.second = rhs;
	++rhs->m_referencesAsKid;
}

void TextNode::SetNext(TextNode* next)
{
	m_next = next;
	++next->m_referencesAsNext;
}

void TextNodeChain::AddTextBlock(char*& where, const std::vector<std::string> block)
{
	for (size_t i = 0; i < block.size(); ++i)
	{
		memcpy(*(&where + i), block[i].c_str(), block[i].size());
		*(&where + i) += block[i].size();
	}
}

TextNodeChain::~TextNodeChain()
{
	for (auto& i : m_nodes)
		delete i;
}

void TextNodeChain::SetJunk(std::list<std::string>&& junk)
{
	m_junk = std::move(junk);
	// Clear input
	junk.clear();
}

void TextNodeChain::Set(std::vector<GraphNode>& nodes)
{
	// Resize
	size_t length = nodes.size();
	m_nodes.resize(length);

	for (size_t i = 0; i < length; ++i)
		m_nodes[i] = new TextNode(nodes[i]);

	// The slowest part
	for (size_t i = 0; i < length; ++i)
	{
		for (size_t j = 0; j < length; ++j)
		{
			TextNode* setter = m_nodes[i];
			TextNode* getter = m_nodes[j];

			if (nodes[j].Identity() == nodes[i].LeftKid())
				setter->SetLeftKid(getter);

			if (nodes[j].Identity() == nodes[i].RightKid())
				setter->SetRightKid(getter);

			if (nodes[j].Identity() == nodes[i].Next())
				setter->SetNext(getter);
		}
	}

	// Clear input
	nodes.clear();
}

bool TextNodeChain::CreateAndRedirectChart(std::fstream& file)
{
	for (const auto &i : m_junk)
		file << i << "\n";

	if (m_nodes.empty())
		return true;



	return true;
}

TextBlockManager::TextBlockManager(std::string pathToFile, bool& status)
{
	std::fstream file;
	file.open(pathToFile, std::ios::in);
	if (file.is_open())
	{
		status = true;
		std::string line;
		GraphNodeManager reader;
		while (std::getline(file, line))
		{
			if (!reader.ReadLine(line))
			{
				status = false;
				break;
			}
		}

		if (status)
			reader.Set(m_chains);
		file.close();
	}
	else
	{
		std::cout << "Error: File does not exist!" << std::endl;
		status = false;
	}
}

bool TextBlockManager::RedirectToFile(std::string pathToFile)
{
	std::fstream file;
	file.open(pathToFile, std::ios::out | std::ios::app);
	if (file.is_open())
	{
		for (auto& i : m_chains)
		{
			if (!i.CreateAndRedirectChart(file))
				return false;
		}

		file.close();
	}
	else
	{
		std::cout << "Error: Cannot write to file!" << std::endl;
		return false;
	}

	return true;
}