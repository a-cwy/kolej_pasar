#include <stdlib.h>
#include <string.h>

#include "Utilities.h"

#pragma warning(disable:4996)

//Accepts input as char letterGrade[3] and returns corresponding grade point value.
float getGradePoint(char* letterGrade[3]) {
	char conversionArrayKeys[8][3] = {"A", "A-", "B+", "B", "B-", "C+", "C", "F"};
	float conversionArrayValues[8] = {4.00f, 3.75f, 3.50f, 3.00f, 2.75f, 2.50f, 2.00f, 0.00f};


	//interate through conversionArrayKeys to find index of letterGrade by matching value
	for (int i = 0; i < 8; i++) {
		//return conversionArrayValues[i] if letterGrade and conversionArrayKeys[i] are equal
		if (strcmp(*letterGrade, conversionArrayKeys[i]) == 0) return conversionArrayValues[i];
	}

	//return arbitary impossible value if all checks fail
	return 100.0f;
}

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

//Structure for Student, defined as type Student in header file
struct Student {
	char name[51];
	char id[10]; //FORMAT SPECIFIED AS ABCD12345
	float CGPA;
	struct Semester semester1;
	struct Semester semester2;
	struct Semester semester3;
};

//Initialize _DefaultStudent with static information
Student _DefaultStudent = {
	.semester1 = {
		.course1.courseCode = "AAA1003",
		.course2.courseCode = "AAA1014"
	},
	.semester2 = {
		.course1.courseCode = "ABA1003",
		.course2.courseCode = "ABA1014"
	},
	.semester3 = {
		.course1.courseCode = "ACA1003",
		.course2.courseCode = "ACA1014"
	}
};