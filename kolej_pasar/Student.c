#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Student.h"
#include "Utilities.h"
#include "Handlers.h"

#pragma warning(disable:4996)

#define SCHOLARSHIP_100_THRESHOLD 3.85
#define SCHOLARSHIP_50_THRESHOLD 3.75

const char* STUDENT_FUNCTIONS[2] = {"View Score", "Back"};

void displayScholarshipEligibility(struct Student* studentPtr);

void studentMode() {
	int selectedFunction;
	flushTerminal();
	printMenuHeader();

	do {
		selectedFunction = 0;

		//prompt user for function selection
		selectionHandler(&selectedFunction, STUDENT_FUNCTIONS, 2);

		//run relevant function based on operationMode
		switch (selectedFunction) {
		case 1: //view score
		{
			char tempId[15];  //10 + 5 for file extension

			//Prompt user for student ID
			do {
				printf("Enter student ID to view > ");
				rewind(stdin);
				fgets(tempId, 10, stdin);
			} while (!checkIDValidity(tempId));

			//Attempt to read student data from relevant file name.
			struct Student student;
			readStudentData(strcat(tempId, ".bin"), &student);

			//Exit switch with error message if student data file cannot be found.
			if (strcmp(student.name, "INVALID") == 0) {
				flushTerminal();
				printMenuHeader();
				printf("Failed to read student data file.\n");
				printf("Please check if student ID was correctly typed.\n\n");
				break;
			};

			flushTerminal();
			printMenuHeader();
			displayScholarshipEligibility(&student);
			displayStudentInformation(&student);

			flushTerminal();
			printMenuHeader();
			break;
		}
		case 2: //exit student mode
			return;
		default:
			break;
		}
	} while (selectedFunction != 2);
}

//----------ADDITIONAL FUNCTIONS----------
//Check scholarship eligibility and displays a message based on results.
void displayScholarshipEligibility(struct Student* studentPtr) {
	int scholarshipRate = 0;

	//Check for failed subjects and return with message if any are found
	for (int semester = 0; semester < 3; semester++) {
		for (int course = 0; course < 2; course++) {
			if (strcmp(studentPtr->semesters[semester].courses[course].letterGrade, "F") == 0) {
				printf("Sorry, you are not eligible for any scholarship.\n\n");
				return;
			}
		}
	}

	//Get scholarship rate based on threshold
	if (studentPtr->CGPA >= SCHOLARSHIP_100_THRESHOLD) {
		scholarshipRate = 100;
	}
	else if (studentPtr->CGPA >= SCHOLARSHIP_50_THRESHOLD) {
		scholarshipRate = 50;
	}

	//Print message and return if student does not meet threshold
	if (scholarshipRate == 0) {
		printf("Sorry, you are not eligible for any scholarship.\n\n");
		return;
	}

	printf("Congratulations! You are eligible for a %d%% scholarship!\n\n", scholarshipRate);
	return;
}