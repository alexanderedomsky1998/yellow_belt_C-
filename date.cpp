#include "date.h"
#include <iomanip>
#include <sstream>

Date::Date() : year(0), month(0), day(0) {}

Date::Date(int new_year, int new_month, int new_day) {
	if (new_month < 1 || new_month > 12) {
		throw "Month value is invalid: " + to_string(new_month);
	}
	if (new_day < 1 || new_day > 31) {
		throw "Day value is invalid: " + to_string(new_day);
	}
	day = new_day;
	month = new_month;
	year = new_year;
}

int Date::GetYear() const {
	return year;
}

int Date::GetMonth() const {
	return month;
}

int Date::GetDay() const {
	return day;
}


void EnsureNextSymbolAndSkip(stringstream& stream, const string& current_date) {
	if (stream.peek() != '-') {
		throw "Wrong date format: " + current_date;
	}
	stream.ignore(1);
}

Date ParseDate(istream& stream) {
	Date date;
	if (stream.eof()) {
		return date;
	}
	string current_date;
	stream >> current_date;
	stringstream d(current_date);
	int year = 0, month = 0, day = 0;
	d >> year;
	EnsureNextSymbolAndSkip(d, current_date);
	if (!(d >> month)) {
		throw "Wrong date format: " + current_date;
	}
	EnsureNextSymbolAndSkip(d, current_date);
	if (!(d >> day)) {
		throw "Wrong date format: " + current_date;
	}
	string error = "";
	d >> error;
	date = { year, month, day };
	if (error != "") {
		throw "Wrong date format: " + current_date;
	}
	return date;
}

ostream& operator<<(ostream& stream, const Date& date) {
	stream << setfill('0');
	stream << setw(4) << date.GetYear() << '-'
		<< setw(2) << date.GetMonth() << '-'
		<< setw(2) << date.GetDay();
	return stream;
}

bool operator<(const Date& lhs, const Date& rhs) {
	if ((lhs.GetYear() == rhs.GetYear()) && (lhs.GetMonth() == rhs.GetMonth())) {
		return lhs.GetDay() < rhs.GetDay();
	}
	else if ((lhs.GetYear() == rhs.GetYear()) && (lhs.GetMonth() != rhs.GetMonth())) {
		return lhs.GetMonth() < rhs.GetMonth();
	}
	else {
		return lhs.GetYear() < rhs.GetYear();
	}
}

bool operator==(const Date& lhs, const Date& rhs) {
	return lhs.GetDay() == rhs.GetDay() &&
		   lhs.GetMonth() == rhs.GetMonth() &&
		   lhs.GetYear() == rhs.GetYear();
}

bool operator<=(const Date& lhs, const Date& rhs) {
	return (lhs < rhs) || (lhs == rhs);
}
bool operator>(const Date& lhs, const Date& rhs) {
	return !(lhs <= rhs);
}
bool operator>=(const Date& lhs, const Date& rhs) {
	return (lhs > rhs) || (lhs == rhs);
}
bool operator!=(const Date& lhs, const Date& rhs) {
	return !(lhs == rhs);
}
