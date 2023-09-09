#include <stdlib.h>
#include <stdio.h>

#include "Handlers.h"
#include "Utilities.h"
#include "Admin.h"
#include "Student.h"

#pragma warning(disable:4996)

const char* OPERATION_MODES[3] = { "Administrator mode", "Student mode", "Exit"};

void main(void) {
	int operationMode;

	do {
		operationMode = 0;

		//print screen header
		flushTerminal();
		printMenuHeader();

		//prompt for access mode
		selectionHandler(&operationMode, OPERATION_MODES, 3);

		//run relevant function based on operationMode
		switch (operationMode) {
		case 1: //admin mode
			adminMode();
			break;
		case 2: //student mode
			studentMode();
			break;
		case 3: //exit
			printf("Thank you for using Kolej Pasar.\n\n");
			break;
		default:
			break;
		}
	} while (operationMode != 3);

	system("pause");
}