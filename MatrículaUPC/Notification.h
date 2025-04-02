#ifndef __NOTIFICATION_H__
#define __NOTIFICATION_H__
#include "Resources.h"
class Notification {
private:
	string Name;
public:
	Notification();
	Notification(string Name);
	~Notification();
	string getName();
	void setName(string Name);
};
Notification::Notification() {

}
Notification::Notification(string Name) {
	this->Name = Name;
}
Notification::~Notification() {
}
string Notification::getName() {
	return Name;
}
void Notification::setName(string Name) {
	this->Name = Name;
}
#endif // !__NOTIFICATION_H__