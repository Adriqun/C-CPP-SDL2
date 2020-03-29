C++ Memory Order - czyli kolejność zapytań odczytu jak i zapisu do pamięci

Problem polega na tym, że kod wykonywany przez program jest "niedeterministyczny w małej skali".
Przykładowo mamy trzy wyrażenia na zmiennych globalnych x, y i z typu int:
{
	x = 0;
	y = z;
	z = 1;
	// <- Patrzac z perspektywy tego miejsca w kodzie nie obchodzi nas czy najpierw wykonany zostal
	// zapis do x czy zapis do y, kod który wykona się podczas dzialania programu mógł najpierw
	// przypisać wartość do zmiennej y a dopiero później do x. Program czesto wykonuje "część" kodu
	// do przodu tj. wykonuje odczyt lub zapis mimo, że ta część kodu "nie została" jeszcze wykonana.
	// Takie zachowanie wykonywane jest w celach optymalizacyjnych, gdy program poprawnie wykona
	// odczyt lub zapis "do przodu" zyskujemy na czasie.

	if (!x) // <- Bedac w tym miejscu w kodzie program mogl juz zdąrzyć poprosić o dane, które
	{		// przechowuje zmienna x oraz o dane które przechowuje zmienna y, mimo, że if (!x) się jeszcze nie wykonał
		int a = z;
		int b = y;
	}
	else
	{
		// ...
	}

	// Taki dostęp do pamięci w celach odczytu lub zapisu najlepiej zoobrazować sobie jako
	// wysyłanie i odbieranie maila. Wysylanie jak i odbieranie maila trwa. Wysylajac dwa maile
	// moze okazac się, że ten mail który wysłaliśmy jako drugi, został odebrany jako pierwszy
	// Tak dziala pamieć w komputerze, to samo może się zdarzyć dla odczytu (odbierania mail)
	// Mimo, że przypisujemy x oraz y jakąś wartośc wcale nie oznacza to, że dane zmiennej x
	// zostaną szybciej uzupelnione. W ponizszych przykladach przyjmujemy, że "dana część kodu"
	// zostanie wykonana w takiej a takiej kolejności, jednak tak naprawdę mamy na myśli, że
	// kod wykona się w takiej kolejności w jakiej występuje natomiast zapis jak i odczyt jest już
	// w innej kolejności niż w jakiej występuje.
}

Problem z kolejnością dostępu do pamięci pojawia się w momencie gdy mamy więcej niż jeden wątek.
Przykładowo jeden wątek mógł poprosić o dane dla zmiennej x podczas gdy w tym samym czasie inny wątek
przypisuje zmiennej y nową wartość. Mimo, że zmienne x i y wskazują na inne miejsce w pamięci to wcale nie oznacza to
że są od siebie niezależne. Takie zachowanie jest nieakceptowalne stąd dla wielu wątków wymyślono
tzw. bramki "fences". Bramki blokują niejako swobodę dostępu do pamięci tj. zmuszają do tego aby kod wykonywany był
sekwencyjnie (dostęp do pamięci wykonywany był sekwencyjnie).
Dla przykładu gdyby nasze trzy zmienne x, y i z były zmiennymi atomowymi to każda operacja na nich jest
zabezpieczona poprzez dodatkową generacje kodu czyli tych bramek, wiemy jednak, że nie zawsze potrzebujemy aby każda
operacja odczytu/zapisu była sekwencyjna, w niektórych przypadkach jest nam to obojętne, a jeśli jest nam to obojętne
to warto przyspieszyć nasz program poprzez dodanie odpowiedniej flagi. O flagach poniżej.


int global;
std::atomic<bool> x, y;
std::atomic<int> z;

1. std::memory_order_seq_cst
	Jest defaultowy argument dla operacji store (zapis) i load (odczyt).
	Gwarantuje, że operacje zapisu/odczytu które występują przed danym wyrażeniem wykonują się przed np.
	{
		global = 123;
		bool tmp = x.load(std::memory_order_relaxed);
		y.store(false, std::memory_order_relaxed);
		// Nie wiemy w jakiej "kolejnosci wykona sie powyzszy kod" ale mamy pewnosc ze wykona sie
		// przed ponizszym wyrazeniem. (tj. wiemy w jakiej kolejnosci kod sie wykona ale sama kolejnosc zapytan o dane w pamieci lub
		// tez ich zapis nie jest nam znany i to jest ok!)
		z.store(0, std::memory_order_seq_cst); // lub operacja load
	}
	
	Tryb ten gwarantuje również, że operacje zapisu/odczytu, które występują po danym wyrażeniu wykonają się po nim np.
	{
		z.store(0, std::memory_order_seq_cst); // lub operacja load
		// Nie wiemy w jakiej kolejnosci wykona sie ponizszy kod ale mamy pewnosc ze wykona sie
		// po powyzszym wyrazeniu
		global = 123;
		bool tmp = x.load(std::memory_order_relaxed);
		y.store(false, std::memory_order_relaxed);
	}
	
2. std::memory_order_relaxed
	Flaga ta zapewnia, że kolejność (dostępu do pamięci) zapisu jak i odczytu, która występuje przed jak i po
	naszym wyrażeniu nie mają znaczenia.
	{
		global = 123;
		bool tmp = x.load(std::memory_order_relaxed);
		y.store(false, std::memory_order_relaxed);
		z.store(0, std::memory_order_relaxed); // <-- Tak naprawde nie wiemy czy najpierw
		// zostanie wykonane przypisanie do global, czy zapis x.store, czy być może x.load, nic
		// nie jest pewne
	}
	{
		z.store(0, std::memory_order_relaxed); // <-- Nie mamy pewnosci że to wyrażenie wykona się przed
		// ponizszymi wyrazeniami (tj. wiemy że wykona się przed patrząc na kod
		// ale sam zapis do pamięci może zostać wykonany później!)
		global = 123;
		bool tmp = x.load(std::memory_order_relaxed);
		y.store(false, std::memory_order_relaxed);
	}

3.	std::memory_order_acquire
	Gwarantuje on, że operacje zapisu jak i odczytu które występują przed danym wyrażeniem wykonają się również przed nim.
	{
		global = 123;
		bool tmp = x.load(std::memory_order_relaxed);
		y.store(false, std::memory_order_relaxed);
		z.store(0, std::memory_order_acquire); // <-- Mamy pewnosc ze wszystkie operacje ktore występują
		// przed tym wyrazeniem zostana uprzednio wykonane, tj. zapis do global, załadowanie x, zapis do y
		// wykonają się przed zapisem do z!
	}

	std::memory_order_release
	Gwarantuje on, że operacja zapisu jak i odczytu, która występuje po danym wyrażeniu wykona się równiez po nim.
	{
		z.store(0, std::memory_order_relaxed); // <-- mamy pewność, że zmienna z będzie równa 0 po tym wyrażeniu!

		global = 123;
		bool tmp = x.load(std::memory_order_relaxed);
		y.store(false, std::memory_order_relaxed);
	}


4. std::memory_order_acq_rel
	Łączy w sobie cechy dwóch poprzednich flag. Flagę ta najlepiej wykorzystywany jest dla wątków pośrednich np.
	{
		std::atomic<int> data[5];
		std::atomic<bool> sync1(false), sync2(false);

		void thread_1()
		{
			data[0].store(42, std::memory_order_relaxed);
			data[1].store(43, std::memory_order_relaxed);
			data[2].store(44, std::memory_order_relaxed);
			data[3].store(45, std::memory_order_relaxed);
			data[4].store(46, std::memory_order_relaxed);
			sync1.store(true, std::memory_order_release);
		}

		void thread_2()
		{	// Watek posredni
			while (!sync1.load(std::memory_order_acquire)); // Czekaj na sync1 = true
			sync2.store(true, std::memory_order_release);
		}

		void thread_3()
		{
			while (!sync2.load(std::memory_order_acquire)); // Czekaj na sync2 = true
			assert(data[0].load(std::memory_order_relaxed) == 42);
			assert(data[1].load(std::memory_order_relaxed) == 43);
			assert(data[2].load(std::memory_order_relaxed) == 44);
			assert(data[3].load(std::memory_order_relaxed) == 45);
			assert(data[4].load(std::memory_order_relaxed) == 46);
		}
	}

	Powyższą funkcje thread_2 można zastąpić flagą std::memory_order_acq_rel w następujący sposób
	{
		std::atomic<int> sync(0);
		void thread_1()
		{
			// ...
			sync.store(1, std::memory_order_release);
		}

		void thread_2()
		{	// Watek posredni
			int expected = 1;
			while (!sync.compare_exchange_strong(expected, 2, std::memory_order_acq_rel))
				expected = 1;
			// ...
		}

		void thread_3()
		{
			while (!sync.load(std::memory_order_acquire) < 2); // Czekaj na sync2 > 2
			// ...
		}
	}

5. std::memory_order_consume
	Służy do zabezpieczenia "łańcuchu zależności" (dependency chain) danej zmiennej. Podobnie jak std::memory_order_acquire
	zapewnia, że każda operacja zapisu i odczytu która występuje przed tym wyrażeniem nie może zmienić swojej kolejności