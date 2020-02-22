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

	// Set handle
	// |---X---|
	// | #0 AB |
	// | "arg" Y
	// | ;comm |
	// |-------|
	m_handle.x = m_rows[0].size() / 2;
	m_handle.y = m_rows.size() / 2;
}

TextBlock::TextBlock(TextNode* rhs)
{
	m_handle = rhs->m_handle;
	m_rows = std::move(rhs->m_rows);
}

const std::vector<std::string>& TextBlock::Get() const
{
	return m_rows;
}

size_t TextBlock::Width()
{
	return m_rows[0].size();
}

size_t TextBlock::Height()
{
	return m_rows.size();
}

void TextBlock::AddOrphan(TextBlock* kid)
{
	// |-------|
	// | #0 AB |
	// | "arg" |--+
	// | ;comm |  |
	// |-------|  |  |-------|
	//            |  | #0 AB |
	//            +->| "arg" |
	//               | ;comm |
	//               |-------|

	size_t width = m_rows[0].size();
	size_t height = m_rows.size();
	size_t orphanWidth = kid->m_rows[0].size();
	size_t orphanHeight = kid->m_rows.size();

	// Adjust new size
	m_rows.resize(height + orphanHeight - 1);
	for (auto &i : m_rows)
		i.resize(width + orphanWidth + 5, ' ');

	// Draw horizontal line
	m_rows[m_handle.y][width] = '-';
	m_rows[m_handle.y][width + 1] = '-';
	m_rows[m_handle.y][width + 2] = '+';

	// Draw vertical line
	size_t verticalLastPoint = height - 1 + kid->m_handle.y;
	for (size_t i = m_handle.y + 1; i < height - 1 + kid->m_handle.y; ++i)
		m_rows[i][width + 2] = '|';

	// Draw horizontal line
	m_rows[verticalLastPoint][width + 2] = '+';
	m_rows[verticalLastPoint][width + 3] = '-';
	m_rows[verticalLastPoint][width + 4] = '-';

	// Copy orphan
	for (size_t i = height - 1, j = 0; i < m_rows.size(); ++i, ++j)
		memcpy(&m_rows[i][width + 5], &kid->m_rows[j][0], orphanWidth);

	// Clear orphan
	kid->m_rows.clear();
}

void TextNode::SetVisited()
{
	m_alreadyVisited = true;
}

bool TextNode::AlreadVisited()
{
	return m_alreadyVisited;
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

unsigned int TextNode::GetIndex()
{
	return m_index;
}

TextNode* TextNode::GetLeftKid()
{
	return m_kids.first;
}

TextNode* TextNode::GetRightKid()
{
	return m_kids.second;
}

TextNode* TextNode::GetNext()
{
	return m_next;
}

void LinearNode::SetNext(long long next)
{
	m_next = next;
}

unsigned int LinearNode::GetIndex()
{
	return m_index;
}

const long long LinearNode::GetNext() const
{
	return m_next;
}

void TextNodeChain::Linearise(TextNode* current, std::unordered_map<size_t, TextNode*>& container)
{
	if (current && !current->AlreadVisited())
	{
		current->SetVisited();
		m_nodes.push_back(new LinearNode(current, current->GetIndex()));
		Linearise(current->GetLeftKid(), container);
		Linearise(current->GetRightKid(), container);
		Linearise(current->GetNext(), container);
	}
}

TextNodeChain::~TextNodeChain()
{
	for (auto& i : m_nodes)
		delete i;
	m_nodes.clear();
}

void TextNodeChain::SetJunk(std::list<std::string>&& junk)
{
	m_junk = std::move(junk);
	// Clear input
	junk.clear();
}

void TextNodeChain::Set(std::vector<GraphNode>& nodes)
{
	size_t length = nodes.size();
	if (length)
	{
		// Set
		std::unordered_map<size_t, TextNode*> mapped;
		for (size_t i = 0; i < length; ++i)
			mapped[i] = new TextNode(nodes[i], i);

		// The slowest part - collecting data
		for (size_t i = 0; i < length; ++i)
		{
			for (size_t j = 0; j < length; ++j)
			{
				TextNode* setter = static_cast<TextNode*>(mapped[i]);
				TextNode* getter = static_cast<TextNode*>(mapped[j]);

				if (nodes[j].Identity() == nodes[i].LeftKid())
					setter->SetLeftKid(getter);

				if (nodes[j].Identity() == nodes[i].RightKid())
					setter->SetRightKid(getter);

				if (nodes[j].Identity() == nodes[i].Next())
					setter->SetNext(getter);
			}
		}

		for (auto& i : mapped)
			Linearise(i.second, mapped);
		for (int i = 0; i < m_nodes.size() - 1; ++i)
		{
			TextNode* where = mapped[m_nodes[i]->GetIndex()];
			TextNode* next = where->GetLeftKid();

			if (!next)
				where->GetNext();

			if (!next)
			{
				m_nodes[i]->SetNext(-1);
				continue;
			}

			for (long long j = 0; j < static_cast<long long>(m_nodes.size()); ++j)
			{
				if (m_nodes[j]->GetIndex() == next->GetIndex())
					m_nodes[i]->SetNext(j);
			}
		}
		m_nodes.back()->SetNext(-1);

		// Clear mapped
		for (auto& i : mapped)
			delete i.second;
		mapped.clear();

		// Clear input
		nodes.clear();
	}
}

bool TextNodeChain::CreateAndRedirectChart(std::fstream& file)
{
	for (const auto &i : m_junk)
		file << i << "\n";

	if (m_nodes.empty())
		return true;

	// Set table height
	size_t tableHeight = 0;
	for (auto& i : m_nodes)
		tableHeight += i->Height();
	tableHeight -= (m_nodes.size() - 1);
	std::vector<std::string> table;
	table.resize(tableHeight);

	// Set table widths
	size_t tableWidth = 0;
	for (size_t i = 0, j = 0; i < m_nodes.size(); ++i)
	{
		tableWidth += m_nodes[i]->Width();
		for (size_t k = 0; k < m_nodes[i]->Height(); ++k)
			table[j++].resize(tableWidth, ' ');
		--j;
		tableWidth += 5;
	}

	// Draw nodes
	size_t x = 0, y = 0;
	for (auto& i : m_nodes)
	{
		const std::vector<std::string>& block = i->Get();

		for (size_t j = 0; j < block.size(); ++j)
		{
			memcpy(&table[y][x], &block[j][0], block[j].size());
			++y;
		}

		--y;
		x += 5 + i->Width();
	}

	// Draw lines


	for (const auto& i : table)
		file << i << "\n";
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