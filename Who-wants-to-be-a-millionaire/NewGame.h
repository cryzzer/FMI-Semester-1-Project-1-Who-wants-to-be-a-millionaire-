#pragma once


using namespace std;

void PrintQuestionAndAnswers(char printingQuestionID[], char question[], char option1[], char option2[], char option3[], char option4[],
	char correctAnswer, char possibleAnswers[], const int SIZE_OF_ANSWERS, int& level, bool& gameLost, bool& fFjoker, bool& audJoker, 
	bool& friendJoker, char gameOverQuestion[]);

void SearchHowManyPossibleQuestions(char nameOfFile[], int& timesQuestionExists, char questionID[]);

void PrintPassedQuestion(int possibleEarnings[], int& level);

void PrintGameOver(int possibleEarnings[], int& level, char gameOverQuestion[]);

void FiftyFiftyJoker(char correctAnswer, char option1[], char option2[], char option3[], char option4[]);

void AudienceHelpJoker(char possibleAnswers[], char correctAnswer, int& level);

void CallFriendJoker(char possibleAnswers[], char correctAnswer, int& level);

void PrintSelectedQuestion(char nameOfFile[], int numberOfSelectedQuestion, char questionID[], int& level, bool& gameLost, bool& fFjoker, bool& audJoker, bool& friendJoker,
	char gameOverQuestion[]);

void StartNewGame(char nameOfFile[], bool randomTopic);

void NewGame();
