//written by Jtaim
//date 24 Sept 2015
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 Drill step 4.
1. Write a program that consists of a while-loop that (each time around the loop)
   reads in two int numbers and then prints them. Exit the program when a terminating '|' is entered.
2. Change the program to write out the smaller value is: followed by the smaller of the
   numbers and the larger value is: followed by the larger value.
3. Augment the program so that it writes the line the numbers are equal (only) if they are equal.
4. Change the program so that it uses double instead of int.
*/

#include "section4.h" //custom header
bool check_input(const char);

//C++ programs start by executing the function main
int main()
{
	double val1 = 0.0;
	double val2 = 0.0;
	const char termVal = '|';
	bool terminate = true;

	while (terminate)
	{
		cout << "Enter two integer numbers. Enter " << termVal << " to exit.\n";
		if (!(cin >> val1))
			terminate = check_input(termVal);
		else if (!(cin >> val2))
			terminate = check_input(termVal);
		else
		{
			if (val1 != val2)
				cout << "The smaller value is: " << (val1 < val2 ? val1 : val2) << '\n'
				     << "The larger value is: " << (val1 > val2 ? val1 : val2) << "\n\n";
			else
				cout << "The numbers are equal.\n\n";
		}
	}
	keep_window_open();
	return 0;
}

bool check_input(const char termVal)
{
	bool goodBad = true;
	if (cin.eof())
	{
		cin.clear();
		//cin.ignore(INT_MAX, '\n');
		cout << "EOF found\n";
		goodBad = false;
	}
	else if (cin.fail())
	{
		char x = '?';
		cin.clear();
		cin >> x;
		cin.ignore(INT_MAX, '\n');	//clear cin buffer until find new line char
		if (termVal == x)
		{
			cout << "Program terminated, detected entered " << x << " key press\n";
			goodBad = false;
		}
		else if (x == 26) // 26 = ctrl-z and  ctrl-d = 04 wonder why i need this
		{
			cout << "EOF 26 found\n";
			goodBad = false;
		}
		else
		{
			cout << "Entered value is not valid\n";
			goodBad = true;
		}
	}
	else if (cin.bad())
	{
		cin.clear();
		//cin.ignore(INT_MAX, '\n');
		cout << "unknown termination\n";
		goodBad = false;
	}
	return goodBad;
}