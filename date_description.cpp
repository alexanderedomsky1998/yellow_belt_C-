#include "date_description.h"
#include <algorithm>
#include <iterator>
#include <unordered_set>
using namespace std;

void DateDescription::Add(const string& event) {
	if (unique_events.find(event) == unique_events.end()) {
		order_events.push_back(event);
		unique_events.insert(event);
	}
}

vector<pair<Date, string>> DateDescription::Find(const Date& date, const function<bool(const Date& date, const string& event)>& pred) const {
	vector<string> result_string;

	copy_if(begin(order_events), end(order_events), back_inserter(result_string),
		[date, pred](const string& event_) {
		return pred(date, event_);
	});

	vector<pair<Date, string>> result;
	for (const auto& event_ : result_string) {
		result.push_back({ date, event_ });
	}
	return result;
}

unsigned DateDescription::Erase(const Date& date, const function<bool(const Date&, const string&)>& pred) {

	auto it_start_to_delete = stable_partition(order_events.begin(), order_events.end(),
		[date, pred](const string& event_) {return !pred(date, event_); });

	if (it_start_to_delete == order_events.end()) {
		return 0;
	}

	for (auto it = it_start_to_delete; it != order_events.end();) {
		unique_events.erase(*(it++));
	}

	size_t old_size = order_events.size();

	order_events.erase(it_start_to_delete, order_events.end());

	return old_size - order_events.size();
}

set<string> DateDescription::GetUnique() const {
	return unique_events;
}

vector<string> DateDescription::GetOrdered() const {
	return order_events;
}
