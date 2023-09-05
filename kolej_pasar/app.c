#include <stdlib.h>
#include <stdio.h>

#include "Handlers.h"
#include "Utilities.h"
#include "Admin.h"

#pragma warning(disable:4996)

const char* operationModesArray[2] = { "Administrator mode", "Student mode"};

void main(void) {
	//int operationMode = 1 (admin) || 2 (student)
	int operationMode = 0;
	
	//print screen header
	printMenuHeader();

	//prompt for access mode
	selectionHandler(&operationMode, operationModesArray, 2);

	//run relevant function based on operationMode
	switch (operationMode) {
	//admin mode	
	case 1:
		adminMode(&operationMode);
		break;
	case 2:
		break;
	default:
		printf("Unexpected invalid operation mode, please restart program.");
		break;
	}

	system("pause");
}