#pragma once
#include "date.h"
#include <set>
#include <unordered_set>
#include <vector>
#include <string>
#include <string>
#include <algorithm>
#include <functional>
using namespace std;

class DateDescription {
public:
	void Add(const string& event);
	unsigned Erase(const Date& date, const function<bool(const Date& date, const string& event)>& pred);
	vector<pair<Date, string>> Find(const Date& date, const function<bool(const Date& date, const string& event)>& pred) const;
	set<string> GetUnique() const;
	vector<string> GetOrdered() const;
private:
	vector<string> order_events;
	set<string> unique_events;
};
