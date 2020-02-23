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
	std::string args = (Options::m_data & 1 << Options::RemoveArguments) ? "" : rhs.m_arguments;
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
	size_t kidXOffset = (Width() - 1) / 4;
	m_leftKidX = kidXOffset;
	m_rightKidX = m_rows[0].size() - (kidXOffset + 1);
	m_KidY = m_rows.size();
	m_nextX = m_rows[0].size();
	m_nextY = 1;

	if (Options::m_data & 1 << Options::PrintHandleInformation)
	{
		m_rows[m_KidY - 1][m_leftKidX] = 'l';
		m_rows[m_KidY - 1][m_rightKidX] = 'r';
		m_rows[m_nextY][m_nextX - 1] = 'n';
	}
}

TextBlock::TextBlock(TextNode* rhs)
{
	// Set rows
	m_rows = std::move(rhs->m_rows);

	// Set handle
	m_leftKidX = rhs->GetLeftKidX();
	m_rightKidX = rhs->GetRightKidX();
	m_KidY = rhs->GetKidY();
	m_nextX = rhs->GetNextX();
	m_nextY = rhs->GetNextY();
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

size_t TextBlock::GetLeftKidX()
{
	return m_leftKidX;
}

size_t TextBlock::GetRightKidX()
{
	return m_rightKidX;
}

size_t TextBlock::GetKidY()
{
	return m_KidY;
}

size_t TextBlock::GetNextX()
{
	return m_nextX;
}

size_t TextBlock::GetNextY()
{
	return m_nextY;
}

void TextNode::SetVisited()
{
	m_alreadyVisited = true;
}

bool TextNode::AlreadyVisited()
{
	return m_alreadyVisited;
}

const Reference& TextNode::GetReference() const
{
	return m_reference;
}

void TextNode::SetLeftKid(TextNode* lhs)
{
	m_kids.first = lhs;
	++lhs->m_reference.asLeftKid;
}

void TextNode::SetRightKid(TextNode* rhs)
{
	m_kids.second = rhs;
	++rhs->m_reference.asRightKid;
}

void TextNode::SetNext(TextNode* next)
{
	m_next = next;
	++next->m_reference.asNext;
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

void LinearNode::SetLeftKid(long long leftKid)
{
	m_kids.first = leftKid;
}

void LinearNode::SetRightKid(long long rightKid)
{
	m_kids.second = rightKid;
}

void LinearNode::SetNext(long long next)
{
	m_next = next;
}

unsigned int LinearNode::GetIndex()
{
	return m_index;
}

unsigned int LinearNode::GetReferencesAsLeftKid()
{
	return m_reference.asLeftKid;
}

unsigned int LinearNode::GetReferencesAsRightKid()
{
	return m_reference.asRightKid;
}

unsigned int LinearNode::GetReferencesAsNext()
{
	return m_reference.asNext;
}

const long long LinearNode::GetLeftKid() const
{
	return m_kids.first;
}

const long long LinearNode::GetRightKid() const
{
	return m_kids.second;
}

const long long LinearNode::GetNext() const
{
	return m_next;
}

bool LinearNode::HasLeftKid()
{
	return m_kids.first != -1;
}

bool LinearNode::HasRightKid()
{
	return m_kids.second != -1;
}

bool LinearNode::HasNext()
{
	return m_next != -1;
}

void TextNodeChain::Linearise(TextNode* current, std::unordered_map<size_t, TextNode*>& container)
{
	if (current && !current->AlreadyVisited())
	{
		current->SetVisited();
		m_nodes.push_back(new LinearNode(current, current->GetIndex(), current->GetReference()));
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
			TextNode* leftKid = where->GetLeftKid();
			TextNode* rightKid = where->GetRightKid();
			TextNode* next = where->GetNext();

			if (!leftKid && !rightKid && !next)
			{
				m_nodes[i]->SetNext(-1);
				continue;
			}

			for (long long j = 0; j < static_cast<long long>(m_nodes.size()); ++j)
			{
				if (leftKid && m_nodes[j]->GetIndex() == leftKid->GetIndex())
				{
					m_nodes[i]->SetLeftKid(j);
					if ((!next || m_nodes[i]->GetNext() != -1) &&
						(!rightKid || m_nodes[i]->GetRightKid() != -1))
						break; // If there is no next/right kid or if next/right kid exists and it is already set
				}

				if (rightKid && m_nodes[j]->GetIndex() == rightKid->GetIndex())
				{
					m_nodes[i]->SetRightKid(j);
					if ((!next || m_nodes[i]->GetNext() != -1) &&
						(!leftKid || m_nodes[i]->GetLeftKid() != -1))
						break; // If there is no next/left kid or if next/left kid exists and it is already set
				}

				if (next && m_nodes[j]->GetIndex() == next->GetIndex())
				{
					m_nodes[i]->SetNext(j);
					if ((!leftKid || m_nodes[i]->GetLeftKid() != -1) &&
						(!rightKid || m_nodes[i]->GetRightKid() != -1))
						break; // If there are no kids or if kids exist they are already set
				}
			}
		}

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
	const size_t heightOffset = 4;
	size_t tableHeight = heightOffset * 2;
	for (auto& i : m_nodes)
		tableHeight += i->Height();
	tableHeight += m_nodes.size();
	std::vector<std::string> table;
	table.resize(tableHeight);

	// Set table widths
	const size_t gap = 2, totalGap = 7;
	const size_t widthOffset = 3;
	size_t tableWidth = widthOffset;
	for (auto& i : m_nodes)
		tableWidth += i->Width() + totalGap;
	for (auto& i : table)
		i.resize(tableWidth, ' ');

	// Draw nodes, collect handles
	std::vector<size_t> xs, ys;
	xs.reserve(m_nodes.size());
	ys.reserve(m_nodes.size());
	size_t x = widthOffset, y = heightOffset;
	for (size_t i = 0; i < m_nodes.size(); ++i)
	{
		xs.push_back(x);
		ys.push_back(y);

		const std::vector<std::string>& block = m_nodes[i]->Get();
		if (i > 0 &&
			m_nodes[i]->GetReferencesAsLeftKid() == 1 &&
			!m_nodes[i]->GetReferencesAsNext())
		{
			if (m_nodes[i - 1]->HasRightKid())
			{
				// Previous node has right kid
				// Current node is left kid
				x = xs[i - 1] + m_nodes[i - 1]->GetRightKidX() + gap + 2;
				xs.back() = x;
				for (size_t j = 0; j < block.size(); ++j)
					memcpy(&table[y++][x], &block[j][0], block[j].size());

				if (i + 1 < m_nodes.size() &&
					(m_nodes[i + 1]->GetReferencesAsLeftKid() ||
						m_nodes[i + 1]->GetReferencesAsRightKid()))
					++y;
				else if (m_nodes[i - 1]->GetRightKid() < static_cast<long long>(i) &&
					m_nodes[i]->GetLeftKid() < static_cast<long long>(i) &&
					m_nodes[i]->GetRightKid() < static_cast<long long>(i) &&
					m_nodes[i]->GetNext() < static_cast<long long>(i))
					y = ys[i];
				else
					++y;
			}
			else
			{
				// Previous node has no right kid
				// Current node is orphan left kid
				x = xs[i - 1] + m_nodes[i - 1]->GetLeftKidX() + gap + 1;
				xs.back() = x;
				for (size_t j = 0; j < block.size(); ++j)
					memcpy(&table[y++][x], &block[j][0], block[j].size());

				if (i + 1 < m_nodes.size() &&
					(m_nodes[i + 1]->GetReferencesAsLeftKid() ||
					m_nodes[i + 1]->GetReferencesAsRightKid()))
					++y;
				else if (m_nodes[i]->GetLeftKid() < static_cast<long long>(i) &&
					m_nodes[i]->GetRightKid() < static_cast<long long>(i) &&
					m_nodes[i]->GetNext() < static_cast<long long>(i))
					y = ys[i];
				else
					++y;
			}
		}
		else if (i > 0 &&
			m_nodes[i]->GetReferencesAsRightKid() == 1 &&
			!m_nodes[i]->GetReferencesAsNext())
		{
			// Previous node has left kid and right kid
			// Current node is right kid
			x = xs[i - 1] + m_nodes[i - 1]->GetRightKidX() + gap + 1;
			xs.back() = x;
			for (size_t j = 0; j < block.size(); ++j)
				memcpy(&table[y++][x], &block[j][0], block[j].size());

			if (i + 1 < m_nodes.size() &&
				(m_nodes[i + 1]->GetReferencesAsLeftKid() ||
					m_nodes[i + 1]->GetReferencesAsRightKid()))
				++y;
			else if (m_nodes[i]->GetLeftKid() < static_cast<long long>(i) &&
				m_nodes[i]->GetRightKid() < static_cast<long long>(i) &&
				m_nodes[i]->GetNext() < static_cast<long long>(i))
				y = ys[i];
			else
				++y;
		}
		else
		{
			for (size_t j = 0; j < block.size(); ++j)
				memcpy(&table[y++][x], &block[j][0], block[j].size());
			++y;
		}

		x += totalGap + m_nodes[i]->Width();
	}

	// Draw lines
	std::list<std::pair<size_t, size_t>> pernamentCrosses;
	std::list<std::pair<size_t, size_t>> pernamentRightArrows;
	for (size_t i = 0; i < m_nodes.size(); ++i)
	{
		if (m_nodes[i]->GetNext() > -1)
		{
			if (m_nodes[i]->GetNext() > static_cast<long long>(i))
			{
				size_t cx = xs[i] + m_nodes[i]->GetNextX();
				size_t cy = ys[i] + m_nodes[i]->GetNextY();
				size_t xPoint = xs[m_nodes[i]->GetNext()];
				size_t yPoint = ys[m_nodes[i]->GetNext()] + m_nodes[m_nodes[i]->GetNext()]->GetNextY();
				for (size_t k = cx; k < xPoint - gap; ++k)
					table[cy][k] = '-';
				for (size_t k = xPoint - gap; k < xPoint - 1; ++k)
					table[yPoint][k] = '-';

				if (cy != yPoint)
				{
					size_t xCross = xPoint - gap - 1;
					for (size_t k = cy; k < yPoint; ++k)
						table[k][xCross] = '|';
					pernamentCrosses.push_front(std::make_pair(cy, xCross));
					pernamentCrosses.push_front(std::make_pair(yPoint, xCross));
				}

				pernamentRightArrows.push_back(std::make_pair(yPoint, xPoint - 1));
			}
			else
			{
				size_t cx = xs[i] + m_nodes[i]->GetNextX();
				size_t cy = ys[i] + m_nodes[i]->GetNextY();
				size_t xPoint = xs[m_nodes[i]->GetNext()];
				size_t yPoint = ys[m_nodes[i]->GetNext()] + m_nodes[m_nodes[i]->GetNext()]->GetNextY();
				size_t tPoint = ys[m_nodes[i]->GetNext()] - gap - 1;

				for (size_t k = cx; k < cx + gap; ++k)
					table[cy][k] = '-';
				for (size_t k = tPoint; k < cy; ++k)
					table[k][cx + gap] = '|';
				for (size_t k = xPoint - gap - 1; k < cx + gap; ++k)
					table[tPoint][k] = '-';
				for (size_t k = tPoint; k < yPoint; ++k)
					table[k][xPoint - gap - 1] = '|';
				pernamentCrosses.push_front(std::make_pair(cy, cx + gap));
				pernamentCrosses.push_front(std::make_pair(tPoint, cx + gap));
				pernamentCrosses.push_front(std::make_pair(tPoint, xPoint - gap - 1));
			}
		}

		if (m_nodes[i]->GetLeftKid() > -1)
		{
			if (m_nodes[i]->GetLeftKid() > static_cast<long long>(i))
			{
				size_t cx = xs[i] + m_nodes[i]->GetLeftKidX();
				size_t cy = ys[i] + m_nodes[i]->GetKidY();
				size_t xPoint = xs[m_nodes[i]->GetLeftKid()];
				size_t yPoint = ys[m_nodes[i]->GetLeftKid()] + m_nodes[m_nodes[i]->GetLeftKid()]->GetNextY();
				for (size_t k = cx; k < xPoint; ++k)
					table[yPoint][k] = '-';
				for (size_t k = cy; k < yPoint; ++k)
					table[k][cx] = '|';
				pernamentCrosses.push_front(std::make_pair(yPoint, cx));
				pernamentRightArrows.push_back(std::make_pair(yPoint, xPoint - 1));
			}
			else
			{
				size_t cx = xs[i] + m_nodes[i]->GetLeftKidX();
				size_t cy = ys[i] + m_nodes[i]->GetKidY();
				size_t xPoint = xs[m_nodes[i]->GetLeftKid()];
				size_t yPoint = ys[m_nodes[i]->GetLeftKid()] + m_nodes[m_nodes[i]->GetLeftKid()]->GetNextY();
				for (size_t k = cy; k < cy + gap; ++k)
					table[k][cx] = '|';
				for (size_t k = xPoint - gap; k < cx; ++k)
					table[cy + gap][k] = '-';
				for (size_t k = yPoint; k < cy + gap; ++k)
					table[k][xPoint - gap - 1] = '|';
				pernamentCrosses.push_front(std::make_pair(cy + gap, cx));
				pernamentCrosses.push_front(std::make_pair(cy + gap, xPoint - gap - 1));
				pernamentCrosses.push_front(std::make_pair(yPoint, xPoint - gap - 1));
			}
		}

		if (m_nodes[i]->GetRightKid() > -1)
		{
			if (m_nodes[i]->GetRightKid() > static_cast<long long>(i))
			{
				size_t cx = xs[i] + m_nodes[i]->GetRightKidX();
				size_t cy = ys[i] + m_nodes[i]->GetKidY();
				size_t xPoint = xs[m_nodes[i]->GetRightKid()];
				size_t yPoint = ys[m_nodes[i]->GetRightKid()] + m_nodes[m_nodes[i]->GetRightKid()]->GetNextY();
				for (size_t k = cx; k < xPoint; ++k)
					table[yPoint][k] = '-';
				for (size_t k = cy; k < yPoint; ++k)
					table[k][cx] = '|';
				pernamentCrosses.push_front(std::make_pair(yPoint, cx));
				pernamentRightArrows.push_back(std::make_pair(yPoint, xPoint - 1));
			}
			else
			{
				size_t cx = xs[i] + m_nodes[i]->GetRightKidX();
				size_t cy = ys[i] + m_nodes[i]->GetKidY();
				size_t xPoint = xs[m_nodes[i]->GetRightKid()];
				size_t yPoint = ys[m_nodes[i]->GetRightKid()] + m_nodes[m_nodes[i]->GetRightKid()]->GetNextY();
				for (size_t k = cy; k < cy + gap + 2; ++k)
					table[k][cx] = '|';
				for (size_t k = xPoint - gap; k < cx; ++k)
					table[cy + gap + 2][k] = '-';
				for (size_t k = yPoint; k < cy + gap + 2; ++k)
					table[k][xPoint - gap - 1] = '|';
				pernamentCrosses.push_front(std::make_pair(cy + gap + 2, cx));
				pernamentCrosses.push_front(std::make_pair(cy + gap + 2, xPoint - gap - 1));
				pernamentCrosses.push_front(std::make_pair(yPoint, xPoint - gap - 1));
			}
		}
	}

	// Draw crosses and right arrows
	for (const auto& i : pernamentCrosses)
		table[i.first][i.second] = '+';
	for (const auto& i : pernamentRightArrows)
		table[i.first][i.second] = '>';

	// Redirect table
	for (auto& i : table)
	{
		long long j = static_cast<long long>(i.size()) - 1;
		for (; j >= 0; --j)
		{
			if (i[j] != ' ')
				break;
		}

		if (++j)
		{
			i.resize(j);
			file << i << "\n";
		}
	}
		
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
	file.open(pathToFile, std::ios::out);
	if (file.is_open())
	{
		for (auto& i : m_chains)
		{
			if (!i.CreateAndRedirectChart(file))
				return false;
			file << "\n";
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