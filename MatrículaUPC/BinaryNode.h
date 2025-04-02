#ifndef __BINARY_NODE_H__
#define __BINARY_NODE_H__
template<class T>
class BinaryNode {
private:
	T Object;
	BinaryNode<T>* Father;
	BinaryNode<T>* Rigth;
	BinaryNode<T>* Left;
public:
	BinaryNode(T Object);
	~BinaryNode();
	T getObject();
	BinaryNode<T>*& getFather();
	BinaryNode<T>*& getRigth();
	BinaryNode<T>*& getLeft();
	void setObject(T Object);
	void setFather(BinaryNode<T>* Father);
	void setRigth(BinaryNode<T>* Rigth);
	void setLeft(BinaryNode<T>* Left);
};
template<class T>
BinaryNode<T>::BinaryNode(T Object) {
	this->Object = Object;
	Father = nullptr;
	Rigth = nullptr;
	Left = nullptr;
}
template<class T>
BinaryNode<T>::~BinaryNode() {
	Father = nullptr;
	Rigth = nullptr;
	Left = nullptr;
}
template<class T>
T BinaryNode<T>::getObject() {
	return Object;
}
template<class T>
BinaryNode<T>*& BinaryNode<T>::getFather() {
	return Father;
}
template<class T>
BinaryNode<T>*& BinaryNode<T>::getRigth() {
	return Rigth;
}
template<class T>
BinaryNode<T>*& BinaryNode<T>::getLeft() {
	return Left;
}
template<class T>
void BinaryNode<T>::setObject(T Object) {
	this->Object = Object;
}
template<class T>
void BinaryNode<T>::setFather(BinaryNode<T>* Father) {
	this->Father = Father;
}
template<class T>
void BinaryNode<T>::setRigth(BinaryNode<T>* Rigth) {
	this->Rigth = Rigth;
}
template<class T>
void BinaryNode<T>::setLeft(BinaryNode<T>* Left) {
	this->Left = Left;
}
#endif // !__BINARY_NODE_H__