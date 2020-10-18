#include <mutex>
#include <atomic>
#include <exception>

template<typename T>
class LockFreeStack
{
	struct Node
	{
		std::shared_ptr<T> data;
		Node* next;
		Node(T const& data) : data(std::make_shared<T>(data))
		{
		}
	};

	std::atomic<Node*> head;
	std::atomic<unsigned> threadsInPop;
	std::atomic<Node*> toBeDeleted;
	
	static void deleteNodes(Node* nodes)
	{
		while (nodes)
		{
			Node next = nodes->next;
			delete nodes;
			nodes = next;
		}
	}

	void tryReclaim(Node* oldHead)
	{
		if (threadsInPop == 1)
		{
			Node* nodesToDelete = toBeDeleted.exchange(nullptr);
			if (!--threadsInPop)
				deleteNodes(nodesToDelete);
			else if (nodesToDelete)
				chainPendingNodes(nodesToDelete);
			delete oldHead;
		}
		else
		{
			chainPendingNode(oldHead);
			--threadsInPop;
		}
	}

	void chainPendingNodes(Node* nodes)
	{
		Node* last = nodes;
		while (Node* const next = last->next)
			last = next;
		chainPendingNodes(nodes, last);
	}

	void chainPendingNodes(Node* first, Node* last)
	{
		last->next = toBeDeleted;
		while (!toBeDeleted.compare_exchange_weak(last->next, first));
	}

	void chainPendingNode(Node* n)
	{
		chainPendingNodes(n, n);
	}
public:

	void push(T const& data)
	{
		Node* const newNode = new Node(data);
		newNode->next = head.load(); // Load current value of the head
		while (!head.compare_exchange_weak(newNode->next, newNode)); // If head changed, newNode->next is updated
	}

	std::shared_ptr<T> pop()
	{
		++threadsInPop;
		Node* oldHead = head.load();
		while (oldHead && !head.compare_exchange_weak(oldHead, oldHead->next)); // Check also if oldHead is not nullptr
		std::shared_ptr<T> result;
		if (oldHead)
			result.swap(oldHead->data);
		tryReclaim(oldHead); // Reclaim deleted nodes if you can
		return result;
	}
};


int main(int argc, char** argv)
{
	return 0;
}
