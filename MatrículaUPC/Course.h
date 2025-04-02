#ifndef __COURSE_H__
#define __COURSE_H__
#include "Enrollment.h"
class Course
{
private:
	Enrollment Schedule;
	string CourseName;
	string CourseSection;
	short CreditWeight;
	string Campus;
	string Modality;
public:
	Course();
	Course(string CourseName, string CourseSection, string SessionDay, string StartTime, string FinishTime, short CreditWeight, string Campus, string Modality);
	~Course();
	Enrollment getEnrollment();
	string getCourseName();
	string getCourseSection();
	short getCreditWeight();
	string getCampus();
	string getModality();
	void setEnrollment(Enrollment Schedule);
	void setCourseName(string CourseName);
	void setCourseSection(string CourseSection);
	void setCreditWeight(short CreditWeight);
	void setCampus(string Campus);
	void setModality(string Modality);
};
Course::Course() {

}
Course::Course(string CourseName, string CourseSection, string SessionDay, string StartTime, string FinishTime, short CreditWeight, string Campus, string Modality) {
	Schedule = Enrollment(SessionDay, StartTime, FinishTime);
	this->CourseName = CourseName;
	this->CourseSection = CourseSection;
	this->CreditWeight = CreditWeight;
	this->Campus = Campus;
	this->Modality = Modality;
}
Course::~Course() {

}
Enrollment Course::getEnrollment() {
	return Schedule;
}
string Course::getCourseName() {
	return CourseName;
}
string Course::getCourseSection() {
	return CourseSection;
}
short Course::getCreditWeight() {
	return CreditWeight;
}
string Course::getCampus() {
	return Campus;
}
string Course::getModality() {
	return Modality;
}
void Course::setEnrollment(Enrollment Schedule) {
	this->Schedule = Schedule;
}
void Course::setCourseName(string CourseName) {
	this->CourseName = CourseName;
}
void Course::setCourseSection(string CourseSection) {
	this->CourseSection = CourseSection;
}
void Course::setCreditWeight(short CreditWeight) {
	this->CreditWeight = CreditWeight;
}
void Course::setCampus(string Campus) {
	this->Campus = Campus;
}
void Course::setModality(string Modality) {
	this->Modality = Modality;
}
#endif // !__COURSE_H__