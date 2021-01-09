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
void FiftyFiftyJoker() {

}
void AudienceHelpJoker() {

}
void CallFriendJoker() {

}

void PrintQuestionAndAnswers(char printingQuestionID[], char question[], char option1[], char option2[], char option3[], char option4[],
	char correctAnswer, char possibleAnswers[], const int sizeOfAnswers, int& level, bool& gameLost) {

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

	char inputAnswer;
	do {//if an incorrect choice is being validated, it resets the page, giving the user the ability to enter again, untill a valid choice is inputed
		cout << endl << endl << endl << endl << endl << endl;
		cout << "  " << printingQuestionID << endl;
		Border();
		cout << "\n  " << question << endl << endl;
		cout << "  " << option1;
		cout << right << setw(50 - option1Size - 1) << option2 << endl;
		cout << "  " << option3;
		cout << right << setw(50 - option3Size - 1) << option4 << endl;//not working properly
		Border();

		
		cout << "  Your answer (" << possibleAnswers[0] << ", " << possibleAnswers[1] << ", " << possibleAnswers[2] << " or " << possibleAnswers[3] << "): ";
		cin >> inputAnswer;
		system("cls");//clearing console
	} while (inputAnswer!=possibleAnswers[0] && inputAnswer != possibleAnswers[1] && inputAnswer != possibleAnswers[2] && inputAnswer != possibleAnswers[3]);

	//ValidInput(inputAnswer, possibleAnswers, sizeOfAnswers);
	if (inputAnswer == correctAnswer) {
	}
	else {
		gameLost = true;
	}
}
void PrintSelectedQuestion(char nameOfFile[], int numberOfSelectedQuestion, char questionID[], int& level, bool& gameLost) {
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
	PrintQuestionAndAnswers(printingQuestionID,question, option1, option2, option3, option4, correctAnswer, possibleAnswers, sizeOfAnswers, level, gameLost);
}
void PrintPassedQuestion(int possibleEarnings[], int& level) {//printing won amount of money for round
	cout << endl << endl << endl << endl << endl << endl;
	Border();
	cout << endl;
	cout << "  Congratulations, you won " << possibleEarnings[level - 1] << '$' << endl;
	Border();
}
void PrintGameOver() {//printing game over
	cout << endl << endl << endl << endl << endl << endl;
	Border();
	cout << endl;
	cout << "GAME OVER";
	Border();
}

void StartNewGame(char nameOfFile[]) {
	system("cls");//clearing console
	srand(time(nullptr));//setting the seed, from which the randomiser will randomise
	int level = 1;//levels(questions) from 1 to 15 (currently working with questions to 10)

	char questionID[6] = { 'I','D', ':', '\0', '\0' };//ID validation prototype


	bool gameLost = false;//flag that will show if an incorrect answer has been entered, resulting Game Over
	const int numberSums = 15;
	//sum of how much money will the user win after each round
	int possibleEarnings[numberSums] = { 500, 1000, 2000, 3000, 5000, 7000, 10000, 20000, 30000, 50000, 70000, 100000, 250000, 500000, 1000000 };
	do {

		IDLookingGenerator(level, questionID);//creating ID to search for

		int timesQuestionExists = 0;
		SearchHowManyPossibleQuestions(nameOfFile, timesQuestionExists, questionID);//finding how many questions for level are available

		int numberOfSelectedQuestion = rand() % timesQuestionExists + 1;//creating a random number (from 1 to the number of max questions for level)
																		//that will indicate when the program has "traveled" to this question

		PrintSelectedQuestion(nameOfFile, numberOfSelectedQuestion, questionID, level, gameLost);//printing question and answers
		
		if (!gameLost) {

			PrintPassedQuestion(possibleEarnings, level);//pringting the prize for round
			system("pause");//stopping the console so the message stays on, then after hitting a button, the game continues
			system("cls");//clearing console
		}
		else {
			PrintGameOver();//printing game over
		}
		level++;//level up

	} while (level < 10 && gameLost == false);//contitions when the game is lost/ stops playing it
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

	NewGame();

	return 0;
}