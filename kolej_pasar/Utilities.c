#include <stdlib.h>
#include <string.h>

#include "Utilities.h"

#pragma warning(disable:4996)

//Print menu header
void printMenuHeader(void) {
	printf("===================================================\n");
	printf("||                  Kolej Pasar                  ||\n");
	printf("===================================================\n");

	return;
}

void flushTerminal(void) {
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

	return;
}

//Accepts input as char letterGrade[3] and returns corresponding grade point value.
float getGradePoint(char *letterGrade) {
	char conversionArrayKeys[8][3] = {"A", "A-", "B+", "B", "B-", "C+", "C", "F"};
	float conversionArrayValues[8] = {4.00f, 3.75f, 3.50f, 3.00f, 2.75f, 2.50f, 2.00f, 0.00f};


	//iterate through conversionArrayKeys to find index of letterGrade by matching value
	for (int i = 0; i < 8; i++) {
		//return conversionArrayValues[i] if letterGrade and conversionArrayKeys[i] are equal
		if (strcmp(letterGrade, &conversionArrayKeys[i]) == 0) return conversionArrayValues[i];
	}

	//return arbitary impossible value if all checks fail
	return -1.0f;
}

//Initialize _DefaultStudent with static information
/*struct Student _DefaultStudent = {
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
};*/