#ifndef __STUDENT_H__
#define __STUDENT_H__
#include "SimpleCircularLinkedList.h"
#include "Person.h"
#include "Course.h"
#include "Heap.h"
#include "Notification.h"
class Student : public Person {
private:
	SimpleCircularLinkedList<Course*>* CourseList;
	Heap<Notification>* NotificationHeap;
	string StudentID;
	string Password;
	short Credits;
public:
	Student();
	Student(string FirstName, string SecondName, string LastName, string MothersLastName, int Age, string StudentID, short Credits, string Password);
	~Student();
	string getStudentID();
	string getPassword();
	short getCredits();
	void setStudentID(string StudentID);
	void setPassword(string Password);
	void setCredits(short Credits);
	Course* getCourse(size_t Index);
	SimpleCircularLinkedList<Course*>* getCourseList();
	Heap<Notification>* getNotificationHeap();
};
Student::Student() :Person() {

}
Student::Student(string FirstName, string SecondName, string LastName, string MothersLastName, int Age, string StudentID, short Credits, string Password) : Person(FirstName, SecondName, LastName, MothersLastName, Age) {
	CourseList = new SimpleCircularLinkedList<Course*>();
	NotificationHeap = new Heap<Notification>();
	this->StudentID = StudentID;
	this->Password = Password;
	this->Credits = Credits;
}
Student::~Student() {
	CourseList->DeletePointer([](Course* C) {delete C; });
	delete NotificationHeap;
	delete CourseList;
	NotificationHeap = nullptr;
	CourseList = nullptr;
}
string Student::getStudentID() {
	return StudentID;
}
string Student::getPassword() {
	return Password;
}
short Student::getCredits() {
	return Credits;
}
void Student::setStudentID(string StudentID) {
	this->StudentID = StudentID;
}
void Student::setPassword(string Password) {
	this->Password = Password;
}
void Student::setCredits(short Credits) {
	this->Credits = Credits;
}
Course* Student::getCourse(size_t Index) {
	return CourseList->ObtainIndex(Index);
}
SimpleCircularLinkedList<Course*>* Student::getCourseList() {
	return CourseList;
}
Heap<Notification>* Student::getNotificationHeap() {
	return NotificationHeap;
}
#endif //!__STUDENT_H__