#ifndef __HEAP_NODE_H__
#define __HEAP_NODE_H__
template<class T>
class HeapNode
{
private:
	T Object;
	HeapNode<T>* PreviousNode;
public:
	HeapNode(T Object);
	~HeapNode();
	T getObject();
	HeapNode<T>* getPreviousNode();
	void setObject(T Object);
	void setPreviousNode(HeapNode<T>* PreviousNode);
};
template<class T>
HeapNode<T>::HeapNode(T Object)
{
	this->Object = Object;
	PreviousNode = nullptr;
}
template<class T>
HeapNode<T>::~HeapNode()
{
	PreviousNode = nullptr;
}
template<class T>
T HeapNode<T>::getObject() {
	return Object;
}
template<class T>
HeapNode<T>* HeapNode<T>::getPreviousNode() {
	return PreviousNode;
}
template<class T>
void HeapNode<T>::setObject(T Object) {
	this->Object = Object;
}
template<class T>
void HeapNode<T>::setPreviousNode(HeapNode<T>* PreviousNode) {
	this->PreviousNode = PreviousNode;
}
#endif // !__HEAP_NODE_H__