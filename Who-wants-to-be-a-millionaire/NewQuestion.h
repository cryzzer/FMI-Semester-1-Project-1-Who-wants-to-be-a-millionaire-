#pragma once

void PrintSuccessfulNewQuest();

void EnteringNewInfoIntoFile(char fileName[], char question[], char option1[], char option2[], char option3[], char option4[], char& correctAnswer,
	char fullID[], int numberOfQuestion);

void WritingNewQuestionAnswers(char question[], char option1[], char option2[], char option3[], char option4[], char& correctAnswer,
	int& diffChoice, char fullQuestionID[]);

void SelectingDifficultyOfQuestion(int& diffChoise, int numberOfQuetionChoises[]);

void SelectingCategory(char& choice, char choiceSelection[]);

void EnteringNewQuestion();

