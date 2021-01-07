#include <iostream>
#include <fstream>
#include <iomanip>
#include <time.h>
#include <stdlib.h>

using namespace std;

char LevelFromIntToChar(int level) {//turning level number into number of ID    example: ID:01
	return '0' + level;
}
void IDLookingGenerator(int level, char questionID [6]) {//creating the ID that the program will look for
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

void CopyStr(char originalString[], char copiedVersion[], int sizeCopiedArray, char stopCopyingAfter) {
	for (int i = 0; i < sizeCopiedArray; i++) {
		copiedVersion[i] = originalString[i];
		//cout << "CV: " << copiedVersion[i] << "   OV: " << originalString[i] << endl;
		if (copiedVersion[i] == stopCopyingAfter) {
			break;
		}
	}
}

void Border() {
	cout << endl;
	cout << setw(3);
	for (int i = 0; i < 116;i++) {//printing border
		cout << '=';
	}
	cout << endl;
}
void ValidInput(char& number, char string[], const int sizeOfString) {
	bool validChoice = false;
	do {
		cin >> number;
		for (int i = 0; i < sizeOfString;i++) {//if the input does not match with any of the remaining options, continue the loop untill a viable
			if (number != string[i]) {         // option is inputed
				continue;
			}
			validChoice = true;//flag for stopping the function
			break;
		}
	} while (!validChoice);//looping while a valid choice isn't entered
}

void SearchHowManyPossibleQuestions(char nameOfFile [], int& timesQuestionExists, char questionID[]) {
	ifstream questionFile(nameOfFile);  //opening file
	char printingString[6] = {'\0'}; //creating an char array, that will compare later
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
void PrintQuestionAndAnswers(char gettingLine[], const int sizeOfRow, ifstream questionFile(), char nameOfFile[]) {

}
void PrintSelectedQuestion(char nameOfFile[], int numberOfSelectedQuestion, char questionID[]) {
	const int sizeOfRow = 1000;
	
	ifstream questionFile(nameOfFile);  //opening file
	char printingString[6] = { '\0' };    //creating an char array, that will compare later
	char gettingLine[sizeOfRow];
	
	int currentNumberOfQuestion = 0;

	char question[sizeOfRow] = {'\0'};
	char option1[sizeOfRow / 10] = { '\0' };
	char option2[sizeOfRow / 10] = { '\0' };
	char option3[sizeOfRow / 10] = { '\0' };
	char option4[sizeOfRow / 10] = { '\0' };
	char correctAnswer;
	char inputAnswer;


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
		if (currentNumberOfQuestion == numberOfSelectedQuestion) {
			
			questionFile.getline(gettingLine, sizeOfRow, '\n');
			//cout << gettingLine << endl;
			CopyStr(gettingLine, question, sizeOfRow, '?');
			cout << question << endl;

			questionFile.getline(gettingLine, sizeOfRow, '\n');
			//cout << gettingLine << endl;
			CopyStr(gettingLine, option1, sizeOfRow, '\n');
			cout << option1 << endl;

			questionFile.getline(gettingLine, sizeOfRow, '\n');
			//cout << gettingLine << endl;
			CopyStr(gettingLine, option2, sizeOfRow, '\n');
			cout << option2 << endl;

			questionFile.getline(gettingLine, sizeOfRow, '\n');
			//cout << gettingLine << endl;
			CopyStr(gettingLine, option3, sizeOfRow, '\n');
			cout << option3 << endl;


			questionFile.getline(gettingLine, sizeOfRow, '\n');
			//cout << gettingLine << endl;
			CopyStr(gettingLine, option4, sizeOfRow, '\n');
			cout << option4 << endl;

			questionFile.getline(gettingLine, sizeOfRow, '\n');
			questionFile.getline(gettingLine, sizeOfRow, '\n');
			//cout << gettingLine << endl;
			correctAnswer = gettingLine[0];

			cout << question << endl;

			questionFile.close();
		}
	}


}

void StartNewGame(char nameOfFile []) {
	srand(time(nullptr));
	int level = 1;

	char questionID[6] = { 'I','D', ':', '\0', '\0' };
	IDLookingGenerator(level, questionID);

	bool gameLost = false;
	//while (true) {// level > 10 || gameLost == true

		int timesQuestionExists = 0;
		SearchHowManyPossibleQuestions(nameOfFile, timesQuestionExists,questionID);
		int numberOfSelectedQuestion = rand() % timesQuestionExists + 1;
		PrintSelectedQuestion(nameOfFile, numberOfSelectedQuestion, questionID);


	//}
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
	char possibleChoices[sizeOfString] = { '1', '2', '3', '4', '5', '9'};
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
	NewGame();
	//StartNewGame;
	return 0;
}