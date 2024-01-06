/* 
 * File:   EventSet.cpp
 * @author MP-Team DECSAI
 * @note To be implemented by students 
 */


#include <unordered_map>
#include "EventSet.h"

using namespace std;


/**
 * @brief Give string[] and a string, it searches for string within string[]
 * @param array     The set of strings to llok for
 * @param n_array   The size of string[]
 * @param name      The string that is being seeked
 * @return          The position of the first occurrence of string within string[]
 *  -1 if the string does not belong to string[]
 */
int findString(const string array[], int n_array, const string & name) {
    int pos = -1;
    bool found = false;
    for (int i = 0; i < n_array && !found; i++) {
        if (array[i] == name) {
            pos = i;
            found = true;
        }
    }
    return pos;
}


EventSet::EventSet() : _nEvents(0) {
}

int EventSet::size() const {
    return _nEvents;
}

std::string EventSet::to_string() const {
    string result;
    result = std::to_string(_nEvents) + " ";
    for (int i = 0; i < _nEvents; i++)
        result += _events[i].to_string() + "\n";
    return result;
}

void EventSet::clear() {
    _nEvents = 0;
}

int EventSet::add(const Event & e) {
    int ok = 1;
    if (_nEvents < MAXEVENT) {
        _events[_nEvents] = e;
        _nEvents++;
    } else ok = 0;
    return ok;
}

int EventSet::add(const std::string& line) {
    Event e(line);
    return add(e);
}

const Event & EventSet::at(int pos) const {
//    assert(0 <= pos && pos < size());
//    return _events[pos];
    
    if (0 <= pos && pos < size())
        return _events[pos];
    else {
        return NULL_EVENT;
    } 
}


EventSet rawFilterEvents(const EventSet& es, const std::string &field, const std::string &value) {
    EventSet result;
    for (int i = 0; i < es.size(); i++) {
        if (es.at(i).getField(field) == value)
            result.add(es.at(i));
    }
    return result;
    
}

void findUnique(const EventSet& es, const std::string &field, std::string values[], int & n_values) {
    string value;
    n_values=0;
    for (int i = 0; i < es.size(); i++) {
        value = es.at(i).getField(field);
        if (findString(values, n_values, value) == -1)
            values[n_values++] = value;
    }
}

// external functions

float sumPrice(const EventSet & evSet) {
    float result = 0;
    float price;
    for (int i = 0; i < evSet.size(); i++) {
        price = evSet.at(i).getPrice();
        result += price;
    }
    return result;
}

