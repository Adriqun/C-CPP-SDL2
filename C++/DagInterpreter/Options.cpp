#include "Options.h"
#include <iostream>
#include <limits>
#include <array>

void Options::PrintHelp()
{
	std::cout << "Dag interpreter options are:\n";
	std::cout << "0. Print dag interpreter options: -help\n";
	std::cout << "1. Remove comments: -rmc\n";
	std::cout << "2. Remove arguments: -rma\n";
	std::cout << "3. Reduce comments(sets max comments length): -rdc <unsigned int>\n";
	std::cout << "4. Reduce arguments(sets max arguments length): -rda <unsigned int>\n";
	std::cout << "5. Set left alignment: -sla\n";
	std::cout << "6. Set right alignment: -sra\n";
	std::cout << "7. Set center alignment: -sca\n";
	std::cout << "8. Print node number inside the edge: -pnn\n";
	std::cout << "9. Print top most used nodes: -top <unsigned int>\n";
	std::cout << "10. Specify directed acyclic graph file: -file <filename>\n";
}

bool Options::Compare(char* argument)
{
	if (lastIdentifier != None)
	{
		switch (lastIdentifier)
		{
			case ReduceComments:
			case ReduceArguments:
			case PrintMostUsed:
			{
				if (!*argument || !isdigit(*argument))
				{
					std::cout << "Error: Expected argument is <unsigned int>!" << std::endl;
					return false;
				}

				unsigned long long value = static_cast<unsigned long long>((*argument++) - '0');
				while (*argument)
				{
					if (!isdigit(*argument))
					{
						std::cout << "Error: Expected argument <unsigned int> is inconsistent!" << std::endl;
						return false;
					}
						
					value = value * 10 + static_cast<unsigned long long>(((*argument++) - '0'));
					if (value > static_cast<unsigned long long>(std::numeric_limits<unsigned int>::max()))
					{
						std::cout << "Error: Specified <unsigned int> argument exceeds its range!" << std::endl;
						return false;
					}
				}

				switch (lastIdentifier)
				{
					case ReduceComments:
					{
						m_maxCommentLength = static_cast<unsigned int>(value);
						break;
					}
					case ReduceArguments:
					{
						m_maxArgumentsLength = static_cast<unsigned int>(value);
						break;
					}
					case PrintMostUsed:
					{
						m_TopMostUsed = static_cast<unsigned int>(value);
						break;
					}
				}
				break;
			}
			case SpecifyFile:
			{
				m_files.emplace_back(argument);
				break;
			}
			default:
				break;
		}

		lastIdentifier = None;
		return true;
	}

	if (*argument++ != '-')
	{
		std::cout << "Error: Missing '-' in specified switch \"" << argument << "\"" << std::endl;
		return false;
	}

	switch (*argument)
	{
		case 'h':
		{
			if (*++argument == 'e' && *++argument == 'l' && *++argument == 'p' && !*++argument)
			{
				if (m_data & Identifier::Help)
				{
					std::cout << "Error: Switch \"-help\" was specified more than once!" << std::endl;
					return false;
				}

				m_data &= Identifier::Help;
				return true;
			}
			break;
		}
		case 'r':
		{
			if (*(argument + 3))
				break;

			switch (*++argument)
			{
				case 'm':
				{
					if (*++argument == 'c')
					{
						if (m_data & Identifier::RemoveComments)
						{
							std::cout << "Error: Switch \"-rmc\" was specified more than once!" << std::endl;
							return false;
						}

						m_data &= Identifier::RemoveComments;
						return true;
					}
					else if (*argument == 'a')
					{
						if (m_data & Identifier::RemoveArguments)
						{
							std::cout << "Error: Switch \"-rma\" was specified more than once!" << std::endl;
							return false;
						}

						m_data &= Identifier::RemoveArguments;
						return true;
					}
					break;
				}
				case 'd':
				{
					if (*++argument == 'c')
					{
						lastIdentifier = Identifier::ReduceComments;
						m_data &= Identifier::ReduceComments;
						return true;
					}
					else if (*argument == 'a')
					{
						lastIdentifier = Identifier::ReduceArguments;
						m_data &= Identifier::ReduceArguments;
						return true;
					}
					break;
				}
				default:
					break;
			}
			break;
		}
		case 's':
		{
			if (!*(argument + 1) || *(argument + 2) != 'a' || *(argument + 3))
				break;
			switch (*++argument)
			{
				case 'l':
				{
					if (m_data & Identifier::SetLeftAlignment)
					{
						std::cout << "Error: Switch \"-sla\" was specified more than once!" << std::endl;
						return false;
					}

					m_data &= Identifier::SetLeftAlignment;
					return true;
				}
				case 'r':
				{
					if (m_data & Identifier::SetRightAlignment)
					{
						std::cout << "Error: Switch \"-sra\" was specified more than once!" << std::endl;
						return false;
					}

					m_data &= Identifier::SetRightAlignment;
					return true;
				}
				case 'c':
				{
					if (m_data & Identifier::SetCenterAlignment)
					{
						std::cout << "Error: Switch \"-sca\" was specified more than once!" << std::endl;
						return false;
					}

					m_data &= Identifier::SetCenterAlignment;
					return true;
				}
			}
			break;
		}
		case 'p':
		{
			if (*++argument == 'n' && *++argument == 'n' && !*++argument)
			{
				if (m_data & Identifier::PrintNodeNumberInsideEdge)
				{
					std::cout << "Error: Switch \"-pnn\" was specified more than once!" << std::endl;
					return false;
				}

				m_data &= Identifier::PrintNodeNumberInsideEdge;
				return true;
			}
			break;
		}
		case 't':
		{
			if (*++argument == 'o' && *++argument == 'p' && !*++argument)
			{
				if (m_data & Identifier::PrintMostUsed)
				{
					std::cout << "Error: Switch \"-top\" was specified more than once!" << std::endl;
					return false;
				}

				m_data &= Identifier::PrintMostUsed;
				return true;
			}
			break;
		}
		case 'f':
		{
			if (*++argument == 'i' && *++argument == 'l' && *++argument == 'e' && !*++argument)
			{
				lastIdentifier = Identifier::SpecifyFile;
				m_data &= Identifier::SpecifyFile;
				return true;
			}
			break;
		}
	}

	std::cout << "Error: Cannot find specified switch \"" << argument << "\"!" << std::endl;
	return false;
}

Options::Options(int argc, char** argv, bool& status)
{
	if (argc == 1)
	{
		PrintHelp();
		status = false;
	}
	else
	{
		status = true;
		lastIdentifier = None;
		m_maxCommentLength = std::numeric_limits<unsigned int>::max();
		m_maxArgumentsLength = std::numeric_limits<unsigned int>::max();
		m_TopMostUsed = 0;
		m_data = 0;

		for (int i = 1; i < argc; ++i)
		{
			if (!Compare(argv[i]))
			{
				status = false;
				std::cout << "Error: Cannot parse command line!\n";
				break;
			}
		}

		if (lastIdentifier != None)
		{
			status = false;
			std::cout << "Error: Last specified switch requires argument!\n";
		}
		else if (status)
		{
			if (m_data & Identifier::Help)
			{
				status = false;
				PrintHelp();
			}
			else
			{
				if (m_data & Identifier::RemoveArguments && m_data & Identifier::ReduceArguments)
				{
					status = false;
					std::cout << "Error: Specified switch \"-rma\" disqualify \"-rda\"!\n";
				}
				
				if (m_data & Identifier::RemoveComments && m_data & Identifier::ReduceComments)
				{
					status = false;
					std::cout << "Error: Specified switch \"-rmc\" disqualify \"-rdc\"!\n";
				}

				if ((m_data & Identifier::SetLeftAlignment && (m_data & Identifier::SetRightAlignment || m_data & Identifier::SetCenterAlignment)) ||
					(m_data & Identifier::SetCenterAlignment && (m_data & Identifier::SetLeftAlignment || m_data & Identifier::SetRightAlignment)) ||
					(m_data & Identifier::SetRightAlignment && (m_data & Identifier::SetCenterAlignment || m_data & Identifier::SetLeftAlignment)))
				{
					status = false;
					std::cout << "Error: More than one alignment specified!\n";
				}
			}
		}
	}
}

Options::~Options()
{
	std::cout << "Press enter to continue...";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::list<std::string>::iterator Options::Begin()
{
	return m_files.begin();
}

std::list<std::string>::iterator Options::End()
{
	return m_files.end();
}