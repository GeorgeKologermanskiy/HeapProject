#pragma once
#include <algorithm>
#include <set>
#include <assert.h>
#include "IHeap.h"

class heap :public IHeap {
	std::multiset<int> all;
public:
	int Size()const {
		return (int)all.size();
	}

	heap() {}

	~heap() {}

	void Meld(IHeap * T2_) {
		heap * T2 = dynamic_cast<heap*>(T2_);
		while (!T2->all.empty()) {
			all.insert(*T2->all.begin());
			T2->all.erase(T2->all.begin());
		}
	}

	void Insert(int value) {
		all.insert(value);
	}

	int GetMin()const {
		assert(Size() != 0);
		return *all.begin();
	}

	int ExtractMin() {
		int ReturnValue = GetMin();
		all.erase(all.begin());
		return ReturnValue;
	}

};
