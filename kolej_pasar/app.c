#include <stdlib.h>
#include <stdio.h>
#pragma warning(disable:4996)

//function to repeat prompt until valid mode is selected
void modeSelectionHandler(int* operationModePtr) {
	while (*operationModePtr == 0) {
		printf("> ");
		rewind(stdin);
		if (scanf("%d", operationModePtr) == NULL) continue;

		switch (*operationModePtr) {
		case 1:
			printf("Administrator mode selected.\n");
			return;

		case 2:
			printf("Student mode selected.\n");
			return;

		default:
			*operationModePtr = 0;
		}

	}
}

void main(void) {
	// int operationMode = 0 (repeat prompt) || 1 (admin) || 2 (student)
	int operationMode = 0;
	
	printf("Kolej Pasar\n");
	printf("==================================================\n");
	printf("Type to select access mode\n1\t-\tadministrator mode\n2\t-\tstudent mode\n\n\n");
	modeSelectionHandler(&operationMode);

	system("pause");
}