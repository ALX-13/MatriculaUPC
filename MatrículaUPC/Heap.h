#ifndef __HEAP_H__
#define __HEAP_H__
#include "HeapNode.h"
template<class T>
class Heap
{
private:
	HeapNode<T>* LastNode;
	size_t Size;
public:
	Heap();
	~Heap();
	HeapNode<T>* getHeapNode(size_t Indez);
	size_t getSize();
	void Push(T Object);
	T Pop();
	T Peek();
	bool IsEmpty();
};
template<class T>
Heap<T>::Heap()
{
	LastNode = nullptr;
	Size = 0;
}
template<class T>
Heap<T>::~Heap()
{
	HeapNode<T>* Auxiliary = LastNode;
	while (Auxiliary != nullptr)
	{
		LastNode = LastNode->getPreviousNode();
		delete Auxiliary;
		Auxiliary = LastNode;
	}
}
template<class T>
HeapNode<T>* Heap<T>::getHeapNode(size_t Index) {
	HeapNode<T>* Auxiliary = LastNode;
	for (size_t i = Size - 1; i > Index; i--)
	{
		Auxiliary = Auxiliary->getPreviousNode();
	}
	return Auxiliary;
}
template<class T>
size_t Heap<T>::getSize() {
	return Size;
}
template<class T>
void Heap<T>::Push(T Object) {
	HeapNode<T>* NewNode = new HeapNode<T>(Object);
	if (LastNode == nullptr) {

	}
	else {
		NewNode->setPreviousNode(LastNode);
	}
	Size++;
	LastNode = NewNode;
	NewNode = nullptr;
}
template<class T>
T Heap<T>::Pop() {
	HeapNode<T>* Auxiliary = LastNode;
	T Object = LastNode->getObject();
	LastNode = LastNode->getPreviousNode();
	Size--;
	delete Auxiliary;
	Auxiliary = nullptr;
	return Object;
}
template<class T>
T Heap<T>::Peek() {
	return LastNode->getObject();
}
template<class T>
bool Heap<T>::IsEmpty() {
	return LastNode == nullptr;
}
#endif // !__HEAP_H__