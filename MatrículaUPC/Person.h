#ifndef __PERSON_H__
#define __PERSON_H__
#include "Resources.h"
class Person
{
protected:
	string FirstName;
	string SecondName;
	string LastName;
	string MothersLastName;
	int OldAge;
public:
	Person();
	Person(string FirstName, string SecondName, string LastName, string MothersLastName, int OldAge);
	~Person();
	string getFirstName();
	string getSecondName();
	string getLastName();
	string getMothersLastName();
	int getOldAge();
	void setFirstName(string FirstName);
	void setSecondName(string SecondName);
	void setLastName(string LastName);
	void setMothersLastName(string MothersLastName);
	void setOldAge(int OldAge);
};
Person::Person() {
}
Person::Person(string FirstName, string SecondName, string LastName, string MothersLastName, int OldAge) {
	this->FirstName = FirstName;
	this->SecondName = SecondName;
	this->LastName = LastName;
	this->MothersLastName = MothersLastName;
	this->OldAge = OldAge;
}
Person::~Person() {

}
string Person::getFirstName() {
	return FirstName;
}
string Person::getSecondName() {
	return SecondName;
}
string Person::getLastName() {
	return LastName;
}
string Person::getMothersLastName() {
	return MothersLastName;
}
int Person::getOldAge() {
	return this->OldAge;
}
void Person::setFirstName(string FirstName) {
	this->FirstName = FirstName;
}
void Person::setSecondName(string SecondName) {
	this->SecondName = SecondName;
}
void Person::setLastName(string LastName) {
	this->LastName = LastName;
}
void Person::setMothersLastName(string MothersLastName) {
	this->MothersLastName = MothersLastName;
}
void Person::setOldAge(int OldAge) {
	this->OldAge = OldAge;
}
#endif // !__PERSON_H__