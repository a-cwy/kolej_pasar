#pragma once

void printMenuHeader(void);
void flushTerminal(void);
float getGradePoint(char* letterGrade[3]);
void calcQualityPoint(struct Student* studentPtr);
void calcGPA(struct Student* studentPtr);
void calcCGPA(struct Student* studentPtr);

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
	char name[51];
	char id[10]; //FORMAT SPECIFIED AS ABCD12345
	float CGPA;
	struct Semester semesters[3];
};