#pragma once
#include "date.h"
#include "date_description.h"
#include <map>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <functional>

using namespace std;



class Database
{
public:
	void Print(ostream& stream) const;
	pair<Date, string> Last(const Date& date) const;
	vector<pair<Date, string>> FindIf(const function<bool(const Date&, const string&)>& pred) const;
	unsigned RemoveIf(const function<bool(const Date&, const string&)>& pred);
	void Add(const Date& date, const string& event);
private:
	map<Date, DateDescription> database_;
};


ostream& operator<<(ostream& stream, const pair<Date, string>& date_to_event);