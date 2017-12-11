#pragma once
#include <algorithm>
#include <assert.h>
#include "IHeap.h"

class skew_heap :public IHeap {
	struct T {
		int value;
		T * l, *r;
		T() :value(0), l(0), r(0) {}
		T(int value) :value(value), l(0), r(0) {}
		~T() {}
	};

	T * root;

	T* Merge(T * T1, T * T2) {
		if (!T1)return T2;
		if (!T2)return T1;
		if (T1->value > T2->value)
			std::swap(T1, T2);
		T1->r = Merge(T1->r, T2);
		std::swap(T1->r, T1->l);
		return T1;
	}

public:
	skew_heap() :root(0) {}

	skew_heap(int value) :root(new T(value)) {}

	void Meld(IHeap & T2) {
		skew_heap * T2_ = dynamic_cast<skew_heap*>(&T2);
		root = Merge(root, T2_->root);
	}

	void Insert(int value) {
		root = Merge(root, new T(value));
	}

	int GetMin()const {
		assert(root != 0);
		return root->value;
	}

	int ExtractMin() {
		int ReturnValue = GetMin();
		T * tmp = Merge(root->l, root->r);
		root->l = root->r = 0;
		delete root;
		root = tmp;
		return ReturnValue;
	}
};