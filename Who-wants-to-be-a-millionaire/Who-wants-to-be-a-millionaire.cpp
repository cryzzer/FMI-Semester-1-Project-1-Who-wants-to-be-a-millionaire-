#include <iostream>
#include <fstream>
#include <iomanip>
#include <time.h>
#include <stdlib.h>

using namespace std;

char LevelFromIntToChar(int level) {//turning level number into number of ID    example: ID:01
	return '0' + level;
}
void IDLookingGenerator(int level, char questionID[6]) {//creating the ID that the program will look for
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
	const int sizeOfConsoleRow = 120;
	for (int i = 0; i < (sizeOfConsoleRow - 4);i++) {//printing border
		cout << '=';
	}
	cout << endl;
}

void ValidInput(char& number, char string[], const int sizeOfString) {
	bool validChoice = false;
	do {
		cin >> number;
		for (int i = 0; i < sizeOfString;i++) {//if the input does not match with any of the remaining options, 
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
	const int sizeOfRow = 1000;
	char gettingLine[sizeOfRow];
	while (questionFile.getline(gettingLine, sizeOfRow)) {//getting the whole line
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
	char correctAnswer, char possibleAnswers[], const int sizeOfAnswers, int& level, bool& gameLost, bool& fFjoker, bool& audJoker, bool& friendJoker) {

	const int sizeOfConsoleRow = 120;//this will be the default size of the row of the console
	int questionSize = StrLength(question);//finding the size of the question

	//if the size is more than 116(which is where the double lines end), this part of the code finds where is the last position,
	//where there isn't a latin letter, and starts copying the rest of the elements from his right side 2 steps over,
	//then rewrites the found position to a new line, and the second two elements after him to 2 space bars
	if (questionSize > (sizeOfConsoleRow - 4)) {
		int startElementToCopy = sizeOfConsoleRow - 4;
		for (startElementToCopy = sizeOfConsoleRow - 4; ((question[startElementToCopy] <= 'Z' && question[startElementToCopy] >= 'A') ||
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

	const int MessageSize = 4;//the size of message yes or no!
	char usingJoker[MessageSize] = "yes";//creating available options to be chosen
	char notUsingJoker[MessageSize] = "no!";
	char inputChoiceIfJoker[MessageSize] = { '\0' };
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


		cout << endl << endl << endl << endl << endl << endl;
		cout << "  " << printingQuestionID << endl;
		Border();
		cout << "\n  " << question << endl << endl;
		cout << "  " << option1;
		cout << right << setw(50 - option1Size - 1) << option2 << endl;
		cout << "  " << option3;
		cout << right << setw(50 - option3Size - 1) << option4 << endl;//not working properly
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
			cout << "  Do you want to use a joker? (type: yes or no!)";
			cin >> inputChoiceIfJoker;
			ValidInputForWords(inputChoiceIfJoker, notUsingJoker, MessageSize, incorrectValidation);//checking if the user said no!
			showingAvailableJokers = false;//disabling jockers for round
			if (incorrectValidation == true) {
				incorrectValidation = false;

				ValidInputForWords(inputChoiceIfJoker, usingJoker, MessageSize, incorrectValidation);//checking if the user said yes
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
	}
}
void PrintSelectedQuestion(char nameOfFile[], int numberOfSelectedQuestion, char questionID[], int& level, bool& gameLost, bool& fFjoker, bool& audJoker, bool& friendJoker) {
	const int sizeOfRow = 1000;//row equals line

	ifstream questionFile(nameOfFile);  //opening file

	//the array will have exactly 5 simbols inside, which is the number of the ID  example: "ID:01"+terminating zero
	char printingString[6] = { '\0' };    //creating an char array, that will compare later;
	char gettingLine[sizeOfRow];

	int currentNumberOfQuestion = 0;

	char printingQuestionID[20] = { '\0' };//12 is the size of ID 

	char question[sizeOfRow] = { '\0' };
	char option1[sizeOfRow / 10] = { '\0' };
	char option2[sizeOfRow / 10] = { '\0' };
	char option3[sizeOfRow / 10] = { '\0' };
	char option4[sizeOfRow / 10] = { '\0' };
	char correctAnswer = { '\0' };

	while (questionFile.getline(gettingLine, sizeOfRow)) {//getting the whole line
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

			questionFile.getline(gettingLine, sizeOfRow, '\n');//gettig question
			CopyStr(gettingLine, question);//coppying question

			questionFile.getline(gettingLine, sizeOfRow, '\n');//getting option 1
			CopyStr(gettingLine, option1);//coppying option 1, same goes for the other 3 options

			questionFile.getline(gettingLine, sizeOfRow, '\n');
			CopyStr(gettingLine, option2);

			questionFile.getline(gettingLine, sizeOfRow, '\n');
			CopyStr(gettingLine, option3);


			questionFile.getline(gettingLine, sizeOfRow, '\n');
			CopyStr(gettingLine, option4);

			//since there is a new line between the 4th option and the correct answer, skip 1 line of the text
			questionFile.getline(gettingLine, sizeOfRow, '\n');
			questionFile.getline(gettingLine, sizeOfRow, '\n');
			correctAnswer = gettingLine[0];//copying the correct answer

			questionFile.close();
		}
	}
	int sizeOfAnswers = 5;
	char possibleAnswers[5] = { 'A', 'B', 'C', 'D' };//adding valid choices to be compared with the input
	PrintQuestionAndAnswers(printingQuestionID,question, option1, option2, option3, option4, correctAnswer, possibleAnswers, sizeOfAnswers, 
		level, gameLost,fFjoker, audJoker, friendJoker);
}
void PrintPassedQuestion(int possibleEarnings[], int& level) {//printing won amount of money for round
	cout << endl << endl << endl << endl << endl << endl;
	Border();
	cout << endl;
	cout << "                                          ";
	cout << "Congratulations, you won " << possibleEarnings[level - 1] << '$' << endl;//winning money after round
	Border();
}
void PrintGameOver(int possibleEarnings[], int& level) {//printing game over
	cout << endl << endl << endl << endl << endl << endl;
	Border();
	cout << endl;//if user lost game, he wins an amount, after a certain level is passed
	cout << "                                                           ";
	cout << "GAME OVER\n";
	if (level < 5) {
		cout << "                                                       ";
		cout << "You have won 0$";
	}
	else if (level > 5 && level < 10) {
		cout << "                                                       ";
		cout << "You have won 1000$";
	}
	else if (level > 10 && level < 16) {
		cout << "                                                       ";
		cout << "You have won 32000$";
	}

	Border();
}

void StartNewGame(char nameOfFile[]) {
	system("cls");//clearing console
	srand(time(nullptr));//setting the seed, from which the randomiser will randomise
	int level = 15;//levels(questions) from 1 to 15 (currently working with questions to 10)

	char questionID[6] = { 'I','D', ':', '\0', '\0' };//ID validation prototype

	bool fFjoker = true;
	bool audJoker = true;
	bool friendJoker = true;

	bool gameLost = false;//flag that will show if an incorrect answer has been entered, resulting Game Over
	const int numberSums = 15;
	//sum of how much money will the user win after each round
	int possibleEarnings[numberSums] = { 100, 200, 300, 500, 1000, 2000, 4000, 8000, 16000, 32000, 64000, 125000, 250000, 500000, 1000000 };
	do {

		IDLookingGenerator(level, questionID);//creating ID to search for

		int timesQuestionExists = 0;
		SearchHowManyPossibleQuestions(nameOfFile, timesQuestionExists, questionID);//finding how many questions for level are available

		int numberOfSelectedQuestion = rand() % timesQuestionExists + 1;//creating a random number (from 1 to the number of max questions for level)
																		//that will indicate when the program has "traveled" to this question

		PrintSelectedQuestion(nameOfFile, numberOfSelectedQuestion, questionID, level, gameLost, fFjoker, audJoker, friendJoker);//printing question and answers
		
		if (!gameLost) {
			if (level < 15) {

				PrintPassedQuestion(possibleEarnings, level);//pringting the prize for round
				cout << "\n                         ";
				cout << "  Do you want to keep the money, and stop playing ?(type yes or no!)";
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
						ValidInputForWords(yesNo, continuingGame, MESSAGE_SIZE, inCorrectValidation);
						if (inCorrectValidation == true) {
							cout << "\n\n  Incorrect validation, please (type yes or no!)";
						}
						else {
							contGame = true;
							break;
						}

					}
					contGame = true;
					break;
				} while (inCorrectValidation == false);
				if (contGame == true) {
					system("cls");//clearing console
				}
				else {
					system("cls");//clearing console
					cout << endl << endl << endl << endl << endl << endl;
					Border();
					cout << endl;
					cout << "                               ";//keeping money and leaving game
					cout << "You won " << possibleEarnings[level - 1] << "$ in Who wants to be a millionaire, thanks for playing! ";
					cout << endl;
					Border();
					break;
				}
			}
		}
		else {
			PrintGameOver(possibleEarnings, level);//printing game over
		}
		level++;//level up

	} while (level <= 15 && gameLost == false);//contitions when the game is lost/ stops playing it

	if (level == 16 && gameLost == false) {
		cout << endl << endl << endl << endl << endl << endl;
		Border();
		cout << endl;
		cout << "                               ";
		cout << "Congratulations, you have won the big prize of 1,000,000$ \n";// if level 15 is completed, user wins the big prize
		cout << "                                                           ";
		cout << "Thanks for playing!";
	}
}


void NewGame() {
	cout << endl << endl << endl << endl << endl << endl;
	Border();
	cout << endl;
	cout << setw(69) << "Choose category:\n\n";
	cout << setw(69) << "1. Life\n";
	cout << setw(69) << "2. History\n";
	cout << setw(69) << "3. Cinema\n";
	cout << setw(69) << "4. Sports\n";
	cout << setw(69) << "5. Politics\n\n";
	cout << setw(69) << "9. All categories\n\n";
	Border();
	cout << "Enter your choice: ";

	const int sizeOfString = 10;
	char possibleChoices[sizeOfString] = { '1', '2', '3', '4', '5', '9' };
	char choice;
	ValidInput(choice, possibleChoices, sizeOfString);

	if (choice == '1') {
		char topic[20] = "Life.txt";
		StartNewGame(topic);
	}
	else if (choice == '2') {
		char topic[20] = "History.txt";
	}
	else if (choice == '3') {
		char topic[20] = "Cinema.txt";
	}
	else if (choice == '4') {
		char topic[20] = "Sports.txt";
	}
	else if (choice == '5') {
		char topic[20] = "Politics.txt";
	}
	else {

	}
}
void EnteringNewQuestion() {

}
void EditingExistingQuestion() {

}
void GameOver() {

}
void MainMenu() {
	
}

int main()
{

	//size of font - 24
	//dimentions of console - 120x27, but console must be at least 120 wide

	/*int level = 14;
	char possibleAnswers[5] = { 'A', 'B', 'C', 'D' };
	char correctAnswer = 'B';
	AudienceHelpJoker(possibleAnswers, correctAnswer, level);*/
	
	NewGame();

	return 0;
}