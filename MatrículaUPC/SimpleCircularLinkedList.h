#ifndef __SIMPLE_CIRCULAR_LINKED_LIST_H__
#define __SIMPLE_CIRCULAR_LINKED_LIST_H__
#include "SimpleNode.h" 
template<class T>
class SimpleCircularLinkedList
{
private:
	SimpleNode<T>* FirstNode;
	SimpleNode<T>* LastNode;
	size_t Size;
public:
	class Iterator {
	public:
		size_t Index;
		SimpleNode<T>* Auxiliary;
	public:
		Iterator(size_t Index, SimpleNode<T>* Auxiliary) : Index(Index), Auxiliary(Auxiliary) {}
		void operator++() { Index++; Auxiliary = Auxiliary->getNextNode(); }
		bool operator!=(Iterator x) { return Index != x.Index; }
		T operator*() { return Auxiliary->getObject(); }
	};
	Iterator begin() {
		return Iterator(0, FirstNode);
	}
	Iterator end() {
		return Iterator(Size, FirstNode);
	}
	SimpleCircularLinkedList();
	~SimpleCircularLinkedList();
	SimpleNode<T>* getSimpleNode(size_t Index);
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
SimpleCircularLinkedList<T>::SimpleCircularLinkedList()
{
	FirstNode = nullptr;
	LastNode = nullptr;
	Size = 0;
}
template<class T>
SimpleCircularLinkedList<T>::~SimpleCircularLinkedList() {
	for (size_t i = 0; i < Size; ++i) {
		SimpleNode<T>* Auxiliary = FirstNode->getNextNode();
		delete FirstNode;
		FirstNode = Auxiliary;
	}
}
template<class T>
SimpleNode<T>* SimpleCircularLinkedList<T>::getSimpleNode(size_t Index) {
	SimpleNode<T>* Auxiliary = FirstNode;
	for (size_t i = 0; i < Index; i++)
	{
		Auxiliary = Auxiliary->getNextNode();
	}
	return Auxiliary;
}
template<class T>
size_t SimpleCircularLinkedList<T>::getSize() {
	return Size;
}
template<class T>
bool SimpleCircularLinkedList<T>::IsEmpty() {
	return FirstNode == nullptr;
}
template<class T>
void SimpleCircularLinkedList<T>::AddToStart(T Object) {
	SimpleNode<T>* NewNode = new SimpleNode<T>(Object);

	if (FirstNode == nullptr) {
		NewNode->setNextNode(NewNode);
		LastNode = NewNode;
	}
	else {
		NewNode->setNextNode(FirstNode);
		LastNode->setNextNode(NewNode);
	}
	FirstNode = NewNode;
	Size++;
	NewNode = nullptr;
}
template<class T>
void SimpleCircularLinkedList<T>::AddToIndex(T Object, size_t Index) {
	SimpleNode<T>* NewNode = new SimpleNode<T>(Object);
	if (Index == 0) {
		if (FirstNode == nullptr) {
			NewNode->setNextNode(NewNode);
			LastNode = NewNode;
		}
		else {
			NewNode->setNextNode(FirstNode);
		}
		FirstNode = NewNode;
		LastNode->setNextNode(FirstNode);
	}
	else {
		SimpleNode<T>* Auxiliary = FirstNode;
		for (size_t i = 1; i < Index; i++)
		{
			Auxiliary = Auxiliary->getNextNode();
		}
		NewNode->setNextNode(Auxiliary->getNextNode());
		Auxiliary->setNextNode(NewNode);
		Auxiliary = nullptr;
	}
	Size++;
	NewNode = nullptr;
}
template<class T>
void SimpleCircularLinkedList<T>::AddToEnd(T Object) {
	SimpleNode<T>* NewNode = new SimpleNode<T>(Object);
	if (FirstNode == nullptr) {
		NewNode->setNextNode(NewNode);
		FirstNode = NewNode;
		LastNode = NewNode;
	}
	else {
		SimpleNode<T>* Auxiliary = LastNode;
		NewNode->setNextNode(FirstNode);
		LastNode = NewNode;
		Auxiliary->setNextNode(NewNode);
		Auxiliary = nullptr;
	}
	Size++;
	NewNode = nullptr;
}
template<class T>
void SimpleCircularLinkedList<T>::ModifyStart(T Object) {
	FirstNode->setObject(Object);
}
template<class T>
void SimpleCircularLinkedList<T>::ModifyIndex(T Object, size_t Index) {
	if (Size == 0) {
		return;
	}
	if (Index == 0) {
		FirstNode->setObject(Object);
	}
	else
		if (Index == Size - 1) {
			LastNode->setObject(Object);
		}
		else {
			SimpleNode<T>* Auxiliary = FirstNode->getNextNode();
			for (size_t i = 1; i < Index; i++)
			{
				Auxiliary = Auxiliary->getNextNode();
			}
			Auxiliary->setObject(Object);
			Auxiliary = nullptr;
		}
}
template<class T>
void SimpleCircularLinkedList<T>::ModifyEnd(T Object) {
	LastNode->setObject(Object);
}
template<class T>
void SimpleCircularLinkedList<T>::RemoveStart() {
	if (Size == 0) {
		return;
	}
	if (Size == 1) {
		delete FirstNode;
		FirstNode = nullptr;
		LastNode = nullptr;
	}
	else {
		SimpleNode<T>* Auxiliary = FirstNode;
		FirstNode = FirstNode->getNextNode();
		LastNode->setNextNode(FirstNode);
		delete Auxiliary;
		Auxiliary = nullptr;
	}
	Size--;
}
template<class T>
void SimpleCircularLinkedList<T>::RemoveIndex(size_t Index) {
	if (Size == 0) {
		return;
	}
	SimpleNode<T>* Auxiliary = FirstNode;
	if (Index == 0) {
		if (Size == 1) {
			delete FirstNode;
			FirstNode = nullptr;
			LastNode = nullptr;
		}
		else {
			FirstNode = FirstNode->getNextNode();
			LastNode->setNextNode(FirstNode);
			delete Auxiliary;
		}
	}
	else
		if (Index == Size - 1) {
			for (size_t i = 1; i < Index; i++)
			{
				Auxiliary = Auxiliary->getNextNode();
			}
			Auxiliary->setNextNode(FirstNode);
			delete LastNode;
			LastNode = Auxiliary;
		}
		else {
			for (size_t i = 1; i < Index; i++)
			{
				Auxiliary = Auxiliary->getNextNode();
			}
			SimpleNode<T>* Auxiliary2 = Auxiliary->getNextNode();
			Auxiliary->setNextNode(Auxiliary2->getNextNode());
			delete Auxiliary2;
			Auxiliary2 = nullptr;
		}
	Size--;
	Auxiliary = nullptr;
}
template<class T>
void SimpleCircularLinkedList<T>::RemoveEnd() {
	if (Size == 0) {
		return;
	}
	SimpleNode<T>* Auxiliary = FirstNode;
	if (Size == 1) {
		FirstNode->setNextNode(nullptr);
		LastNode->setNextNode(nullptr);
		FirstNode = nullptr;
		LastNode = nullptr;
		delete Auxiliary;
		Auxiliary = nullptr;
	}
	else {
		for (size_t i = 0; i < Size - 2; i++)
		{
			Auxiliary = Auxiliary->getNextNode();
		}
		SimpleNode<T>* Auxiliary2 = Auxiliary->getNextNode();
		Auxiliary->setNextNode(FirstNode);
		LastNode = Auxiliary;
		delete Auxiliary2;
		Auxiliary2 = nullptr;
	}
	Size--;
	Auxiliary = nullptr;
}
template<class T>
T SimpleCircularLinkedList<T>::ObtainStart() {
	return FirstNode->getObject();
}
template<class T>
T SimpleCircularLinkedList<T>::ObtainIndex(size_t Index) {
	SimpleNode<T>* Auxiliary = FirstNode;
	for (size_t i = 0; i < Index; i++)
	{
		Auxiliary = Auxiliary->getNextNode();
	}
	return Auxiliary->getObject();
}
template<class T>
T SimpleCircularLinkedList<T>::ObtainEnd() {
	return LastNode->getObject();
}
template<class T>
T SimpleCircularLinkedList<T>::ObtainRandom() {
	int Random = 0 + rand() % +Size;

	SimpleNode<T>* Auxiliary = FirstNode;
	for (size_t i = 0; i < Random; i++) {
		Auxiliary = Auxiliary->getNextNode();
	}
	return Auxiliary->getObject();
}
template<class T>
void SimpleCircularLinkedList<T>::DeletePointer(function<void(T)> Deleter) {
	SimpleNode<T>* Auxiliary = FirstNode;
	for (size_t i = 0; i < Size; ++i) {
		Deleter(Auxiliary->getObject());
		Auxiliary = Auxiliary->getNextNode();
	}
}
#endif // !__SIMPLE_CIRCULAR_LINKED_LIST_H__