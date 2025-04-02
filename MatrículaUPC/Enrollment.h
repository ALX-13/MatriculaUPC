#ifndef __ENROLLMENT_H__
#define __ENROLLMENT_H__
#include "Resources.h"
#include "Time.h"
class Enrollment
{
private:
	string SessionDay;
	Time CalendarTime;
public:
	Enrollment();
	Enrollment(string SessionDay, string StartTime, string FinishTime);
	~Enrollment();
	string getSessionDay();
	Time getEnrollmentTime();
	void setSessionDay(string SessionDay);
};
Enrollment::Enrollment() {
}
Enrollment::Enrollment(string SessionDay, string StartTime, string FinishTime) {
	this->SessionDay = SessionDay;
	CalendarTime = Time(StartTime, FinishTime);
}
Enrollment::~Enrollment() {
}
string Enrollment::getSessionDay() {
	return this->SessionDay;
}
Time Enrollment::getEnrollmentTime() {
	return CalendarTime;
}
void Enrollment::setSessionDay(string SessionDay) {
	this->SessionDay = SessionDay;
}
#endif // !__ENROLLMENT_H__