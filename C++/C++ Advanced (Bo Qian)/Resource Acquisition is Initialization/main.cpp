#include <cstdio>
#include <mutex>

class Lock {
	std::tr1::shared_ptr<Mutex_t> pMutex;
public:
	explicit Lock(Mutex_t* pm) :pMutex(pm, Mutex_unlock) {
		Mutex_lock(pm);
	}

};

int main()
{
	Lock L1(&mu);
	Lock L2(L1);

	return 0;
}
