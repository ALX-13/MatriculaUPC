#ifndef __HASH_ENTITY_H__
#define __HASH_ENTITY_H__
#include "Resources.h"
template<class T>
class HashEntity {
private:
	string Key;
	T Object;
public:
	HashEntity(string Key, T Object);
	~HashEntity();
	string getKey();
	T getObject();
	void setKey(string Key);
	void setObject(T Object);
};
template<class T>
HashEntity<T>::HashEntity(string Key, T Object) {
	this->Key = Key;
	this->Object = Object;
}
template<class T>
HashEntity<T>::~HashEntity() {

}
template<class T>
string HashEntity<T>::getKey() {
	return Key;
}
template<class T>
T HashEntity<T>::getObject() {
	return Object;
}
template<class T>
void HashEntity<T>::setKey(string Key) {
	this->Key = Key;
}
template<class T>
void HashEntity<T>::setObject(T Object) {
	this->Object = Object;
}
#endif // !__HASH_ENTITY_H__