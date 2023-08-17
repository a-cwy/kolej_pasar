#include <stdlib.h>
#include <stdio.h>

#include "Handlers.h"

#pragma warning(disable:4996)

void modeSelectionHandler(int* operationModePtr) {
	while (*operationModePtr == 0) {
		printf("> ");

		//return value check
		rewind(stdin);
		if (!scanf("%d", operationModePtr)) continue;

		//check for selected operation mode and update operationMode variable in main()
		//if input is invalid, repeat prompt
		switch (*operationModePtr) {
		case 1:
			printf("Administrator mode selected.\n\n");
			return;

		case 2:
			printf("Student mode selected.\n\n");
			return;

		default:
			*operationModePtr = 0;
		}
	}
}