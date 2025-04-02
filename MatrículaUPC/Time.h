#ifndef __TIME_H__
#define __TIME_H__
#include <string>
using namespace std;
class Time
{
private:
	string StartTime;
	string FinishTime;
public:
	Time();
	Time(string StartTime, string FinishTime);
	~Time();
	string getStartTime();
	string getFinishTime();
	void setStartTime(string StartTime);
	void setFinishTime(string FinishTime);
};
Time::Time()
{
}
Time::Time(string StartTime, string FinishTime)
{
	this->StartTime = StartTime;
	this->FinishTime = FinishTime;
}
Time::~Time()
{
}
string Time::getStartTime() {
	return StartTime;
}
string Time::getFinishTime() {
	return FinishTime;
}
void Time::setStartTime(string StartTime) {
	this->StartTime = StartTime;
}
void Time::setFinishTime(string FinishTime) {
	this->FinishTime = FinishTime;
}
#endif // !__TIME_H__