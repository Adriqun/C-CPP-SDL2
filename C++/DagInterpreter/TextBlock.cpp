#include "TextBlock.h"
#include "GraphNode.h"
#include "Options.h"
#include <iostream>
#include <fstream>
#include <array>

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
	std::string op = rhs.m_operator;
	std::string args = (Options::m_data & 1 << Options::ReduceArguments) ? "" : rhs.m_arguments;
	std::string comment = (Options::m_data & 1 << Options::RemoveComments) ? "" : rhs.m_comment;

	// Reduce
	if (Options::m_data & 1 << Options::ReduceArguments && args.size() > Options::m_maxArgumentsLength)
		args.resize(Options::m_maxArgumentsLength);
	if (Options::m_data & 1 << Options::ReduceComments && op.size() > Options::m_maxCommentLength)
		op.resize(Options::m_maxCommentLength);

	// Calculate max height
	size_t height = 3;
	if (!args.empty())
		++height;
	if (!comment.empty())
		++height;
	m_rows.resize(height);

	// Prepare identifier and operator string
	if (!(Options::m_data & 1 << Options::PrintNodeNumberInsideEdge))
	{
		op = id + " " + op;
		id.clear();
	}

	// Calculate max width
	size_t width = id.size();
	if (width < args.size())
		width = args.size();
	if (width < comment.size())
		width = comment.size();
	if (width < op.size())
		width = op.size();
	width += 4; // "| " + " |"

	// Determine starting positions for all strings
	std::array<size_t, 4> spositions = { 2, 2, 2, 2 };
	if (Options::m_data & 1 << Options::SetRightAlignment)
	{
		spositions[0] = width - 2 - id.size();
		spositions[1] = width - 2 - op.size();
		spositions[2] = width - 2 - args.size();
		spositions[3] = width - 2 - comment.size();
	}
	else if (Options::m_data & 1 << Options::SetCenterAlignment)
	{
		spositions[0] = (width - id.size()) / 2;
		spositions[1] = (width - op.size()) / 2;
		spositions[2] = (width - args.size()) / 2;
		spositions[3] = (width - comment.size()) / 2;
	}

	// Set top and bottom
	m_rows[0].resize(width, '-');
	m_rows[0].back() = m_rows[0].front() = '|';
	m_rows[height - 1].resize(width, '-');
	m_rows[height - 1].back() = m_rows[height - 1].front() = '|';

	// Set identifier
	if (!id.empty())
	{
		for (const auto &i : id)
			m_rows[0][spositions[0]++] = i;
	}
	
	// Set operator
	m_rows[1].resize(width, ' ');
	m_rows[1].back() = m_rows[1].front() = '|';
	for (const auto &i : op)
		m_rows[1][spositions[1]++] = i;

	// Set arguments
	if (!args.empty())
	{
		m_rows[2].resize(width, ' ');
		m_rows[2].back() = m_rows[2].front() = '|';
		for (const auto& i : args)
			m_rows[2][spositions[2]++] = i;
	}

	// Set comment
	if (!comment.empty())
	{
		m_rows[height - 2].resize(width, ' ');
		m_rows[height - 2].back() = m_rows[height - 2].front() = '|';
		for (const auto& i : comment)
			m_rows[height - 2][spositions[3]++] = i;
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
		unsigned int row = 0;
		GraphNodeManager reader;
		while (std::getline(file, line))
		{
			if (!reader.ReadLine(line, ++row))
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
		std::cout << "Error: File \"" << pathToFile << "\" does not exist!" << std::endl;
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
		std::cout << "Error: Cannot write to file \"" << pathToFile << "\"!" << std::endl;
		return false;
	}

	return true;
}