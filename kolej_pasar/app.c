#include <stdlib.h>
#include <stdio.h>

#include "Handlers.h"
#include "Utilities.h"
#include "Admin.h"

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
			//admin mode	
		case 1:
			adminMode(&operationMode);
			break;
		case 2:
			break;
		case 3:
			printf("Thank you for using Kolej Pasar.\n\n");
			break;
		default:
			printf("\n\nUnexpected invalid operation mode, please restart program.\n\n");
			break;
		}
	} while (operationMode != 3);

	system("pause");
}