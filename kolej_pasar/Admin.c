#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Admin.h"
#include "Utilities.h"
#include "Handlers.h"

#pragma warning(disable:4996)

const char* adminFunctionsArray[5] = { "Add student", "Edit student", "Delete student", "View student", "Generate student scores" };

//FUNCTION DECLARATIONS
struct Student addStudent();

//main exported adminMode function
void adminMode(int* operationModePtr) {
	//temp
	struct Student student1;

	//flushTerminal();
	printMenuHeader();

	int selectedMode = 0;

	selectionHandler(&selectedMode, adminFunctionsArray, 5);

	switch (selectedMode) {
	case 1:
		student1 = addStudent();
		calcQualityPoint(&student1);
		calcGPA(&student1);
		calcCGPA(&student1);
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	default:
		break;
	}
}

//Creates a new struct Student and returns it with initialized data based on user input
struct Student addStudent(void) {
	//Create temporary struct Student to return after function
	struct Student tempStudent;

	//Get student data from user input
	printf("Enter student ID (ABCD12345) > ");
	rewind(stdin);
	gets(tempStudent.id);
	
	printf("Enter student name > ");
	rewind(stdin);
	gets(tempStudent.name);

	//Loop to get semester and course information
	printf("--------------------------------------------------");
	for (int semester = 0; semester < 3; semester++) {
		for (int course = 0; course < 2; course++) {
			printf("\nEnter information for semester %d course %d.\n",semester + 1, course + 1);
			printf("Course code (AAA1000) \t> ");
			rewind(stdin);
			gets(tempStudent.semesters[semester].courses[course].courseCode);

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