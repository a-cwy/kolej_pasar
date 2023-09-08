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
void displayStudentInformation(struct Student* studentPtr);

//main exported adminMode function
void adminMode(int* operationModePtr) {
	int selectedMode;

	flushTerminal();
	printMenuHeader();
	do {
		selectedMode = 0;
		//prompt user for function selection until 0 is entered to exit program
		selectionHandler(&selectedMode, ADMIN_FUNCTIONS, 4);
		switch (selectedMode) {
		case 1: //add student
		{
			struct Student tempStudent;
			tempStudent = addStudent();
			
			//Process struct to generate remaining information
			generateFilepath(&tempStudent);
			calcQualityPoint(&tempStudent);
			calcGPA(&tempStudent);
			calcCGPA(&tempStudent);
			writeStudentData(tempStudent.filepath, &tempStudent);

			flushTerminal();
			printMenuHeader();
			printf("Student with ID %s successfully added.\n", tempStudent.id);
			break;
		}
		case 2: //view student
		{
			char tempId[10];

			//Prompt user for student ID
			do {
				printf("Enter student ID to view > ");
				rewind(stdin);
				fgets(tempId, 10, stdin);
			} while (checkIDValidity(&tempId) == 0);
			
			//Attempt to read student data from relevant file name.
			struct Student* tempStudent = malloc(sizeof(struct Student));
			readStudentData(strcat(tempId, ".bin"), tempStudent);

			//Exit switch with error message if student data file cannot be found.
			if (strcmp(tempStudent->name, "INVALID") == 0) {
				flushTerminal();
				printMenuHeader();
				printf("Failed to read student data file.\n");
				printf("Please check if student ID was correctly typed.\n\n");
				break;
			};

			displayStudentInformation(tempStudent);
			flushTerminal();
			printMenuHeader();
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

//----------ADDITIONAL FUNCTIONS----------
//Creates a new struct Student and returns it with initialized data based on user input
struct Student addStudent(void) {
	//Create temporary struct Student to return after function
	struct Student tempStudent = {.id = "INVALID"};

	//Get student data from user input
	do {
		printf("Enter student ID (ABCD12345) > ");
		rewind(stdin);
		fgets(tempStudent.id, 10, stdin);
	} while (checkIDValidity(&tempStudent.id) == 0);
	
	printf("Enter student name > ");
	rewind(stdin);
	fgets(tempStudent.name, 81, stdin);

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
			
			do
			{
				printf("Credit Hours \t\t> ");
				rewind(stdin);
			} while (!scanf("%d", &tempStudent.semesters[semester].courses[course].creditHour));
			
			//loop to re-prompt for valid letterGrade value
			char inputBuffer[3];
			do {
				printf("A | A- | B+ | B | B- | C+ | C | F\n"
					"Grade\t\t\t> ");
				rewind(stdin);
				fgets(inputBuffer, 3, stdin);
				if (inputBuffer[1] == '\n') inputBuffer[1] = '\0';
			} while (getGradePoint(&inputBuffer) < 0.0f);
			strcpy(&tempStudent.semesters[semester].courses[course].letterGrade, &inputBuffer);


			printf("--------------------------------------------------");
		}
	}

	return(tempStudent);
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
	flushTerminal();
	printMenuHeader();

	printf("%-8s: %s", "Name", studentPtr->name);
	printf("%-8s: %s\n", "ID", studentPtr->id);
	printf("%-8s: %.2f\n", "CGPA", studentPtr->CGPA);
	printf("\n");
	printf("#_____________________________________________________________________________#\n");
	printf("|Semester 1               |Semester 2               |Semester 3               |\n");
	printf("|-------------------------|-------------------------|-------------------------|\n");
	
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