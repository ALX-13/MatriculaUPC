#ifndef __TUTOR_H__
#define __TUTOR_H__
#include "Person.h"
#include "SimpleCircularLinkedList.h"
class Tutor :public Person
{
private:
	string TutorData;
public:
	Tutor(string FirstName, string SecondName, string LastName, string MothersLastName, int Age);
	~Tutor();
	string TutorProfile();
};
Tutor::Tutor(string FirstName, string SecondName, string LastName, string MothersLastName, int Age) : Person(FirstName, SecondName, LastName, MothersLastName, Age) {

}
Tutor::~Tutor() {

}
string Tutor::TutorProfile() {
	TutorData = "";
	TutorData += "Nombre del Profesor: " + FirstName + " " + SecondName + "\n";
	TutorData += "Apellidos del Profesor: " + LastName + " " + MothersLastName + "\n";
	return TutorData;
}
#endif //!__TUTOR_H__