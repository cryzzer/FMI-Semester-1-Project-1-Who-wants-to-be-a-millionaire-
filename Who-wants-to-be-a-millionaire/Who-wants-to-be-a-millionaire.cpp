#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
void Border() {
	cout << endl;
	cout << setw(3);
	for (int i = 0; i < 116;i++) {
		cout << '=';
	}
	cout << endl;
}
void ValidInput(char& number, char string[], const int sizeOfString) {
	bool validChoice = false;
	do {
		cin >> number;
		for (int i = 0; i < sizeOfString;i++) {
			if (number != string[i]) {
				continue;
			}
			validChoice = true;
			break;
		}
	} while (!validChoice);
}

void StartNewGame() {

}

void NewGame() {
	Border();
	cout << endl;
	cout << setw(69) << "Choose category:\n\n";
	cout << setw(69) << "1. Politics\n";
	cout << setw(69) << "2. History\n";
	cout << setw(69) << "3. Geography\n";
	cout << setw(69) << "4. Literature\n";
	cout << setw(69) << "5. Physics\n\n";
	cout << setw(69) << "9. All categories\n\n";
	cout << "Enter your choice: ";

	const int sizeOfString = 10;
	char possibleChoices[sizeOfString] = { '1', '2', '3', '4', '5', '9'};
	char choice;
	ValidInput(choice, possibleChoices, sizeOfString);
	Border();//not working properly, need to show up before validation

	switch (choice) {
		case 1: {

			break;
		}
		case 2: {
			break;
		}
		case 3: {
			break;
		}
		case 4: {
			break;
		}
		case 5: {
			break;
		}
		default: {
		}
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
}