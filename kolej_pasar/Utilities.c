#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>

#include "Utilities.h"

#pragma warning(disable:4996)

//----------OUTPUT FUNCTIONS----------
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
	//map implementation to pair letterGrades with gradePoint values
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
	//iterate through semesters and courses and calculate qualityPoint for each course
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
	//iterate through semesters and courses and calculate GPA for each semester
	for (int semester = 0; semester < 3; semester++) {
		int totalCreditHour = 0;
		float totalQualityPoint = 0.0f;

		for (int course = 0; course < 2; course++) {
			totalCreditHour += studentPtr->semesters[semester].courses[course].creditHour;
			totalQualityPoint += studentPtr->semesters[semester].courses[course].qualityPoint;
		}

		studentPtr->semesters[semester].GPA = (float)totalQualityPoint / totalCreditHour;
	}

	return;
}

//Calculates and updates CPGA for struct Student
void calcCGPA(struct Student* studentPtr) {
	int totalCreditHour = 0;
	float totalQualityPoint = 0.0f;

	//iterate through semesters and courses and calculate CGPA
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

//Displays formatted data from struct Student
void displayStudentInformation(struct Student* studentPtr) {
	/* Display Format
	Name	:	Test Student
	ID		:	QQQQ11111
	CGPA	:	4.0

	#_____________________________________________________________________________#
	|Semester 1				  |Semester 2				|Semester 3				  |
	|-------------------------|-------------------------|-------------------------|
	|Course		:	AAA1000	  |Course	  :	  AAB1000	|Course		:	AAC1000	  |
	|Grade		:	A		  |Grade	  :	  A			|Grade		:	A		  |
	|Cr. Hours  :	3		  |Cr. Hours  :	  3			|Cr. Hours  :	3		  |
	|						  |							|						  |
	|Course		:	AAA2000	  |Course	  :	  AAB2000	|Course		:	AAC2000	  |
	|Grade		:	A		  |Grade	  :	  A			|Grade		:	A		  |
	|Cr. Hours  :	3		  |Cr. Hours  :	  3			|Cr. Hours  :	3		  |
	|						  |							|						  |
	|GPA		:	4.0		  |GPA		:	4.0		    |GPA		:	4.0		  |
	#-----------------------------------------------------------------------------#

	Press enter to go back.
	*/
	printf("%-8s: %s", "Name", studentPtr->name);
	printf("%-8s: %s\n", "ID", studentPtr->id);
	printf("%-8s: %.2f\n", "CGPA", studentPtr->CGPA);
	printf("\n");
	printf("#_____________________________________________________________________________#\n");
	printf("|Semester 1               |Semester 2               |Semester 3               |\n");
	printf("|-------------------------|-------------------------|-------------------------|\n");

	//loop through each semester and course to print details
	for (int course = 0; course < 2; course++) {
		printf("|");
		for (int semester = 0; semester < 3; semester++) {
			printf("%-11s:   %-10s", "Course", studentPtr->semesters[semester].courses[course].courseCode);
			printf("|");
		}
		printf("\n");

		printf("|");
		for (int semester = 0; semester < 3; semester++) {
			printf("%-11s:   %-10s", "Grade", studentPtr->semesters[semester].courses[course].letterGrade);
			printf("|");
		}
		printf("\n");

		printf("|");
		for (int semester = 0; semester < 3; semester++) {
			printf("%-11s:   %-10d", "Cr. Hours", studentPtr->semesters[semester].courses[course].creditHour);
			printf("|");
		}
		printf("\n");
		printf("|                         |                         |                         |\n");
	}

	printf("|");
	for (int semester = 0; semester < 3; semester++) {
		printf("%-11s:   %-10.2f", "GPA", studentPtr->semesters[semester].GPA);
		printf("|");
	}
	printf("\n");

	printf("#_____________________________________________________________________________#\n");
	printf("\n\n");

	printf("Press enter to go back.");
	rewind(stdin);
	gets();
}





//----------STRING FORMAT CHECK FUNCTIONS----------
//Check if student ID is in valid format
bool checkIDValidity(char* idString) {
	//format : ABCD12345

	//Alphabet check
	for (int i = 0; i < 4; i++) {
		idString[i] = toupper(idString[i]);
		if (isalpha(idString[i]) == 0) return false;
	}

	//Numericals check
	for (int i = 4; i < 9; i++) {
		if (isdigit(idString[i]) == 0) return false;
	}

	return true;
}

//Check if course code is in valid format
bool checkCourseCodeValidity(char* courseCodeString) {
	//format : ABC1234

	//Alphabet check
	for (int i = 0; i < 3; i++) {
		courseCodeString[i] = toupper(courseCodeString[i]);
		if (isalpha(courseCodeString[i]) == 0) return false;
	}

	//Numericals check
	for (int i = 3; i < 7; i++) {
		if (isdigit(courseCodeString[i]) == 0) return false;
	}

	return true;
}