#pragma once
#include <algorithm>
#include <assert.h>
#include "IHeap.h"

class leftist_heap :public IHeap {
	struct T {
		int value;
		T * l, *r;
		int d;
		T() :value(0), l(0), r(0), d(1) {}
		T(int value) :value(value), l(0), r(0), d(1) {}
		~T() {
			if (l)delete l;
			if (r)delete r;
		}
	};

	int d(T * t) {
		return t ? t->d : 0;
	}

	T * root;

	T* Merge(T * T1, T * T2) {
		if (!T1)return T2;
		if (!T2)return T1;
		if (T1->value > T2->value)
			std::swap(T1, T2);
		T1->r = Merge(T1->r, T2);
		if (d(T1->r) > d(T1->l))
			std::swap(T1->l, T1->r);
		T1->d = d(T1->r) + 1;
		return T1;
	}

public:
	leftist_heap() :root(0) {}

	leftist_heap(int value) :root(new T(value)) {}

	~leftist_heap() {
		if(root)delete root;
	}

	void Meld(IHeap * T2) {
		leftist_heap * T2_ = dynamic_cast<leftist_heap*>(T2);
		root = Merge(root, T2_->root);
		T2_->root = NULL;
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