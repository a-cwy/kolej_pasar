#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Student.h"
#include "Utilities.h"
#include "Handlers.h"

#pragma warning(disable:4996)

const char* STUDENT_FUNCTIONS[2] = {"View Score", "Back"};

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
			//student initialized with INVALID name in case student data cannot be read
			struct Student student = { .id = "INVALID" };
			readStudentData(strcat(tempId, ".bin"), &student);

			//Exit switch with error message if student data file cannot be found.
			if (strcmp(student.name, "INVALID") == 0) {
				flushTerminal();
				printMenuHeader();
				printf("Failed to read student data file.\n");
				printf("Please check if student ID was correctly typed.\n\n");
				break;
			};

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