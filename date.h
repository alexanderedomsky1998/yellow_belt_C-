#pragma once
#include <iostream>
#include <string>

using namespace std;

class Date
{
public:
	Date();
	Date(int new_day, int new_month, int new_year);
	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;

	friend bool operator<(const Date& lhs, const Date& rhs);
	friend bool operator<=(const Date& lhs, const Date& rhs);
	friend bool operator>(const Date& lhs, const Date& rhs);
	friend bool operator>=(const Date& lhs, const Date& rhs);
	friend bool operator!=(const Date& lhs, const Date& rhs);
	friend bool operator==(const Date& lhs, const Date& rhs);
	friend ostream& operator<<(ostream& os, const Date& date);
private:
	int day, month, year;
};


Date ParseDate(istream& stream);