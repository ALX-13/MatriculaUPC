#ifndef __UPC_H__
#define __UPC_H__
#include "Resources.h"
#include "DoubleCircularLinkedList.h"
#include "BinarySearchTree.h"
#include "HashTable.h"
#include "Student.h"
#include "Tutor.h"
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

class UPC
{
private:
	HashTable<Student*>* StudentsTable;
	BinarySearchTree<Student*>* StudentsTree;
	DoubleCircularLinkedList<Student*>* StudentsDoubleList;
	DoubleCircularLinkedList<Tutor>* Teachers;
	DoubleCircularLinkedList<Course>* Courses;


	fstream FileIO;
	ofstream FileWriter;
	ifstream FileReader;

	string ObjectQuantity;
	string CoverterTotxt;
	string Message;

	short Selection;
	short Option;
	string OptionSelective;
	bool Looping;
	bool RestartSystem;
	short PauseTime;
	short Random;

	Student* User;
public:
	UPC();
	~UPC();

	void UPCVbeta();
	void LoaderUPCData();
	void LoaderTxtDataSet();
	void LoaderTxtCourseData();
	void LoaderTxtTeacherData();
	void LoaderTxtStudentData();

	void SelectionHandler();

	void LogoGenius();
	void DisplayUPCMenu();

	void SignIn();
	void SignUp();
	void LogOut();
	void TerminateExecution();

	void DisplayUserProfile();
	void DisplayUserCalendar();
	void DisplayUserNotification();
	void DisplayUPCCourses();

	void RecursiveReaderTxtUPCDataSet(size_t Iter, int Limitation, char ClassType, SimpleCircularLinkedList<string>& DataSet);
	void RecursiveReaderTxtCourseFile(size_t Iter, int Limitation, char ClassType);
	void RecursiveReaderTxtPersonFile(size_t Iter, int Limitation, char ClassType);
	void RecursiveReaderTxtNotificationFile(size_t Iter, int Limitation);

	void RecursiveWriterTxtStudentFile(size_t Iter, size_t Limitation);
	void RecursiveWriterTxtCourseFile(size_t Iter, size_t Limitation);
	void RecursiveWriterTxtNotificationFile(size_t Iter, int Limitation);

	void RecursiveDisplayStudentsAccount(size_t Iter, size_t Limitation);
	void RecursiveDisplayUserCalendar(size_t Iter, size_t Limitation);
	void RecursiveDisplayCourse(size_t Iter, size_t Limitation, char ClassType);
	void RecursiveCourseEnrollment(size_t Iter, size_t Limitation);

	void QuickSort(SimpleCircularLinkedList<Student*>* Students, size_t LimitsLeft, size_t LimitsRight);
	void QuickSort(DoubleCircularLinkedList<Student*>* Students, size_t LimitsLeft, size_t LimitsRight);
	void MergeSort(SimpleCircularLinkedList<Student*>* Students, size_t LimitsLeft, size_t LimitsRight);
	void MergeSort(DoubleCircularLinkedList<Student*>* Students, size_t LimitsLeft, size_t LimitsRight);
	void BubbleSort(SimpleCircularLinkedList<Student*>* Students);
	void BubbleSort(DoubleCircularLinkedList<Student*>* Students);
	void FisherYatesShuffle(SimpleCircularLinkedList<Student*>* Students);
	void FisherYatesShuffle(DoubleCircularLinkedList<Student*>* Students);
};
UPC::UPC() {
	StudentsTable = new HashTable<Student*>(100);
	StudentsTree = new BinarySearchTree<Student*>();
	StudentsDoubleList = new DoubleCircularLinkedList<Student*>();
	Teachers = new DoubleCircularLinkedList<Tutor>();
	Courses = new DoubleCircularLinkedList<Course>();


	Looping = true;
	Selection = 0;
	Option = 0;
	OptionSelective = "";

	RestartSystem = true;

	PauseTime = 100;
	Random = 1 + rand() % +3;

	User = nullptr;
}
UPC::~UPC()
{
	delete StudentsDoubleList;
	StudentsTable->DoubleListConverted()->DeletePointer([](Student* S) {delete S; });
	delete StudentsTable;
	StudentsTree->DeletePointer([](Student* S) {delete S; });
	delete StudentsTree;
	delete Teachers;
	delete Courses;

	StudentsDoubleList = nullptr;
	StudentsTable = nullptr;
	StudentsTree = nullptr;
	Teachers = nullptr;
	Courses = nullptr;

	User = nullptr;
}

void UPC::UPCVbeta() {
	/// [   REPEATER UPC SYSTEM   ]
	while (Looping) {
		/// [   CLEANER SCREEN   ]
		system("cls");
		/// [   CLEANER SCREEN   ]


		/// [   UPC MENU   ]
		DisplayUPCMenu();
		/// [   UPC MENU   ]


		/// [   SELECTION HANDLER   ]
		SelectionHandler();
		/// [   SELECTION HANDLER   ]


		/// [   FUNCTION DELAY TIME   ]
		_sleep(PauseTime * 5);
		/// [   FUNCTION DELAY TIME   ]
	}
	/// [   REPEATER UPC SYSTEM   ]
}

void UPC::LoaderUPCData() { // BIG O = O(n)
	color(hConsole, 10);
	cout << " [   OK   ]";
	color(hConsole, 15);
	cout << "   Started Remount Root File "; Message = "System.\n\n"; // 2, 1 operacion de << y una de asignacion
	for (string::iterator i = Message.begin(); i != Message.end(); ++i) { // 1 + n(1 + 1 + 2)
		cout << i.operator*();  // 1 operacion <<
	}
	_sleep(PauseTime);

	cout << "              Starting Read File System..." << endl; // 2 operaciones de <<
	/// [   UPC DATA LOADER FUNCTIONS   ]
	LoaderTxtCourseData(); // 1
	LoaderTxtTeacherData(); // 1
	LoaderTxtDataSet(); // 1
	LoaderTxtStudentData(); // 1
	/// [   UPC DATA LOADER FUNCTIONS   ]

	FileWriter.open("Students.txt", ios::out);
	if (FileWriter.is_open()) {

		FileWriter << StudentsDoubleList->getSize() << endl;

		RecursiveWriterTxtStudentFile(0, StudentsDoubleList->getSize() - 1);

		FileWriter.close();
	}
}
void UPC::LoaderTxtDataSet() {
	/// [   UPC-COURSES FILE OPENDED   ]
	FileIO.open("UPCDataSet.txt", ios::in);
	/// [   UPC-COURSES FILE OPENDED   ]

	/// [   UPC-COURSES FILE VIEWER   ]
	if (FileIO.is_open()) {
		/// [   OBJECT QUANTITY READING   ]
		getline(FileIO, ObjectQuantity);
		/// [   OBJECT QUANTITY READING   ]


		/// [   DATASET-RELATED VARIABLES   ]
		SimpleCircularLinkedList<string> Names;
		/// [   DATASET-RELATED VARIABLES   ]


		/// [   RECURSIVE COURSES READER FUNCTION   ]
		RecursiveReaderTxtUPCDataSet(0, stoi(ObjectQuantity) - 1, 'N', Names);
		/// [   RECURSIVE COURSES READER FUNCTION   ]


		/// [   OBJECT QUANTITY READING   ]
		getline(FileIO, ObjectQuantity);
		/// [   OBJECT QUANTITY READING   ]


		/// [   DATASET-RELATED VARIABLES   ]
		SimpleCircularLinkedList<string> LastNames;
		/// [   DATASET-RELATED VARIABLES   ]


		/// [   RECURSIVE COURSES READER FUNCTION   ]
		RecursiveReaderTxtUPCDataSet(0, stoi(ObjectQuantity) - 1, 'L', LastNames);
		/// [   RECURSIVE COURSES READER FUNCTION   ]


		/// [   PERSON-RELATED VARIABLES   ]
		string FirstName;
		string SecondName;
		string LastName;
		string MothersLastName;
		int OldAge;
		/// [   PERSON-RELATED VARIABLES   ]


		/// [   STUDENT-RELATED VARIABLES   ]
		string StudentID;
		short Credits;
		string Password;
		/// [   STUDENT-RELATED VARIABLES   ]


		/// [   DATASET-RELATED VARIABLES   ]
		int NumberRandom;
		char CharRandom;
		/// [   DATASET-RELATED VARIABLES   ]

		for (int i = 0; i < 100; i++) {
			FirstName = Names.ObtainRandom();

			do {
				SecondName = Names.ObtainRandom();
			} while (SecondName == FirstName);


			LastName = LastNames.ObtainRandom();
			do
			{
				MothersLastName = LastNames.ObtainRandom();
			} while (LastName == MothersLastName);

			OldAge = 18 + rand() % +23;

			StudentID = "U202";

			NumberRandom = 0 + rand() % +4;

			StudentID += to_string(NumberRandom);

			NumberRandom = 0 + rand() % +10;

			StudentID += to_string(NumberRandom);


			NumberRandom = 1 + rand() % +2;
			if (NumberRandom == 1) {
				CharRandom = 97 + rand() % +26;
				StudentID += CharRandom;
			}
			else
				if (NumberRandom == 2) {
					NumberRandom = 1 + rand() % +9;
					StudentID += to_string(NumberRandom);
				}

			NumberRandom = 100 + rand() % 900;

			StudentID += to_string(NumberRandom);

			NumberRandom = 4 + rand() % 6;

			Password = "";
			for (int i = 0; i < NumberRandom; i++) {
				Password += char(48 + rand() % +75);
			}

			Student* S = new Student(FirstName, SecondName, LastName, MothersLastName, OldAge, StudentID, 21, Password);

			NumberRandom = 1 + rand() % +3;

			Course CourseRandom;

			int t = Courses->getSize() - 2;
			for (size_t i = 0; i < NumberRandom; i++) {
				CourseRandom = Courses->ObtainIndex(0 + rand() % +t);
				Course* C = new Course(CourseRandom.getCourseName(), CourseRandom.getCourseSection(), CourseRandom.getEnrollment().getSessionDay(), CourseRandom.getEnrollment().getEnrollmentTime().getStartTime(), CourseRandom.getEnrollment().getEnrollmentTime().getFinishTime(), CourseRandom.getCreditWeight(), CourseRandom.getCampus(), CourseRandom.getModality());
				S->getCourseList()->AddToEnd(C);
				S->setCredits(S->getCredits() - CourseRandom.getCreditWeight());
			}

			StudentsTable->Add(StudentID, S);
			StudentsDoubleList->AddToEnd(S);

			Console::SetCursorPosition(54, 25); cout << "[ " << StudentsTable->getSize() << "% ]" << endl << endl;
		}
		/// [   UPC-COURSES FILE CLOSED   ]
		FileIO.close();
		/// [   UPC-COURSES FILE CLOSED   ]
	}
	/// [   UPC-COURSES FILE VIEWER   ]
}
void UPC::LoaderTxtCourseData() {
	/// [   UPC-COURSES FILE OPENDED   ]
	FileIO.open("Courses.txt", ios::in);
	/// [   UPC-COURSES FILE OPENDED   ]


	/// [   UPC-COURSES FILE VIEWER   ]
	if (FileIO.is_open()) {
		/// [   OBJECT QUANTITY READING   ]
		getline(FileIO, ObjectQuantity);
		/// [   OBJECT QUANTITY READING   ]


		/// [   RECURSIVE COURSES READER FUNCTION   ]
		RecursiveReaderTxtCourseFile(0, stoi(ObjectQuantity) - 1, 'C');
		/// [   RECURSIVE COURSES READER FUNCTION   ]


		/// [   UPC-COURSES FILE CLOSED   ]
		FileIO.close();
		/// [   UPC-COURSES FILE CLOSED   ]
	}
	/// [   UPC-COURSES FILE VIEWER   ]
}
void UPC::LoaderTxtTeacherData() {
	/// [   UPC-TEACHERS FILE OPENDED   ]
	FileIO.open("Teachers.txt", ios::in);
	/// [   UPC-TEACHERS FILE OPENDED   ]


	/// [   UPC-TEACHERS FILE VIEWER   ]
	if (FileIO.is_open()) {
		/// [   OBJECT QUANTITY READING   ]
		getline(FileIO, ObjectQuantity);
		/// [   OBJECT QUANTITY READING   ]


		/// [   RECURSIVE TEACHERS READER FUNCTION   ]
		RecursiveReaderTxtPersonFile(0, stoi(ObjectQuantity) - 1, 'T');
		/// [   RECURSIVE TEACHERS READER FUNCTION   ]


		/// [   UPC-TEACHERS FILE CLOSED   ]
		FileIO.close();
		/// [   UPC-TEACHERS FILE CLOSED   ]
	}
	/// [   UPC-TEACHERS FILE VIEWER   ]
}
void UPC::LoaderTxtStudentData() {
	/// [   UPC-STUDENTS FILE OPENDED   ]
	FileIO.open("Students.txt", ios::in);
	/// [   UPC-STUDENTS FILE OPENDED   ]


	/// [   UPC-STUDENTS FILE VIEWER   ]
	if (FileIO.is_open()) {
		/// [   OBJECT QUANTITY READING   ]
		getline(FileIO, ObjectQuantity);
		/// [   OBJECT QUANTITY READING   ]


		/// [   RECURSIVE STUDENTS READER FUNCTION   ]
		if (stoi(ObjectQuantity) > 0)
			RecursiveReaderTxtPersonFile(0, stoi(ObjectQuantity) - 1, 'S');
		/// [   RECURSIVE STUDENTS READER FUNCTION   ]


		/// [   UPC-STUDENTS FILE CLOSED   ]
		FileIO.close();
		/// [   UPC-STUDENTS FILE CLOSED   ]
	}
	/// [   UPC-STUDENTS FILE VIEWER   ]
}

void UPC::SelectionHandler() {
	/// [   OPTION INPUT   ]
	cout << endl << " get source "; Message = "option ";
	for (string::iterator i = Message.begin(); i != Message.end(); ++i) {
		cout << (*i);
	}
	cin >> Option;
	/// [   OPTION INPUT   ]

	system("cls");

	/// [   UPC MENU   ]
	LogoGenius();
	/// [   UPC MENU   ]

	if (User == nullptr) {
		switch (Option)
		{
		case 1:
			SignIn();
			break;
		case 2:
			SignUp();
			break;
		case 3:
			TerminateExecution();
			break;
		default:
			break;
		}
	}
	else {
		switch (Option)
		{
		case 1:
			DisplayUserProfile();
			break;
		case 2:
			DisplayUserCalendar();
			break;
		case 3:
			DisplayUserNotification();
			break;
		case 4:
			DisplayUPCCourses();
			break;
		case 5:
			LogOut();
			break;
		case 6:
			TerminateExecution();
			break;
		default:
			break;
		}
		cin.get();
	}
	Option = 0;
}

void UPC::LogoGenius() { // BIG O = O(n)
	if (RestartSystem) { // 1 + max(INTERNA IF = 11 + 15n, INTERNA ELSE = 0)
		cout << endl << " Execute Shell Program "; Message = "UPC VSTUDIO\n"; // 3, 2 operaciones << y una de igualdad
		for (string::iterator i = Message.begin(); i != Message.end(); ++i) { // 1 + n(1 + 2 + 2)
			cout << i.operator*(); _sleep(PauseTime / 10); // 2, 1 operacion << y una de division
		}
		_sleep(PauseTime);

		cout << " Swift[ UPC ]: ~/   tools   -sudo/"; Message = "UPC\n"; // 2, 1 operacion << y una de igualdad
		for (string::iterator i = Message.begin(); i != Message.end(); ++i) { // 1 + n(1 + 2 + 2)
			cout << i.operator*(); _sleep(PauseTime / 10); // 2, 1 operacion << y una de division
		}
		_sleep(PauseTime);

		cout << " Loading. Please "; Message = "wait..."; // 2, 1 operacion << y una de igualdad
		for (string::iterator i = Message.begin(); i != Message.end(); ++i) { // 1 + n(1 + 2 + 2)
			cout << i.operator*(); _sleep(PauseTime / 10); // 2, 1 operacion << y una de division
		}
		_sleep(PauseTime * 5); system("cls"); // 1, una operacion de multiplicacion
	}
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	color(hConsole, 79);
	if (User == nullptr) {  // 1 + max(INTERNA IF = 1, INTERNA ELSE = 5)

		for (int i = 0; i < 56; i++) {
			cout << " ";
		}
		cout << "NULL"; // 1 operacion <<
		for (int i = 0; i < 57; i++) {
			cout << " ";
		}
		cout << endl; _sleep(PauseTime);
	}
	else {
		for (int i = 0; i < 48; i++) {
			cout << " ";
		}
		cout << User->getStudentID() << char(64) << "upc.edu.pe"; // 5 operaciones <<
		for (int i = 0; i < 48; i++) {
			cout << " ";
		}
		cout << endl; _sleep(PauseTime);
	}
	color(hConsole, 15);

	cout << " =================================================================================================================== " << endl; _sleep(PauseTime); // 2 operaciones <<
	cout << " UPC:  PowerShell  post - exploitation  agent  " << char(179) << "  [Version]  3.905" << endl; _sleep(PauseTime); // 4 operaciones <<
	cout << " =================================================================================================================== " << endl << endl; _sleep(PauseTime); // 3 operaciones <<
	cout << " =================================================================================================================== " << endl << endl; // 3 operaciones <<

	if (RestartSystem) {  // 1 + max(INTERNA IF = 1, INTERNA ELSE = 4)
		Random = 2; // 1 operacion de igualdad
	}
	else {
		Random = 1 + rand() % +3; // 4, una operacion de igualdad, 2 de suma, 1 de mod
	}


	if (Random == 1 && Option == 0) { // 1 + max(INTERNA IF = 17, INTERNA ELSE = 0)
		cout << "  _____ _   _ ___________  ___   _   _  _____ _____ " << endl;
		cout << " |_   _| " << char(92) << " | |_   _| ___ " << char(92) << "/ _ " << char(92) << " | " << char(92) << " | ||  ___|_   _|" << endl;
		cout << "   | | |  " << char(92) << "| | | | | |_/ / /_" << char(92) << " " << char(92) << "|  " << char(92) << "| || |__   | |  " << endl;
		cout << "   | | | . ` | | | |    /|  _  || . ` ||  __|  | |  " << endl;
		cout << "  _| |_| |" << char(92) << "  | | | | |" << char(92) << " " << char(92) << "| | | || |" << char(92) << "  || |___  | |  " << endl;
		cout << "  " << char(92) << "___/" << char(92) << "_| " << char(92) << "_/ " << char(92) << "_/ " << char(92) << "_| " << char(92) << "_" << char(92) << "_| |_/" << char(92) << "_| " << char(92) << "_/" << char(92) << "____/  " << char(92) << "_/  " << endl << endl << endl;
	}
	else
		if (Random == 2 && Option == 0) { // 1 + max(INTERNA IF = 17, INTERNA ELSE = 0)
			cout << "  ___ _   _ _____ ____      _    _   _ _____ _____ " << endl;
			cout << " |_ _| " << char(92) << " | |_   _|  _ " << char(92) << "    / " << char(92) << "  | " << char(92) << " | | ____|_   _|" << endl;
			cout << "  | ||  " << char(92) << "| | | | | |_) |  / _ " << char(92) << " |  " << char(92) << "| |  _|   | |  " << endl;
			cout << "  | || |" << char(92) << "  | | | |  _ <  / ___ " << char(92) << "| |" << char(92) << "  | |___  | |  " << endl;
			cout << " |___|_| " << char(92) << "_| |_| |_| " << char(92) << "_" << char(92) << "/_/   " << char(92) << "_" << char(92) << "_| " << char(92) << "_|_____| |_|  " << endl << endl << endl;
		}
		else
			if (Random == 3 && Option == 0) {
				short slab1 = 219;
				short slab2 = 220;
				short slab3 = 223;
				short shadow1 = 176;
				short shadow2 = 177;
				short shadow3 = 178;

				cout << "  " << char(slab1) << "" << char(slab1) << "" << char(shadow3) << " " << char(slab1) << "" << char(slab1) << "" << char(slab1) << "" << char(slab2) << "    " << char(slab1) << " " << char(slab2) << "" << char(slab2) << "" << char(slab2) << "" << char(slab1) << "" << char(slab1) << "" << char(slab1) << "" << char(slab1) << "" << char(slab1) << "" << char(shadow3) << " " << char(slab1) << "" << char(slab2) << "" << char(slab3) << "" << char(slab1) << "" << char(slab1) << "" << char(slab1) << "   " << char(slab2) << "" << char(slab2) << "" << char(slab2) << "       " << char(slab1) << "" << char(slab1) << "" << char(slab1) << "" << char(slab2) << "    " << char(slab1) << " " << char(shadow3) << "" << char(slab1) << "" << char(slab1) << "" << char(slab1) << "" << char(slab1) << "" << char(slab1) << "" << char(slab2) << "" << char(slab2) << "" << char(slab2) << "" << char(slab1) << "" << char(slab1) << "" << char(slab1) << "" << char(slab1) << "" << char(slab1) << "" << char(shadow3) << endl;
				cout << " " << char(shadow3) << "" << char(slab1) << "" << char(slab1) << "" << char(shadow2) << " " << char(slab1) << "" << char(slab1) << " " << char(slab3) << "" << char(slab1) << "   " << char(slab1) << " " << char(shadow3) << "  " << char(slab1) << "" << char(slab1) << "" << char(shadow2) << " " << char(shadow3) << "" << char(shadow2) << "" << char(shadow3) << "" << char(slab1) << "" << char(slab1) << " " << char(shadow2) << " " << char(slab1) << "" << char(slab1) << "" << char(shadow2) << "" << char(shadow2) << "" << char(slab1) << "" << char(slab1) << "" << char(slab1) << "" << char(slab1) << "" << char(slab2) << "     " << char(slab1) << "" << char(slab1) << " " << char(slab3) << "" << char(slab1) << "   " << char(slab1) << " " << char(shadow3) << "" << char(slab1) << "   " << char(slab3) << "" << char(shadow3) << "  " << char(slab1) << "" << char(slab1) << "" << char(shadow2) << " " << char(shadow3) << "" << char(shadow2) << endl;
				cout << " " << char(shadow2) << "" << char(slab1) << "" << char(slab1) << "" << char(shadow2) << "" << char(shadow3) << "" << char(slab1) << "" << char(slab1) << "  " << char(slab3) << "" << char(slab1) << " " << char(slab1) << "" << char(slab1) << "" << char(shadow2) << "" << char(shadow2) << " " << char(shadow3) << "" << char(slab1) << "" << char(slab1) << "" << char(shadow1) << " " << char(shadow2) << "" << char(shadow1) << "" << char(shadow3) << "" << char(slab1) << "" << char(slab1) << " " << char(shadow1) << "" << char(slab2) << "" << char(slab1) << " " << char(shadow2) << "" << char(shadow2) << "" << char(slab1) << "" << char(slab1) << "  " << char(slab3) << "" << char(slab1) << "" << char(slab2) << "  " << char(shadow3) << "" << char(slab1) << "" << char(slab1) << "  " << char(slab3) << "" << char(slab1) << " " << char(slab1) << "" << char(slab1) << "" << char(shadow2) << "" << char(shadow2) << "" << char(slab1) << "" << char(slab1) << "" << char(slab1) << "  " << char(shadow2) << " " << char(shadow3) << "" << char(slab1) << "" << char(slab1) << "" << char(shadow1) << " " << char(shadow2) << "" << char(shadow1) << endl;
				cout << " " << char(shadow1) << "" << char(slab1) << "" << char(slab1) << "" << char(shadow1) << "" << char(shadow3) << "" << char(slab1) << "" << char(slab1) << "" << char(shadow2) << "  " << char(slab1) << " " << char(slab1) << "" << char(slab1) << "" << char(shadow2) << "" << char(shadow1) << " " << char(shadow3) << "" << char(slab1) << "" << char(slab1) << "" << char(shadow3) << " " << char(shadow1) << " " << char(shadow2) << "" << char(slab1) << "" << char(slab1) << "" << char(slab3) << "" << char(slab3) << "" << char(slab1) << "" << char(slab2) << "  " << char(shadow1) << "" << char(slab1) << "" << char(slab1) << "" << char(slab2) << "" << char(slab2) << "" << char(slab2) << "" << char(slab2) << "" << char(slab1) << "" << char(slab1) << " " << char(shadow3) << "" << char(slab1) << "" << char(slab1) << "" << char(shadow2) << "  " << char(slab1) << " " << char(slab1) << "" << char(slab1) << "" << char(shadow2) << "" << char(shadow2) << "" << char(shadow3) << "" << char(slab1) << "  " << char(slab2) << "" << char(shadow1) << " " << char(shadow3) << "" << char(slab1) << "" << char(slab1) << "" << char(shadow3) << " " << char(shadow1) << endl;
				cout << " " << char(shadow1) << "" << char(slab1) << "" << char(slab1) << "" << char(shadow1) << "" << char(shadow2) << "" << char(slab1) << "" << char(slab1) << "" << char(shadow1) << "   " << char(shadow3) << "" << char(slab1) << "" << char(slab1) << "" << char(shadow1) << "  " << char(shadow2) << "" << char(slab1) << "" << char(slab1) << "" << char(shadow2) << " " << char(shadow1) << " " << char(shadow1) << "" << char(slab1) << "" << char(slab1) << "" << char(shadow3) << " " << char(shadow2) << "" << char(slab1) << "" << char(slab1) << "" << char(shadow2) << " " << char(shadow3) << "" << char(slab1) << "   " << char(shadow3) << "" << char(slab1) << "" << char(slab1) << "" << char(shadow2) << "" << char(shadow2) << "" << char(slab1) << "" << char(slab1) << "" << char(shadow1) << "   " << char(shadow3) << "" << char(slab1) << "" << char(slab1) << "" << char(shadow1) << "" << char(shadow1) << "" << char(shadow2) << "" << char(slab1) << "" << char(slab1) << "" << char(slab1) << "" << char(slab1) << "" << char(shadow2) << " " << char(shadow2) << "" << char(slab1) << "" << char(slab1) << "" << char(shadow2) << " " << char(shadow1) << endl;
				cout << " " << char(shadow1) << "" << char(shadow3) << "  " << char(shadow1) << " " << char(shadow2) << "" << char(shadow1) << "   " << char(shadow2) << " " << char(shadow2) << "   " << char(shadow2) << " " << char(shadow1) << "" << char(shadow1) << "   " << char(shadow1) << " " << char(shadow2) << "" << char(shadow3) << " " << char(shadow1) << "" << char(shadow2) << "" << char(shadow3) << "" << char(shadow1) << " " << char(shadow2) << "" << char(shadow2) << "   " << char(shadow3) << "" << char(shadow2) << "" << char(slab1) << "" << char(shadow1) << "" << char(shadow1) << " " << char(shadow2) << "" << char(shadow1) << "   " << char(shadow2) << " " << char(shadow2) << " " << char(shadow1) << "" << char(shadow1) << " " << char(shadow2) << "" << char(shadow1) << " " << char(shadow1) << " " << char(shadow2) << " " << char(shadow1) << "" << char(shadow1) << endl;
				cout << "  " << char(shadow2) << " " << char(shadow1) << "" << char(shadow1) << " " << char(shadow1) << "" << char(shadow1) << "   " << char(shadow1) << " " << char(shadow2) << "" << char(shadow1) << "    " << char(shadow1) << "      " << char(shadow1) << "" << char(shadow2) << " " << char(shadow1) << " " << char(shadow2) << "" << char(shadow1) << "  " << char(shadow2) << "   " << char(shadow2) << "" << char(shadow2) << " " << char(shadow1) << "" << char(shadow1) << " " << char(shadow1) << "" << char(shadow1) << "   " << char(shadow1) << " " << char(shadow2) << "" << char(shadow1) << " " << char(shadow1) << " " << char(shadow1) << "  " << char(shadow1) << "   " << char(shadow1) << endl;
				cout << "  " << char(shadow2) << " " << char(shadow1) << "   " << char(shadow1) << "   " << char(shadow1) << " " << char(shadow1) << "   " << char(shadow1) << "        " << char(shadow1) << "" << char(shadow1) << "   " << char(shadow1) << "   " << char(shadow1) << "   " << char(shadow2) << "      " << char(shadow1) << "   " << char(shadow1) << " " << char(shadow1) << "    " << char(shadow1) << "    " << char(shadow1) << endl;
				cout << "  " << char(shadow1) << "           " << char(shadow1) << "             " << char(shadow1) << "           " << char(shadow1) << "  " << char(shadow1) << "         " << char(shadow1) << "    " << char(shadow1) << "  " << char(shadow1) << endl << endl << endl;
			}

	if (RestartSystem) { // 1 + max(INTERNA IF = 17, INTERNA ELSE = 0)
		_sleep(PauseTime * 5); // 1 operacion de multiplicacion
		cout << endl << " [            192.24.93.0 SD. 0:0:0:0:  "; Message = "[sda]\n\n"; // 2 operaciones << y 1 de asignacion
		for (string::iterator i = Message.begin(); i < Message.end(); i++) { // 1 + n(1 + 2 + 2)
			cout << i.operator*(); _sleep(PauseTime / 10); // 2, 1 operacion de << y una de division
		}
		_sleep(PauseTime);


		/// [   RESTART LOCAL VARIABLES   ]
		Looping = true; // 1 operacion de asignacion
		Selection = 0; // 1 operacion de asignacion
		Option = 0; // 1 operacion de asignacion
		OptionSelective = ""; // 1 operacion de asignacion
		User = nullptr; // 1 operacion de asignacion
		ObjectQuantity = ""; // 1 operacion de asignacion
		CoverterTotxt = ""; // 1 operacion de asignacion
		/// [   RESTART LOCAL VARIABLES   ]
		color(hConsole, 10);
		cout << " [   OK   ]";
		color(hConsole, 15);
		cout << "   Started SSC : Set preliminary "; Message = "keymap.\n\n"; // 1 operacion << y 1 de asignacion
		for (string::iterator i = Message.begin(); i < Message.end(); i++) { // 1 + n(1 + 2 + 2)
			cout << i.operator*(); _sleep(PauseTime / 10); // 2, 1 operacion de << y una de division
		}
		_sleep(PauseTime);

		cout << "              Starting Remount Root File "; Message = "System...\n\n"; // 1 operacion << y 1 de asignacion
		for (string::iterator i = Message.begin(); i < Message.end(); i++) { // 1 + n(1 + 2 + 2)
			cout << i.operator*(); _sleep(PauseTime / 10); // 2, 1 operacion de << y una de division
		}


		/// [   UPC DATA LOADER   ]
		LoaderUPCData();
		/// [   UPC DATA LOADER   ]


		RestartSystem = false; _sleep(PauseTime * 5); // 2 operacion de multiplicacion
		color(hConsole, 10);
		cout << " [   OK   ]";
		color(hConsole, 15);
		cout << "   Reached target Local File System "; Message = "(Pre).\n"; // 1 operacion << y 1 de asignacion
		for (string::iterator i = Message.begin(); i < Message.end(); i++) { // 1 + n(1 + 2 + 2)
			cout << i.operator*(); _sleep(PauseTime / 10); // 2, 1 operacion de << y una de division
		}
		_sleep(PauseTime * 5); // 1 operacion de multiplicacion

		system("cls"); LogoGenius(); _sleep(PauseTime * 5); // 1 operacion de multiplicacion
	}
}
void UPC::DisplayUPCMenu() { // BIG O = O(n)
	LogoGenius(); // n

	if (User == nullptr) { // 1 + max(INTERNA IF = 11 + 15n, INTERNA ELSE = 19 + 25n)
		cout << " [   1   ]   Sign "; Message = "In\n"; // 2, 1 operacion de << y una de asignacion
		for (string::iterator i = Message.begin(); i != Message.end(); ++i) { // 1 + n(1 + 2 + 2)
			cout << i.operator*(); _sleep(PauseTime / 10); // 2, 1 operacion de << y una de division
		}

		cout << endl << " [   2   ]   Sign "; Message = "Up\n"; // 3, 2 operaciones de << y una de asignacion
		for (string::iterator i = Message.begin(); i != Message.end(); ++i) { // 1 + n(1 + 2 + 2)
			cout << i.operator*(); _sleep(PauseTime / 10); // 2, 1 operacion de << y una de division
		}

		cout << endl << " [   3   ]   "; Message = "Exit\n"; // 3, 2 operaciones de << y una de asignacion
		for (string::iterator i = Message.begin(); i != Message.end(); ++i) { // 1 + n(1 + 2 + 2)
			cout << i.operator*(); _sleep(PauseTime / 10); // 2, 1 operacion de << y una de division
		}
	}
	else {
		cout << " [   1   ]   View "; Message = "Profile\n"; // 2, 1 operacion de << y una de asignacion
		for (string::iterator i = Message.begin(); i != Message.end(); ++i) { // 1 + n(1 + 2 + 2)
			cout << i.operator*(); _sleep(PauseTime / 10); // 2, 1 operacion de << y una de division
		}

		cout << endl << " [   2   ]   My "; Message = "Calendar\n"; // 3, 2 operaciones de << y una de asignacion
		for (string::iterator i = Message.begin(); i != Message.end(); ++i) { // 1 + n(1 + 2 + 2)
			cout << i.operator*(); _sleep(PauseTime / 10); // 2, 1 operacion de << y una de division
		}

		cout << endl << " [   3   ]   "; Message = "Notifications\n"; // 3, 2 operaciones de << y una de asignacion
		for (string::iterator i = Message.begin(); i != Message.end(); ++i) { // 1 + n(1 + 2 + 2)
			cout << i.operator*(); _sleep(PauseTime / 10); // 2, 1 operacion de << y una de division
		}

		cout << endl << " [   4   ]   "; Message = "View Courses\n"; // 3, 2 operaciones de << y una de asignacion
		for (string::iterator i = Message.begin(); i != Message.end(); ++i) { // 1 + n(1 + 2 + 2)
			cout << i.operator*(); _sleep(PauseTime / 10); // 2, 1 operacion de << y una de division
		}

		cout << endl << " [   5   ]   Log "; Message = "Out\n"; // 3, 2 operaciones de << y una de asignacion
		for (string::iterator i = Message.begin(); i != Message.end(); ++i) { // 1 + n(1 + 2 + 2)
			cout << i.operator*(); _sleep(PauseTime / 10); // 2, 1 operacion de << y una de division
		}

		cout << endl << " [   6   ]   "; Message = "Exit\n"; // 3, 2 operaciones de << y una de asignacion
		for (string::iterator i = Message.begin(); i != Message.end(); ++i) { // 1 + n(1 + 2 + 2)
			cout << i.operator*(); _sleep(PauseTime / 10); // 2, 1 operacion de << y una de division
		}
	}
}

void UPC::SignIn() {
	if (StudentsTable->getSize() != 0) {
		string Password;

		cout << " _ooooo__oooo____oooo___ooo____oo____oooo_ooo____oo_" << endl;
		cout << " oo___oo__oo___oo____oo_oooo___oo_____oo__oooo___oo_" << endl;
		cout << " _oo______oo__oo________oo_oo__oo_____oo__oo_oo__oo_" << endl;
		cout << " ___oo____oo__oo____ooo_oo__oo_oo_____oo__oo__oo_oo_" << endl;
		cout << " oo___oo__oo___oo____oo_oo___oooo_____oo__oo___oooo_" << endl;
		cout << " _ooooo__oooo____oooo___oo____ooo____oooo_oo____ooo_" << endl;
		cout << " ___________________________________________________" << endl << endl << endl;

		RecursiveDisplayStudentsAccount(0, StudentsDoubleList->getSize() - 1);
		do {
			Message = " get source account ";
			for (string::iterator i = Message.begin(); i != Message.end(); ++i) {
				cout << i.operator*(); _sleep(PauseTime / 10);
			}
			cin >> OptionSelective;
			try {
				stoi(OptionSelective);
				if (stoi(OptionSelective) == -1) { return; }
			}
			catch (const invalid_argument& e) {
				if (OptionSelective == "Quick") {
					QuickSort(StudentsDoubleList, 0, StudentsDoubleList->getSize() - 1);
				}
				else
					if (OptionSelective == "Merge") {
						MergeSort(StudentsDoubleList, 0, StudentsDoubleList->getSize() - 1);
					}
					else
						if (OptionSelective == "Bubble") {
							BubbleSort(StudentsDoubleList);
						}
						else
							if (OptionSelective == "Yates") {
								FisherYatesShuffle(StudentsDoubleList);
							}
				return;
			}
			catch (const out_of_range& e) {
				if (OptionSelective == "Quick") {
					QuickSort(StudentsDoubleList, 0, StudentsDoubleList->getSize() - 1);
				}
				else
					if (OptionSelective == "Merge") {
						MergeSort(StudentsDoubleList, 0, StudentsDoubleList->getSize() - 1);
					}
					else
						if (OptionSelective == "Bubble") {
							BubbleSort(StudentsDoubleList);
						}
						else
							if (OptionSelective == "Yates") {
								FisherYatesShuffle(StudentsDoubleList);
							}
				return;
			}

		} while (stoi(OptionSelective) < 1 || stoi(OptionSelective) > StudentsDoubleList->getSize());

		do {
			Message = "\n Password: ";
			for (string::iterator i = Message.begin(); i != Message.end(); ++i) {
				cout << i.operator*(); _sleep(PauseTime / 10);
			}
			cin >> Password;
		} while (Password != StudentsDoubleList->ObtainIndex(stoi(OptionSelective) - 1)->getPassword());

		User = StudentsDoubleList->ObtainIndex(stoi(OptionSelective) - 1);


		system("cls");
		LogoGenius();

		Console::SetCursorPosition(16, 37); cout << "      ooooo      " << endl;
		Console::SetCursorPosition(16, 38); cout << "   ooooooooooo   " << endl;
		Console::SetCursorPosition(16, 39); cout << " ooo         ooo " << endl;
		Console::SetCursorPosition(16, 40); cout << "oo     ooo     oo" << endl;
		Console::SetCursorPosition(16, 41); cout << "     ooooooo     " << endl;
		Console::SetCursorPosition(16, 42); cout << "   oo       oo   " << endl;
		Console::SetCursorPosition(16, 43); cout << "        o        " << endl;
		Console::SetCursorPosition(16, 44); cout << "       ooo       " << endl;
		Console::SetCursorPosition(16, 45); cout << "        o        ";

		Console::SetCursorPosition(83, 37); cout << "   _______________" << endl;
		Console::SetCursorPosition(83, 38); cout << "  /|             |" << endl;
		Console::SetCursorPosition(83, 39); cout << " / |  _______    |" << endl;
		Console::SetCursorPosition(83, 40); cout << "/__|             |" << endl;
		Console::SetCursorPosition(83, 41); cout << "|     _______    |" << endl;
		Console::SetCursorPosition(83, 42); cout << "|                |" << endl;
		Console::SetCursorPosition(83, 43); cout << "|     _______    |" << endl;
		Console::SetCursorPosition(83, 44); cout << "|                |" << endl;
		Console::SetCursorPosition(83, 45); cout << "|________________|";

		Console::SetCursorPosition(43, 40); cout << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << endl;
		Console::SetCursorPosition(43, 41); cout << "/ / / / / / / / / / / / / / / " << endl;


		Console::SetCursorPosition(0, 7);
		cout << "     // PERSON header structure" << endl;
		cout << "     //" << endl << endl << endl;


		cout << "     typedef struct {" << endl;
		cout << "        u32string FirstName                            ";
		color(hConsole, 10);
		cout << "[     connected     ];" << endl; _sleep(PauseTime);
		color(hConsole, 15);
		Console::SetCursorPosition(43, 41);
		cout << " / / / / / / / / / / / / / / /" << endl;
		Console::SetCursorPosition(0, 13);
		cout << "        u32string SecondName                           ";
		color(hConsole, 10);
		cout << "[     connected     ];" << endl; _sleep(PauseTime);
		color(hConsole, 15);
		Console::SetCursorPosition(43, 40);
		cout << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << endl;
		Console::SetCursorPosition(0, 14);
		cout << "        u32string LastName                             ";
		color(hConsole, 10);
		cout << "[     connected     ];" << endl; _sleep(PauseTime);
		color(hConsole, 15);
		Console::SetCursorPosition(43, 41);
		cout << "/ / / / / / / / / / / / / / / " << endl;
		Console::SetCursorPosition(0, 15);
		cout << "        u32string MothersLastName                      ";
		color(hConsole, 10);
		cout << "[     connected     ];" << endl; _sleep(PauseTime);
		color(hConsole, 15);
		Console::SetCursorPosition(43, 40);
		cout << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << endl;
		Console::SetCursorPosition(0, 16);
		cout << "        u_int32_t Age                                  ";
		color(hConsole, 10);
		cout << "[     connected     ];" << endl; _sleep(PauseTime);
		color(hConsole, 15);
		Console::SetCursorPosition(43, 41);
		cout << " / / / / / / / / / / / / / / /" << endl;
		Console::SetCursorPosition(0, 17);

		cout << endl << "     } cr_person_t; " << endl << endl << endl; _sleep(PauseTime);
		Console::SetCursorPosition(43, 40);
		cout << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << endl;
		Console::SetCursorPosition(0, 21);

		for (int i = 0; i < 3; i++) {
			color(hConsole, 0);
			Console::SetCursorPosition(55, 12); cout << "[     connected     ];";
			Console::SetCursorPosition(55, 13); cout << "[     connected     ];";
			Console::SetCursorPosition(55, 14); cout << "[     connected     ];";
			Console::SetCursorPosition(55, 15); cout << "[     connected     ];";
			Console::SetCursorPosition(55, 16); cout << "[     connected     ];";
			_sleep(PauseTime);
			color(hConsole, 10);
			Console::SetCursorPosition(55, 12); cout << "[     connected     ];";
			Console::SetCursorPosition(55, 13); cout << "[     connected     ];";
			Console::SetCursorPosition(55, 14); cout << "[     connected     ];";
			Console::SetCursorPosition(55, 15); cout << "[     connected     ];";
			Console::SetCursorPosition(55, 16); cout << "[     connected     ];";
			_sleep(PauseTime);
		}
		color(hConsole, 15);

		Console::SetCursorPosition(0, 21);
		cout << "     //" << endl; _sleep(PauseTime);
		Console::SetCursorPosition(43, 41);
		cout << "/ / / / / / / / / / / / / / / " << endl;
		Console::SetCursorPosition(0, 22);

		cout << "     // STUDENT BLOCK definitions" << endl; _sleep(PauseTime);
		Console::SetCursorPosition(43, 40);
		cout << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << endl;
		Console::SetCursorPosition(0, 23);

		cout << "     //" << endl << endl << endl; _sleep(PauseTime);
		Console::SetCursorPosition(43, 41);
		cout << " / / / / / / / / / / / / / / /" << endl;
		Console::SetCursorPosition(0, 26);


		cout << "     typedef struct {" << endl; _sleep(PauseTime);
		Console::SetCursorPosition(43, 40);
		cout << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << endl;
		Console::SetCursorPosition(0, 27);

		cout << "        var_list CourseList                            ";
		color(hConsole, 10);
		cout << "[     connected     ]; " << endl; _sleep(PauseTime);
		color(hConsole, 15);
		Console::SetCursorPosition(43, 41);
		cout << "/ / / / / / / / / / / / / / / " << endl;
		Console::SetCursorPosition(0, 28);

		cout << "        var_list DiplomaList                           ";
		color(hConsole, 10);
		cout << "[     connected     ];" << endl; _sleep(PauseTime);
		color(hConsole, 15);
		Console::SetCursorPosition(43, 40);
		cout << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << endl;
		Console::SetCursorPosition(0, 29);


		cout << "        var_list NotificationHeap                      ";
		color(hConsole, 10);
		cout << "[     connected     ];" << endl; _sleep(PauseTime);
		color(hConsole, 15);
		Console::SetCursorPosition(43, 41);
		cout << " / / / / / / / / / / / / / / /" << endl;
		Console::SetCursorPosition(0, 30);

		cout << "        u32string Password                             ";
		color(hConsole, 10);
		cout << "[     connected     ];" << endl; _sleep(PauseTime);
		color(hConsole, 15);
		Console::SetCursorPosition(43, 40);
		cout << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << endl;
		Console::SetCursorPosition(0, 31);

		cout << "        u32string StudentID                            ";
		color(hConsole, 10);
		cout << "[     connected     ];" << endl; _sleep(PauseTime);
		color(hConsole, 15);
		Console::SetCursorPosition(43, 41);
		cout << "/ / / / / / / / / / / / / / / " << endl;
		Console::SetCursorPosition(0, 32);

		cout << endl << "     } cr_student_t, cr_user_t;" << endl;
		cout << "     //";

		for (int i = 0; i < 3; i++) {
			color(hConsole, 0);
			Console::SetCursorPosition(55, 27); cout << "[     connected     ];";
			Console::SetCursorPosition(55, 28); cout << "[     connected     ];";
			Console::SetCursorPosition(55, 29); cout << "[     connected     ];";
			Console::SetCursorPosition(55, 30); cout << "[     connected     ];";
			Console::SetCursorPosition(55, 31); cout << "[     connected     ];";
			_sleep(PauseTime);
			color(hConsole, 10);
			Console::SetCursorPosition(55, 27); cout << "[     connected     ];";
			Console::SetCursorPosition(55, 28); cout << "[     connected     ];";
			Console::SetCursorPosition(55, 29); cout << "[     connected     ];";
			Console::SetCursorPosition(55, 30); cout << "[     connected     ];";
			Console::SetCursorPosition(55, 31); cout << "[     connected     ];";
			_sleep(PauseTime);
		}
		color(hConsole, 15);
	}
	else {
		cout << "--No hay cuentas que usar--";
	}
}
void UPC::SignUp() {
	color(hConsole, 9);
	cout << "  ad88888ba   88    ,ad8888ba,   888b      88     88        88  88888888ba " << endl; _sleep(PauseTime / 10);
	cout << " d8'     '8b  88   d8''    `'8b  8888b     88     88        88  88      '8b" << endl; _sleep(PauseTime / 10);
	cout << " Y8,          88  d8'            88 `8b    88     88        88  88      ,8P" << endl; _sleep(PauseTime / 10);
	cout << " `Y8aaaaa,    88  88             88  `8b   88     88        88  88aaaaaa8P'" << endl; _sleep(PauseTime / 10);
	cout << "   `'''''8b,  88  88      88888  88   `8b  88     88        88  88'''''''  " << endl; _sleep(PauseTime / 10);
	cout << "         `8b  88  Y8,        88  88    `8b 88     88        88  88         " << endl; _sleep(PauseTime / 10);
	cout << " Y8a     a8P  88   Y8a.    .a88  88     `8888     Y8a.    .a8P  88         " << endl; _sleep(PauseTime / 10);
	cout << "  'Y88888P'   88    `'Y88888P'   88      `888      `'Y8888Y''   88         " << endl << endl << endl; _sleep(PauseTime / 10);
	color(hConsole, 15);
	string FirstName;
	string SecondName;
	string LastName;
	string MothersLastName;
	short Age;
	string StudentID;
	string Password;

	cout << " Sign Up - Trophy UPC v7.00PC " << endl; _sleep(PauseTime);
	cout << " Copyright (C) UPC Technologies, LTD" << endl << endl; _sleep(PauseTime);

	cout << " Copyright by UPC Company" << endl; _sleep(PauseTime);
	cout << " Rev.4.25" << endl; _sleep(PauseTime);
	cout << " Main Processor : XXXXXXXXXXXXXXXXXXXX" << endl; _sleep(PauseTime);
	cout << " Memory Testing : " << &StudentsTable << " OK" << endl << endl << endl << endl; _sleep(PauseTime);
	cout << " Students Cache Size : 79KB" << endl; _sleep(PauseTime);
	cout << " First Name Student : "; cin >> FirstName;
	cout << " Second Name Student : "; cin >> SecondName;
	cout << " Last Name Student : "; cin >> LastName;
	cout << " Mother's Last Name Student : "; cin >> MothersLastName;
	cout << " Old-Age Student : "; cin >> Age;
	do {
		cout << " ID Student : "; cin >> StudentID;
		StudentID[0] = toupper(StudentID[0]);
	} while (StudentID[0] != ('U') || StudentID.size() != 10);
	cout << " Not-So-Secret Password : "; cin >> Password; cout << endl;

	StudentsDoubleList->AddToEnd(new Student(FirstName, SecondName, LastName, MothersLastName, Age, StudentID, 21, Password));
	User = StudentsDoubleList->ObtainEnd();

	FileWriter.open("Students.txt", ios::out);
	if (FileWriter.is_open()) {
		FileWriter << StudentsDoubleList->getSize() << endl;
		RecursiveWriterTxtStudentFile(0, StudentsDoubleList->getSize() - 1);
		FileWriter.close();
	}

	CoverterTotxt = StudentID + ".txt";

	FileWriter.open(CoverterTotxt, ios::out);
	if (FileWriter.is_open()) {
		FileWriter << User->getCourseList()->getSize() << endl;
		if (User->getNotificationHeap()->getSize() > 0) {
			RecursiveWriterTxtCourseFile(0, User->getCourseList()->getSize() - 1);
			FileWriter << endl;
		}

		FileWriter << User->getNotificationHeap()->getSize();
		if (User->getNotificationHeap()->getSize() > 0) {
			FileWriter << endl;
			RecursiveWriterTxtNotificationFile(0, User->getNotificationHeap()->getSize() - 1);
		}

		FileWriter.close();
	}

	cout << " Floppy file(s) fail (80)" << endl << endl << endl; _sleep(PauseTime);
	cout << " Press any button to Continue"; _sleep(PauseTime);
}
void UPC::LogOut() {

	cout << "     // PERSON header structure" << endl;
	cout << "     //" << endl << endl << endl;


	cout << "     typedef struct {" << endl;
	cout << "        u32string FirstName                            ";
	color(hConsole, 10);
	cout << "[     connected     ];" << endl;
	color(hConsole, 15);
	cout << "        u32string SecondName                           ";
	color(hConsole, 10);
	cout << "[     connected     ];" << endl;
	color(hConsole, 15);
	cout << "        u32string LastName                             ";
	color(hConsole, 10);
	cout << "[     connected     ];" << endl;
	color(hConsole, 15);
	cout << "        u32string MothersLastName                      ";
	color(hConsole, 10);
	cout << "[     connected     ];" << endl;
	color(hConsole, 15);
	cout << "        u_int32_t Age                                  ";
	color(hConsole, 10);
	cout << "[     connected     ];" << endl;
	color(hConsole, 15);
	cout << endl << "     } cr_person_t; " << endl << endl << endl;


	cout << "     //" << endl;
	cout << "     // STUDENT BLOCK definitions" << endl;
	cout << "     //" << endl << endl << endl;

	cout << "     typedef struct {" << endl;
	cout << "        var_list CourseList                            ";
	color(hConsole, 10);
	cout << "[     connected     ]; " << endl;
	color(hConsole, 15);
	cout << "        var_list DiplomaList                           ";
	color(hConsole, 10);
	cout << "[     connected     ];" << endl;
	color(hConsole, 15);
	cout << "        var_list NotificationHeap                      ";
	color(hConsole, 10);
	cout << "[     connected     ];" << endl;
	color(hConsole, 15);
	cout << "        u32string Password                             ";
	color(hConsole, 10);
	cout << "[     connected     ];" << endl;
	color(hConsole, 15);
	cout << "        u32string StudentID                            ";
	color(hConsole, 10);
	cout << "[     connected     ];" << endl;
	color(hConsole, 15);
	cout << endl << "     } cr_student_t, cr_user_t;" << endl;
	cout << "     //";

	Console::SetCursorPosition(16, 37); cout << "      ooooo      " << endl;
	Console::SetCursorPosition(16, 38); cout << "   ooooooooooo   " << endl;
	Console::SetCursorPosition(16, 39); cout << " ooo         ooo " << endl;
	Console::SetCursorPosition(16, 40); cout << "oo     ooo     oo" << endl;
	Console::SetCursorPosition(16, 41); cout << "     ooooooo     " << endl;
	Console::SetCursorPosition(16, 42); cout << "   oo       oo   " << endl;
	Console::SetCursorPosition(16, 43); cout << "        o        " << endl;
	Console::SetCursorPosition(16, 44); cout << "       ooo       " << endl;
	Console::SetCursorPosition(16, 45); cout << "        o        " << endl << endl;

	Console::SetCursorPosition(83, 37); cout << "   _______________" << endl;
	Console::SetCursorPosition(83, 38); cout << "  /|             |" << endl;
	Console::SetCursorPosition(83, 39); cout << " / |  _______    |" << endl;
	Console::SetCursorPosition(83, 40); cout << "/__|             |" << endl;
	Console::SetCursorPosition(83, 41); cout << "|     _______    |" << endl;
	Console::SetCursorPosition(83, 42); cout << "|                |" << endl;
	Console::SetCursorPosition(83, 43); cout << "|     _______    |" << endl;
	Console::SetCursorPosition(83, 44); cout << "|                |" << endl;
	Console::SetCursorPosition(83, 45); cout << "|________________|" << endl << endl;

	Console::SetCursorPosition(43, 40); cout << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << "         " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << " " << char(92) << endl;
	Console::SetCursorPosition(43, 41); cout << " / / / / /         / / / / / /" << endl;
	_sleep(PauseTime);

	color(hConsole, 4);
	Console::SetCursorPosition(55, 12); cout << "[    disconnected   ];"; _sleep(PauseTime);
	Console::SetCursorPosition(54, 38); cout << " oo   oo" << endl;
	Console::SetCursorPosition(54, 39); cout << "  oo oo" << endl;
	Console::SetCursorPosition(54, 40); cout << "   ooo" << endl;
	Console::SetCursorPosition(54, 41); cout << "   ooo" << endl;
	Console::SetCursorPosition(54, 42); cout << "  oo oo" << endl;
	Console::SetCursorPosition(54, 43); cout << " oo   oo" << endl;
	Console::SetCursorPosition(55, 13); cout << "[    disconnected   ];"; _sleep(PauseTime);
	color(hConsole, 0);
	Console::SetCursorPosition(54, 38); cout << " oo   oo" << endl;
	Console::SetCursorPosition(54, 39); cout << "  oo oo" << endl;
	Console::SetCursorPosition(54, 40); cout << "   ooo" << endl;
	Console::SetCursorPosition(54, 41); cout << "   ooo" << endl;
	Console::SetCursorPosition(54, 42); cout << "  oo oo" << endl;
	Console::SetCursorPosition(54, 43); cout << " oo   oo" << endl;
	color(hConsole, 4);
	Console::SetCursorPosition(55, 14); cout << "[    disconnected   ];"; _sleep(PauseTime);
	color(hConsole, 4);
	Console::SetCursorPosition(54, 38); cout << " oo   oo" << endl;
	Console::SetCursorPosition(54, 39); cout << "  oo oo" << endl;
	Console::SetCursorPosition(54, 40); cout << "   ooo" << endl;
	Console::SetCursorPosition(54, 41); cout << "   ooo" << endl;
	Console::SetCursorPosition(54, 42); cout << "  oo oo" << endl;
	Console::SetCursorPosition(54, 43); cout << " oo   oo" << endl;
	color(hConsole, 4);
	Console::SetCursorPosition(55, 15); cout << "[    disconnected   ];"; _sleep(PauseTime);
	color(hConsole, 0);
	Console::SetCursorPosition(54, 38); cout << " oo   oo" << endl;
	Console::SetCursorPosition(54, 39); cout << "  oo oo" << endl;
	Console::SetCursorPosition(54, 40); cout << "   ooo" << endl;
	Console::SetCursorPosition(54, 41); cout << "   ooo" << endl;
	Console::SetCursorPosition(54, 42); cout << "  oo oo" << endl;
	Console::SetCursorPosition(54, 43); cout << " oo   oo" << endl;
	color(hConsole, 4);
	Console::SetCursorPosition(55, 16); cout << "[    disconnected   ];"; _sleep(PauseTime);
	color(hConsole, 4);
	Console::SetCursorPosition(54, 38); cout << " oo   oo" << endl;
	Console::SetCursorPosition(54, 39); cout << "  oo oo" << endl;
	Console::SetCursorPosition(54, 40); cout << "   ooo" << endl;
	Console::SetCursorPosition(54, 41); cout << "   ooo" << endl;
	Console::SetCursorPosition(54, 42); cout << "  oo oo" << endl;
	Console::SetCursorPosition(54, 43); cout << " oo   oo" << endl;
	color(hConsole, 4);

	for (int i = 0; i < 3; i++) {
		color(hConsole, 0);
		Console::SetCursorPosition(55, 12); cout << "[    disconnected   ];";
		Console::SetCursorPosition(55, 13); cout << "[    disconnected   ];";
		Console::SetCursorPosition(55, 14); cout << "[    disconnected   ];";
		Console::SetCursorPosition(55, 15); cout << "[    disconnected   ];";
		Console::SetCursorPosition(55, 16); cout << "[    disconnected   ];";

		Console::SetCursorPosition(54, 38); cout << " oo   oo" << endl;
		Console::SetCursorPosition(54, 39); cout << "  oo oo" << endl;
		Console::SetCursorPosition(54, 40); cout << "   ooo" << endl;
		Console::SetCursorPosition(54, 41); cout << "   ooo" << endl;
		Console::SetCursorPosition(54, 42); cout << "  oo oo" << endl;
		Console::SetCursorPosition(54, 43); cout << " oo   oo" << endl;
		_sleep(PauseTime);
		color(hConsole, 4);
		Console::SetCursorPosition(55, 12); cout << "[    disconnected   ];";
		Console::SetCursorPosition(55, 13); cout << "[    disconnected   ];";
		Console::SetCursorPosition(55, 14); cout << "[    disconnected   ];";
		Console::SetCursorPosition(55, 15); cout << "[    disconnected   ];";
		Console::SetCursorPosition(55, 16); cout << "[    disconnected   ];";

		Console::SetCursorPosition(54, 38); cout << " oo   oo" << endl;
		Console::SetCursorPosition(54, 39); cout << "  oo oo" << endl;
		Console::SetCursorPosition(54, 40); cout << "   ooo" << endl;
		Console::SetCursorPosition(54, 41); cout << "   ooo" << endl;
		Console::SetCursorPosition(54, 42); cout << "  oo oo" << endl;
		Console::SetCursorPosition(54, 43); cout << " oo   oo" << endl;
		_sleep(PauseTime);
	}
	color(hConsole, 15);

	color(hConsole, 4);
	Console::SetCursorPosition(55, 27); cout << "[    disconnected   ];"; _sleep(PauseTime);
	color(hConsole, 0);
	Console::SetCursorPosition(54, 38); cout << " oo   oo" << endl;
	Console::SetCursorPosition(54, 39); cout << "  oo oo" << endl;
	Console::SetCursorPosition(54, 40); cout << "   ooo" << endl;
	Console::SetCursorPosition(54, 41); cout << "   ooo" << endl;
	Console::SetCursorPosition(54, 42); cout << "  oo oo" << endl;
	Console::SetCursorPosition(54, 43); cout << " oo   oo" << endl;
	color(hConsole, 4);
	Console::SetCursorPosition(55, 28); cout << "[    disconnected   ];"; _sleep(PauseTime);
	color(hConsole, 4);
	Console::SetCursorPosition(54, 38); cout << " oo   oo" << endl;
	Console::SetCursorPosition(54, 39); cout << "  oo oo" << endl;
	Console::SetCursorPosition(54, 40); cout << "   ooo" << endl;
	Console::SetCursorPosition(54, 41); cout << "   ooo" << endl;
	Console::SetCursorPosition(54, 42); cout << "  oo oo" << endl;
	Console::SetCursorPosition(54, 43); cout << " oo   oo" << endl;
	color(hConsole, 4);
	Console::SetCursorPosition(55, 29); cout << "[    disconnected   ];"; _sleep(PauseTime);
	color(hConsole, 0);
	Console::SetCursorPosition(54, 38); cout << " oo   oo" << endl;
	Console::SetCursorPosition(54, 39); cout << "  oo oo" << endl;
	Console::SetCursorPosition(54, 40); cout << "   ooo" << endl;
	Console::SetCursorPosition(54, 41); cout << "   ooo" << endl;
	Console::SetCursorPosition(54, 42); cout << "  oo oo" << endl;
	Console::SetCursorPosition(54, 43); cout << " oo   oo" << endl;
	color(hConsole, 4);
	Console::SetCursorPosition(55, 30); cout << "[    disconnected   ];"; _sleep(PauseTime);
	color(hConsole, 4);
	Console::SetCursorPosition(54, 38); cout << " oo   oo" << endl;
	Console::SetCursorPosition(54, 39); cout << "  oo oo" << endl;
	Console::SetCursorPosition(54, 40); cout << "   ooo" << endl;
	Console::SetCursorPosition(54, 41); cout << "   ooo" << endl;
	Console::SetCursorPosition(54, 42); cout << "  oo oo" << endl;
	Console::SetCursorPosition(54, 43); cout << " oo   oo" << endl;
	color(hConsole, 4);
	Console::SetCursorPosition(55, 31); cout << "[    disconnected   ];";

	for (int i = 0; i < 3; i++) {
		color(hConsole, 0);
		Console::SetCursorPosition(55, 27); cout << "[    disconnected   ];";
		Console::SetCursorPosition(55, 28); cout << "[    disconnected   ];";
		Console::SetCursorPosition(55, 29); cout << "[    disconnected   ];";
		Console::SetCursorPosition(55, 30); cout << "[    disconnected   ];";
		Console::SetCursorPosition(55, 31); cout << "[    disconnected   ];";

		Console::SetCursorPosition(54, 38); cout << " oo   oo" << endl;
		Console::SetCursorPosition(54, 39); cout << "  oo oo" << endl;
		Console::SetCursorPosition(54, 40); cout << "   ooo" << endl;
		Console::SetCursorPosition(54, 41); cout << "   ooo" << endl;
		Console::SetCursorPosition(54, 42); cout << "  oo oo" << endl;
		Console::SetCursorPosition(54, 43); cout << " oo   oo" << endl;
		_sleep(PauseTime);

		color(hConsole, 4);
		Console::SetCursorPosition(55, 27); cout << "[    disconnected   ];";
		Console::SetCursorPosition(55, 28); cout << "[    disconnected   ];";
		Console::SetCursorPosition(55, 29); cout << "[    disconnected   ];";
		Console::SetCursorPosition(55, 30); cout << "[    disconnected   ];";
		Console::SetCursorPosition(55, 31); cout << "[    disconnected   ];";

		Console::SetCursorPosition(54, 38); cout << " oo   oo" << endl;
		Console::SetCursorPosition(54, 39); cout << "  oo oo" << endl;
		Console::SetCursorPosition(54, 40); cout << "   ooo" << endl;
		Console::SetCursorPosition(54, 41); cout << "   ooo" << endl;
		Console::SetCursorPosition(54, 42); cout << "  oo oo" << endl;
		Console::SetCursorPosition(54, 43); cout << " oo   oo" << endl;
		_sleep(PauseTime);
	}
	color(hConsole, 15);

	User = nullptr;
}
void UPC::TerminateExecution() {
	Looping = false;
	cout << " ERROR: ";
}

void UPC::DisplayUserProfile() {
	cout << "  ________  ________  ________  ________ ___  ___       _______" << endl;
	cout << " |" << char(92) << "   __  " << char(92) << "|" << char(92) << "   __  " << char(92) << "|" << char(92) << "   __  " << char(92) << "|" << char(92) << "  _____" << char(92) << char(92) << "  " << char(92) << "|" << char(92) << "  " << char(92) << "     |" << char(92) << "  ___ " << char(92) << endl;
	cout << " " << char(92) << " " << char(92) << "  " << char(92) << "|" << char(92) << "  " << char(92) << " " << char(92) << "  " << char(92) << "|" << char(92) << "  " << char(92) << " " << char(92) << "  " << char(92) << "|" << char(92) << "  " << char(92) << " " << char(92) << "  " << char(92) << "__/" << char(92) << " " << char(92) << "  " << char(92) << " " << char(92) << "  " << char(92) << "    " << char(92) << " " << char(92) << "   __/|" << endl;
	cout << "  " << char(92) << " " << char(92) << "   ____" << char(92) << " " << char(92) << "   _  _" << char(92) << " " << char(92) << "  " << char(92) << char(92) << char(92) << "  " << char(92) << " " << char(92) << "   __" << char(92) << char(92) << " " << char(92) << "  " << char(92) << " " << char(92) << "  " << char(92) << "    " << char(92) << " " << char(92) << "  " << char(92) << "_|/__" << endl;
	cout << "   " << char(92) << " " << char(92) << "  " << char(92) << "___|" << char(92) << " " << char(92) << "  " << char(92) << char(92) << "  " << char(92) << char(92) << " " << char(92) << "  " << char(92) << char(92) << char(92) << "  " << char(92) << " " << char(92) << "  " << char(92) << "_| " << char(92) << " " << char(92) << "  " << char(92) << " " << char(92) << "  " << char(92) << "____" << char(92) << " " << char(92) << "  " << char(92) << "_|" << char(92) << " " << char(92) << endl;
	cout << "    " << char(92) << " " << char(92) << "__" << char(92) << "    " << char(92) << " " << char(92) << "__" << char(92) << char(92) << "__" << char(92) << char(92) << " " << char(92) << "_______" << char(92) << " " << char(92) << "__" << char(92) << "   " << char(92) << " " << char(92) << "__" << char(92) << " " << char(92) << "_______" << char(92) << " " << char(92) << "_______" << char(92) << endl;
	cout << "     " << char(92) << "|__|     " << char(92) << "|__|" << char(92) << "|__|" << char(92) << "|_______|" << char(92) << "|__|    " << char(92) << "|__|" << char(92) << "|_______|" << char(92) << "|_______|" << endl << endl;

	cout << "      ";
	color(hConsole, 10);
	if (User->getCredits() > 9)
		cout << User->getCredits();
	else
		cout << "0" << User->getCredits();

	color(hConsole, 15);
	cout << " credits currently held" << endl; _sleep(PauseTime);


	cout << "      ";
	color(hConsole, 10);
	if (User->getCourseList()->getSize() > 9)
		cout << User->getCourseList()->getSize();
	else
		cout << "0" << User->getCourseList()->getSize();

	color(hConsole, 15);
	cout << " courses currently enrolled" << endl; _sleep(PauseTime);


	cout << "      ";
	color(hConsole, 10);
	if (User->getNotificationHeap()->getSize() > 9)
		cout << User->getNotificationHeap()->getSize();
	else
		cout << "0" << User->getNotificationHeap()->getSize();

	color(hConsole, 15);
	cout << " unread notifications" << endl << endl; _sleep(PauseTime);

	cout << " <Employed";
	color(hConsole, 9);
	cout << " stored variables /user";
	color(hConsole, 15);
	cout << "> " << char(175); Message = " options\n\n";
	for (string::iterator i = Message.begin(); i != Message.end(); ++i)
		cout << i.operator*(); _sleep(PauseTime / 10);

	cout << " Description:" << endl; _sleep(PauseTime);
	cout << "     Dedicated and curious, " << User->getOldAge() << "-year-old " << User->getFirstName() << " " << User->getLastName() << " is a passionate student ready to improve \n     his problem-solving skills and creativity, has a positive attitude and unwavering commitment\n     to his studies. With student ID " << User->getStudentID() << ", he enthusiastically embraces his educational journey." << endl << endl; _sleep(PauseTime);

	cout << " Options:" << endl; _sleep(PauseTime);

	cout << "     Atribute";
	for (size_t i = 0; i < 10; i++) {
		cout << " ";
	}
	cout << "Value";
	for (size_t i = 0; i < 7; i++) {
		cout << " ";
	}
	cout << "Description" << endl; _sleep(PauseTime);

	cout << "     --------";
	for (size_t i = 0; i < 10; i++) {
		cout << " ";
	}
	cout << "-----";
	for (size_t i = 0; i < 10; i++) {
		cout << " ";
	}
	cout << "-----------" << endl; _sleep(PauseTime);

	cout << "     FirstName";
	for (size_t i = 0; i < 9; i++) {
		cout << " ";
	}
	cout << User->getFirstName();
	for (size_t i = User->getFirstName().size(); i < 15; i++) {
		cout << " ";
	}
	cout << "Permission granted to generate variables and display files on the screen." << endl; _sleep(PauseTime);

	cout << "     SecondName";
	for (size_t i = 0; i < 8; i++) {
		cout << " ";
	}
	cout << User->getSecondName();
	for (size_t i = User->getSecondName().size(); i < 15; i++) {
		cout << " ";
	}
	cout << "No intermediary server to utilize for the inquiry (default, none, other)." << endl << endl; _sleep(PauseTime);

	cout << "     LastName";
	for (size_t i = 0; i < 10; i++) {
		cout << " ";
	}
	cout << User->getLastName();
	for (size_t i = User->getLastName().size(); i < 15; i++) {
		cout << " ";
	}
	cout << "User-agent string to use for the display request (default, none, other)." << endl << endl << endl; _sleep(PauseTime);

	cout << "     MothersLastName";
	for (size_t i = 0; i < 3; i++) {
		cout << " ";
	}
	cout << User->getMothersLastName();
	for (size_t i = User->getMothersLastName().size(); i < 15; i++) {
		cout << " ";
	}
	cout << "Authorization to generate variables for output of files, necessary,                                                  showcase on the screen." << endl << endl; _sleep(PauseTime);

	cout << "     Old-Age";
	for (size_t i = 0; i < 11; i++) {
		cout << " ";
	}
	cout << User->getOldAge();
	for (size_t i = 2; i < 15; i++) {
		cout << " ";
	}
	cout << "User-agent identifier to employ for the storing request (default, none, other)." << endl << endl << endl << endl; _sleep(PauseTime);

	cout << " <Copied";
	color(hConsole, 9);
	cout << " stagelabels";
	color(hConsole, 15);
	cout << "> " << char(175) << " get studentslist/obtainindex/profile ";
	Message = "intranet0.00\n";
	for (size_t i = 0; i < Message.size(); i++) {
		cout << Message[i]; _sleep(PauseTime / 10);
	}
	_sleep(PauseTime);

	cout << " <Copied";
	color(hConsole, 9);
	cout << " stagelabels";
	color(hConsole, 15);
	cout << "> " << char(175);
	Message = " generate\n\n";
	for (size_t i = 0; i < Message.size(); i++) {
		cout << Message[i]; _sleep(PauseTime / 10);
	}
	_sleep(PauseTime);

	color(hConsole, 9);
	cout << " [*] user output value run /implaided" << endl << endl;
	color(hConsole, 15);
	_sleep(PauseTime);

	cout << " <Copied";
	color(hConsole, 9);
	cout << " stagelabels";
	color(hConsole, 15);
	cout << "> " << char(175);
	Message = " Modificate list detail students [Y/n] ";
	for (size_t i = 0; i < Message.size(); i++) {
		cout << Message[i]; _sleep(PauseTime / 10);
	}

	cin >> OptionSelective;

	if (toupper(OptionSelective[0]) != 'Y') {
		return;
	}
	system("cls");
	LogoGenius();
	int t;
	for (int i = 0; i < StudentsDoubleList->getSize(); i++) {
		if (User->getStudentID() == StudentsDoubleList->ObtainIndex(i)->getStudentID()) {
			t = i;
		}
	}

	cout << " #_ Loading, please wait..." << endl << endl; _sleep(PauseTime * 5);
	cout << " [ 2.201060524] sd 0:0:0:0:0ddbu22 [Upc] Assuming drive cache: write through" << endl; _sleep(PauseTime);
	cout << " Valid path for Overwrite User." << endl << endl; _sleep(PauseTime);

	color(hConsole, 10);
	cout << " Started:";
	color(hConsole, 15);
	cout << "  Attempting to overwrite Intranet fuse file" << endl; _sleep(PauseTime);
	cout << " See 'systemctm status: 'runIntraware//fuse.mount'' for details" << endl << endl; _sleep(PauseTime);

	cout << " [ 0.000000] init_memory_mapping: [mem " << &StudentsDoubleList << "-" << StudentsDoubleList->ObtainEnd() << "]" << endl; _sleep(PauseTime);
	cout << " [ 1.169734] [mem " << &StudentsTable << "-" << &User << "]" << endl << endl; _sleep(PauseTime);

	cout << " area 1 status: ";
	color(hConsole, 10);
	cout << "OK";
	color(hConsole, 15);
	cout << "  UPC" << t << "-vr (FirstName) : " << User->getFirstName() << endl; _sleep(PauseTime);
	cout << " area 2 status: ";
	color(hConsole, 10);
	cout << "OK";
	color(hConsole, 15);
	cout << "  UPC" << t << "-vr (SecondName): " << User->getSecondName() << endl; _sleep(PauseTime);
	cout << " area 3 status: ";
	color(hConsole, 10);
	cout << "OK";
	color(hConsole, 15);
	cout << "  UPC" << t << "-vr (LastName) : " << User->getLastName() << endl; _sleep(PauseTime);
	cout << " area 4 status: ";
	color(hConsole, 10);
	cout << "OK";
	color(hConsole, 15);
	cout << "  UPC" << t << "-vr (MLastName): " << User->getMothersLastName() << endl; _sleep(PauseTime);
	cout << " area 5 status: ";
	color(hConsole, 10);
	cout << "OK";
	color(hConsole, 15);
	cout << "  UPC" << t << "-vr (Old-Age): " << User->getOldAge() << endl; _sleep(PauseTime);
	cout << " area 6 status: ";
	color(hConsole, 10);
	cout << "OK";
	color(hConsole, 15);
	cout << "  UPC" << t << "-vr (Password) : " << User->getPassword() << endl; _sleep(PauseTime);
	cout << " area 7 status: ";
	color(hConsole, 10);
	cout << "OK";
	color(hConsole, 15);
	cout << "  UPC" << t << "-vr (Courses) : " << User->getCourseList()->getSize() << endl; _sleep(PauseTime);
	cout << " status: ";
	color(hConsole, 10);
	cout << "OK";
	color(hConsole, 15);
	cout << "  found INTRANET HT-table mapped at [mem " << &StudentsTree << "-" << &User << "]" << endl << endl; _sleep(PauseTime);

	do {
		cout << " Edit Mounted area "; cin >> Selection;
	} while (Selection < 1 && Selection > 6);

	if (Selection == 1) {
		string FirstName;
		cout << " [ " << &FirstName << "] NewVariable: FirstName = "; cin >> FirstName;
		User->setFirstName(FirstName);
		cout << " Overwriting initrd memory" << endl << endl;
	}
	else
		if (Selection == 2) {
			string SecondName;
			cout << " [ " << &SecondName << "] NewVariable: SecondName = "; cin >> SecondName;
			User->setSecondName(SecondName);
			cout << " Overwriting initrd memory" << endl << endl;
		}
		else
			if (Selection == 3) {
				string LastName;
				cout << " [ " << &LastName << "] NewVariable: LastName = "; cin >> LastName;
				User->setLastName(LastName);
				cout << " Overwriting initrd memory" << endl << endl;
			}
			else
				if (Selection == 4) {
					string MothersLastName;
					cout << " [ " << &MothersLastName << "] NewVariable: MLastName = "; cin >> MothersLastName;
					User->setMothersLastName(MothersLastName);
					cout << " Overwriting initrd memory" << endl << endl;
				}
				else
					if (Selection == 5) {
						int OldAge;
						cout << " [ " << &OldAge << "] NewVariable: Old-Age = "; cin >> OldAge;
						User->setOldAge(OldAge);
						cout << " Overwriting initrd memory" << endl << endl;
					}
					else
						if (Selection == 6) {
							string Password;
							cout << " [ " << &Password << "] NewVariable: Password = "; cin >> Password;
							User->setPassword(Password);
							cout << " Overwriting initrd memory" << endl << endl;
						}
						else
							if (Selection == 7) {
								if (User->getCourseList()->getSize() == 0) {
									cout << endl << " ERROR: You ain't got any Courses" << endl << endl;
								}
								else {
									string Password;
									for (size_t i = 0; i < User->getCourseList()->getSize(); i++) {
										cout << " course " << i + 1 << " status: ";
										color(hConsole, 10);
										cout << "OK";
										color(hConsole, 15);
										cout << "  [ ";
										if (User->getCourseList()->ObtainIndex(i)->getCampus() == "Monterrico") {
											color(hConsole, 4);
										}
										else
											if (User->getCourseList()->ObtainIndex(i)->getCampus() == "San Isidro") {
												color(hConsole, 9);
											}
											else
												if (User->getCourseList()->ObtainIndex(i)->getCampus() == "Villa") {
													color(hConsole, 2);
												}
												else
													if (User->getCourseList()->ObtainIndex(i)->getCampus() == "San Miguel") {
														color(hConsole, 8);
													}
										cout << User->getCourseList()->ObtainIndex(i)->getCourseSection();
										color(hConsole, 15);
										cout << " ] USER-vr(CourseName) = " << User->getCourseList()->ObtainIndex(i)->getCourseName() << endl;

										_sleep(PauseTime);
									}
									do {
										cout << endl << " Remove Mounted area ";
										cin >> Selection;
									} while (Selection<1 || Selection>User->getCourseList()->getSize());
									cout << endl << " [ " << &User->getCourseList()->ObtainIndex(Selection - 1)->getCourseSection() << "]  delete : User->getCourseList()->RemoveIndex(" << Selection - 1 << ")";
									cout << endl << " Overwriting initrd memory" << endl << endl;

									User->setCredits(User->getCredits() + User->getCourseList()->ObtainIndex(Selection - 1)->getCreditWeight());
									User->getCourseList()->RemoveIndex(Selection - 1);

									CoverterTotxt = User->getStudentID() + ".txt";

									FileWriter.open(CoverterTotxt, ios::out);
									if (FileWriter.is_open()) {
										FileWriter << User->getCourseList()->getSize() << endl;
										RecursiveWriterTxtCourseFile(0, User->getCourseList()->getSize() - 1);

										FileWriter << endl << User->getNotificationHeap()->getSize();
										if (User->getNotificationHeap()->getSize() > 0) {
											FileWriter << endl;
											RecursiveWriterTxtNotificationFile(0, User->getNotificationHeap()->getSize() - 1);
										}

										FileWriter.close();
									}
								}
							}

	cout << " Overwriting area " << Selection << " for overwrite variable corruption" << endl; _sleep(PauseTime);
	cout << " Monitoring of Crehana file... ng dmeventd or progress overwriting." << endl; _sleep(PauseTime);
	cout << " init_memory_mapping: [mem " << &StudentsTree << "-" << StudentsDoubleList->ObtainEnd() << "]" << endl << endl; _sleep(PauseTime);

	cout << " Mounted variable Chehaware: user edited:" << endl << endl << endl; _sleep(PauseTime);

	for (size_t i = 0; i < 45; i++)
	{
		cout << " -"; _sleep(PauseTime);
	}

	FileWriter.open("Students.txt", ios::out);
	if (FileWriter.is_open()) {

		FileWriter << StudentsDoubleList->getSize() << endl;

		RecursiveWriterTxtStudentFile(0, StudentsDoubleList->getSize() - 1);

		FileWriter.close();
	}
}
void UPC::DisplayUserCalendar() {
	cout << "  " << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(187) << " " << char(219) << char(219) << char(219) << char(219) << char(219) << char(187) << " " << char(219) << char(219) << char(187) << "     " << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(187) << char(219) << char(219) << char(219) << char(187) << "   " << char(219) << char(219) << char(187) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(187) << "  " << char(219) << char(219) << char(219) << char(219) << char(219) << char(187) << " " << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(187) << endl;
	cout << " " << char(219) << char(219) << char(201) << char(205) << char(205) << char(205) << char(205) << char(188) << char(219) << char(219) << char(201) << char(205) << char(205) << char(219) << char(219) << char(187) << char(219) << char(219) << char(186) << "     " << char(219) << char(219) << char(201) << char(205) << char(205) << char(205) << char(205) << char(188) << char(219) << char(219) << char(219) << char(219) << char(187) << "  " << char(219) << char(219) << char(186) << char(219) << char(219) << char(201) << char(205) << char(205) << char(219) << char(219) << char(187) << char(219) << char(219) << char(201) << char(205) << char(205) << char(219) << char(219) << char(187) << char(219) << char(219) << char(201) << char(205) << char(205) << char(219) << char(219) << char(187) << endl;
	cout << " " << char(219) << char(219) << char(186) << "     " << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(186) << char(219) << char(219) << char(186) << "     " << char(219) << char(219) << char(219) << char(219) << char(219) << char(187) << "  " << char(219) << char(219) << char(201) << char(219) << char(219) << char(187) << " " << char(219) << char(219) << char(186) << char(219) << char(219) << char(186) << "  " << char(219) << char(219) << char(186) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(186) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(201) << char(188) << endl;
	cout << " " << char(219) << char(219) << char(186) << "     " << char(219) << char(219) << char(201) << char(205) << char(205) << char(219) << char(219) << char(186) << char(219) << char(219) << char(186) << "     " << char(219) << char(219) << char(201) << char(205) << char(205) << char(188) << "  " << char(219) << char(219) << char(186) << char(200) << char(219) << char(219) << char(187) << char(219) << char(219) << char(186) << char(219) << char(219) << char(186) << "  " << char(219) << char(219) << char(186) << char(219) << char(219) << char(201) << char(205) << char(205) << char(219) << char(219) << char(186) << char(219) << char(219) << char(201) << char(205) << char(205) << char(219) << char(219) << char(187) << endl;
	cout << " " << char(200) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(187) << char(219) << char(219) << char(186) << "  " << char(219) << char(219) << char(186) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(187) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(187) << char(219) << char(219) << char(186) << " " << char(200) << char(219) << char(219) << char(219) << char(219) << char(186) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(201) << char(188) << char(219) << char(219) << char(186) << "  " << char(219) << char(219) << char(186) << char(219) << char(219) << char(186) << "  " << char(219) << char(219) << char(186) << endl;
	cout << "  " << char(200) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(200) << char(205) << char(188) << "  " << char(200) << char(205) << char(188) << char(200) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(188) << char(200) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(188) << char(200) << char(205) << char(188) << "  " << char(200) << char(205) << char(205) << char(205) << char(188) << char(200) << char(205) << char(205) << char(205) << char(205) << char(205) << char(188) << " " << char(200) << char(205) << char(188) << "  " << char(200) << char(205) << char(188) << char(200) << char(205) << char(188) << "  " << char(200) << char(205) << char(188) << endl << endl;

	RecursiveDisplayUserCalendar(0, 15);
	cin.get();
}
void UPC::DisplayUPCCourses() {
	RecursiveDisplayCourse(0, Courses->getSize() - 1, 'C');

	do {
		cout << " get source course ";
		cin >> Selection;
	} while (Selection < 1 || Selection > Courses->getSize());
	Selection--;

	cout << "                             "; _sleep(PauseTime / 10);
	for (int i = 0; i < 20; i++)
		cout << char(220);
	cout << endl; _sleep(PauseTime / 10);
	cout << "                             " << char(219) << "                  " << char(219) << endl; _sleep(PauseTime / 10);
	cout << "                             " << char(219) << "     Section:     " << char(219) << endl; _sleep(PauseTime / 10);
	cout << "                             " << char(219) << "                  " << char(219) << endl; _sleep(PauseTime / 10);
	cout << "                             " << char(219) << "       " << Courses->ObtainIndex(Selection).getCourseSection() << "       " << char(219) << endl; _sleep(PauseTime / 10);
	cout << "                             " << char(219) << "                  " << char(219) << endl; _sleep(PauseTime / 10);
	cout << "                             ";
	for (int i = 0; i < 20; i++)
		cout << char(223);
	cout << endl; _sleep(PauseTime / 10);
	cout << "                                   " << char(186) << "      " << char(186) << endl; _sleep(PauseTime / 10);
	cout << "                                   " << char(186) << "      " << char(186) << endl; _sleep(PauseTime / 10);
	cout << "                                   " << char(186) << "      " << char(186) << endl; _sleep(PauseTime / 10);
	cout << "                                   " << char(186) << "      " << char(186) << endl; _sleep(PauseTime / 10);
	cout << "                                   " << char(186) << "      " << char(186) << endl; _sleep(PauseTime / 10);
	cout << "                                   " << char(186) << "      " << char(186) << endl; _sleep(PauseTime / 10);
	cout << "      ";
	for (int i = 0; i < 20; i++)
		cout << char(220);
	cout << "         " << char(186) << "      " << char(186) << "         "; _sleep(PauseTime / 10);
	for (int i = 0; i < 20; i++)
		cout << char(220);
	cout << endl; _sleep(PauseTime / 10);
	cout << "      " << char(219) << "                  " << char(219) << "         " << char(186) << "      " << char(186) << "         " << char(219) << "                  " << char(219) << endl; _sleep(PauseTime / 10);
	cout << "      " << char(219) << "       Day:       " << char(219) << "         " << char(186) << "      " << char(186) << "         " << char(219) << "     Schedule:    " << char(219) << endl; _sleep(PauseTime / 10);
	cout << "      " << char(219) << "                  " << char(219) << " " << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(188) << "      " << char(200) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << " " << char(219) << "                  " << char(219) << endl; _sleep(PauseTime / 10);
	cout << "      " << char(219); _sleep(PauseTime / 10);

	if (Courses->ObtainIndex(Selection).getEnrollment().getSessionDay().size() == 9) {
		cout << "     " << Courses->ObtainIndex(Selection).getEnrollment().getSessionDay() << "    ";
	}
	else
		if (Courses->ObtainIndex(Selection).getEnrollment().getSessionDay().size() == 8) {
			cout << "     " << Courses->ObtainIndex(Selection).getEnrollment().getSessionDay() << "     ";
		}
		else
			if (Courses->ObtainIndex(Selection).getEnrollment().getSessionDay().size() == 7) {
				cout << "      " << Courses->ObtainIndex(Selection).getEnrollment().getSessionDay() << "     ";
			}
			else
				if (Courses->ObtainIndex(Selection).getEnrollment().getSessionDay().size() == 6) {
					cout << "      " << Courses->ObtainIndex(Selection).getEnrollment().getSessionDay() << "      ";
				}
	_sleep(PauseTime / 10);
	cout << char(219) << "                          " << char(219) << "   " << Courses->ObtainIndex(Selection).getEnrollment().getEnrollmentTime().getStartTime() << "--" << Courses->ObtainIndex(Selection).getEnrollment().getEnrollmentTime().getFinishTime() << "   " << char(219) << endl; _sleep(PauseTime / 10);
	cout << "      " << char(219) << "                  " << char(219) << "                          " << char(219) << "                  " << char(219) << endl; _sleep(PauseTime / 10);
	cout << "      "; _sleep(PauseTime / 10);
	for (int i = 0; i < 20; i++)
		cout << char(223);
	cout << "                          "; _sleep(PauseTime / 10);
	for (int i = 0; i < 20; i++)
		cout << char(223);
	cout << endl << endl; _sleep(PauseTime / 10);

	cout << " enroll in the course: [Y/n] ";
	cin >> OptionSelective;

	if (toupper(OptionSelective.at(0)) != 'Y') {
		return;
	}

	if (User->getCourseList()->getSize() > 0) {
		RecursiveCourseEnrollment(0, User->getCourseList()->getSize() - 1);
	}
	else {
		User->setCredits(User->getCredits() - Courses->ObtainIndex(Selection).getCreditWeight());
		User->getCourseList()->AddToEnd(new Course(Courses->ObtainIndex(Selection).getCourseName(), Courses->ObtainIndex(Selection).getCourseSection(), Courses->ObtainIndex(Selection).getEnrollment().getSessionDay(), Courses->ObtainIndex(Selection).getEnrollment().getEnrollmentTime().getStartTime(), Courses->ObtainIndex(Selection).getEnrollment().getEnrollmentTime().getFinishTime(), Courses->ObtainIndex(Selection).getCreditWeight(), Courses->ObtainIndex(Selection).getCampus(), Courses->ObtainIndex(Selection).getModality()));
		User->getNotificationHeap()->Push(Notification(Courses->ObtainIndex(Selection).getCourseName()));

		CoverterTotxt = User->getStudentID() + ".txt";

		FileWriter.open(CoverterTotxt, ios::out);
		if (FileWriter.is_open()) {
			FileWriter << User->getCourseList()->getSize() << endl;
			RecursiveWriterTxtCourseFile(0, User->getCourseList()->getSize() - 1);

			FileWriter << endl << User->getNotificationHeap()->getSize();
			if (User->getNotificationHeap()->getSize() > 0) {
				FileWriter << endl;
				RecursiveWriterTxtNotificationFile(0, User->getNotificationHeap()->getSize() - 1);
			}

			FileWriter.close();
		}

		FileWriter.open("Students.txt", ios::out);
		if (FileWriter.is_open()) {

			FileWriter << StudentsDoubleList->getSize() << endl;

			RecursiveWriterTxtStudentFile(0, StudentsDoubleList->getSize() - 1);

			FileWriter.close();
		}
	}
}
void UPC::DisplayUserNotification() {
	if (User->getNotificationHeap()->getSize() == 0) {
		cout << " ERROR: You ain't got notifications";
	}
	else {
		cout << "     _   ______  _____________________________  ______________  _   _______" << endl;
		cout << "    / | / / __ " << char(92) << "/_  __/  _/ ____/  _/ ____/   |/_  __/  _/ __ " << char(92) << "/ | / / ___/" << endl;
		cout << "   /  |/ / / / / / /  / // /_   / // /   / /| | / /  / // / / /  |/ /" << char(92) << "__ " << char(92) << " " << endl;
		cout << "  / /|  / /_/ / / / _/ // __/ _/ // /___/ ___ |/ / _/ // /_/ / /|  /___/ / " << endl;
		cout << " /_/ |_/" << char(92) << "____/ /_/ /___/_/   /___/" << char(92) << "____/_/  |_/_/ /___/" << char(92) << "____/_/ |_//____/  " << endl << endl;

		cout << "               Notification         " << endl;
		cout << "     _______________|_______________" << endl;
		cout << "     |                             |" << endl;
		cout << "     |                             |" << endl;
		cout << "     |                             |" << endl;
		cout << "  You got                       In the" << endl;
		cout << "   a new                        course" << endl;
		cout << " Enrrolment" << "                    " << User->getNotificationHeap()->Peek().getName() << endl;

		User->getNotificationHeap()->Pop();
		cin.get();

		CoverterTotxt = User->getStudentID() + ".txt";

		FileWriter.open(CoverterTotxt, ios::out);
		if (FileWriter.is_open()) {
			FileWriter << User->getCourseList()->getSize();
			if (User->getCourseList()->getSize() > 0) {
				FileWriter << endl;
				RecursiveWriterTxtCourseFile(0, User->getCourseList()->getSize() - 1);
			}
		}

		FileWriter << endl << User->getNotificationHeap()->getSize();
		if (User->getNotificationHeap()->getSize() > 0) {
			FileWriter << endl;
			RecursiveWriterTxtNotificationFile(0, User->getNotificationHeap()->getSize() - 1);
		}
		FileWriter.close();
	}
}

void UPC::RecursiveReaderTxtUPCDataSet(size_t Iter, int Limitation, char ClassType, SimpleCircularLinkedList<string>& DataSet) {
	/// [   RECURSION LIMITATION   ]
	if (Iter > Limitation) {
		return;
	}
	/// [   RECURSION LIMITATION   ]


	/// [   STUDENT-DATA VARIABLES   ]
	string Name;
	string LastName;
	/// [   STUDENT-DATA VARIABLES   ]


	if (ClassType == 'L') {
		/// [   UPC LAST-NAME READING   ]
		getline(FileIO, LastName);
		/// [   UPC LAST-NAME READING   ]


		/// [   LAST-NAME CREATOR   ]
		DataSet.AddToEnd(LastName);
		/// [   LAST-NAME CREATOR   ]
	}
	else
		if (ClassType == 'N') {
			/// [   UPC NAME READING   ]
			getline(FileIO, Name);
			/// [   UPC NAME READING   ]


			/// [   NAME CREATOR   ]
			DataSet.AddToEnd(Name);
			/// [   NAME CREATOR   ]
		}


	/// [   RECURSION   ]
	RecursiveReaderTxtUPCDataSet(Iter + 1, Limitation, ClassType, DataSet);
	/// [   RECURSION   ]
}
void UPC::RecursiveReaderTxtCourseFile(size_t Iter, int Limitation, char ClassType) {
	/// [   RECURSION LIMITATION   ]
	if (Iter > Limitation) {
		return;
	}
	/// [   RECURSION LIMITATION   ]


	/// [   COURSE-RELATED VARIABLES   ]
	string CourseName;
	string CourseSection;
	string SessionDay;
	string StartTime;
	string FinishTime;
	string Weight;
	string Campus;
	string Modality;
	/// [   COURSE-RELATED VARIABLES   ]


	/// [   CLASS SELECTION   ]
	if (ClassType == 'C') {
		if (RestartSystem == true && Iter == 0) {
			cout << "              Starting Load/Save Random Seed... " << endl; _sleep(PauseTime);
		}


		/// [   CREHANA COURSE-DATA READING   ]
		getline(FileIO, CourseName);
		getline(FileIO, CourseSection);
		getline(FileIO, SessionDay);
		getline(FileIO, StartTime);
		getline(FileIO, FinishTime);
		getline(FileIO, Weight);
		getline(FileIO, Campus);
		getline(FileIO, Modality);
		/// [   CREHANA COURSE-DATA READING   ]


		if (RestartSystem == true && Iter == 0) {
			cout << "              Starting Objects Construction System... " << endl << endl; _sleep(PauseTime);
		}

		/// [   COURSE CREATOR   ]
		Courses->AddToEnd(Course(CourseName, CourseSection, SessionDay, StartTime, FinishTime, stoi(Weight), Campus, Modality));
		/// [   COURSE CREATOR   ]
	}
	else
		if (ClassType == 'S') {

			/// [   STUDENT COURSE-DATA READING   ]
			getline(FileReader, CourseName);
			getline(FileReader, CourseSection);
			getline(FileReader, SessionDay);
			getline(FileReader, StartTime);
			getline(FileReader, FinishTime);
			getline(FileReader, Weight);
			getline(FileReader, Campus);
			getline(FileReader, Modality);
			/// [   STUDENT COURSE-DATA READING   ]


			/// [   COURSE CREATOR   ]
			StudentsDoubleList->ObtainEnd()->getCourseList()->AddToEnd(new Course(CourseName, CourseSection, SessionDay, StartTime, FinishTime, stoi(Weight), Campus, Modality));
			/// [   COURSE CREATOR   ]
		}
	/// [   CLASS SELECTION   ]


	/// [   RECURSION   ]
	RecursiveReaderTxtCourseFile(Iter + 1, Limitation, ClassType);
	/// [   RECURSION   ]
}
void UPC::RecursiveReaderTxtPersonFile(size_t Iter, int Limitation, char ClassType) {
	/// [   RECURSION LIMITATION   ]
	if (Iter > Limitation) {
		return;
	}
	/// [   RECURSION LIMITATION   ]


	/// [   PERSON-RELATED VARIABLES   ]
	string FirstName;
	string SecondName;
	string LastName;
	string MothersLastName;
	string OldAge;
	/// [   PERSON-RELATED VARIABLES   ]


	/// [   CLASS SELECTION   ]
	if (ClassType == 'T') {
	}
	else
		if (ClassType == 'S') {
			/// [   STUDENT-RELATED VARIABLES   ]
			string StudentID;
			string Credits;
			string Password;
			/// [   STUDENT-RELATED VARIABLES   ]

			/// [   STUDENT-DATA INPUT   ]
			getline(FileIO, FirstName);
			getline(FileIO, SecondName);
			getline(FileIO, LastName);
			getline(FileIO, MothersLastName);
			getline(FileIO, OldAge);
			getline(FileIO, StudentID);
			getline(FileIO, Credits);
			getline(FileIO, Password);
			/// [   STUDENT-DATA INPUT   ]
			if (RestartSystem == true && Iter == Limitation) {
				color(hConsole, 10);
				cout << " [   OK   ]";
				color(hConsole, 15);
				cout << "   Started Read File System." << endl << endl; _sleep(PauseTime);

				color(hConsole, 10);
				cout << " [   OK   ]";
				color(hConsole, 15);
				cout << "   Started Load/Save Random Seed." << endl << endl; _sleep(PauseTime);
			}

			/// [   STUDENT CREATOR   ]
			StudentsDoubleList->AddToEnd(new Student(FirstName, SecondName, LastName, MothersLastName, stoi(OldAge), StudentID, stoi(Credits), Password));
			StudentsTree->Add(new Student(FirstName, SecondName, LastName, MothersLastName, stoi(OldAge), StudentID, stoi(Credits), Password));
			/// [   STUDENT CREATOR   ]
			if (RestartSystem == true && Iter == Limitation) {
				color(hConsole, 10);
				cout << " [   OK   ]";
				color(hConsole, 15);
				cout << "   Started Objects Construction System." << endl << endl << endl; _sleep(PauseTime);
			}


			/// [   USER-ID TXT CONVERTER   ]
			CoverterTotxt = StudentID + ".txt";
			/// [   USER-ID TXT CONVERTER   ]


			/// [   USER FILE OPENDED   ]
			FileReader.open(CoverterTotxt, ios::in);
			/// [   USER FILE OPENDED   ]


			/// [   USER FILE VIEWER   ]
			if (FileReader.is_open()) {
				/// [   OBJECT QUANTITY INPUT   ]
				getline(FileReader, ObjectQuantity);
				/// [   OBJECT QUANTITY INPUT   ]


				/// [   COURSE RETRIEVAL   ]
				if (stoi(ObjectQuantity) != 0) {
					RecursiveReaderTxtCourseFile(0, stoi(ObjectQuantity) - 1, 'S');
				}
				/// [   COURSE RETRIEVAL   ]

				/// [   OBJECT QUANTITY INPUT   ]
				getline(FileReader, ObjectQuantity);
				/// [   OBJECT QUANTITY INPUT   ]


				/// [   NOTIFICATION RETRIEVAL   ]
				if (stoi(ObjectQuantity) != 0) {
					RecursiveReaderTxtNotificationFile(0, stoi(ObjectQuantity) - 1);
				}
				/// [   NOTIFICATION RETRIEVAL   ]

				/// [   USER FILE CLOSED   ]
				FileReader.close();
				/// [   USER FILE CLOSED   ]
			}
			/// [   USER FILE VIEWER   ]
		}
	/// [   CLASS SELECTION   ]


	/// [   RECURSION   ]
	RecursiveReaderTxtPersonFile(Iter + 1, Limitation, ClassType);
	/// [   RECURSION   ]
}
void UPC::RecursiveReaderTxtNotificationFile(size_t Iter, int Limitation) {
	/// [   RECURSION LIMITATION   ]
	if (Iter > Limitation) {
		return;
	}
	/// [   RECURSION LIMITATION   ]


	/// [   DIPLOMA-RELATED VARIABLES   ]
	string Name;
	/// [   DIPLOMA-RELATED VARIABLES   ]


	/// [   DIPLOMA-DATA READING   ]
	getline(FileReader, Name);
	/// [   DIPLOMA-DATA READING   ]


	/// [   DIPLOMA CREATOR   ]
	StudentsDoubleList->ObtainEnd()->getNotificationHeap()->Push(Notification(Name));
	/// [   DIPLOMA CREATOR   ]


	/// [   RECURSION   ]
	RecursiveReaderTxtNotificationFile(Iter + 1, Limitation);
	/// [   RECURSION   ]
}

void UPC::RecursiveWriterTxtCourseFile(size_t Iter, size_t Limitation) {
	/// [   RECURSION LIMITATION   ]
	if (Iter > Limitation) {
		return;
	}
	/// [   RECURSION LIMITATION   ]


	/// [   USER COURSE-DATA WRITING   ]
	FileWriter << User->getCourseList()->ObtainIndex(Iter)->getCourseName() << endl;
	FileWriter << User->getCourseList()->ObtainIndex(Iter)->getCourseSection() << endl;
	FileWriter << User->getCourseList()->ObtainIndex(Iter)->getEnrollment().getSessionDay() << endl;
	FileWriter << User->getCourseList()->ObtainIndex(Iter)->getEnrollment().getEnrollmentTime().getStartTime() << endl;
	FileWriter << User->getCourseList()->ObtainIndex(Iter)->getEnrollment().getEnrollmentTime().getFinishTime() << endl;
	FileWriter << User->getCourseList()->ObtainIndex(Iter)->getCreditWeight() << endl;
	FileWriter << User->getCourseList()->ObtainIndex(Iter)->getCampus() << endl;
	FileWriter << User->getCourseList()->ObtainIndex(Iter)->getModality();
	/// [   USER COURSE-DATA WRITING   ]


	/// [   LINE BREAK   ]
	if (Iter != Limitation) {
		FileWriter << endl;
	}
	/// [   LINE BREAK   ]


	/// [   RECURSION   ]
	RecursiveWriterTxtCourseFile(Iter + 1, Limitation);
	/// [   RECURSION   ]
}
void UPC::RecursiveWriterTxtStudentFile(size_t Iter, size_t Limitation) {
	/// [   RECURSION LIMITATION   ]
	if (Iter > Limitation) {
		return;
	}
	/// [   RECURSION LIMITATION   ]


	/// [   STUDENTS-DATA WRITING   ]
	FileWriter << StudentsDoubleList->ObtainIndex(Iter)->getFirstName() << endl;
	FileWriter << StudentsDoubleList->ObtainIndex(Iter)->getSecondName() << endl;
	FileWriter << StudentsDoubleList->ObtainIndex(Iter)->getLastName() << endl;
	FileWriter << StudentsDoubleList->ObtainIndex(Iter)->getMothersLastName() << endl;
	FileWriter << StudentsDoubleList->ObtainIndex(Iter)->getOldAge() << endl;
	FileWriter << StudentsDoubleList->ObtainIndex(Iter)->getStudentID() << endl;
	FileWriter << StudentsDoubleList->ObtainIndex(Iter)->getCredits() << endl;
	FileWriter << StudentsDoubleList->ObtainIndex(Iter)->getPassword();
	/// [   STUDENTS-DATA WRITING   ]


	/// [   LINE BREAK   ]
	if (Iter != Limitation) {
		FileWriter << endl;
	}
	/// [   LINE BREAK   ]


	/// [   RECURSION   ]
	RecursiveWriterTxtStudentFile(Iter + 1, Limitation);
	/// [   RECURSION   ]
}
void UPC::RecursiveWriterTxtNotificationFile(size_t Iter, int Limitation) {
	/// [   RECURSION LIMITATION   ]
	if (Iter > Limitation) {
		return;
	}
	/// [   RECURSION LIMITATION   ]


	/// [   USER NOTIFICATION-DATA WRITING   ]
	FileWriter << User->getNotificationHeap()->getHeapNode(Iter)->getObject().getName();
	/// [   USER NOTIFICATION-DATA WRITING   ]


	/// [   LINE BREAK   ]
	if (Iter != Limitation) {
		FileWriter << endl;
	}
	/// [   LINE BREAK   ]


	/// [   RECURSION   ]
	RecursiveWriterTxtNotificationFile(Iter + 1, Limitation);
	/// [   RECURSION   ]
}

void UPC::RecursiveDisplayCourse(size_t Iter, size_t Limitation, char ClassType) {
	if (Iter > Limitation)
		return;

	if (ClassType == 'C') {
		cout << " " << char(201);
		for (size_t i = 0; i < 12 + Courses->ObtainIndex(Iter).getCourseName().size(); i++)
			cout << char(205);

		cout << char(187) << endl; _sleep(PauseTime / 10);


		cout << " " << char(186) << "      " << Courses->ObtainIndex(Iter).getCourseName() << "      " << char(186) << endl;


		cout << " " << char(186) << "      ";
		for (int i = 0; i < Courses->ObtainIndex(Iter).getCourseName().size(); i++)
			cout << " ";


		cout << "      " << char(186) << endl; _sleep(PauseTime / 10);


		cout << " " << char(186) << "      ";
		for (int i = 1; i < (Courses->ObtainIndex(Iter).getCourseName().size() / 2) - 1; i++)
			cout << " ";

		cout << Courses->ObtainIndex(Iter).getCourseSection();
		for (int i = 0; i < (Courses->ObtainIndex(Iter).getCourseName().size() / 2) - 1; i++)
			if (Courses->ObtainIndex(Iter).getCourseName().size() % 2 == 0) {
				if (i > 0)
					cout << " ";
			}
			else
				cout << " ";
		cout << "      " << char(186);

		cout << endl;
		cout << " " << char(200);
		for (size_t i = 0; i < 12 + Courses->ObtainIndex(Iter).getCourseName().size(); i++)
			cout << char(205);

		cout << char(188);
		cout << endl; _sleep(PauseTime / 10);


		for (int i = 1; i < (Courses->ObtainIndex(Iter).getCourseName().size() / 2); i++)
			cout << " ";

		cout << "       |" << Iter + 1 << "|" << endl << endl; _sleep(PauseTime / 10);
	}
	else
		if (ClassType == 'S') {
			cout << " " << char(201) << char(205);
			for (int i = 0; i < User->getCourseList()->ObtainIndex(Iter)->getCourseName().size(); i++)
				cout << char(205);

			cout << char(205) << char(187);

			cout << endl; _sleep(PauseTime / 10);

			cout << " " << char(186) << " " << User->getCourseList()->ObtainIndex(Iter)->getCourseName() << " " << char(186) << " |" << Iter + 1 << "|";

			cout << endl; _sleep(PauseTime / 10);

			cout << " " << char(200) << char(205);
			for (int i = 0; i < User->getCourseList()->ObtainIndex(Iter)->getCourseName().size(); i++)
				cout << char(205);

			cout << char(205) << char(188);
			cout << endl; _sleep(PauseTime / 10);
		}
	RecursiveDisplayCourse(Iter + 1, Limitation, ClassType);
}
void UPC::RecursiveDisplayStudentsAccount(size_t Iter, size_t Limitation) {
	/// [   RECURSION LIMITATION   ]
	if (Iter > Limitation)
		return;
	/// [   RECURSION LIMITATION   ]

	if (Iter == 0) {
		cout << " root trace recruited accounts "; Message = "power:/\n\n\n";
		for (string::iterator i = Message.begin(); i != Message.end(); ++i)
			cout << i.operator*();
	}
	Message = "";

	cout << " " << Iter + 1 << "    [" << StudentsDoubleList->ObtainIndex(Iter)->getFirstName() << "." << StudentsDoubleList->ObtainIndex(Iter)->getLastName().at(0);

	for (size_t i = StudentsDoubleList->ObtainIndex(Iter)->getFirstName().size() + 2; i < 15; i++) {
		cout << " ";
	}
	cout << StudentsDoubleList->ObtainIndex(Iter)->getStudentID() << "     ";


	int step = 1;
	for (DoubleCircularLinkedList<Student*>::Iterator i = StudentsDoubleList->begin(); i != StudentsDoubleList->end(); ++i) {
		if (i.Index != Iter)
			if (StudentsDoubleList->ObtainIndex(Iter)->getLastName() > StudentsDoubleList->ObtainIndex(i.Index)->getLastName())
				step++;
	}

	for (size_t i = 0; i < ((100 * step) / StudentsDoubleList->getSize()) / 2; i++)
		Message += char(179);

	color(hConsole, 10);
	for (size_t i = 0; i < Message.size() / 2; i++) {
		cout << Message[i];
	}
	for (size_t i = Message.size() / 2; i < Message.size(); i++) {
		cout << Message[i]; _sleep(PauseTime / 10);
	}


	color(hConsole, 15);
	for (size_t i = ((100 * step) / StudentsDoubleList->getSize()) / 2; i < 50; i++) {
		cout << " ";
	}

	cout << "]" << endl << endl;
	/// [   RECURSION   ]
	RecursiveDisplayStudentsAccount(Iter + 1, Limitation);
	/// [   RECURSION   ]
}
void UPC::RecursiveDisplayUserCalendar(size_t Iter, size_t Limitation) {
	if (Iter == 0) {
		cout << " " << char(201);
		for (size_t i = 0; i < 6; i++)
		{
			if (i != 0) {
				cout << char(203);
			}
			for (size_t j = 0; j < 13; j++)
			{
				cout << char(205);
			}
			if (i == 5) {
				cout << char(187);
			}
		}
		cout << endl; _sleep(PauseTime / 10);
		cout << " " << char(186);
		cout << "  Time/Day   ";
		cout << char(186);
		cout << "      M      ";
		cout << char(186);
		cout << "      T      ";
		cout << char(186);
		cout << "      W      ";
		cout << char(186);
		cout << "      T      ";
		cout << char(186);
		cout << "      F      ";
		cout << char(186);
		cout << endl; _sleep(PauseTime / 10);
		cout << " " << char(204);
		for (size_t i = 0; i < 6; i++)
		{
			if (i != 0) {
				cout << char(206);
			}
			for (size_t j = 0; j < 13; j++)
			{
				cout << char(205);
			}
			if (i == 5) {
				cout << char(185);
			}
		}
		cout << endl; _sleep(PauseTime / 10);
	}
	if (Iter > Limitation) {
		return;
	}

	if (Iter > 0) {
		cout << endl; _sleep(PauseTime / 10);
	}
	cout << " " << char(186);
	if (Iter < 2) {
		cout << " 0" << 7 + Iter << ":00-0" << 7 + Iter + 1 << ":00 ";
	}
	else if (Iter == 2) {
		cout << " 0" << 7 + Iter << ":00-" << 7 + Iter + 1 << ":00 ";
	}
	else if (Iter > 2) {
		cout << " " << 7 + Iter << ":00-" << 7 + Iter + 1 << ":00 ";
	}

	string days[] = { "Lunes","Martes","Miercoles","Jueves","Viernes" };

	for (size_t j = 0; j < 5; j++)
	{
		if (User->getCourseList()->getSize() > 0) {
			if (Iter < 2) {
				for (size_t t = 0; t < User->getCourseList()->getSize(); t++)
				{
					if (User->getCourseList()->ObtainIndex(t)->getEnrollment().getSessionDay() == days[j] && (User->getCourseList()->ObtainIndex(t)->getEnrollment().getEnrollmentTime().getStartTime() == "0" + to_string(7 + Iter) + ":00" || User->getCourseList()->ObtainIndex(t)->getEnrollment().getEnrollmentTime().getFinishTime() == "0" + to_string(7 + Iter + 1) + ":00")) {
						cout << char(186) << "    ";
						if (User->getCourseList()->ObtainIndex(t)->getCampus() == "Monterrico") {
							color(hConsole, 4);
						}
						else
							if (User->getCourseList()->ObtainIndex(t)->getCampus() == "San Isidro") {
								color(hConsole, 9);
							}
							else
								if (User->getCourseList()->ObtainIndex(t)->getCampus() == "Villa") {
									color(hConsole, 2);
								}
								else
									if (User->getCourseList()->ObtainIndex(t)->getCampus() == "San Miguel") {
										color(hConsole, 8);
									}
						cout << User->getCourseList()->ObtainIndex(t)->getCourseSection();
						color(hConsole, 7);
						cout << "     ";
						break;
					}
					else {
						if (t == User->getCourseList()->getSize() - 1) {
							cout << char(186) << "             ";
						}
					}
				}
			}
			else
				if (Iter == 2) {
					for (size_t t = 0; t < User->getCourseList()->getSize(); t++)
					{
						if (User->getCourseList()->ObtainIndex(t)->getEnrollment().getSessionDay() == days[j] && (User->getCourseList()->ObtainIndex(t)->getEnrollment().getEnrollmentTime().getStartTime() == "0" + to_string(7 + Iter) + ":00" || User->getCourseList()->ObtainIndex(t)->getEnrollment().getEnrollmentTime().getFinishTime() == to_string(7 + Iter + 1) + ":00")) {
							cout << char(186) << "    ";
							if (User->getCourseList()->ObtainIndex(t)->getCampus() == "Monterrico") {
								color(hConsole, 4);
							}
							else
								if (User->getCourseList()->ObtainIndex(t)->getCampus() == "San Isidro") {
									color(hConsole, 9);
								}
								else
									if (User->getCourseList()->ObtainIndex(t)->getCampus() == "Villa") {
										color(hConsole, 2);
									}
									else
										if (User->getCourseList()->ObtainIndex(t)->getCampus() == "San Miguel") {
											color(hConsole, 8);
										}
							cout << User->getCourseList()->ObtainIndex(t)->getCourseSection();
							color(hConsole, 7);
							cout << "     ";
							break;
						}
						else {
							if (t == User->getCourseList()->getSize() - 1) {
								cout << char(186) << "             ";
							}
						}
					}
				}
				else
					if (Iter > 2) {
						for (size_t t = 0; t < User->getCourseList()->getSize(); t++)
						{
							if (User->getCourseList()->ObtainIndex(t)->getEnrollment().getSessionDay() == days[j] && (User->getCourseList()->ObtainIndex(t)->getEnrollment().getEnrollmentTime().getStartTime() == to_string(7 + Iter) + ":00" || User->getCourseList()->ObtainIndex(t)->getEnrollment().getEnrollmentTime().getFinishTime() == to_string(7 + Iter + 2) + ":00" || User->getCourseList()->ObtainIndex(t)->getEnrollment().getEnrollmentTime().getFinishTime() == to_string(7 + Iter + 1) + ":00")) {
								cout << char(186) << "    ";
								if (User->getCourseList()->ObtainIndex(t)->getCampus() == "Monterrico") {
									color(hConsole, 4);
								}
								else
									if (User->getCourseList()->ObtainIndex(t)->getCampus() == "San Isidro") {
										color(hConsole, 9);
									}
									else
										if (User->getCourseList()->ObtainIndex(t)->getCampus() == "Villa") {
											color(hConsole, 2);
										}
										else
											if (User->getCourseList()->ObtainIndex(t)->getCampus() == "San Miguel") {
												color(hConsole, 8);
											}
								cout << User->getCourseList()->ObtainIndex(t)->getCourseSection();
								color(hConsole, 7);
								cout << "     ";
								break;
							}
							else {
								if (t == User->getCourseList()->getSize() - 1) {
									cout << char(186) << "             ";
								}
							}
						}
					}
		}
		else {
			cout << char(186) << "             ";
		}
	}

	cout << char(186);
	cout << endl; _sleep(PauseTime / 10);

	for (size_t i = 0; i < 6; i++)
	{
		if (i == 0 && Iter == 15) {
			cout << " " << char(200);
		}
		else
			if (i == 0) {
				cout << " " << char(204);
			}

		for (size_t j = 0; j < 13; j++)
		{
			cout << char(205);
		}
		if (Iter == 15) {
			if (i == 5) {
				cout << char(188);
			}
			else {
				cout << char(202);
			}
		}
		else {
			if (i == 5) {
				cout << char(185);
			}
			else {
				cout << char(206);
			}
		}
	}
	RecursiveDisplayUserCalendar(Iter + 1, Limitation);
}
void UPC::RecursiveCourseEnrollment(size_t Iter, size_t Limitation) {
	if (Iter > Limitation) {
		return;
	}

	if (User->getCourseList()->ObtainIndex(Iter)->getCourseName() == Courses->ObtainIndex(Selection).getCourseName()) {
		cout << endl << " ERROR: You already erroled in this course";
		return;
	}
	else
		if (User->getCourseList()->ObtainIndex(Iter)->getEnrollment().getSessionDay() == Courses->ObtainIndex(Selection).getEnrollment().getSessionDay()) {
			if (User->getCourseList()->ObtainIndex(Iter)->getEnrollment().getEnrollmentTime().getStartTime() == Courses->ObtainIndex(Selection).getEnrollment().getEnrollmentTime().getStartTime() || User->getCourseList()->ObtainIndex(Iter)->getEnrollment().getEnrollmentTime().getStartTime() == Courses->ObtainIndex(Selection).getEnrollment().getEnrollmentTime().getFinishTime() || User->getCourseList()->ObtainIndex(Iter)->getEnrollment().getEnrollmentTime().getFinishTime() == Courses->ObtainIndex(Selection).getEnrollment().getEnrollmentTime().getFinishTime() || User->getCourseList()->ObtainIndex(Iter)->getEnrollment().getEnrollmentTime().getFinishTime() == Courses->ObtainIndex(Selection).getEnrollment().getEnrollmentTime().getStartTime()) {
				cout << endl << " ERROR: You have a crossing with another course";
				return;
			}
			cout << endl << " ERROR: You have a crossing with another course";
		}
		else {
			if (Iter == User->getCourseList()->getSize() - 1) {
				if (User->getCredits() - Courses->ObtainIndex(Selection).getCreditWeight() < 0) {
					cout << endl << " ERROR: You don't have enough credits";
				}
				else {
					User->setCredits(User->getCredits() - Courses->ObtainIndex(Selection).getCreditWeight());
					User->getCourseList()->AddToEnd(new Course(Courses->ObtainIndex(Selection).getCourseName(), Courses->ObtainIndex(Selection).getCourseSection(), Courses->ObtainIndex(Selection).getEnrollment().getSessionDay(), Courses->ObtainIndex(Selection).getEnrollment().getEnrollmentTime().getStartTime(), Courses->ObtainIndex(Selection).getEnrollment().getEnrollmentTime().getFinishTime(), Courses->ObtainIndex(Selection).getCreditWeight(), Courses->ObtainIndex(Selection).getCampus(), Courses->ObtainIndex(Selection).getModality()));
					User->getNotificationHeap()->Push(Notification(Courses->ObtainIndex(Selection).getCourseName()));
					CoverterTotxt = User->getStudentID() + ".txt";

					FileWriter.open(CoverterTotxt, ios::out);
					if (FileWriter.is_open()) {
						FileWriter << User->getCourseList()->getSize() << endl;
						RecursiveWriterTxtCourseFile(0, User->getCourseList()->getSize() - 1);

						FileWriter << endl << User->getNotificationHeap()->getSize();
						if (User->getNotificationHeap()->getSize() > 0) {
							FileWriter << endl;
							RecursiveWriterTxtNotificationFile(0, User->getNotificationHeap()->getSize() - 1);
						}

						FileWriter.close();
					}

					FileWriter.open("Students.txt", ios::out);
					if (FileWriter.is_open()) {
						FileWriter << StudentsDoubleList->getSize() << endl;
						RecursiveWriterTxtStudentFile(0, StudentsDoubleList->getSize() - 1);

						FileWriter.close();
					}
					return;
				}
			}
		}
	RecursiveCourseEnrollment(Iter + 1, Limitation);
}

void UPC::QuickSort(SimpleCircularLinkedList<Student*>* Students, size_t LimitsLeft, size_t LimitsRight) {
	size_t IndexLeft = LimitsLeft;
	size_t IndexRight = LimitsRight;
	Student* MiddleValue = Students->ObtainIndex((IndexLeft + IndexRight) / 2);
	Student* Auxiliary = nullptr;
	do {
		while (Students->ObtainIndex(IndexLeft)->getLastName() < MiddleValue->getLastName() && IndexLeft < LimitsRight) {
			IndexLeft++;
		}
		while (Students->ObtainIndex(IndexRight)->getLastName() > MiddleValue->getLastName() && IndexRight < LimitsLeft) {
			IndexRight++;
		}
		if (IndexLeft <= IndexRight) {
			Auxiliary = Students->ObtainIndex(IndexLeft);
			Students->ModifyIndex(Students->ObtainIndex(IndexRight), IndexLeft);
			Students->ModifyIndex(Auxiliary, IndexRight);
			IndexLeft++;
			IndexRight++;
		}
	} while (IndexLeft <= IndexRight);

	if (LimitsLeft < IndexRight) {
		QuickSort(Students, LimitsLeft, IndexRight);
	}
	if (LimitsRight > IndexLeft) {
		QuickSort(Students, IndexLeft, LimitsRight);
	}
}
void UPC::QuickSort(DoubleCircularLinkedList<Student*>* Students, size_t LimitsLeft, size_t LimitsRight) {
	size_t IndexLeft = LimitsLeft;
	size_t IndexRight = LimitsRight;
	Student* MiddleValue = Students->ObtainIndex((IndexLeft + IndexRight) / 2);
	Student* Auxiliary = nullptr;
	do {
		while (Students->ObtainIndex(IndexLeft)->getLastName() < MiddleValue->getLastName() && IndexLeft < LimitsRight) {
			IndexLeft++;
		}
		while (Students->ObtainIndex(IndexRight)->getLastName() > MiddleValue->getLastName() && IndexRight > LimitsLeft) {
			IndexRight--;
		}
		if (IndexLeft <= IndexRight) {
			Auxiliary = Students->ObtainIndex(IndexLeft);
			Students->ModifyIndex(Students->ObtainIndex(IndexRight), IndexLeft);
			Students->ModifyIndex(Auxiliary, IndexRight);
			IndexLeft++;
			IndexRight--;
		}
	} while (IndexLeft <= IndexRight);

	if (LimitsLeft < IndexRight) {
		QuickSort(Students, LimitsLeft, IndexRight);
	}
	if (LimitsRight > IndexLeft) {
		QuickSort(Students, IndexLeft, LimitsRight);
	}
}
void UPC::MergeSort(SimpleCircularLinkedList<Student*>* Students, size_t LimitsLeft, size_t LimitsRight) {
	if (LimitsLeft < LimitsRight) {
		size_t Middle = LimitsLeft + (LimitsRight - LimitsLeft) / 2;
		MergeSort(Students, LimitsLeft, Middle);
		MergeSort(Students, Middle + 1, LimitsRight);

		int i, j, k;
		int elementosIzq = Middle - LimitsLeft + 1;
		int elementosDer = LimitsRight - Middle;

		SimpleCircularLinkedList<Student*>* Left = new SimpleCircularLinkedList<Student*>();
		SimpleCircularLinkedList<Student*>* Right = new SimpleCircularLinkedList<Student*>();

		for (int i = 0; i < elementosIzq; i++) {
			Left->AddToIndex(Students->ObtainIndex(LimitsLeft + i), i);
		}
		for (int j = 0; j < elementosDer; j++) {
			Right->AddToIndex(Students->ObtainIndex(Middle + 1 + j), j);
		}

		i = 0;
		j = 0;
		k = LimitsLeft;

		while (i < elementosIzq && j < elementosDer) {
			if (Left->ObtainIndex(i)->getFirstName() <= Right->ObtainIndex(j)->getFirstName()) {
				Students->ModifyIndex(Left->ObtainIndex(i), k);
				i++;
			}
			else {
				Students->ModifyIndex(Right->ObtainIndex(j), k);
				j++;
			}
			k++;
		}

		while (j < elementosDer) {
			Students->ModifyIndex(Right->ObtainIndex(j), k);
			j++;
			k++;
		}
		while (i < elementosIzq) {
			Students->ModifyIndex(Left->ObtainIndex(i), k);
			i++;
			k++;
		}
	}
}
void UPC::MergeSort(DoubleCircularLinkedList<Student*>* Students, size_t LimitsLeft, size_t LimitsRight) {
	if (LimitsLeft < LimitsRight) {
		size_t Middle = LimitsLeft + (LimitsRight - LimitsLeft) / 2;
		MergeSort(Students, LimitsLeft, Middle);
		MergeSort(Students, Middle + 1, LimitsRight);

		int i, j, k;
		int elementosIzq = Middle - LimitsLeft + 1;
		int elementosDer = LimitsRight - Middle;

		DoubleCircularLinkedList<Student*>* Left = new DoubleCircularLinkedList<Student*>();
		DoubleCircularLinkedList<Student*>* Right = new DoubleCircularLinkedList<Student*>();

		for (int i = 0; i < elementosIzq; i++) {
			Left->AddToIndex(Students->ObtainIndex(LimitsLeft + i), i);
		}
		for (int j = 0; j < elementosDer; j++) {
			Right->AddToIndex(Students->ObtainIndex(Middle + 1 + j), j);
		}

		i = 0;
		j = 0;
		k = LimitsLeft;

		while (i < elementosIzq && j < elementosDer) {
			if (Left->ObtainIndex(i)->getFirstName() <= Right->ObtainIndex(j)->getFirstName()) {
				Students->ModifyIndex(Left->ObtainIndex(i), k);
				i++;
			}
			else {
				Students->ModifyIndex(Right->ObtainIndex(j), k);
				j++;
			}
			k++;
		}

		while (j < elementosDer) {
			Students->ModifyIndex(Right->ObtainIndex(j), k);
			j++;
			k++;
		}
		while (i < elementosIzq) {
			Students->ModifyIndex(Left->ObtainIndex(i), k);
			i++;
			k++;
		}
	}
}
void UPC::BubbleSort(SimpleCircularLinkedList<Student*>* Students) {
	int Size = Students->getSize();
	bool Swapped;

	for (int i = 0; i < Size - 1; i++) {
		Swapped = false;

		for (int j = 0; j < Size - i - 1; j++) {
			if (Students->ObtainIndex(j)->getStudentID() > Students->ObtainIndex(j + 1)->getStudentID()) {
				Student* Auxiliary = Students->ObtainIndex(j);
				Students->ModifyIndex(Students->ObtainIndex(j + 1), j);
				Students->ModifyIndex(Auxiliary, j + 1);
				Swapped = true;
			}
		}

		// Si no se realiz� ning�n intercambio en la iteraci�n, la lista ya est� ordenada
		if (!Swapped) {
			break;
		}
	}
}
void UPC::BubbleSort(DoubleCircularLinkedList<Student*>* Students) {
	int Size = Students->getSize();
	bool Swapped;

	for (int i = 0; i < Size - 1; i++) {
		Swapped = false;

		for (int j = 0; j < Size - i - 1; j++) {
			if (Students->ObtainIndex(j)->getStudentID() > Students->ObtainIndex(j + 1)->getStudentID()) {
				Student* Auxiliary = Students->ObtainIndex(j);
				Students->ModifyIndex(Students->ObtainIndex(j + 1), j);
				Students->ModifyIndex(Auxiliary, j + 1);
				Swapped = true;
			}
		}

		// Si no se realiz� ning�n intercambio en la iteraci�n, la lista ya est� ordenada
		if (!Swapped) {
			break;
		}
	}
}
void UPC::FisherYatesShuffle(SimpleCircularLinkedList<Student*>* Students) {
	int Size = Students->getSize();

	for (int i = Size - 1; i > 0; i--) {
		int j = rand() % +(i + 1);
		Student* Auxiliary = Students->ObtainIndex(i);
		Students->ModifyIndex(Students->ObtainIndex(j), i);
		Students->ModifyIndex(Auxiliary, j);
	}
}
void UPC::FisherYatesShuffle(DoubleCircularLinkedList<Student*>* Students) {
	int Size = Students->getSize();

	for (int i = Size - 1; i > 0; i--) {
		int j = rand() % +(i + 1);
		Student* Auxiliary = Students->ObtainIndex(i);
		Students->ModifyIndex(Students->ObtainIndex(j), i);
		Students->ModifyIndex(Auxiliary, j);
	}
}
#endif //!__UPC_H__

void UPC_Vbeta() {
	srand(time(NULL));
	UPC UPCVbeta;
	UPCVbeta.UPCVbeta();
}