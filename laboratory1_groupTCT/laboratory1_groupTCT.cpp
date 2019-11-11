#include "pch.h"
#include <iostream>

using namespace std;

enum ERROR {
	invalidNumberOfArguments,
	invalidNumberInput,
	invalidNumberInputRange,
	invalidOperatorInput,
	divisionByZero,
	dummyVariableCheck,
	
};

enum OPERATOR {
	addition,
	subtraction,
	multiplication,
	division,
	arithmeticRemainder,
};

const int MAXIMUM_LENGTH = 13;

void getExpression(char* expression);
void checkingAndCalculating(char* expression);
bool validInput(char* expression, string* expressionElements);
bool errorDisplaying(int error);
void getElements(char* expression, string* elements);
bool validNumberOfArguments(char* expression);
bool validInteger(string n);
string removeDecimalPoint(string initialNumber);
bool validRange(double number);
bool validOperator(string n);
bool errorChecking(string* elements);
int getOperator(string op);
bool errorChecking(string* elements);
void calculatorPerforming(int number1, int op, int number2);
double stringToInteger(string initialNumber);
void exitMessage();



void getExpression(char* expression) {
	cout << "Please enter your arithmetic expression as <arg1><space><op><space><arg2> (enter Exit to stop calculator):" << endl;
	cin.getline(expression, MAXIMUM_LENGTH);
}

void checkingAndCalculating(char* expression) {
	string expressionElements[3];

	if (validInput(expression, expressionElements)) {
		calculatorPerforming((int)stringToInteger(*expressionElements), getOperator(*(expressionElements + 1)), (int) stringToInteger(*(expressionElements + 2)));
	}
}

bool validInput(char* expression, string* expressionElements) {
	if (!validNumberOfArguments(expression)) {
		return errorDisplaying(invalidNumberOfArguments);
	}
	else {
		getElements(expression, expressionElements);
		return errorChecking(expressionElements);
	}
}

bool errorChecking(string* elements) {
	if (!validInteger(*elements) || !validInteger(*(elements + 2))) {
		return errorDisplaying(invalidNumberInput);
	}
	else if (!validRange(stringToInteger(*elements)) || !validRange(stringToInteger(*(elements + 2)))) {
		return errorDisplaying(invalidNumberInputRange);
	}
	else if (!validOperator(*(elements + 1))) {
		return errorDisplaying(invalidOperatorInput);
	}
	return true;
}

bool errorDisplaying(int error) {
	switch (error) {
	case invalidNumberOfArguments:
		cout << "Invalid number of arguments" << endl;
		break;
	case invalidNumberInput:
		cout << "Invalid number input (please enter integer)" << endl;
		break;
	case invalidNumberInputRange:
		cout << "Invalid input range (please enter numbers between -32,768 and 32,767)" << endl;
		break;
	case invalidOperatorInput:
		cout << "Invalid operator input (operators can be +, -, *, /, %)" << endl;
		break;
	case divisionByZero:
		cout << "Cannot devide by zero" << endl;
		break;
	case dummyVariableCheck:
		cout << "Dummy variables" << endl;
		break;
	}
	return false;
}

void getElements(char* expression, string* elements) {
	for (int i = 0; i < 3; i++)
	{
		while (*expression != ' ' && *expression != '\0')
		{
			elements[i] += *expression;
			expression++;
		}
		expression++;
	}
}

bool validNumberOfArguments(char* expression) {
	int count = 0;
	while (*expression != '\0')
	{
		if (*expression == ' ') {
			++count;
		}
		++expression;
	}
	return (++count == 3);
}

bool validInteger(string number)
{
	int dotCounting = 0;
	int offset;
	if (number[0] == '+' || number[0] == '-') {
		offset = 1;
	} else {
		offset = 0;
	}
	for (int i = offset; i < number.length(); i++)
	{
		if (isdigit(number[i]) == 0 && number[i] != '.')
			return false;
		if (dotCounting == 1 && number[i] != '0')
			//errorDisplaying(afterDecimalError);
			return false;
		if (number[i] == '.')
			dotCounting++;
	}
	return true;
}

bool validRange(double number)
{
	return (number >= -32768 && number <= 32767);
}

bool validOperator(string op)
{
	if (op.length() != 1) {
		return false;
	} else {
		return (op == "+" || op == "-" || op == "*" || op == "/" || op == "%");
	}
}

int getOperator(string op)
{
	if (op == "+") return addition;
	else if (op == "-") return subtraction;
	else if (op == "*") return multiplication;
	else if (op == "/") return division;
	else if (op == "%") return arithmeticRemainder;
	else return 0;
}

void calculatorPerforming(int number1, int op, int number2)
{
	switch (op) {
	case addition:
		cout << number1 << " + " << number2 << " = " << number1 + number2 << endl; 
		break;
	case subtraction:
		cout << number1 << " - " << number2 << " = " << number1 - number2 << endl;
		break;
	case multiplication:
		cout << number1 << " * " << number2 << " = " << number1 * number2 << endl;
		break;
	case division:
		if (number2 == 0) {
			errorDisplaying(divisionByZero);
		} else {
			cout << number1 << " / " << number2 << " = " << number1 / number2 << endl;
		}
		break;
	case arithmeticRemainder:
		if (number2 == 0) {
			errorDisplaying(divisionByZero);
		} else {
			cout << number1 << " % " << number2 << " = " << number1 % number2 << endl;
		}
		break;
	}
}

string removeDecimalPoint(string initialNumber)
{
	string number;
	for (int i = 0; i < initialNumber.length(); i++)
	{
		if (initialNumber[i] == '.') {
			break;
		} else {
			number += initialNumber[i];
		}
	}
	return number;
}

double stringToInteger(string numberString)
{
	numberString = removeDecimalPoint(numberString);
	double number = 0;
	int offset;
	if (numberString[0] == '-' || numberString[0] == '+')
		offset = 1;
	else offset = 0;
	for (int i = offset; i < numberString.length(); i++)
	{
		number += (numberString[i] - '0') * (int)pow(10, numberString.length() - 1 - i);
	}
	return (numberString[0] == '-') ? -number : number;
}

void exitMessage() {
	cout << "LABORATORY GROUP TCT" << endl;
	cout << "s3748840, s3748840@rmit.edu.au, Cuong, Nguyen" << endl;
	cout << "s3757934, s3757934@rmit.edu.au, Tien, Nguyen" << endl;
	cout << "s3747274, s3747274@rmit.edu.au, Tam, Nguyen" << endl;
}

int main(int argc, char* argv[]) {
	char expression[] = "";
	char exit[] = "Exit";

	getExpression(expression);
	while (strcmp(expression,exit) != 0) {
		checkingAndCalculating(expression);
		getExpression(expression);
	}
	exitMessage();

	return 0;
}

