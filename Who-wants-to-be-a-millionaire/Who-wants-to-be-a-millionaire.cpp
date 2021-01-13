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
#include <windows.h>
#include <stdlib.h>
#include "EditQuestion.h"
#include "NewGame.h"
#include "NewQuestion.h"
#include "UsefulFunctions.h"

using namespace std;

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