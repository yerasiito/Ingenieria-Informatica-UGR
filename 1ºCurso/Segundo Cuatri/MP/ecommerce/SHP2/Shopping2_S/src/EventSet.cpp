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

}

std::string EventSet::to_string() const {
    string result;
    result = std::to_string(_nEvents) + " ";
    for (int i = 0; i < _nEvents; i++)
        result += _events[i].to_string() + "\n";
    return result;
}

EventSet::EventSet() {
}

int EventSet::size() const {

}


void EventSet::clear() {
}

int EventSet::add(const Event & e) {

}

int EventSet::add(const std::string& line) {

}

const Event & EventSet::at(int pos) const {

}


EventSet rawFilterEvents(const EventSet& es, const std::string &field, const std::string &value) {
    
}

void findUnique(const EventSet& es, const std::string &field, std::string values[], int & n_values) {

}

float sumPrice(const EventSet & evSet) {
}

