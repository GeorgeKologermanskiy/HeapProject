#pragma once
#include <algorithm>
#include <set>
#include <assert.h>

class heap {
	std::multiset<int> all;
public:
	int Size()const {
		return (int)all.size();
	}
	heap() {}
	void Meld(heap & T2) {
		while (!T2.all.empty()) {
			all.insert(*T2.all.begin());
			T2.all.erase(T2.all.begin());
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
/*
class heap {
	struct T {
		int value;
		T * l, *r;
		T() :value(0), l(0), r(0) {}
		T(int value) :value(value), l(0), r(0) {}
		~T() {}
	};

	T * root;

	int Size_;

	T* Merge(T * T1, T * T2) {
		if (!T1)return T2;
		if (!T2)return T1;
		if (T1->value > T2->value)
			std::swap(T1, T2);
		if (rand() & 1)
			std::swap(T1->l, T1->r);
		T1->r = Merge(T1->r, T2);
		return T1;
	}

public:

	int Size()const {
		return Size_;
	}

	heap() :root(0), Size_(0) {}

	heap(int value) :root(new T(value)), Size_(1) {}

	void Meld(heap & T2) {
		Size_ += T2.Size_;
		root = Merge(root, T2.root);
	}

	void Insert(int value) {
		++Size_;
		root = Merge(root, new T(value));
	}

	int GetMin()const {
		assert(root != 0);
		return root->value;
	}

	int ExtractMin() {
		--Size_;
		int ReturnValue = GetMin();
		T * tmp = Merge(root->l, root->r);
		root->l = root->r = 0;
		delete root;
		root = tmp;
		return ReturnValue;
	}
};*/