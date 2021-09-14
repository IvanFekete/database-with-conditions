//
// Created by Ivan Fekete on 17.10.2020.
//

#include "database.h"
#include <sstream>

string stringify(const Date& date, const string& event) {
    stringstream ss;
    ss << date << " " << event;
    return ss.str();
}

Database::Database() {}

void Database::Add(const Date& date, const string& event) {
    if (!eventsSets[date].count(event)) {
        events[date].push_back(event);
        eventsSets[date].insert(event);
    }
}

void Database::Print(ostream& os) const {
    for (const auto& [date, events] : events) {
        for (const auto& event: events) {
            os << stringify(date, event) << endl;
        }
    }
}

int Database::RemoveIf(function<bool(const Date &, const string &)> filter) {
    int counter = 0;
    vector<Date> keysToRemove;
    for (auto& [date, eventNames] : events) {
        vector<string> savedEventNames;
        for (const auto& eventName: eventNames) {
            if (!filter(date, eventName)) {
                savedEventNames.push_back(eventName);
            } else {
                counter++;
                eventsSets[date].erase(eventName);
            }
        }
        eventNames = savedEventNames;
        if (eventNames.empty()) {
            keysToRemove.push_back(date);
        }
    }

    for (const auto& key: keysToRemove) {
        events.erase(key);
        eventsSets.erase(key);
    }

    return counter;
}


vector<string> Database::FindIf(function<bool(const Date&, const string&)> filter) const{
    vector<string> result;
    for (const auto& [date, eventNames] : events) {
        for (const auto& eventName: eventNames) {
            if (filter(date, eventName)) {
                result.push_back(stringify(date, eventName));
            }
        }
    }

    return result;
}

string Database::Last(const Date& date) const{
    auto it = events.upper_bound(date);
    if (it == events.begin()) {
        throw invalid_argument("");
    }
    it--;
    stringstream ss;
    return stringify(it->first, it->second.back());
}