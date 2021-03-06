namespace Контейнерные классы {
	Типы:
		Последовательные контейнеры (начальный, конечный, следующий, предыдущий элементы) {
			vector, deque, list
			_  _  _  _  _  _  _  _
		   |_||_||_||_||_||_||_||_| - vector

		   	_  	  _     _     _     _     _     _     _
		   |_|<->|_|<->|_|<->|_|<->|_|<->|_|<->|_|<->|_| - deque

		   	_  	  _     _     _     _     _     _     _
		   |_|<->|_|<->|_|<->|_|<->|_|<->|_|<->|_|<->|_| - list

		 + Адаптеры для последовательных контейнеров:
			queue, stack, priority_queue
		
		}

		Ассоциативные контейнеры (ключ, возможна информативная часть) {
			map, multimap, set (состоит только из ключей - без дубликатов), multiset (множество ключей с дубликатами),
			bitset
		}

		Для доступа к элементам контейнера существует класс Iterator (иногда называют умным указателем).

					vector		deque		list
		push_front	  -			 O(1)		O(1)
		push_back	 O(1)		 O(1)		O(1)
		pop_front	 O(1)		 O(1)		O(1)
		pop_back 	 O(1)		 O(1)		O(1)
		insert		 O(n)		 O(n)		O(1)
		erase		 O(n)		 O(n)		O(1)
		at, []       O(1)		 O(1)		 -

		// insert(it v2.start, it v2.end, it v1) see on cppreference
}