#include <stdlib.h>
#include <stdio.h>

#include "Handlers.h"

#pragma warning(disable:4996)

void selectionHandler(int* operationModePtr, char** choicesArray, int choicesArraySize) {
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
			printf("%s selected.\n\n\n", choicesArray[*operationModePtr - 1]);
		}
		else {
			*operationModePtr = 0;
		}
	} while (*operationModePtr == 0);
}