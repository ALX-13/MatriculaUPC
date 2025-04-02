#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__
#include "HashEntity.h"
#include "DoubleCircularLinkedList.h"
#include "SimpleCircularLinkedList.h"
template<class T>
class HashTable
{
private:
	HashEntity<T>** Table;
	size_t Capacity;
	size_t Size;
public:
	HashTable(size_t Capacity);
	~HashTable();
	size_t getCapacity();
	size_t getSize();
	void Add(string Key, T Object);
	bool Search(string Key);
	T Obtain(string Key);
	int HashFunction1(string Key);
	int HashFunction2(string Key, int Hash1);
	int HashFunction3(string Key);
	DoubleCircularLinkedList<T>* DoubleListConverted();
	SimpleCircularLinkedList<T>* SimpleListConverted();
};
template<class T>
HashTable<T>::HashTable(size_t Capacity) {
	this->Capacity = Capacity;
	Table = new HashEntity<T>*[Capacity];
	for (int i = 0; i < Capacity; ++i) {
		Table[i] = nullptr;
	}
	Size = 0;
}
template<class T>
HashTable<T>::~HashTable()
{
	for (size_t i = 0; i < Capacity; i++) {
		if (Table[i] != nullptr) {
			delete Table[i];
		}
	}
	delete[] Table;
}
template<class T>
size_t HashTable<T>::getCapacity() {
	return Capacity;
}
template<class T>
size_t HashTable<T>::getSize() {
	return Size;
}
template<class T>
void HashTable<T>::Add(string Key, T Object) {
	if (Size == Capacity) {
		return;
	}
	else {
		int Base, Hash;

		try {
			char CharKey = Key.at(6);
			int CharValue = stoi(string(1, CharKey));

			Base = HashFunction3(Key);
			Hash = Base;

			while (Table[Hash] != nullptr) {
				Hash++;
				if (Hash == Capacity) {
					Hash = 0;
				}
			}
		}
		catch (const invalid_argument& e) {
			Base = HashFunction1(Key);
			Hash = Base;

			while (Table[Hash] != nullptr) {
				Hash++;
				if (Hash == Capacity) {
					Hash = 0;
				}
			}
		}
		catch (const out_of_range& e) {
			Base = HashFunction1(Key);
			Hash = Base;

			while (Table[Hash] != nullptr) {
				Hash = HashFunction2(Key, Hash);
			}
		}
		Table[Hash] = new HashEntity<T>(Key, Object);
		Size++;
	}
}
template<class T>
bool HashTable<T>::Search(string Key) {
	int Step = 0;
	int i, Base;

	try {
		char CharKey = Key.at(6);
		int CharValue = stoi(string(1, CharKey));

		i = Base = HashFunction3(Key);

		while (true) {
			if (Table[i] == nullptr)return false;
			else if (Table[i]->getKey() == Key) {
				return true;
			}
			else Step++;

			i = i + Step;

			if (i > Capacity) {
				i = 0;
			}
		}
	}
	catch (const invalid_argument& e) {
		i = Base = HashFunction1(Key);

		while (true) {
			if (Table[i] == nullptr)return false;
			else if (Table[i]->getKey() == Key) {
				return true;
			}
			else Step++;

			i = i + Step;
		}
	}
	catch (const out_of_range& e) {
		i = Base = HashFunction1(Key);

		while (true) {
			if (Table[i] == nullptr)return false;
			else if (Table[i]->getKey() == Key) {
				return true;
			}
			else Step++;

			i = i + Step;
		}
	}
}
template<class T>
T HashTable<T>::Obtain(string Key) {
	int Step = 0;
	int i, Base;

	try {
		char CharKey = Key.at(6);
		int CharValue = stoi(string(1, CharKey));

		i = Base = HashFunction3(Key);

		while (true) {
			if (Table[i] == nullptr)return NULL;
			else if (Table[i]->getKey() == Key) {
				return Table[i]->getObject();
			}
			else Step++;

			i = i + Step;
		}

		if (i > Capacity) {
			i = 0;
		}
	}
	catch (const invalid_argument& e) {
		i = Base = HashFunction1(Key);

		while (true) {
			if (Table[i] == nullptr)return NULL;
			else if (Table[i]->getKey() == Key) {
				return Table[i]->getObject();
			}
			else Step++;

			i = i + Step;
		}
	}
	catch (const out_of_range& e) {
		i = Base = HashFunction1(Key);

		while (true) {
			if (Table[i] == nullptr)return NULL;
			else if (Table[i]->getKey() == Key) {
				return Table[i]->getObject();
			}
			else Step++;

			i = i + Step;
		}
	}
}
template<class T>
int HashTable<T>::HashFunction1(string Key) {
	string Year = "";
	string CharKey = "";

	Year = Key.at(4);
	CharKey = Key.at(9);

	int CharValue = 0;
	int YearValue = 0;
	long long Hash = 0;

	CharValue = stoi(CharKey);
	YearValue = 20 + stoi(Year);
	Hash = pow(YearValue, CharValue);

	return Hash % Capacity;
}
template<class T>
int HashTable<T>::HashFunction2(string Key, int Hash1) {
	char Value1 = Key.at(7);
	char Value2 = Key.at(8);
	char Value3 = Key.at(9);

	long long Hash2 = 0;
	Hash2 = Hash1 * (stoi(string(1, Value1)) + stoi(string(1, Value2)) + stoi(string(1, Value3)));
	return Hash2 % Capacity;
}
template<class T>
int HashTable<T>::HashFunction3(string Key) {
	string Code = "";
	Code = Key.at(1) + Key.at(2) + Key.at(3) + Key.at(4) + Key.at(5) + Key.at(6) + Key.at(7) + Key.at(8) + Key.at(9);

	long long CodeValue = stoi(Code);

	return CodeValue % 100;
}
template<class T>
DoubleCircularLinkedList<T>* HashTable<T>::DoubleListConverted() {
	DoubleCircularLinkedList<T>* DoubleList = new DoubleCircularLinkedList<T>();
	for (size_t i = 0; i < Capacity; i++) {
		if (Table[i] != nullptr) {
			DoubleList->AddToEnd(Table[i]->getObject());
		}
	}
	return DoubleList;
}
template<class T>
SimpleCircularLinkedList<T>* HashTable<T>::SimpleListConverted() {
	SimpleCircularLinkedList<T>* SimpleList = new SimpleCircularLinkedList<T>();
	for (size_t i = 0; i < Capacity; i++) {
		if (Table[i] != nullptr) {
			SimpleList->AddToEnd(Table[i]);
		}
	}
	return SimpleList;
}
#endif // !__HASH_TABLE_H__