#pragma once

void selectionHandler(int* operationModePtr, const char** choicesArray, int choicesArraySize);
void writeStudentData(char* filename, struct Student* student);
void readStudentData(char* filename, struct Student* studentPtr);
void deleteStudentData(char* filename);