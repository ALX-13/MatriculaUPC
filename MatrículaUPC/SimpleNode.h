#ifndef __SIMPLE_NODE_H__
#define __SIMPLE_NODE_H__
#include "Resources.h"
template<class T>
class SimpleNode
{
private:
	T Object;
	SimpleNode<T>* NextNode;
public:
	SimpleNode(T Object);
	~SimpleNode();
	T getObject();
	SimpleNode<T>* getNextNode();
	void setObject(T Object);
	void setNextNode(SimpleNode<T>* NextNode);
};
template<class T>
SimpleNode<T>::SimpleNode(T Object)
{
	this->Object = Object;
	NextNode = nullptr;
}
template<class T>
SimpleNode<T>::~SimpleNode()
{
	NextNode = nullptr;
}
template<class T>
T SimpleNode<T>::getObject() {
	return Object;
}
template<class T>
SimpleNode<T>* SimpleNode<T>::getNextNode() {
	return NextNode;
}
template<class T>
void SimpleNode<T>::setObject(T Object) {
	this->Object = Object;
}
template<class T>
void SimpleNode<T>::setNextNode(SimpleNode<T>* NextNode) {
	this->NextNode = NextNode;
}
#endif // !__SIMPLE_NODE_H__