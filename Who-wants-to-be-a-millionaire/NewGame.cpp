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
* <NewGame function>
*
*/
#ifndef NEWGAME

#define NEWGAME 1



#include <iostream>
#include "UsefulFunctions.h"
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include "NewGame.h"

using namespace std;

void PrintQuestionAndAnswers(char printingQuestionID[], char question[], char option1[], char option2[], char option3[], char option4[],
	char correctAnswer, char possibleAnswers[], const int SIZE_OF_ANSWERS, int& level, bool& gameLost, bool& fFjoker, bool& audJoker, bool& friendJoker, char gameOverQuestion[]) {

	ProperNewLineToString(question);

	int option1Size = StrLength(option1);//using this to center the options
	int option3Size = StrLength(option3);

	char inputAnswer = '\0';

	const int MESSAGE_SIZE = 4;//the size of message yes or no!
	char inputChoiceIfJoker = '\0';
	bool AskUsingJoker = true;//asks if the user wants to use joker
	bool showingAvailableJokers = false;

	if (fFjoker == true || audJoker == true || friendJoker == true) {
		AskUsingJoker = true;//if at least 1 joker is available ask user
	}
	else {
		AskUsingJoker = false;//otherwise no
	}

	bool AudienceHelp = false;//activating help
	bool FriendHelp = false;//activating help
	bool incorrectValidation = false;
	do {//if an incorrect choice is being validated, it resets the page, giving the user the ability to enter again, untill a valid choice is inputed



		NewLines(6);
		cout << "  " << printingQuestionID << endl;
		Border();
		cout << "\n  " << question << endl << endl;
		cout << "  " << option1;
		EmptySpaces(60 - option1Size);//how many empty spaces there will be so B) and D) are in one line
		cout << option2 << endl;
		cout << "  " << option3;
		EmptySpaces(60 - option3Size);
		cout << option4 << endl;//not working properly
		if (AudienceHelp == true) {
			AudienceHelpJoker(possibleAnswers, correctAnswer, level);//activating help
			AudienceHelp = false;
		}
		if (FriendHelp == true) {
			CallFriendJoker(possibleAnswers, correctAnswer, level);//activating help
			FriendHelp = false;
		}

		Border();
		if (AskUsingJoker == true) {
			cout << "  Do you want to use a joker? (type: 'y' for yes or 'n' for no)";
			if (incorrectValidation == true) {
				cout << "  \n  Please enter a valid input(y/n)";
			}
			cin >> inputChoiceIfJoker;

			if ((inputChoiceIfJoker != 'y') && (inputChoiceIfJoker != 'n')) {//checking if the user said no!
				incorrectValidation = true;
				system("cls");//clearing console
				continue;
			}
			else {
				incorrectValidation = false;
			}

			if (inputChoiceIfJoker == 'y') {
				showingAvailableJokers = true;
			}
			else if (inputChoiceIfJoker == 'n') {
				showingAvailableJokers = false;//disabling jockers for round
				AskUsingJoker = false;//disabling jockers for round
				system("cls");//clearing console
				continue;
			}

			if (showingAvailableJokers == true) {//if he wants jocker
				char ff = '\0';
				char aud = '\0';
				char frnd = '\0';
				char exit = '0';

				if (fFjoker == true || audJoker == true || friendJoker == true) {//asking for a valid input
					cout << "  Enter your choice:" << endl;
					if (fFjoker == true) {
						cout << "  press X for 50/50" << endl;
						ff = 'X';
					}
					if (audJoker == true) {
						cout << "  press Y for help from the audience" << endl;
						aud = 'Y';
					}
					if (friendJoker == true) {
						cout << "  press Z for calling a friend" << endl;
						frnd = 'Z';
					}
					cout << "  press 0 for escape:" << endl;
				}
				cout << "  Your choice:";
				char choice = '\0';
				do {
					cin >> choice;

				} while (choice != ff && choice != aud && choice != frnd && choice != exit);

				if (choice == ff) {//activating 50/50 jocker and disabling him for future rounds
					FiftyFiftyJoker(correctAnswer, option1, option2, option3, option4);
					fFjoker = false;
					system("cls");//clearing console
					AskUsingJoker = false;
					continue;
				}
				else if (choice == aud) {//activating help from audience jocker and disabling him for future rounds
					AudienceHelp = true;
					audJoker = false;
					system("cls");//clearing console
					AskUsingJoker = false;
					continue;
				}
				else if (choice == frnd) {//activating help from friend jocker and disabling him for future rounds
					FriendHelp = true;
					friendJoker = false;
					system("cls");//clearing console
					AskUsingJoker = false;
					continue;
				}
				else if (choice == exit) {//exiting jokers menu, and giving the ability to choose to use them again
					AskUsingJoker = true;
					system("cls");//clearing console
					continue;
				}
			}
		}
		cout << "  Your answer (" << possibleAnswers[0] << ", " << possibleAnswers[1] << ", " << possibleAnswers[2] << " or " << possibleAnswers[3] << "): ";
		cin >> inputAnswer;
		system("cls");//clearing console
	} while (inputAnswer != possibleAnswers[0] && inputAnswer != possibleAnswers[1] && inputAnswer != possibleAnswers[2] && inputAnswer != possibleAnswers[3]);

	//ValidInput(inputAnswer, possibleAnswers, sizeOfAnswers);
	if (inputAnswer == correctAnswer) {
	}
	else {
		gameLost = true;//game over if answer isn't correct
		if (option1[0] == correctAnswer) {
			CopyStr(option1, gameOverQuestion);
		}
		else if (option2[0] == correctAnswer) {
			CopyStr(option2, gameOverQuestion);
		}
		else if (option3[0] == correctAnswer) {
			CopyStr(option3, gameOverQuestion);
		}
		else {
			CopyStr(option4, gameOverQuestion);
		}
	}
}

void SearchHowManyPossibleQuestions(char nameOfFile[], int& timesQuestionExists, char questionID[]) {
	ifstream questionFile(nameOfFile);  //opening file
	char printingString[6] = { '\0' }; //creating an char array, that will compare later
	const int SIZE_OF_ROW = 1000;
	char gettingLine[SIZE_OF_ROW];
	while (questionFile.getline(gettingLine, SIZE_OF_ROW)) {//getting the whole line
		for (int i = 0; i < 6; i++) {
			printingString[i] = gettingLine[i];//rewriting the first 5 simbols to a new char array
		}
		printingString[5] = '\0';//adding manual terminating zero to the last element

		bool isSame = true;//creating a flag that will signal if the arrays are equal(the IDs)
		for (int i = 0; i < 5; i++) {
			if (printingString[i] != questionID[i]) {
				isSame = false;
				break;
			}
		}
		if (isSame) {
			timesQuestionExists++;//giving the integer +1 to its value
		}
	}
	questionFile.close();//closing file
}

void PrintPassedQuestion(int possibleEarnings[], int& level) {//printing won amount of money for round
	NewLines(6);
	Border();
	cout << endl;
	cout << "                                      Congratulations, you won " << possibleEarnings[level - 1] << '$' << endl;//winning money after round
	Border();
}

void PrintGameOver(int possibleEarnings[], int& level, char gameOverQuestion[]) {//printing game over
	NewLines(6);
	Border();
	cout << endl;//if user lost game, he wins an amount, after a certain level is passed
	cout << "                                                      GAME OVER\n";
	cout << "                                          The correct answer was: " << gameOverQuestion << endl;// printing the correct answer
	if (level <= 5) {
		cout << "                                                 You have won 0$";
	}
	else if (level > 5 && level <= 10) {
		cout << "                                                You have won 1000$";
	}
	else if (level > 10 && level < 16) {
		cout << "                                               You have won 32000$";
	}

	Border();
}

void FiftyFiftyJoker(char correctAnswer, char option1[], char option2[], char option3[], char option4[]) {
	int sizeOption1 = StrLength(option1);//getting the size of all 4 options
	int sizeOption2 = StrLength(option2);
	int sizeOption3 = StrLength(option3);
	int sizeOption4 = StrLength(option4);

	srand(time(nullptr));//setting the seed, from which the randomiser will randomise
	int skipNumber = 0;
	if (option1[0] == correctAnswer) {
		skipNumber = 1;
	}
	else if (option2[0] == correctAnswer) {//finding which option is the correct answer
		skipNumber = 2;
	}
	else if (option3[0] == correctAnswer) {
		skipNumber = 3;
	}
	else if (option4[0] == correctAnswer) {
		skipNumber = 4;
	}

	int storage[5];//storage where the two numbers are stored

	int randomNumber1;
	do {
		randomNumber1 = rand() % 4 + 1;
	} while (randomNumber1 == skipNumber);//randomising the first one, and checking if it does not match with the correct answer number

	storage[0] = randomNumber1;//storing the first number
	int randomNumber2;
	do {
		randomNumber2 = rand() % 4 + 1;
	} while (randomNumber2 == storage[0] || randomNumber2 == skipNumber);//doing the same as the first number, but checks if it does not match with the 1st one

	switch (randomNumber1) {//this is the part, where the selected options to be removed are turned into empty spaces
	case 1:
		FillingEmptySpace(option1, sizeOption1);
		if (randomNumber2 == 2) {
			FillingEmptySpace(option2, sizeOption2);
		}
		else if (randomNumber2 == 3) {
			FillingEmptySpace(option3, sizeOption3);
		}
		else if (randomNumber2 == 4) {
			FillingEmptySpace(option4, sizeOption4);
		}
		break;
	case 2:
		FillingEmptySpace(option2, sizeOption2);
		if (randomNumber2 == 1) {
			FillingEmptySpace(option1, sizeOption1);
		}
		else if (randomNumber2 == 3) {
			FillingEmptySpace(option3, sizeOption3);
		}
		else if (randomNumber2 == 4) {
			FillingEmptySpace(option4, sizeOption4);
		}
		break;
	case 3:
		FillingEmptySpace(option3, sizeOption3);
		if (randomNumber2 == 1) {
			FillingEmptySpace(option1, sizeOption1);
		}
		else if (randomNumber2 == 2) {
			FillingEmptySpace(option2, sizeOption2);
		}
		else if (randomNumber2 == 4) {
			FillingEmptySpace(option4, sizeOption4);
		}
		break;
	case 4:
		FillingEmptySpace(option4, sizeOption4);
		if (randomNumber2 == 1) {
			FillingEmptySpace(option1, sizeOption1);
		}
		else if (randomNumber2 == 2) {
			FillingEmptySpace(option2, sizeOption2);
		}
		else if (randomNumber2 == 3) {
			FillingEmptySpace(option3, sizeOption3);
		}
		break;
	}
}

void AudienceHelpJoker(char possibleAnswers[], char correctAnswer, int& level) {
	srand(time(nullptr));//setting the seed, from which the randomiser will randomise
	int currentMaxPercentage = 100;//this is equal to 100%
	int percentChanceofLying = 0;//getting the percantage of lying
	if (level >= 1 && level <= 5) {//the bigger the level is, the bigger the percentage is
		percentChanceofLying = 30;
	}
	else if (level >= 6 && level <= 10) {
		percentChanceofLying = 60;
	}
	else if (level >= 11 && level <= 15) {
		percentChanceofLying = 80;
	}
	int randomNumber1 = rand() % currentMaxPercentage + 1;

	if (randomNumber1 > percentChanceofLying) {//deciding if the number rolled over the "percentChanceofLying"
		cout << "\n  The audiece has decided! They think that the correct answer is " << correctAnswer << endl;
	}
	else {//if it rolled under, create a random option to be printed, as a lie
		int indexOfCorrectAnswer = 0;
		for (int i = 0; i < 4; i++) {
			if (possibleAnswers[i] == correctAnswer) {
				indexOfCorrectAnswer = i;
				break;
			}
		}
		int optionOneToFour = 0;
		do {
			optionOneToFour = rand() % 4 + 0;
		} while (optionOneToFour == indexOfCorrectAnswer);
		cout << "\n  The audiece has decided! They think that the correct answer is " << possibleAnswers[optionOneToFour] << endl;
	}
}

void CallFriendJoker(char possibleAnswers[], char correctAnswer, int& level) {//basicly the same function as help from the audience, but with different prints
	srand(time(nullptr));//setting the seed, from which the randomiser will randomise
	int currentMaxPercentage = 100;
	int percentChanceofLying = 0;
	if (level >= 1 && level <= 5) {
		percentChanceofLying = 30;
	}
	else if (level >= 6 && level <= 10) {
		percentChanceofLying = 60;
	}
	else if (level >= 11 && level <= 15) {
		percentChanceofLying = 80;
	}
	int randomNumber1 = rand() % currentMaxPercentage + 1;

	if (randomNumber1 > percentChanceofLying) {
		cout << "\n  Hello, I think that the correct answer should be " << correctAnswer << endl;
	}
	else {
		int indexOfCorrectAnswer = 0;
		for (int i = 0; i < 4; i++) {
			if (possibleAnswers[i] == correctAnswer) {
				indexOfCorrectAnswer = i;
				break;
			}
		}
		int optionOneToFour = 0;
		do {
			optionOneToFour = rand() % 3 + 0;
		} while (optionOneToFour == indexOfCorrectAnswer);
		cout << "\n  Hello, I think that the correct answer should be " << possibleAnswers[optionOneToFour] << endl;
	}
}

void PrintSelectedQuestion(char nameOfFile[], int numberOfSelectedQuestion, char questionID[], int& level, bool& gameLost, bool& fFjoker, bool& audJoker, bool& friendJoker,
	char gameOverQuestion[]) {
	const int SIZE_OF_ROW = 1000;//row equals line

	ifstream questionFile(nameOfFile);  //opening file

	//the array will have exactly 5 simbols inside, which is the number of the ID  example: "ID:01"+terminating zero
	char printingString[6] = { '\0' };    //creating an char array, that will compare later;
	char gettingLine[SIZE_OF_ROW];

	int currentNumberOfQuestion = 0;

	char printingQuestionID[20] = { '\0' };//12 is the size of ID 

	char question[SIZE_OF_ROW] = { '\0' };
	char option1[SIZE_OF_ROW / 10] = { '\0' };
	char option2[SIZE_OF_ROW / 10] = { '\0' };
	char option3[SIZE_OF_ROW / 10] = { '\0' };
	char option4[SIZE_OF_ROW / 10] = { '\0' };
	char correctAnswer = { '\0' };

	while (questionFile.getline(gettingLine, SIZE_OF_ROW)) {//getting the whole line
		for (int i = 0; i < 6; i++) {
			printingString[i] = gettingLine[i];//rewriting the first 5 simbols to a new char array
		}
		printingString[5] = '\0';//adding manual terminating zero to the last element

		bool isSame = true;//creating a flag that will signal if the arrays are equal(the IDs)

		for (int i = 0; i < 5; i++) {
			if (printingString[i] != questionID[i]) {
				isSame = false;
				break;
			}
		}
		if (isSame) {
			currentNumberOfQuestion++;//giving the integer +1 to its value
		}

		//after fining the desired question,begin a manual copying of 
		//the question + possible answers + correct answer
		if (currentNumberOfQuestion == numberOfSelectedQuestion) {

			for (int i = 0; i < 12; i++) {
				printingQuestionID[i] = gettingLine[i];
			}
			printingQuestionID[11] = '\0';//manual adding of ID of question, ready for print

			questionFile.getline(gettingLine, SIZE_OF_ROW, '\n');//gettig question
			CopyStr(gettingLine, question);//coppying question

			questionFile.getline(gettingLine, SIZE_OF_ROW, '\n');//getting option 1
			CopyStr(gettingLine, option1);//coppying option 1, same goes for the other 3 options

			questionFile.getline(gettingLine, SIZE_OF_ROW, '\n');
			CopyStr(gettingLine, option2);

			questionFile.getline(gettingLine, SIZE_OF_ROW, '\n');
			CopyStr(gettingLine, option3);


			questionFile.getline(gettingLine, SIZE_OF_ROW, '\n');
			CopyStr(gettingLine, option4);

			//since there is a new line between the 4th option and the correct answer, skip 1 line of the text
			questionFile.getline(gettingLine, SIZE_OF_ROW, '\n');
			questionFile.getline(gettingLine, SIZE_OF_ROW, '\n');
			correctAnswer = gettingLine[0];//copying the correct answer

			questionFile.close();
		}
	}
	int sizeOfAnswers = 5;
	char possibleAnswers[5] = { 'A', 'B', 'C', 'D' };//adding valid choices to be compared with the input
	PrintQuestionAndAnswers(printingQuestionID, question, option1, option2, option3, option4, correctAnswer, possibleAnswers, sizeOfAnswers,
		level, gameLost, fFjoker, audJoker, friendJoker, gameOverQuestion);
}

void StartNewGame(char nameOfFile[], bool randomTopic) {
	system("cls");//clearing console
	srand(time(nullptr));//setting the seed, from which the randomiser will randomise
	int level = 1;//levels(questions) from 1 to 15 (currently working with questions to 10)

	char questionID[6] = { 'I','D', ':', '\0', '\0' };//ID validation prototype

	bool fFjoker = true;
	bool audJoker = true;
	bool friendJoker = true;

	bool gameLost = false;//flag that will show if an incorrect answer has been entered, resulting Game Over
	const int NUMBER_SUMS = 15;
	//sum of how much money will the user win after each round
	int possibleEarnings[NUMBER_SUMS] = { 100, 200, 300, 500, 1000, 2000, 4000, 8000, 16000, 32000, 64000, 125000, 250000, 500000, 1000000 };
	do {
		if (randomTopic == true) {
			char determZero[20] = { '\0' };
			CopyStr(determZero, nameOfFile);
			int randNumb = rand() % 5 + 1;
			if (randNumb == 1) {
				char topicName1[20] = "Life.txt";
				CopyStr(topicName1, nameOfFile);
			}
			else if (randNumb == 2) {
				char topicName2[20] = "History.txt";
				CopyStr(topicName2, nameOfFile);
			}
			else if (randNumb == 3) {
				char topicName3[20] = "Cinema.txt";
				CopyStr(topicName3, nameOfFile);
			}
			else if (randNumb == 4) {
				char topicName4[20] = "Sports.txt";
				CopyStr(topicName4, nameOfFile);
			}
			else if (randNumb == 5) {
				char topicName5[20] = "Politics.txt";
				CopyStr(topicName5, nameOfFile);
			}
		}
		IDLookingGenerator(level, questionID);//creating ID to search for

		int timesQuestionExists = 0;
		SearchHowManyPossibleQuestions(nameOfFile, timesQuestionExists, questionID);//finding how many questions for level are available

		int numberOfSelectedQuestion = rand() % timesQuestionExists + 1;//creating a random number (from 1 to the number of max questions for level)
																		//that will indicate when the program has "traveled" to this question

		char gameOverQuestion[70] = { '\0' };

		PrintSelectedQuestion(nameOfFile, numberOfSelectedQuestion, questionID, level, gameLost, fFjoker, audJoker, friendJoker, gameOverQuestion);//printing question and answers

		if (!gameLost) {
			if (level < 15) {

				bool inCorrectValidation = false;
				char yesNo = '\0';
				bool contGame = true;

				PrintPassedQuestion(possibleEarnings, level);//pringting the prize for round
				cout << "\n                     Do you want to keep the money, and stop playing ?(type 'y' for yes or 'n' for no)";


				cin >> yesNo;
				while (yesNo != 'y' && yesNo != 'n') {
					system("cls");//clearing console
					PrintPassedQuestion(possibleEarnings, level);//pringting the prize for round
					cout << "\n                     Do you want to keep the money, and stop playing ?(type 'y' for yes or 'n' for no)";
					cout << "\n\n                                  Incorrect validation, please type (y/n)";
					cin >> yesNo;
				}
				if (yesNo == 'y') {
					system("cls");//clearing console
					NewLines(6);
					cout << "  ========================================== Who wants to be a millionaire? ==========================================\n\n";
					cout << "                             You won " << possibleEarnings[level - 1] << "$ in Who wants to be a millionaire, thanks for playing! ";
					cout << endl;//keeping money and leaving game
					Border();
					break;
				}
				else if (yesNo == 'n') {
					system("cls");//clearing console
				}
			}
		}
		else {
			PrintGameOver(possibleEarnings, level, gameOverQuestion);//printing game over
		}
		level++;//level up

	} while (level <= 15 && gameLost == false);//contitions when the game is lost/ stops playing it

	if (level == 16 && gameLost == false) {
		NewLines(6);
		cout << "  ========================================== Who wants to be a millionaire? ==========================================\n\n";
		cout << endl;
		cout << "                                 Congratulations, you have won the big prize of 1,000,000$ \n\n";// if level 15 is completed, user wins the big prize
		cout << "                                                  Thanks for playing!";
		Border();
	}
	cout << endl;
	system("pause");
	system("cls");//clearing console
	return;
}

void NewGame() {
	NewLines(6);
	cout << "  ========================================== Who wants to be a millionaire? ==========================================\n\n";
	cout << endl;
	cout << "                                                   Choose category:\n\n";
	cout << "                                                        1. Life\n";
	cout << "                                                        2. History\n";
	cout << "                                                        3. Cinema\n";
	cout << "                                                        4. Sports\n";
	cout << "                                                        5. Politics\n\n";
	cout << "                                                        9. All categories\n\n";
	cout << "                                                 0. For returnig to Main Menu\n\n";

	Border();
	cout << "Enter your choice: ";

	const int SIZE_OF_STRING = 10;
	char possibleChoices[SIZE_OF_STRING] = { '1', '2', '3', '4', '5', '9', '0' };
	char choice;
	ValidInput(choice, possibleChoices, SIZE_OF_STRING);

	bool randomTopic = false;//adding option to choose all categories

	if (choice == '1') {
		char topic[20] = "Life.txt";
		randomTopic = false;
		StartNewGame(topic, randomTopic);
		return;
	}
	else if (choice == '2') {
		char topic[20] = "History.txt";
		randomTopic = false;
		StartNewGame(topic, randomTopic);
		return;
	}
	else if (choice == '3') {
		char topic[20] = "Cinema.txt";
		randomTopic = false;
		StartNewGame(topic, randomTopic);
		return;
	}
	else if (choice == '4') {
		char topic[20] = "Sports.txt";
		randomTopic = false;
		StartNewGame(topic, randomTopic);
		return;
	}
	else if (choice == '5') {
		char topic[20] = "Politics.txt";
		randomTopic = false;
		StartNewGame(topic, randomTopic);
		return;
	}
	else if (choice == '9') {
		randomTopic = true;
		char topic[20] = { '\0' };
		StartNewGame(topic, randomTopic);
		return;
	}
	else {
		system("cls");//clearing console
		return;
	}
}

#endif // !NEWGAME
