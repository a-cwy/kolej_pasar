#pragma once

void printMenuHeader(void);
void flushTerminal(void);
float getGradePoint(char* letterGrade);
void calcQualityPoint(struct Student* studentPtr);
void calcGPA(struct Student* studentPtr);
void calcCGPA(struct Student* studentPtr);
void generateFilepath(struct Student* studentPtr);
bool checkIDValidity(char* idString);
bool checkCourseCodeValidity(char* courseCodeString);

//Structure for Course
struct Course {
	char courseCode[8]; //FORMAT SPECIFIED AS ABC1234
	char letterGrade[3];
	int creditHour;
	float qualityPoint;
};

//Structure for Semester
struct Semester {
	float GPA;
	struct Course courses[2];
};

//Structure for Student
struct Student {
	char filepath[101];
	char name[81];
	char id[10]; //FORMAT SPECIFIED AS ABCD12345
	float CGPA;
	struct Semester semesters[3];
};