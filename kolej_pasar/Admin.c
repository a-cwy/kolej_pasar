#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Admin.h"
#include "Utilities.h"
#include "Handlers.h"

#pragma warning(disable:4996)

const char* ADMIN_FUNCTIONS[5] = { "Add student", "View student", "Edit student", "Delete student", "Back"};

//FUNCTION DECLARATIONS
void addStudent(struct Student* studentPtr);
void displayStudentInformation(struct Student* studentPtr);

//main exported adminMode function
void adminMode() {
	int selectedFunction;

	flushTerminal();
	printMenuHeader();
	do {
		selectedFunction = 0;
		//prompt user for function selection
		selectionHandler(&selectedFunction, ADMIN_FUNCTIONS, 5);
		switch (selectedFunction) {
		case 1: //add student
		{
			struct Student newStudent;
			addStudent(&newStudent);
			
			//Process struct to generate remaining information
			generateFilepath(&newStudent);
			calcQualityPoint(&newStudent);
			calcGPA(&newStudent);
			calcCGPA(&newStudent);

			//Check if student already exists, then prompt to overwrite existing information
			struct Student tempStudent = { .name = "INVALID" };
			readStudentData(newStudent.filepath, &tempStudent);

			if (strcmp(tempStudent.name, "INVALID") != 0) { //When existing student is found.
				printf("\n\nStudent with ID %s already exists. Overwrite existing information? (Y/N) > ", newStudent.id);

				char choice;
				do { 
					rewind(stdin);
					choice = getchar();
					choice = toupper(choice);
				} while (choice != 'Y' && choice != 'N'); //Input validation

				if (choice == 'Y') { //Overwrites data only when user chooses to. Otherwise, no data is written to file.
					writeStudentData(newStudent.filepath, &newStudent);
					break;
				}
			}
			else { //Writes data to new file if no existing student can be found.
				writeStudentData(newStudent.filepath, &newStudent);
			}

			flushTerminal();
			printMenuHeader();
			printf("Student with ID %s successfully added.\n", newStudent.id);
			break;
		}
		case 2: //view student
		{
			char tempId[15];  //10 + 5 for file extension

			//Prompt user for student ID
			do {
				printf("Enter student ID to view > ");
				rewind(stdin);
				fgets(tempId, 10, stdin);
			} while (!checkIDValidity(&tempId));
			
			//Attempt to read student data from relevant file name.
			//student initialized with INVALID name in case student data cannot be read
			struct Student student = {.id = "INVALID"};
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
		case 3: //edit student
		{
			struct Student newStudent;

			//Get studentID to be edited
			do {
				printf("Enter student ID to be edited (ABCD12345) > ");
				rewind(stdin);
				fgets(newStudent.id, 10, stdin);
			} while (!checkIDValidity(newStudent.id));

			generateFilepath(&newStudent);

			//Check if student exists
			struct Student tempStudent = { .name = "INVALID" };
			readStudentData(newStudent.filepath, &tempStudent);
			if (strcmp(tempStudent.name, "INVALID") != 0) { //When existing student is found.
				printf("\n\nEnter new student information.\n");

				//Save old student filepath to delete relevant datafile if studentID is edited.
				char oldFilepath[15];
				strcpy(&oldFilepath, &newStudent.id);
				strcat(&oldFilepath, ".bin");

				addStudent(&newStudent);
				
				//Process struct to generate remaining information
				generateFilepath(&newStudent);
				calcQualityPoint(&newStudent);
				calcGPA(&newStudent);
				calcCGPA(&newStudent);

				writeStudentData(newStudent.filepath, &newStudent);
				//Delete relevant old datafile if studentID is edited.
				if (strcmp(&oldFilepath, &newStudent.filepath) != 0) {
					deleteStudentData(&oldFilepath);
				}

				flushTerminal();
				printMenuHeader();
				printf("Student with ID %s successfully edited.\n\n", newStudent.id);
			}
			else { //Prints error and exits if no existing student can be found.
				flushTerminal();
				printMenuHeader();
				printf("No such student with ID %s can be found.\n\n", newStudent.id);
			}
			
			break;
		}
		case 4: //delete student
		{
			struct Student student;

			//Get studentID to be deleted
			do {
				printf("Enter student ID to be deleted (ABCD12345) > ");
				rewind(stdin);
				fgets(student.id, 10, stdin);
			} while (!checkIDValidity(student.id));

			generateFilepath(&student);

			//Check if student exists
			struct Student tempStudent = { .name = "INVALID" };
			readStudentData(student.filepath, &tempStudent);
			if (strcmp(tempStudent.name, "INVALID") != 0) { //When existing student is found.
				//Confirmation prompt
				printf("Deleting student with ID %s. Are you sure? (Y/N) > ", student.id);

				char choice;
				do {
					rewind(stdin);
					choice = getchar();
					choice = toupper(choice);
				} while (choice != 'Y' && choice != 'N'); //Input validation

				if (choice == 'Y') {
					//Delete relevant datafile.
					deleteStudentData(&student.filepath);
					flushTerminal();
					printMenuHeader();
					printf("Student with ID %s successfully deleted.\n\n", student.id);
					break;
				}
			}
			else { //When existing student cannot be found
				flushTerminal();
				printMenuHeader();
				printf("Student with ID %s does not exist.\n\n", student.id);
				break;
			}

			//When user rejects delete confirmation
			flushTerminal();
			printMenuHeader();
			break;
		}
		case 5: //exit admin mode
			return; 
		default:
			break;
		}
	} while (selectedFunction != 0);
}

//----------ADDITIONAL FUNCTIONS----------
//Creates a new struct Student and returns it with initialized data based on user input
void addStudent(struct Student* studentPtr) {
	//Get student data from user input
	do {
		printf("Enter student ID (ABCD12345) > ");
		rewind(stdin);
		fgets(studentPtr->id, 10, stdin);
	} while (!checkIDValidity(studentPtr->id));
	
	printf("Enter student name > ");
	rewind(stdin);
	fgets(studentPtr->name, 81, stdin);

	//Loop to get semester and course information
	printf("--------------------------------------------------");
	for (int semester = 0; semester < 3; semester++) {
		for (int course = 0; course < 2; course++) {
			printf("\nEnter information for semester %d course %d.\n",semester + 1, course + 1);
			do {
				printf("Course code (AAA1000) \t> ");
				rewind(stdin);
				fgets(studentPtr->semesters[semester].courses[course].courseCode, 8, stdin);
			} while (!checkCourseCodeValidity(studentPtr->semesters[semester].courses[course].courseCode));
			
			do
			{
				printf("Credit Hours \t\t> ");
				rewind(stdin);
			} while (!scanf("%d", &studentPtr->semesters[semester].courses[course].creditHour));
			
			//loop to re-prompt for valid letterGrade value
			char inputBuffer[3];
			do {
				printf("A | A- | B+ | B | B- | C+ | C | F\n"
					"Grade\t\t\t> ");
				rewind(stdin);
				fgets(inputBuffer, 3, stdin);
				if (inputBuffer[1] == '\n') inputBuffer[1] = '\0';
			} while (getGradePoint(&inputBuffer) < 0.0f);
			strcpy(&studentPtr->semesters[semester].courses[course].letterGrade, &inputBuffer);


			printf("--------------------------------------------------");
		}
	}

	return;
}