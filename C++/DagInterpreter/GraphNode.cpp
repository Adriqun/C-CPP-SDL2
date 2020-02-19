#include "GraphNode.h"
#include "TextBlock.h"
#include <iostream>

void GraphNode::PrintError(unsigned int row, long long column, const char* message)
{
	std::cout << "Error:" << std::to_string(row) << ":" << std::to_string(column) << ": " << message << std::endl;
}

bool GraphNode::ExtractNumber(int& number, const char*& line, unsigned int row)
{
	const char* copy = line;
	if (isdigit(*line))
	{
		number = *line++ - '0';
		while (*line && isdigit(*line))
		{
			if (number > std::numeric_limits<int>::max())
			{
				PrintError(row, line - copy, "Cannot convert string to number, number is out of range!");
				return false;
			}

			number = number * 10 + (*line++ - '0');
		}
	}
	else if (*line == '-')
	{
		if (*(line + 1) != '1' || isdigit(*(line + 2)))
		{
			PrintError(row, line - copy, "Cannot convert string to number, negative numbers other than -1 are not allowed!");
			return false;
		}

		number = -1;
		line += 2;
	}

	return true;
}

bool GraphNode::ExtractIdentity(const char*& line, unsigned int row)
{
	if (*line != '#')
	{
		PrintError(row, 0, "Cannot convert string to identity, missing '#' character!");
		return false;
	}

	return ExtractNumber(m_identity, ++line, row);
}

bool GraphNode::ExtractKids(const char*& line, unsigned int row)
{
	const char* copy = line;
	if (!ExtractNumber(m_kids.first, line, row))
	{
		PrintError(row, line - copy, "Cannot convert string for the left kid node!");
		return false;
	}

	SkipBlank(line);

	if (!ExtractNumber(m_kids.second, line, row))
	{
		PrintError(row, line - copy, "Cannot convert string for the right kid node!");
		return false;
	}

	return true;
}

bool GraphNode::ExtractNext(const char*& line, unsigned int row)
{
	const char* copy = line;
	if (!ExtractNumber(m_next, line, row))
	{
		PrintError(row, line - copy, "Cannot convert string for the next node!");
		return false;
	}

	return true;
}

bool GraphNode::ExtractOperator(const char*& line, unsigned int row)
{
	const char* copy = line;
	while (*line && (isalpha(*line) || isdigit(*line)))
		m_operator.push_back(*line++);

	if (m_operator.empty())
	{
		PrintError(row, line - copy, "Node contains does not contain operator!");
		return false;
	}

	m_operator.shrink_to_fit();
	return true;
}

bool GraphNode::ExtractArguments(const char*& line, unsigned int row)
{
	if (*line && *line == '"')
	{
		const char* copy = line;
		m_arguments.push_back(*line++); // "
		while (*line && *line != '"')
			m_arguments.push_back(*line++);
		m_arguments.push_back(*line++); // "

		if (m_arguments.back() != '"')
		{
			PrintError(row, line - copy, "Missing quote in arguments!");
			return false;
		}

		m_arguments.shrink_to_fit();
	}

	return true;
}

void GraphNode::ExtractComment(const char*& line)
{
	if (*line && *line == ';')
	{
		while (*line)
			m_comment.push_back(*line++);
		m_comment.shrink_to_fit();
	}
}

void GraphNode::SkipBlank(const char*& line)
{
	while (*line == ' ' || *line == '\t')
		++line;
}

GraphNode::GraphNode(const char* line, unsigned int row, bool& status)
{
	status = false;
	if (ExtractIdentity(line, row))
	{
		SkipBlank(line);
		if (ExtractKids(line, row))
		{
			SkipBlank(line);
			if (ExtractNext(line, row))
			{
				SkipBlank(line);
				if (ExtractOperator(line, row))
				{
					SkipBlank(line);
					if (ExtractArguments(line, row))
					{
						SkipBlank(line);
						ExtractComment(line);
						status = true;
					}
				}
			}
		}
	}
}

const int& GraphNode::Identity() const
{
	return m_identity;
}

const int& GraphNode::LeftKid() const
{
	return m_kids.first;
}

const int& GraphNode::RightKid() const
{
	return m_kids.second;
}

const int& GraphNode::Next() const
{
	return m_next;
}

bool GraphNodeChain::AddToJunk(std::string& line)
{
	if (!line.empty() && line.front() == '#')
		return false;
	m_junk.push_back(line);
	return true;
}

bool GraphNodeChain::AddToNodes(std::string& line, unsigned int row, bool& status)
{
	if (line.empty() || line.front() != '#')
	{
		status = true;
		m_nodes.shrink_to_fit();
		return false;
	}

	GraphNode newNode(line.c_str(), row, status);
	if (!status)
	{
		std::cout << "Error: Graph node chain received stop signal while adding new node!" << std::endl;
		return false;
	}

	m_nodes.push_back(std::move(newNode));
	return true;
}

GraphNodeManager::GraphNodeManager()
{
	m_stream = false;
	m_chains.push_back(GraphNodeChain());
}

bool GraphNodeManager::ReadLine(std::string& line, unsigned int row)
{
	while (true)
	{
		if (!m_stream)
		{
			if (!m_chains.back().AddToJunk(line))
			{
				m_stream = true;
				continue;
			}
		}
		else
		{
			bool status;
			if (!m_chains.back().AddToNodes(line, row, status))
			{
				if (!status)
					return false;
				m_stream = false;
				m_chains.push_back(GraphNodeChain());
				continue;
			}
		}

		break;
	}

	return true;
}

void GraphNodeManager::Set(std::vector<TextNodeChain>& rhs)
{
	size_t size = m_chains.size();
	rhs.resize(size);

	auto jt = m_chains.begin();
	for (size_t i = 0; i < size; ++i)
	{
		rhs[i].SetJunk(std::move(jt->m_junk));
		rhs[i].Set(jt->m_nodes);
		++jt;
	}

	m_chains.clear();
}