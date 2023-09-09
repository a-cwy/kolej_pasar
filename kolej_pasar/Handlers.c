#include <stdlib.h>
#include <stdio.h>

#include "Handlers.h"
#include "Utilities.h"

#pragma warning(disable:4996)

//Handle selection screens
void selectionHandler(int* operationModePtr, const char** choicesArray, int choicesArraySize) {
	/*printf("Type to select access mode\n"
		"1\t-\tAdministrator mode\n"
		"2\t-\tStudent mode\n\n");*/

	//print choices 
	printf("Type to select\n");
	for (int i = 0; i < choicesArraySize; i++) {
		printf("%d\t-\t%s\n", i + 1, choicesArray[i]);
	}
	printf("\n");

	do {
		printf("> ");

		//return value check
		rewind(stdin);
		if (!scanf("%d", operationModePtr)) continue;

		//check for selected operation mode and update operationMode variable in main()
		//if input is invalid, repeat prompt
		if (choicesArray[*operationModePtr - 1]) {
			flushTerminal();
			printMenuHeader();
			printf("%s :\n\n", choicesArray[*operationModePtr - 1]);
		}
		else {
			*operationModePtr = 0;
		}
	} while (*operationModePtr == 0);
}

//Login handler


//---------FUNCTIONS TO HANDLE READING/WRITING OF STUDENT DATA---------
//Adds student data to data file
void writeStudentData(char* filename, struct Student* student) {
	FILE* fptr;

	if ((fptr = fopen(filename, "wb")) == NULL) {
		printf("Failed to create student data file.");
		return;
	}

	fwrite(student, sizeof(struct Student), 1, fptr);
	fclose(fptr);

	return;
}

//Reads student data from data file into passed array ptr
void readStudentData(char* filename, struct Student* studentPtr) {
	FILE* fptr;

	if ((fptr = fopen(filename, "rb")) == NULL) {
		strcpy(studentPtr->name, "INVALID");
		return;
	}

	fread(studentPtr, sizeof(struct Student), 1, fptr);
	fclose(fptr);

	return;
}

void deleteStudentData(char* filename) {
	if (remove(filename)) {
		printf("\n\nFailed to delete file.\n\n");
	}

	return;
}