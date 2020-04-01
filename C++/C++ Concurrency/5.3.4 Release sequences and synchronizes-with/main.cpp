#include <atomic>
#include <thread>
#include <mutex>
#include <vector>
#include <iostream>

std::mutex mutex;
void shared_print(std::thread::id id, int value)
{
	std::lock_guard<std::mutex> locker(mutex);
	std::cout << "Thread [" << id << "] received: " << value << std::endl;
}

std::vector<int> queue_data;
std::atomic<int> count;

void populate_queue()
{
	unsigned const size = 20;
	queue_data.clear();
	for (unsigned i = 0; i < size; ++i)
		queue_data.push_back(i);
	count.store(size, std::memory_order_release);
}

void consume_queue_items()
{
	while (true)
	{
		int item_index;
		if ((item_index = count.fetch_sub(1, std::memory_order_acquire)) <= 0)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(200));
			continue;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(200));
		shared_print(std::this_thread::get_id(), queue_data[item_index - 1]);
	}
}

int main()
{
	std::thread a(populate_queue);
	std::thread b(consume_queue_items);
	std::thread c(consume_queue_items);
	a.join();
	b.join();
	c.join();
	return 0;
}

// W tym przykladzie Anthony pokazuje ze gdyby istnialy dwa watki
// problem z nadpisywaniem count znika, natomiast w powyzszym przykladzie mamy
// trzy watki, jeden watek ktory wrzuca dane do vectora, drugi watek ktory czyta
// te dane oraz zmniejsza zmienna count o 1 oraz trzeci ktory robi dokladnie to
// samo co drugi watek. Problem polega na tym ze drugi watek moze przeczytac
// wartosc jaka przechowuje zmienna count i nadpisac ja ale podczas nadpisywania
// watek trzeci moze przeczytac stara wartosc. Anthony podkresla ze taka sytuacja
// nigdy nie zajdzie, jest to bowiem zabezpieczone zasada "Release sequence" oraz
// "happens-before". Anthony mowi ze moze istniec dowolna liczba watkow ktore 
// biora w tym udzial pod warunkiem ze kazdy z nich przeprowadza operacje RMW
// (operacje Read-Modify-Write takie jak funkcja fetch_sub()/store()...). 

// "If the store is tagged std::memory_order_release/std::memory_order_acq_rel/
// std::memory_order_seq_cst and the load is tagged std::memory_order_aquire/
// std::memory_order_consume/std::memory_order_seq_cst and each operation in the
// chain loads the value written by the previous operation, then the chain of
// the constitutes a release sequence and the initial store synchronizes-with.