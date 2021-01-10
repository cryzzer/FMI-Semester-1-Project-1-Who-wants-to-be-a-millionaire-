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
* <main file>
*
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

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
void FullIDCreatingGenerator(int topicChoice,int number, char fullQuestionID[]) {	//creating the ID that the program will look for only for back numbers
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

void FillingEmptySpace(char option[], int optionSize) {//filling the space of an option for 50/50 joker
	for (int i = 0; i < optionSize; i++) {
		option[i] = ' ';
	}
	option[optionSize] = '\0';
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
void AudienceHelpJoker(char possibleAnswers[],char correctAnswer, int& level) {
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

void PrintQuestionAndAnswers(char printingQuestionID[], char question[], char option1[], char option2[], char option3[], char option4[],
char correctAnswer, char possibleAnswers[], const int SIZE_OF_ANSWERS, int& level, bool& gameLost, bool& fFjoker, bool& audJoker, bool& friendJoker, char gameOverQuestion[]) {

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

	int option1Size = StrLength(option1);//using this to center the options
	int option3Size = StrLength(option3);

	char inputAnswer = '\0';

	const int MESSAGE_SIZE = 4;//the size of message yes or no!
	char usingJoker[MESSAGE_SIZE] = "yes";//creating available options to be chosen
	char notUsingJoker[MESSAGE_SIZE] = "no!";
	char inputChoiceIfJoker[MESSAGE_SIZE] = { '\0' };
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
	do {//if an incorrect choice is being validated, it resets the page, giving the user the ability to enter again, untill a valid choice is inputed
		bool incorrectValidation = false;


		NewLines(6);
		cout << "  " << printingQuestionID << endl;
		Border();
		cout << "\n  " << question << endl << endl;
		cout << "  " << option1;
		EmptySpaces(60 - option1Size);//how many empty spaces there will be so B) and D) are in one line
		cout  << option2 << endl;
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
			cout << "  Do you want to use a joker? (type: 'yes' or 'no!')";
			cin >> inputChoiceIfJoker;
			ValidInputForWords(inputChoiceIfJoker, notUsingJoker, MESSAGE_SIZE, incorrectValidation);//checking if the user said no!
			showingAvailableJokers = false;//disabling jockers for round
			if (incorrectValidation == true) {
				incorrectValidation = false;

				ValidInputForWords(inputChoiceIfJoker, usingJoker, MESSAGE_SIZE, incorrectValidation);//checking if the user said yes
				showingAvailableJokers = true;
				if (incorrectValidation == true) {//looping back to enter a valid choice
					system("cls");//clearing console
					continue;
				}
			}
			else {
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
	} while (inputAnswer!=possibleAnswers[0] && inputAnswer != possibleAnswers[1] && inputAnswer != possibleAnswers[2] && inputAnswer != possibleAnswers[3]);

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
	PrintQuestionAndAnswers(printingQuestionID,question, option1, option2, option3, option4, correctAnswer, possibleAnswers, sizeOfAnswers, 
		level, gameLost,fFjoker, audJoker, friendJoker, gameOverQuestion);
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

				PrintPassedQuestion(possibleEarnings, level);//pringting the prize for round
				cout << "\n                          Do you want to keep the money, and stop playing ?(type 'yes' or 'no!')";
				const int MESSAGE_SIZE = 4;
				bool inCorrectValidation = false;
				char continuingGame[MESSAGE_SIZE] = "yes";//giving the ability to continue the game or keep the money and leave
				char endingGame[MESSAGE_SIZE] = "no!";
				char yesNo[4] = { '\0' };
				bool contGame = true;
				do {
					inCorrectValidation = false;

					cin >> yesNo;//validation checking
					ValidInputForWords(yesNo, endingGame, MESSAGE_SIZE, inCorrectValidation);
					if (inCorrectValidation == true) {
						inCorrectValidation = false;
						ValidInputForWords(yesNo, continuingGame, MESSAGE_SIZE, inCorrectValidation);
						if (inCorrectValidation == true) {
							cout << "\n\n                                  Incorrect validation, please (type 'yes' or 'no!')";
							continue;
						}
						else {
							contGame = false;
							break;
						}

					}
					contGame = true;
					break;
				} while (inCorrectValidation == true);
				if (contGame == true) {
					system("cls");//clearing console
				}
				else {
					system("cls");//clearing console
					NewLines(6);
					cout << "  ========================================== Who wants to be a millionaire? ==========================================\n\n";
					cout << "                             You won " << possibleEarnings[level - 1] << "$ in Who wants to be a millionaire, thanks for playing! ";
					cout << endl;//keeping money and leaving game
					Border();
					break;
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
	else if(choice == '9') {
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

void QuestionCheckNewLine(char question[]) {//checking if in the inserted new question somewhere is a symbol for new line, if yes turns it into empty space
	int sizeQuestion = StrLength(question);
	for (int i = 0; i < sizeQuestion; i++) {
		if (question[i] == '\n') {
			question[i] = ' ';
		}
	}
}

void EnteringNewInfoIntoFile(char fileName[], char question[], char option1[], char option2[], char option3[], char option4[], char& correctAnswer,
							char fullID[], int numberOfQuestion) {
	ofstream NewQuestion(fileName, ios::app);//append, starts the typing from the end of the file

	NewQuestion << endl << fullID << endl;//inserting each string that has been saved
	NewQuestion << numberOfQuestion << ". " << question << "?" << endl;
	NewQuestion << "A) " << option1 << endl;
	NewQuestion << "B) " << option2 << endl;
	NewQuestion << "C) " << option3 << endl;
	NewQuestion << "D) " << option4 << endl << endl;
	NewQuestion << correctAnswer << endl;

	NewQuestion.close();//closing file
}

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
void EnteringNewQuestion() {
	char choice = '\0';
	char choiceSelection[10] = { '1', '2', '3', '4', '5', '0' };

	SelectingCategory(choice, choiceSelection);
	char topic[20] = {'\0'};
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
	int numberOfQuetionChoises[20] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
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
void EditingExistingQuestion() {
	//to be continued...
}
void ThanksForPlaying() {//exiting message
	NewLines(6);
	Border();
	cout << "\n\n                                         Thanks for playing, have a nice day !\n\n";
	Border();
	NewLines(6);
}
void MainMenu() {
	char choice = '\0';
	do {
		choice = '\0';
		NewLines(6);
		cout << "  ========================================== Who wants to be a millionaire? ==========================================\n\n";
		cout << "                                                      1. New Game\n";
		cout << "                                                2. Entering new question\n";
		cout << "                                              3. Editing existing question\n";
		cout << "                                                         0.Exit\n";
		Border();

		cout << "\n                                                   Enter your choice: ";

		
		char possibleChoices[10] = { '1', '2', '3', '0' };
		ValidInput(choice, possibleChoices, 10);
		if (choice == '1') {
			system("cls");//clearing console
			NewGame();
		}
		else if (choice == '2') {
			system("cls");//clearing console
			EnteringNewQuestion();
		}
		else if (choice == '3') {
			system("cls");//clearing console
			EditingExistingQuestion();
		}
		else {
			system("cls");//clearing console
			ThanksForPlaying();
		}

	} while (choice != '0');
	
}

int main()
{
	HWND console = GetConsoleWindow();
	RECT ConsoleRect;
	GetWindowRect(console, &ConsoleRect);

	MoveWindow(console, ConsoleRect.left, ConsoleRect.top, 1360, 700, TRUE);//setting the dimentions of the console
	//size of font - 24
	//dimentions of console - 120x27, but console must be at least 120 wide and 27 high

	MainMenu();

	return 0;
}