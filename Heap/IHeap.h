#pragma once
class IHeap {
public:
	IHeap() {}

	virtual ~IHeap() {};

	virtual void Insert(int) = 0;

	virtual int GetMin()const = 0;

	virtual int ExtractMin() = 0;

	virtual void Meld(IHeap *) = 0;

};
