#include "GraphNode.h"
#include "TextBlock.h"
#include <iostream>

bool GraphNode::ExtractNumber(int& number, const char*& line)
{
	if (isdigit(*line))
	{
		number = *line++ - '0';
		while (*line && isdigit(*line))
		{
			if (number > std::numeric_limits<int>::max())
			{
				std::cout << "Error in graph node, cannot convert string to number, number is out of range\n";
				return false;
			}

			number = number * 10 + (*line++ - '0');
		}
	}
	else if (*line == '-')
	{
		if (*(line + 1) != '1' || isdigit(*(line + 2)))
		{
			std::cout << "Error in graph node, cannot convert string to number, negative numbers other than -1 are not allowed\n";
			return false;
		}

		number = -1;
		line += 2;
	}

	return true;
}

bool GraphNode::ExtractIdentity(const char*& line)
{
	if (*line != '#')
	{
		std::cout << "Error in graph node, cannot convert string to identity, missing '#' character\n";
		return false;
	}

	if (!ExtractNumber(m_identity, ++line))
	{
		std::cout << "Error in graph node, cannot convert string to identity\n";
		return false;
	}

	return true;
}

bool GraphNode::ExtractKids(const char*& line)
{
	if (!ExtractNumber(m_kids.first, line))
	{
		std::cout << "Error in graph node, cannot convert string to left kid\n";
		return false;
	}

	SkipBlank(line);

	if (!ExtractNumber(m_kids.second, line))
	{
		std::cout << "Error in graph node, cannot convert string to right kid\n";
		return false;
	}

	return true;
}

bool GraphNode::ExtractNext(const char*& line)
{
	if (!ExtractNumber(m_next, line))
	{
		std::cout << "Error in graph node, cannot convert string to next\n";
		return false;
	}

	return true;
}

bool GraphNode::ExtractOperator(const char*& line)
{
	while (*line && (isalpha(*line) || isdigit(*line)))
		m_operator.push_back(*line++);

	if (m_operator.empty())
	{
		std::cout << "Error in graph node, missing operator\n";
		return false;
	}

	m_operator.shrink_to_fit();
	return true;
}

bool GraphNode::ExtractArguments(const char*& line)
{
	if (*line && *line == '"')
	{
		m_arguments.push_back(*line++); // "
		while (*line && *line != '"')
			m_arguments.push_back(*line++);
		m_arguments.push_back(*line++); // "

		if (m_arguments.back() != '"')
		{
			std::cout << "Error in graph node, missing quote in arguments\n";
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

GraphNode::GraphNode(const char* line, bool& status)
{
	status = false;
	if (ExtractIdentity(line))
	{
		SkipBlank(line);
		if (ExtractKids(line))
		{
			SkipBlank(line);
			if (ExtractNext(line))
			{
				SkipBlank(line);
				if (ExtractOperator(line))
				{
					SkipBlank(line);
					if (ExtractArguments(line))
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

bool GraphNodeChain::AddToNodes(std::string& line, bool& status)
{
	if (line.empty() || line.front() != '#')
	{
		status = true;
		m_nodes.shrink_to_fit();
		return false;
	}

	GraphNode newNode(line.c_str(), status);
	if (!status)
	{
		std::cout << "Error in graph node chain while adding new node\n";
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

bool GraphNodeManager::ReadLine(std::string& line)
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
			if (!m_chains.back().AddToNodes(line, status))
			{
				if (!status)
				{
					std::cout << "Error in graph node manager\n";
					return false;
				}

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