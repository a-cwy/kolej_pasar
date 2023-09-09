#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

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
	system("cls");
	return;
}

//----------struct Student UTILITY FUNCTIONS---------
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

//Calculates and updates qualityPoint for struct Student
void calcQualityPoint(struct Student *studentPtr) {
	for (int semester = 0; semester < 3; semester++) {
		for (int course = 0; course < 2; course++) {
			int creditHour = studentPtr->semesters[semester].courses[course].creditHour;
			float gradePoint = getGradePoint(&studentPtr->semesters[semester].courses[course].letterGrade);

			studentPtr->semesters[semester].courses[course].qualityPoint = (float)creditHour * gradePoint;
		}
	}

	return;
}

//Calculates and updates GPA for struct Student
void calcGPA(struct Student* studentPtr) {
	for (int semester = 0; semester < 3; semester++) {
		int totalCreditHour = 0;
		float totalQualityPoint = 0.0f;

		for (int course = 0; course < 2; course++) {
			totalCreditHour += studentPtr->semesters[semester].courses[course].creditHour;
			totalQualityPoint += studentPtr->semesters[semester].courses[course].qualityPoint;
			
		}

		studentPtr->semesters[semester].GPA = (float)totalQualityPoint / totalCreditHour ;
	}

	return;
}

//Calculates and updates CPGA for struct Student
void calcCGPA(struct Student* studentPtr) {
		int totalCreditHour = 0;
		float totalQualityPoint = 0.0f;
	for (int semester = 0; semester < 3; semester++) {

		for (int course = 0; course < 2; course++) {
			totalCreditHour += studentPtr->semesters[semester].courses[course].creditHour;
			totalQualityPoint += studentPtr->semesters[semester].courses[course].qualityPoint;

		}

	}
		studentPtr->CGPA = (float)totalQualityPoint / totalCreditHour;

	return;
}

//Generates filepath for struct Student based on student.id
void generateFilepath(struct Student* studentPtr) {
	char temp[15];
	strcpy(temp, studentPtr->id);
	strcpy(studentPtr->filepath, strcat(temp, ".bin"));
}

//----------STRING FORMAT CHECK FUNCTIONS----------
//Check if student ID is in valid format
int checkIDValidity(char* idString) {
	//format : ABCD12345

	//Alphabet check
	for (int i = 0; i < 4; i++) {
		idString[i] = toupper(idString[i]);
		if (isalpha(idString[i]) == 0) return 0;
	}

	//Numericals check
	for (int i = 4; i < 9; i++) {
		if (isdigit(idString[i]) == 0) return 0;
	}

	return 1;
}

//Check if course code is in valid format
int checkCourseCodeValidity(char* courseCodeString) {
	//format : ABC1234

	//Alphabet check
	for (int i = 0; i < 3; i++) {
		courseCodeString[i] = toupper(courseCodeString[i]);
		if (isalpha(courseCodeString[i]) == 0) return 0;
	}

	//Numericals check
	for (int i = 3; i < 7; i++) {
		if (isdigit(courseCodeString[i]) == 0) return 0;
	}

	return 1;
}