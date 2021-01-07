#include <iostream>
#include <fstream>
#include <iomanip>

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
	char printingString[6] = {'\0'};    //creating an char array, that will compare later
	char gettingLine[1000];
	while (questionFile.getline(gettingLine, 1000)) {//getting the whole line
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

void StartNewGame(char nameOfFile []) {
	int level = 1;

	char questionID[6] = { 'I','D', ':', '\0', '\0' };
	IDLookingGenerator(level, questionID);

	bool gameLost = false;
	//while (true) {// level > 10 || gameLost == true

		int timesQuestionExists = 0;
		SearchHowManyPossibleQuestions(nameOfFile, timesQuestionExists,questionID);


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