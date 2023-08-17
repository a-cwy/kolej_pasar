#include <stdlib.h>
#include <stdio.h>

#include "Handlers.h"
#include "Utilities.h"

#pragma warning(disable:4996)

void main(void) {
	//int operationMode = 0 (initial operation condition) || 1 (admin) || 2 (student)
	int operationMode = 0;
	
	//print screen header
	printf("Kolej Pasar\n");
	printf("==================================================\n");

	//prompt for access mode
	printf("Type to select access mode\n1\t-\tadministrator mode\n2\t-\tstudent mode\n\n");
	modeSelectionHandler(&operationMode);

	//run relevant function based on operationMode
	//(operationMode == 1) ? /*admin mode function*/ : /*student mode function*/;

	system("pause");
}