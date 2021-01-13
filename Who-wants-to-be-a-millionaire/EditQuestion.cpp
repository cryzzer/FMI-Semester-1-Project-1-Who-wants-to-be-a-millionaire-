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
* <editQuestion function>
*
*/
#ifndef EDITQUESTION

#define EDITQUESTION 1

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <fstream>
#include "EditQuestion.h"
#include "UsefulFunctions.h"
#include "NewQuestion.h"

using namespace std;

void SearchIDInFiles(char searchQuestID[], char detZero[], char fileName[], bool& questionExists) {

	char newQuestion[1000] = { '\0' };//declaring qestion and answers
	char newOption1[100] = { '\0' };
	char newOption2[100] = { '\0' };
	char newOption3[100] = { '\0' };
	char newOption4[100] = { '\0' };
	char newCorrectAnswer = '\0';

	vector<string> editQuestionFile;//declaring a vectro, wehere we will store the information and will change the question and answers

	for (int i = 1; i <= 5; i++) {//going through all the files, because if the ID doesn't contain in one file, it may contain in another
		CopyStr(detZero, fileName);
		if (i == 1) {
			char verName[20] = "Life.txt";
			CopyStr(verName, fileName);
		}
		else if (i == 2) {
			char verName[20] = "History.txt";
			CopyStr(verName, fileName);
		}
		else if (i == 3) {
			char verName[20] = "Cinema.txt";
			CopyStr(verName, fileName);
		}
		else if (i == 4) {
			char verName[20] = "Sports.txt";
			CopyStr(verName, fileName);
		}
		else {
			char verName[20] = "Politics.txt";
			CopyStr(verName, fileName);
		}
		int lineCounter = 0;//checking on which line we want to enter new question and answers
		ifstream editFile(fileName);//dont forget to close file
		const int ID_SIZE = 12;
		char possibleID[ID_SIZE] = { '\0' };

		const int SIZE_OF_ROW = 1000;
		char currentLine[SIZE_OF_ROW];//declaring char array, where we will drag the information from each line
		while (editFile.getline(currentLine, SIZE_OF_ROW)) {
			lineCounter++;//adding counter
			for (int j = 0; j < 11; j++) {//if the ID's are equal, change the flag that this question exists
				if (searchQuestID[j] == currentLine[j]) {
					questionExists = true;
					continue;
				}
				else {
					questionExists = false;//if any of the symbols does not match, break the loop, continue with the next one and start the inner loop again
					break;
				}
			}
			if (questionExists == false) {//if any of the symbols does not match, break the loop, continue with the next one and start the inner loop again
				continue;
			}
			else {//if this question exists, print the question and ask user if that's the question that he wants to edit
				editFile.getline(currentLine, SIZE_OF_ROW);
				char ynOption = { '\0' };
				ProperNewLineToString(currentLine);//adding manually new line when a word is about to break between 2 lines
				system("cls");//clearing console
				NewLines(6);
				cout << "  ========================================== Who wants to be a millionaire? ==========================================\n\n";
				cout << "  " << searchQuestID;
				NewLines(2);
				cout << "  " << currentLine << endl;
				Border();
				NewLines(1);
				cout << "  Is this the question that you want to edit ? (please type 'y' for yes or 'n' for no)";
				cin >> ynOption;
				while (ynOption != 'y' && ynOption != 'n') {
					cin >> ynOption;
				}
				if (ynOption == 'n') {//if answer is no, return to previous menu
					editFile.close();
					system("cls");//clearing console
					return;
				}
				else if (ynOption == 'y') {//if yes turn the first digits of id into int
					system("cls");//clearing console
					int NumberQuestion = 0;
					//turn the first digits of id into int
					if (searchQuestID[3] == '0') {
						NumberQuestion = searchQuestID[4] - '0';
					}
					else {
						int afterNumber = searchQuestID[4] - '0';
						NumberQuestion = searchQuestID[3] - '0';
						NumberQuestion = (NumberQuestion * 10) + afterNumber;
					}
					//ask user to writhe question + 4 options + correct answer
					WritingNewQuestionAnswers(newQuestion, newOption1, newOption2, newOption3, newOption4, newCorrectAnswer, NumberQuestion, searchQuestID);
					QuestionCheckNewLine(newQuestion);//check if there is a new line, if yes, swap it for empty space
					int newQestLength = StrLength(newQuestion);//getting lengths string of all strings
					int newOpt1Length = StrLength(newOption1);
					int newOpt2Length = StrLength(newOption2);
					int newOpt3Length = StrLength(newOption3);
					int newOpt4Length = StrLength(newOption4);

					//add manually the number of question before actual question, depending if the number is a 2 digit or 1 digit
					if (searchQuestID[3] == '0') {
						char newLinequest[4] = "";
						char addNumberQuest[5] = "X. ";
						addNumberQuest[0] = searchQuestID[4];
						AddAdditonalCharacters(newQuestion, newQestLength, addNumberQuest);
					}
					else {
						char addNumberQuest[6] = "XX. ";
						addNumberQuest[0] = searchQuestID[3];
						addNumberQuest[1] = searchQuestID[4];
						AddAdditonalCharacters(newQuestion, newQestLength, addNumberQuest);
					}
					//adding options to availabe options ( A)  )
					char nOpt1[5] = "A) ";
					AddAdditonalCharacters(newOption1, newOpt1Length, nOpt1);
					char nOpt2[5] = "B) ";
					AddAdditonalCharacters(newOption2, newOpt2Length, nOpt2);
					char nOpt3[5] = "C) ";
					AddAdditonalCharacters(newOption3, newOpt3Length, nOpt3);
					char nOpt4[5] = "D) ";
					AddAdditonalCharacters(newOption4, newOpt4Length, nOpt4);

					editFile.close();//break the loop and close file
					break;

				}
			}
		}
		if (questionExists == false) {//if the ID doesn't match with any other, close the current file and move to the next one
			editFile.close();
			continue;
		}
		fstream changeFileInfo(fileName);//opening again

		while (changeFileInfo.getline(currentLine, SIZE_OF_ROW)) {//writing information into string vector
			editQuestionFile.push_back(currentLine);
		}

		//manually change question + answers
		editQuestionFile[lineCounter] = newQuestion;
		editQuestionFile[lineCounter + 1] = newOption1;
		editQuestionFile[lineCounter + 2] = newOption2;
		editQuestionFile[lineCounter + 3] = newOption3;
		editQuestionFile[lineCounter + 4] = newOption4;
		editQuestionFile[lineCounter + 6] = newCorrectAnswer;//here skip 1 line, because this line is empty and move to the next one (6)

		changeFileInfo.close();//close file

		ofstream clearFileInfo;//open file again
		clearFileInfo.open(fileName, ofstream::out | ofstream::trunc);//delete all previous data in file

		for (int j = 0; j < editQuestionFile.size(); j++) {//add new, edited data in file
			clearFileInfo << editQuestionFile[j] << endl;
		}

		clearFileInfo.close();//close file
		//printing successfull editing
		system("cls");//clearing console
		NewLines(6);
		cout << "  ========================================== Who wants to be a millionaire? ==========================================\n\n";
		cout << "                                      You have successfully edited the question!\n";
		cout << "                                   please press any key to return to previous menu!\n";
		Border();
		cout << "                                         ";
		system("pause");
		system("cls");//clearing console
		return;
	}
	if (questionExists == false) {//if there wasn't a ID that's contained in the files print that a question with this ID does not exists
		system("cls");//clearing console
		NewLines(6);
		cout << "  ========================================== Who wants to be a millionaire? ==========================================\n\n";
		cout << "                                It appears that a question with this ID does not exists,\n";
		cout << "                                      please press any key to return to previous menu!\n";
		Border();
		cout << "                                         ";
		system("pause");
		system("cls");//clearing console
	}
}

void AskForID(char searchQuestID[], char exitSymbol, char fileName[]) {
	char detZero[20] = { '\0' };//array which is used to fill another array with det. zeros

	bool questionExists = false;//flag if question exists

	questionExists = false;

	CopyStr(detZero, searchQuestID);//filling array with det. zeros
	NewLines(6);
	cout << "  ========================================== Who wants to be a millionaire? ==========================================\n\n";
	cout << "  Please insert the ID of the question that you want to edit: ID:XX-YYZZZ\n";
	cout << "  XX stands for number of question (1-15)\n";
	cout << "  YY stands for topic of question: (1 - Life; 2 - History; 3 - Cinema; 4 - Sports; 5 - Politics\n";
	cout << "  ZZZ stands for number of recurring question\n\n";
	cout << "  Example: ID:01-01001\n\n";
	cout << "  Enter 0 to return to Main Menu:\n";
	Border();
	cout << "\n  Enter ID of question or '0': ";
	cin >> searchQuestID;
	if ((searchQuestID[0] == exitSymbol) && (searchQuestID[1] == '\0')) {//check if 0 is input, return to previous menu
		system("cls");//clearing console
		return;
	}
	SearchIDInFiles(searchQuestID, detZero, fileName, questionExists);//searching for entered ID
}

void EditingExistingQuestion() {
	char searchQuestID[20] = { '\0' };
	char exitSymbol = '0';//entering this symbol when you want to leave menu
	char fileName[20] = { '\0' };

	do {
		AskForID(searchQuestID, exitSymbol, fileName);
		if ((searchQuestID[0] == exitSymbol) && (searchQuestID[1] == '\0')) {//asking over and over again
			return;
		}
	} while (searchQuestID[0] != exitSymbol);

}
#endif // EDITQUESTION
