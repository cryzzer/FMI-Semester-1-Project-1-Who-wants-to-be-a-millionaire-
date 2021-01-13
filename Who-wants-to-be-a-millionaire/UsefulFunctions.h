#pragma once
char LevelFromIntToChar(int level);

void NewLines(int number);

void EmptySpaces(int number);

void IDLookingGenerator(int level, char questionID[6]);

void FullIDCreatingGenerator(int topicChoice, int number, char fullQuestionID[]);

void FillingEmptySpace(char option[], int optionSize);

void CopyStr(char originalString[], char copiedVersion[]);

int StrLength(char str[]);

void Border();

void ValidInput(char& number, char string[], const int SIZE_OF_STRING);

void ValidInputForWords(char enteringWord[], char possibleWord[], int MessageSize, bool& incorrectValidation);

void AddAdditonalCharacters(char OGstring[], int& OGlength, char addstr1[]);

void ProperNewLineToString(char question[]);

void ThanksForPlaying();

void QuestionCheckNewLine(char question[]);