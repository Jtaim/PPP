/*
	Written by Jtaim
	Date 13 Jan 2019
	Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

	Section 9 Drill 2
	This drill simply involves the sequence of versions of Date to work 9.4.2.
	For each version define Date called today initialized to June 25, 1978.
	Then, define a Date called tomorrow and give it a value by coping today into it and increasing its day by using add_day().
	Finally, output today and tomorrow using a << defined as in 9.8.

	Your check for a valid date may be very simple.
	Feel free to ignore leap years.
	However, don't accept a month that is not in the [1,12] range or day of the month that is not in the [1,31] range.
	Test each version with at least one invalid date (e.g., 2004,13,-5).
*/

#include"../includes/ppp.h"



struct Date
{
	int year;
	int month;
	int day;
	Date(int y, int m, int d);
	void add_day(const int n);

	static constexpr std::array<int, 12> month_day{31,28,31,30,31,30,31,31,30,31,30,31};
};

Date::Date(int y, int m, int d)
{
	// check that (y,m,d) is a valid date.
	if(m < 1 || m > 12){
		ppp::error("Invalid month!");
	}
	if(d < 1 || d > month_day.at(m - 1)){
		ppp::error("Invalid day!");
	}
	if(y < 0){
		ppp::error("Invalid year!");
	}
	month = m;
	day = d;
	year = y;
}

void Date::add_day(const int n)
{
	// increase dd by n days.
	if(day + n <= month_day.at(month - 1)){
		day += n;
	} else{
		int new_day{day + n - month_day.at(month - 1)};
		while(true){
			++month;
			if(month > 12){
				month = 1;
				++year;
			}
			if(new_day <= month_day.at(month - 1)){
				day = new_day;
				break;
			}
			new_day -= month_day.at(month - 1);
		}
	}
}

std::ostream& operator<<(std::ostream& os, const Date& d)
{
	return os << '(' << d.year << ',' << d.month << ',' << d.day << ')';
}

int main()
try{
	Date today{1978, 6, 25};
	//Date today{2004, 13, -5};
	Date tomorrow = today;
	tomorrow.add_day(1);

	std::cout << "today" << today << '\n';
	std::cout << "tomorrow" << tomorrow << '\n';

	ppp::keep_window_open();
	return 0;
}
catch(std::exception& e){
	std::cerr << "exception: " << e.what() << std::endl;
	ppp::keep_window_open();
	return 1;
}
catch(...){
	std::cerr << "exception\n";
	ppp::keep_window_open();
	return 2;
}