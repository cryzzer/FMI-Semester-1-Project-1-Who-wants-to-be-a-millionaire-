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
* <NEwQuestion function>
*
*/

#ifndef NEWQUESTION

#define NEWQUESTION 1


#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "NewQuestion.h"
#include "UsefulFunctions.h"
#include "NewGame.h"

using namespace std;

void PrintSuccessfulNewQuest() {
	NewLines(6);
	cout << "  ========================================== Who wants to be a millionaire? ==========================================\n\n";
	cout << "                                                   Congratulations!\n\n";
	cout << "                                        You have successfully added new question!\n";
	cout << endl;
	Border();
	cout << endl;
	system("pause");//pausing console
	system("cls");//clearing console
}

void EnteringNewInfoIntoFile(char fileName[], char question[], char option1[], char option2[], char option3[], char option4[], char& correctAnswer,
	char fullID[], int numberOfQuestion) {
	ofstream NewQuestion(fileName, ios::app);//append, starts the typing from the end of the file

	NewQuestion << endl << endl << fullID << endl;//inserting each string that has been saved
	NewQuestion << numberOfQuestion << ". " << question << "?" << endl;
	NewQuestion << "A) " << option1 << endl;
	NewQuestion << "B) " << option2 << endl;
	NewQuestion << "C) " << option3 << endl;
	NewQuestion << "D) " << option4 << endl << endl;
	NewQuestion << correctAnswer << endl;

	NewQuestion.close();//closing file
}

void WritingNewQuestionAnswers(char question[], char option1[], char option2[], char option3[], char option4[], char& correctAnswer,
	int& diffChoice, char fullQuestionID[]) {
	NewLines(6);
	cout << "  ========================================== Who wants to be a millionaire? ==========================================\n\n";
	cout << "  Please write your question below:  (please dont foget to add '?' at the end)\n  (question can hold up to 1000 symbols)\n";
	cout << endl;
	Border();
	cout << "\n  " << diffChoice << ". ";
	if (cin.peek() == '\n') {//using this to catch the new line symbol from the buffer, thats caused because of previous validation of cin
		cin.get();
	}
	cin.getline(question, 1000, '?');

	system("cls");//clearing console

	NewLines(6);
	cout << "  ========================================== Who wants to be a millionaire? ==========================================\n\n";
	cout << "  Please write your optional answers below:  (after completing the anwer, press 'Enter' to continue to the next one)\n";
	cout << "  (each answer can hold up to 100 symbols)\n";
	cout << endl;
	Border();
	char garbage[3] = { '\0' };//using this to suck the incoming new line from entering question
	cin.getline(garbage, 2, '\n');
	cout << "\n  " << "A) ";
	cin.getline(option1, 100, '\n');
	cout << "  " << "B) ";
	cin.getline(option2, 100, '\n');
	cout << "  " << "C) ";
	cin.getline(option3, 100, '\n');
	cout << "  " << "D) ";
	cin.getline(option4, 100, '\n');



	system("cls");//clearing console

	NewLines(6);
	cout << "  ========================================== Who wants to be a millionaire? ==========================================\n\n";
	cout << "  ID of question: " << fullQuestionID << endl;
	cout << "  " << diffChoice << ". " << question << "?\n\n";
	cout << "  A) " << option1 << endl;
	cout << "  B) " << option2 << endl;
	cout << "  C) " << option3 << endl;
	cout << "  D) " << option4 << endl;

	cout << endl;
	Border();
	cout << "  Which one is the correct answer? : (A, B, C or D)";
	do {
		cin >> correctAnswer;
	} while (correctAnswer != 'A' && correctAnswer != 'B' && correctAnswer != 'C' && correctAnswer != 'D');

	system("cls");//clearing console
}

void SelectingDifficultyOfQuestion(int& diffChoise, int numberOfQuetionChoises[]) {
	NewLines(6);
	cout << "  ========================================== Who wants to be a millionaire? ==========================================\n\n";
	cout << "  Select number of question 1-15 (form 1 to 15)\n\n";
	cout << "  Usually questions:    1-5 are considered to be with easy difficulty\n";
	cout << "                        6-10 are considered to be with avarage difficulty\n";
	cout << "                        11-15 are considered to be with hard difficulty\n";
	Border();
	cout << "\n\n  Please enter the number of your choice: ";
	bool validValidChoice = false;
	do {
		cin >> diffChoise;
		for (int i = 0; i < 15; i++) {
			if (diffChoise != numberOfQuetionChoises[i]) {//validation check
				continue;
			}
			validValidChoice = true;
			break;
		}
	} while (!validValidChoice);

}

void SelectingCategory(char& choice, char choiceSelection[]) {
	NewLines(6);
	cout << "  ========================================== Who wants to be a millionaire? ==========================================\n\n";
	cout << "  Enter which category, you want your question to be in:\n\n";
	cout << "  1. Life\n";
	cout << "  2. History\n";
	cout << "  3. Cinema\n";
	cout << "  4. Sports\n";
	cout << "  5. Politics\n\n";
	cout << "  0. For exiting and going back to the Main Menu\n";
	Border();
	cout << "\n\n  Please enter the number of your choice: ";
	ValidInput(choice, choiceSelection, 10);//choosing topic
}

void EnteringNewQuestion() {
	char choice = '\0';
	char choiceSelection[10] = { '1', '2', '3', '4', '5', '0' };

	SelectingCategory(choice, choiceSelection);
	char topic[20] = { '\0' };
	if (choice == '1') {
		char topic1[20] = "Life.txt";
		CopyStr(topic1, topic);
	}
	else if (choice == '2') {
		char topic2[20] = "History.txt";
		CopyStr(topic2, topic);
	}
	else if (choice == '3') {
		char topic3[20] = "Cinema.txt";
		CopyStr(topic3, topic);
	}
	else if (choice == '4') {
		char topic4[20] = "Sports.txt";
		CopyStr(topic4, topic);
	}
	else if (choice == '5') {
		char topic5[20] = "Politics.txt";
		CopyStr(topic5, topic);
	}
	else if (choice == '0') {
		system("cls");//clearing console
		return;
	}
	system("cls");//clearing console

	int diffChoise = 0;
	int numberOfQuetionChoises[20] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
	SelectingDifficultyOfQuestion(diffChoise, numberOfQuetionChoises);
	system("cls");//clearing console

	char questionID[6] = { 'I','D', ':', '\0', '\0' };//ID validation prototype
	IDLookingGenerator(diffChoise, questionID);//creating the front numbers

	int timesQuestionExists = 0;
	SearchHowManyPossibleQuestions(topic, timesQuestionExists, questionID);//searching how many times there is a question with this number  example: 2.

	char fullQuestionID[12] = { '\0' };
	CopyStr(questionID, fullQuestionID);
	int additionalQuestion = timesQuestionExists + 1;//the last 3 digits of the new question

	FullIDCreatingGenerator(choice, additionalQuestion, fullQuestionID);//creating the back numbers

	char question[1005] = { '\0' };
	char option1[105] = { '\0' };
	char option2[105] = { '\0' };
	char option3[105] = { '\0' };
	char option4[105] = { '\0' };
	char correctAnswer = '\0';

	WritingNewQuestionAnswers(question, option1, option2, option3, option4, correctAnswer, diffChoise, fullQuestionID);//User enters the new question + answers

	QuestionCheckNewLine(question);//checking for new line

	EnteringNewInfoIntoFile(topic, question, option1, option2, option3, option4, correctAnswer, fullQuestionID, diffChoise);//entering these statemets in the file

	PrintSuccessfulNewQuest();//print that the new question has been successfull
	return;
}

#endif // !NEWQUESTION