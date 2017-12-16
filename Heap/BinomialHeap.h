#pragma once
#include "IHeap.h"
#include <algorithm>
#include <vector>
#include <iterator>
#include <assert.h>

class binomial_heap :public IHeap {
private:
	struct Node {
		std::vector<Node*> childs_;
		int k_;
		int value_;
		Node() :value_(INT_MAX), k_(0) {}
		Node(int value) :value_(value), k_(0) {}
		~Node() {
			for (size_t i = 0; i < childs_.size(); ++i)
				delete childs_[i];
		}
		void Meld(Node * t) {
			assert(k_ == t->k_);
			if (t->value_ < value_) { std::swap(value_, t->value_); std::swap(childs_, t->childs_); }
			++k_;
			int i = (int)(childs_.size());
			childs_.push_back(t);
			while (i != 0 && childs_[i - 1]->k_ > childs_[i]->k_) {
				std::swap(childs_[i], childs_[i - 1]);
				--i;
			}
		}
	};

	Node * Copy(Node * t) {
		Node * root = new Node(t->value_);
		root->k_ = t->k_;
		for (size_t i = 0; i < t->childs_.size(); ++i)
			root->childs_.push_back(Copy(t->childs_[i]));
		return root;
	}

	int MinimumIndex_;

	std::vector<Node*> all_trees_;

	void UpdateMinimum_() {
		MinimumIndex_ = 0;
		for (size_t i = 1; i < all_trees_.size(); ++i) {
			if (all_trees_[MinimumIndex_]->value_ > all_trees_[i]->value_)
				MinimumIndex_ = i;
		}
	}

	binomial_heap(Node * t) {
		all_trees_ = t->childs_;
		t->childs_.clear();
	}

	struct Comparator {
		bool operator() (Node * fi, Node * se)const {
			return fi->k_ < se->k_;
		}
	};
public:
	binomial_heap() {}

	~binomial_heap() {
		for (size_t i = 0; i < all_trees_.size(); ++i)
			delete all_trees_[i];
	}

	binomial_heap(int value) :MinimumIndex_(0) {
		all_trees_.push_back(new Node(value));
	}

	binomial_heap& operator=(const binomial_heap & b) {
		if (this == &b)return *this;
		MinimumIndex_ = b.MinimumIndex_;
		all_trees_.clear();
		for (size_t i = 0; i < b.all_trees_.size(); ++i)
			all_trees_.push_back(Copy(b.all_trees_[i]));
		return *this;
	}

	void Meld(IHeap * T2) {
		binomial_heap * T2_ = dynamic_cast<binomial_heap*>(T2);
		std::vector<Node*> buffer_;
		std::merge(all_trees_.begin(), all_trees_.end(), T2_->all_trees_.begin(),
			T2_->all_trees_.end(), back_inserter(buffer_), Comparator());
		all_trees_.clear();
		for (size_t i = 0; i < buffer_.size(); ++i) {
			if (i + 1 == buffer_.size() || buffer_[i]->k_ != buffer_[i + 1]->k_ ||
				(i + 2 < buffer_.size() && buffer_[i]->k_ == buffer_[i + 1]->k_ && buffer_[i + 1]->k_ == buffer_[i + 2]->k_)) {
				all_trees_.push_back(buffer_[i]);
			}
			else {
				buffer_[i + 1]->Meld(buffer_[i]);
			}
		}
		T2_->all_trees_.clear();
		UpdateMinimum_();
	}

	void Insert(int value) {
		Meld(new binomial_heap(value));
	}

	int GetMin()const {
		assert(all_trees_.size() > 0);
		return all_trees_[MinimumIndex_]->value_;
	}

	int ExtractMin() {
		int ReturnValue_ = GetMin();
		Node * PosMin = all_trees_[MinimumIndex_];
		all_trees_.erase(all_trees_.begin() + MinimumIndex_);
		Meld(new binomial_heap(PosMin));
		delete PosMin;
		return ReturnValue_;
	}
};