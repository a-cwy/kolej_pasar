#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Admin.h"
#include "Utilities.h"
#include "Handlers.h"

#pragma warning(disable:4996)

const char* ADMIN_FUNCTIONS[5] = { "Add student", "View student", "Edit student", "Delete student"};

//FUNCTION DECLARATIONS
struct Student addStudent();

//main exported adminMode function
void adminMode(int* operationModePtr) {int selectedMode = 0;

	do {
		printMenuHeader();

		//prompt user for function selection until 0 is entered to exit program
		selectionHandler(&selectedMode, ADMIN_FUNCTIONS, 4);
		switch (selectedMode) {
		case 1: //add student
		{
			struct Student tempStudent;
			tempStudent = addStudent();
			generateFilepath(&tempStudent);
			calcQualityPoint(&tempStudent);
			calcGPA(&tempStudent);
			calcCGPA(&tempStudent);
			writeStudentData(tempStudent.filepath, &tempStudent);
			break;
		}
		case 2: //view student
		{
			break;
		}
		case 3: //edit student
			break;
		case 4: //delete student
			break;
		default:
			break;
		}
	} while (selectedMode != 0);
}

//Creates a new struct Student and returns it with initialized data based on user input
struct Student addStudent(void) {
	//Create temporary struct Student to return after function
	struct Student tempStudent = {.id = "INVALID"};

	//Get student data from user input
	do {
		printf("Enter student ID (ABCD12345) > ");
		rewind(stdin);
		gets(tempStudent.id);
	} while (checkIDValidity(&tempStudent.id) == 0);
	
	printf("Enter student name > ");
	rewind(stdin);
	gets(tempStudent.name);

	//Loop to get semester and course information
	printf("--------------------------------------------------");
	for (int semester = 0; semester < 3; semester++) {
		for (int course = 0; course < 2; course++) {
			printf("\nEnter information for semester %d course %d.\n",semester + 1, course + 1);
			do {
				printf("Course code (AAA1000) \t> ");
				rewind(stdin);
				fgets(tempStudent.semesters[semester].courses[course].courseCode, 8, stdin);
			} while (checkCourseCodeValidity(tempStudent.semesters[semester].courses[course].courseCode) == 0);
			
			printf("Credit Hour \t\t> ");
			rewind(stdin);
			scanf("%d", &tempStudent.semesters[semester].courses[course].creditHour);
			
			//loop to re-prompt for valid letterGrade value
			char inputBuffer[3];
			do {
				printf("A | A- | B+ | B | B- | C+ | C | F\n"
					"Grade\t\t\t> ");
				rewind(stdin);
				fgets(inputBuffer, 3, stdin);
			} while (getGradePoint(&inputBuffer) < 0.0f);
			strcpy(&tempStudent.semesters[semester].courses[course].letterGrade, &inputBuffer);


			printf("--------------------------------------------------");
		}
	}

	return(tempStudent);
}