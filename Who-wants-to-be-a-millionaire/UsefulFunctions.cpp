/**
*
* Solution to course project # 1
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2020/2021
*
* @author Danail Nenkov
* @idnumber 62518
* @compiler VC
*
* <useful functions>
*
*/
#ifndef FUNCS
#define FUNCS 1

#include <iostream>
#include <iomanip>
#include "UsefulFunctions.h"

using namespace std;

char LevelFromIntToChar(int level) {//turning level number into number of ID    example: ID:01
	return '0' + level;
}
void NewLines(int number) {
	for (int i = 0; i < number; i++) {//printing new lines
		cout << endl;
	}
}
void EmptySpaces(int number) {
	for (int i = 0; i < number; i++) {//printing empty spaces
		cout << ' ';
	}
}
void IDLookingGenerator(int level, char questionID[6]) {//creating the ID that the program will look for only for front numbers
	if (level < 10) {
		char numberOfID = LevelFromIntToChar(level);
		questionID[3] = '0';//manual adding 0
		questionID[4] = numberOfID;
	}
	else {
		level = level % 10;
		char numberOfID = LevelFromIntToChar(level);
		questionID[3] = '1';//manual adding 1
		questionID[4] = numberOfID;
	}
}
void FullIDCreatingGenerator(int topicChoice, int number, char fullQuestionID[]) {	//creating the ID that the program will look for only for back numbers
	fullQuestionID[5] = '-';
	fullQuestionID[6] = '0';
	fullQuestionID[7] = topicChoice;
	if (number >= 100) {
		int hundreds = number / 100;
		number = number % 100;
		int tens = number / 10;
		int ones = number % 10;
		fullQuestionID[8] = LevelFromIntToChar(hundreds);
		fullQuestionID[9] = LevelFromIntToChar(tens);
		fullQuestionID[10] = LevelFromIntToChar(ones);
	}
	else if (number <= 99 && number >= 10) {
		int tens = number / 10;
		int ones = number % 10;
		fullQuestionID[8] = '0';
		fullQuestionID[9] = LevelFromIntToChar(tens);
		fullQuestionID[10] = LevelFromIntToChar(ones);
	}
	else {
		fullQuestionID[8] = '0';
		fullQuestionID[9] = '0';
		fullQuestionID[10] = LevelFromIntToChar(number);
	}
}

void CopyStr(char originalString[], char copiedVersion[]) {
	int i = 0;
	for (i = 0; originalString[i] != '\0'; i++) {//coppying the text, while the loop meets a terminating zero
		copiedVersion[i] = originalString[i];
	}
	copiedVersion[i] = '\0';//than we add manual terminating zero after the last symbol
}

int StrLength(char str[]) {
	int size = 0;
	while (str[size] != '\0') {//getting size of string      
		size++;
	}
	return size;
}

void Border() {
	cout << endl;
	cout << setw(3);
	const int SIZE_OF_CONSOLE_ROW = 120;
	for (int i = 0; i < (SIZE_OF_CONSOLE_ROW - 4);i++) {//printing border
		cout << '=';
	}
	cout << endl;
}

void ValidInput(char& number, char string[], const int SIZE_OF_STRING) {
	bool validChoice = false;
	do {
		cin >> number;
		for (int i = 0; i < SIZE_OF_STRING;i++) {//if the input does not match with any of the remaining options, 
			if (number != string[i]) {         //continue the loop untill a viable option is inputed
				continue;
			}
			validChoice = true;//flag for stopping the function
			break;
		}
	} while (!validChoice);//looping while a valid choice isn't entered
}

void ValidInputForWords(char enteringWord[], char possibleWord[], int MessageSize, bool& incorrectValidation) {
	for (int i = 0; i < MessageSize; i++) {
		if (enteringWord[i] != possibleWord[i]) {
			incorrectValidation = true;//if an element is different, break the loop and change bool to show that the words do not match
			break;
		}
	}
}

void AddAdditonalCharacters(char OGstring[], int& OGlength, char addstr1[]) {
	int additionalLength1 = StrLength(addstr1);
	for (int i = OGlength - 1; i >= 0; i--) {//coppying all elemtnts 'i' positions forward, so new characters can be swapped in the begining
		OGstring[i + additionalLength1] = OGstring[i];
	}

	for (int i = 0; addstr1[i] != '\0'; i++) {//coppying the text, while the loop meets a terminating zero
		OGstring[i] = addstr1[i];
	}
	OGlength = StrLength(OGstring);
}
void FillingEmptySpace(char option[], int optionSize) {//filling the space of an option for 50/50 joker
	for (int i = 0; i < optionSize; i++) {
		option[i] = ' ';
	}
	option[optionSize] = '\0';
}
void ProperNewLineToString(char question[]) {
	const int SIZE_OF_CONSOLE_ROW = 120;//this will be the default size of the row of the console
	int questionSize = StrLength(question);//finding the size of the question

	//if the size is more than 116(which is where the double lines end), this part of the code finds where is the last position,
	//where there isn't a latin letter, and starts copying the rest of the elements from his right side 2 steps over,
	//then rewrites the found position to a new line, and the second two elements after him to 2 space bars
	if (questionSize > (SIZE_OF_CONSOLE_ROW - 4)) {
		int startElementToCopy = SIZE_OF_CONSOLE_ROW - 4;
		for (startElementToCopy = SIZE_OF_CONSOLE_ROW - 4; ((question[startElementToCopy] <= 'Z' && question[startElementToCopy] >= 'A') ||
			(question[startElementToCopy] <= 'z' && question[startElementToCopy] >= 'a')); startElementToCopy--) {
		}
		for (int currentPosOfElement = questionSize; currentPosOfElement > startElementToCopy; currentPosOfElement--) {
			question[currentPosOfElement + 2] = question[currentPosOfElement];
		}
		question[startElementToCopy] = '\n';
		question[startElementToCopy + 1] = ' ';
		question[startElementToCopy + 2] = ' ';
	}
}
void ThanksForPlaying() {//exiting message
	NewLines(6);
	Border();
	cout << "\n\n                                         Thanks for playing, have a nice day !\n\n";
	Border();
	NewLines(6);
}

void QuestionCheckNewLine(char question[]) {//checking if in the inserted new question somewhere is a symbol for new line, if yes turns it into empty space
	int sizeQuestion = StrLength(question);
	for (int i = 0; i < sizeQuestion; i++) {
		if (question[i] == '\n') {
			question[i] = ' ';
		}
	}
}

#endif // !FUNCS