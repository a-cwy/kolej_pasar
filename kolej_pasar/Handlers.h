#pragma once

void selectionHandler(int* operationModePtr, char** choicesArray, int choicesArraySize);
void writeStudentData(char* filename, struct Student* student);
void readStudentData(char* filename, struct Student* studentPtr);