#ifndef __DOUBLE_NODE_H__
#define __DOUBLE_NODE_H__
#include "Resources.h"
template<class T>
class DoubleNode
{
private:
	T Object;
	DoubleNode<T>* NextNode;
	DoubleNode<T>* PreviousNode;
public:
	DoubleNode(T Object);
	~DoubleNode();
	T& getObject();
	DoubleNode<T>* getNextNode();
	DoubleNode<T>* getPreviousNode();
	void setObject(T Object);
	void setNextNode(DoubleNode<T>* NextNode);
	void setPreviousNode(DoubleNode<T>* PreviousNode);
};
template<class T>
DoubleNode<T>::DoubleNode(T Object)
{
	this->Object = Object;
	NextNode = nullptr;
	PreviousNode = nullptr;
}
template<class T>
DoubleNode<T>::~DoubleNode()
{
	NextNode = nullptr;
	PreviousNode = nullptr;
}
template<class T>
T& DoubleNode<T>::getObject() {
	return Object;
}
template<class T>
DoubleNode<T>* DoubleNode<T>::getNextNode() {
	return NextNode;
}
template<class T>
DoubleNode<T>* DoubleNode<T>::getPreviousNode() {
	return PreviousNode;
}
template<class T>
void DoubleNode<T>::setObject(T Object) {
	this->Object = Object;
}
template<class T>
void DoubleNode<T>::setNextNode(DoubleNode<T>* NextNode) {
	this->NextNode = NextNode;
}
template<class T>
void DoubleNode<T>::setPreviousNode(DoubleNode<T>* PreviousNode) {
	this->PreviousNode = PreviousNode;
}
#endif // !__DOUBLE_NODE_H__