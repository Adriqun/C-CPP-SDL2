#pragma once
#include <list>
#include <mutex>

class GlobalDynamicMemory
{
	std::list<char*> m_blocks;
	std::mutex m_mutex;

public:
	void add(char* block)
	{
		std::lock_guard<std::mutex> locker(m_mutex);
		m_blocks.push_back(block);
	}

	~GlobalDynamicMemory()
	{
		for (auto& i : m_blocks)
			delete[] i;
		m_blocks.clear();
	}
};
GlobalDynamicMemory GDM;

class Task
{
	char* m_data;
	bool m_deffered;
	long long m_identity;
	long long m_name;

public:
	Task(long long identity, long long name)
	{
		m_identity = identity;
		m_name = name;
	}

	~Task()
	{
		if (!m_deffered)
			delete[] m_data;
		else
			GDM.add(m_data);
	}

	const char* data() const
	{
		return m_data;
	}
};