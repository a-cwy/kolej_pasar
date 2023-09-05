#pragma once

void printMenuHeader(void);
void flushTerminal(void);
float getGradePoint(char* letterGrade[3]);

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
	struct Course course1;
	struct Course course2;
};

//Structure for Student
struct Student {
	char name[51];
	char id[10]; //FORMAT SPECIFIED AS ABCD12345
	float CGPA;
	struct Semester semester1;
	struct Semester semester2;
	struct Semester semester3;
};