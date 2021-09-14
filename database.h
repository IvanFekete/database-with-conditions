#pragma once

#include "date.h"
#include <string>
#include <iostream>
#include <functional>
#include <vector>
#include <map>
#include <set>

using namespace std;

class Database {
public :
    Database();
    void Add(const Date& date, const string& event);
    void Print(ostream& os) const;
    int RemoveIf(function<bool(const Date&, const string&)> filter);
    vector<string> FindIf(function<bool(const Date&, const string&)> filter) const;
    string Last(const Date& date) const;
private:
    map<Date, vector<string>> events;
    map<Date, set<string>> eventsSets;
};
