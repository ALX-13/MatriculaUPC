#ifndef __DOUBLE_CIRCULAR_LINKED_LIST_H__
#define __DOUBLE_CIRCULAR_LINKED_LIST_H__
#include "DoubleNode.h"
template<class T>
class DoubleCircularLinkedList {
private:
	DoubleNode<T>* FirstNode;
	DoubleNode<T>* LastNode;
	size_t Size;
public:
	class Iterator {
	public:
		size_t Index;
		DoubleNode<T>* Auxiliary;
		Iterator(size_t Index, DoubleNode<T>* Auxiliary) : Index(Index), Auxiliary(Auxiliary) {}
		void operator++() { Index++; Auxiliary = Auxiliary->getNextNode(); }
		bool operator!=(Iterator x) { return Index != x.Index; }
		T operator*() { return Auxiliary->getObject(); }
	};
	Iterator begin() {
		return Iterator(0, FirstNode);
	}
	Iterator end() {
		return Iterator(Size, nullptr);
	}
	DoubleCircularLinkedList();
	~DoubleCircularLinkedList();
	DoubleNode<T>* getDoubleNode(size_t Index);
	size_t getSize();
	bool IsEmpty();
	void AddToStart(T Object);
	void AddToIndex(T Object, size_t Index);
	void AddToEnd(T Object);
	void ModifyStart(T Object);
	void ModifyIndex(T Object, size_t Index);
	void ModifyEnd(T Object);
	void RemoveStart();
	void RemoveIndex(size_t Index);
	void RemoveEnd();
	T ObtainStart();
	T ObtainIndex(size_t Index);
	T ObtainEnd();
	T ObtainRandom();
	void DeletePointer(function<void(T)> Deleter);

};
template<class T>
DoubleCircularLinkedList<T>::DoubleCircularLinkedList()
{
	FirstNode = nullptr;
	LastNode = nullptr;
	Size = 0;
}
template<class T>
DoubleCircularLinkedList<T>::~DoubleCircularLinkedList()
{
	for (size_t i = 0; i < Size; ++i) {
		DoubleNode<T>* Auxiliary = FirstNode->getNextNode();
		delete FirstNode;
		FirstNode = Auxiliary;
	}
}
template<class T>
DoubleNode<T>* DoubleCircularLinkedList<T>::getDoubleNode(size_t Index) {
	DoubleNode<T>* Auxiliary = FirstNode;
	for (size_t i = 0; i < Index; i++)
	{
		Auxiliary = Auxiliary->getNextNode();
	}
	return Auxiliary;
}
template<class T>
size_t DoubleCircularLinkedList<T>::getSize() {
	return Size;
}
template<class T>
bool DoubleCircularLinkedList<T>::IsEmpty() {
	return FirstNode == nullptr;
}
template<class T>
void DoubleCircularLinkedList<T>::AddToStart(T Object) {
	DoubleNode<T>* NewNode = new DoubleNode<T>(Object);
	if (FirstNode == nullptr) {
		NewNode->setPreviousNode(NewNode);
		NewNode->setNextNode(NewNode);
		LastNode = NewNode;
	}
	else {
		NewNode->setPreviousNode(LastNode);
		NewNode->setNextNode(FirstNode);
		FirstNode->setPreviousNode(NewNode);
		LastNode->setNextNode(NewNode);
	}
	FirstNode = NewNode;
	Size++;
	NewNode = nullptr;
}
template<class T>
void DoubleCircularLinkedList<T>::AddToIndex(T Object, size_t Index) {
	DoubleNode<T>* NewNode = new DoubleNode<T>(Object);
	if (Index == 0) {
		if (FirstNode == nullptr) {
			NewNode->setPreviousNode(NewNode);
			NewNode->setNextNode(NewNode);
			LastNode = NewNode;
		}
		else {
			NewNode->setPreviousNode(LastNode);
			NewNode->setNextNode(FirstNode);
			FirstNode->setPreviousNode(NewNode);
			LastNode->setNextNode(NewNode);
		}
		FirstNode = NewNode;
	}
	else {
		DoubleNode<T>* Auxiliary = FirstNode;
		for (size_t i = 1; i < Index; i++)
		{
			Auxiliary = Auxiliary->getNextNode();
		}
		NewNode->setNextNode(Auxiliary->getNextNode());
		NewNode->setPreviousNode(Auxiliary);
		Auxiliary->getNextNode()->setPreviousNode(NewNode);
		Auxiliary->setNextNode(NewNode);
		Auxiliary = nullptr;
	}
	Size++;
	NewNode = nullptr;
}
template<class T>
void DoubleCircularLinkedList<T>::AddToEnd(T Object) {
	DoubleNode<T>* NewNode = new DoubleNode<T>(Object);
	if (FirstNode == nullptr) {
		NewNode->setPreviousNode(NewNode);
		NewNode->setNextNode(NewNode);
		FirstNode = NewNode;
	}
	else {
		NewNode->setPreviousNode(LastNode);
		NewNode->setNextNode(FirstNode);
		LastNode->setNextNode(NewNode);
		FirstNode->setPreviousNode(NewNode);
	}
	LastNode = NewNode;
	Size++;
	NewNode = nullptr;
}
template<class T>
void DoubleCircularLinkedList<T>::ModifyStart(T Object) {
	FirstNode->setObject(Object);
}
template<class T>
void DoubleCircularLinkedList<T>::ModifyIndex(T Object, size_t Index) {
	DoubleNode<T>* Auxiliary = FirstNode;
	for (size_t i = 0; i < Index; i++)
	{
		Auxiliary = Auxiliary->getNextNode();
	}
	Auxiliary->setObject(Object);
	Auxiliary = nullptr;
}
template<class T>
void DoubleCircularLinkedList<T>::ModifyEnd(T Object) {
	LastNode->setObject(Object);
}
template<class T>
void DoubleCircularLinkedList<T>::RemoveStart() {
	if (Size == 0) {
		return;
	}
	DoubleNode<T>* Auxiliary = FirstNode;
	if (Size == 1) {
		FirstNode = nullptr;
		LastNode = nullptr;
	}
	else {
		FirstNode = FirstNode->getNextNode();
		FirstNode->setPreviousNode(LastNode);
		LastNode->setNextNode(FirstNode);
	}
	Size--;
	delete Auxiliary;
	Auxiliary = nullptr;
}
template<class T>
void DoubleCircularLinkedList<T>::RemoveIndex(size_t Index) {
	if (Size == 0) {
		return;
	}
	DoubleNode<T>* Auxiliary = FirstNode;
	if (Index == 0) {
		if (Size == 1) {
			FirstNode = nullptr;
			LastNode = nullptr;
		}
		else {
			FirstNode = FirstNode->getNextNode();
			FirstNode->setPreviousNode(LastNode);
			LastNode->setNextNode(FirstNode);
		}
	}
	else
		if (Index == Size - 1) {
			if (Size == 1) {
				FirstNode = nullptr;
				LastNode = nullptr;
			}
			else {
				for (size_t i = 1; i < Size; i++)
				{
					Auxiliary = Auxiliary->getNextNode();
				}
				LastNode = LastNode->getPreviousNode();
				LastNode->setNextNode(FirstNode);
				FirstNode->setPreviousNode(LastNode);
			}
		}
		else {
			for (size_t i = 0; i < Index; i++)
			{
				Auxiliary = Auxiliary->getNextNode();
			}
			Auxiliary->getPreviousNode()->setNextNode(Auxiliary->getNextNode());
			Auxiliary->getNextNode()->setPreviousNode(Auxiliary->getPreviousNode());
		}
	Size--;
	delete Auxiliary;
	Auxiliary = nullptr;
}
template<class T>
void DoubleCircularLinkedList<T>::RemoveEnd() {
	DoubleNode<T>* Auxiliary = LastNode;
	if (Size == 1) {
		FirstNode = nullptr;
		LastNode = nullptr;
	}
	else {
		LastNode = LastNode->getPreviousNode();
		LastNode->setNextNode(FirstNode);
		FirstNode->setPreviousNode(LastNode);
	}
	Size--;
	delete Auxiliary;
	Auxiliary = nullptr;
}
template<class T>
T DoubleCircularLinkedList<T>::ObtainStart() {
	return FirstNode->getObject();
}
template<class T>
T DoubleCircularLinkedList<T>::ObtainIndex(size_t Index) {
	DoubleNode<T>* Auxiliary = FirstNode;
	for (size_t i = 0; i < Index; i++)
	{
		Auxiliary = Auxiliary->getNextNode();
	}
	return Auxiliary->getObject();
}
template<class T>
T DoubleCircularLinkedList<T>::ObtainEnd() {
	return LastNode->getObject();
}
template<class T>
T DoubleCircularLinkedList<T>::ObtainRandom() {
	int Random = 0 + rand() % +Size - 2;
	return ObtainIndex(Random);
}
template<class T>
void DoubleCircularLinkedList<T>::DeletePointer(function<void(T)> Deleter) {
	DoubleNode<T>* Auxiliary = FirstNode;
	for (size_t i = 0; i < Size; ++i) {
		Deleter(Auxiliary->getObject());
		Auxiliary = Auxiliary->getNextNode();
	}
}
#endif // !__DOUBLE_CIRCULAR_LINKED_LIST_H__