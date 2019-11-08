#include <iostream>

using namespace std;

bool checkInteger(string n)
{
	int check = 0;
	int offset;
	if (n[0] == '+' || n[0] == '-')
		offset = 1;
	else offset = 0;
	for (int i = offset; i < n.length(); i++)
	{
		if (isdigit(n[i]) == 0 && n[i] != '.')
			return false;
		if (check == 1 && n[i] != '0')
			return false;
		if (n[i] == '.')
			check++;
	}
	return true;
}

string removeDecimalPoint(string n)
{
	string p;
	for (int i = 0; i < n.length(); i++)
	{
		if (n[i] == '.')
			break;
		else
			p += n[i];
	}
	return p;
}

int convertStringToInteger(string n)
{
	int number = 0;
	int offset;
	if (n[0] == '-' || n[0] == '+')
		offset = 1;
	else offset = 0;
	for (int i = offset; i < n.length(); i++)
	{
		number += (n[i] - '0') * (int)pow(10, n.length() - 1 - i);
	}
	if (offset == 1 && n[0] == '-')
		number = -number;
	return number;
}

bool checkRange(int n)
{
	if (n < -32768 || n > 32767)
		return false;
	else return true;
}

bool checkOperator(string n)
{
	if (n.length() == 1)
	{
		if (n == "+" || n == "-" || n == "*" || n == "/" || n == "%")
			return true;
		else return false;
	}
	else return false;
}

int convertOperatorToInteger(string n)
{
	if (n == "+") return 1;
	else if (n == "-") return 2;
	else if (n == "*") return 3;
	else if (n == "/") return 4;
	else if (n == "%") return 5;
	else return 0;
}

int calculate(int number1, int op, int number2)
{
	switch (op)
	{
	case 1:
		return number1 + number2;
		break;
	case 2:
		return number1 - number2;
		break;
	case 3:
		return number1 * number2;
		break;
	case 4:
		if (number2 == 0)
		{
			return 0; // dummy value
		}
		else return number1 / number2;
		break;
	case 5:
		if (number2 == 0)
		{
			return 0; // dummy value
		}
		else return number1 % number2;
		break;
	default:
		return 0; // dummy value
		break;
	}
}

int main(int argc, char* argv[])
{
	while (true)
	{
		char input[100];
		cin.getline(input, 100);

		char* p = input;
		string arg[3]; // break the input into 3 arguments
		for (int i = 0; i < 3; i++)
		{
			while (*p != ' ' && *p != '\0')
			{
				arg[i] += *p;
				p++;
			}
			p++;
		}

		char* s = input;
		int space = 0; // calculate the ammount of space characters
		while (*s != '\0')
		{
			if (*s == ' ')
				space++;
			s++;
		}

		if (arg[0] == "Exit")
		{
			cout << "LABORATORY GROUP TCT" << endl;
			cout << "s3748840, s3748840@rmit.edu.au, Cuong, Nguyen" << endl;
			cout << "s3757934, s3757934@rmit.edu.au, Tien, Nguyen" << endl;
			cout << "s3747274, s3747274@rmit.edu.au, Tam, Nguyen" << endl;
			break;
		}

		int number1 = 0;
		int number2 = 0;
		int opnumber = 0;
		int check = 0; // check value

		if (space != 2)
			cout << "Invalid number of arguments" << endl;
		else
		{
			// Check 1st number
			if (checkInteger(arg[0]))
			{
				number1 = convertStringToInteger(removeDecimalPoint(arg[0]));
				if (checkRange(number1))
				{
					check++;
				}
				else
				{
					cout << "First number is out of range" << endl;
				}
			}
			else cout << "First number is not an integer" << endl;

			// Check operator
			if (checkOperator(arg[1]))
			{
				opnumber = convertOperatorToInteger(arg[1]);
				check++;
			}
			else cout << "Wrong operator" << endl;

			// Check 2nd number
			if (checkInteger(arg[2]))
			{
				number2 = convertStringToInteger(removeDecimalPoint(arg[2]));
				if (checkRange(number2))
				{
					check++;
				}
				else
				{
					cout << "Second number is out of range" << endl;
				}
			}
			else cout << "Second number is not an integer" << endl;

			// All arguments must be valid in order to start the calculation
			if (check != 3)
			{
				cout << "Cannot begin calculation" << endl;
			}
			else
			{
				// The calculation begins
				if ((calculate(number1, opnumber, number2) == 0 && number2 == 0) && (opnumber == 4 || opnumber == 5))
				{
					cout << "Cannot divide by 0" << endl;
				}
				else
				{
					cout << number1 << " " << arg[1] << " " << number2 << " = " << calculate(number1, opnumber, number2) << endl;
				}
			}
		}
	}
	return 0;
}