#include "database.h"
#include <algorithm>
#include <utility>

using namespace std;

void Database::Add(const Date& date, const string& event) {
	database_[date].Add(event);
}

void Database::Print(ostream& stream) const {
	for (const auto& date : database_) {
		for (const auto& event : date.second.GetOrdered()) {
			stream << date.first << " " << event << endl;
		}
	}
}

vector<pair<Date, string>> Database::FindIf(const function<bool(const Date&, const string&)>& pred) const {
	vector<pair<Date, string>> result;
	for (auto& row : database_) {
		vector<pair<Date, string>> add = row.second.Find(row.first, pred);
		result.reserve(result.size() + add.size());
		result.insert(result.end(), add.begin(), add.end());
	}
	return result;
}

unsigned Database::RemoveIf(const function<bool(const Date&, const string&)>& pred) {
	unsigned count = 0;
	vector<Date> date_to_delete;
	for (auto& row : database_) {
		count += row.second.Erase(row.first, pred);
		if (database_[row.first].GetUnique().empty()) {
			date_to_delete.push_back(row.first);
		}
	}
	for (const auto& date_ : date_to_delete) {
		database_.erase(date_);
	}
	return count;
}

pair<Date, string> Database::Last(const Date& date) const {
	if (database_.empty()) {
		throw invalid_argument("No entries");
	}

	auto it = database_.lower_bound(date);

	if (it == database_.cbegin() && date < it->first) {
		throw invalid_argument("No entries for requested date");
	}

	if (it == database_.cend() || it->first != date)
		it = prev(it);

	return{ it->first, it->second.GetOrdered().back() };
}

ostream& operator<<(ostream& stream, const pair<Date, string>& date_to_event) {
	stream << date_to_event.first << " " << date_to_event.second;
	return stream;
}
