/* 
 * File:   EventSet.cpp
 * @author MP-Team DECSAI
 * @warning Update the class. Methods read and write To be implemented by students 
     * remove rawFilters is not longer used, -> deprecated
 */


#include <unordered_map>
#include <string>
#include <fstream>
#include <cassert>
#include "DateTime.h"
#include "EventSet.h"
#include <iostream>

using namespace std;

Event NULL_EVENT = Event();

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
void EventSet::copy(Event *dest) const{
    for (int i=0; i< size();i++)
        dest[i] = _events[i]; // dest[i] = at(i);
}

void EventSet::copy(const EventSet &orig){
    _nEvents = orig.size();
    for (int i=0; i<orig.size();i++)
        _events[i] = orig._events[i]; //at(i) = orig.at(i); version más lenta
}

void EventSet::reallocate(unsigned size){
    Event *aux = new Event[size];
    copy(aux);
    deallocate();

    _events = aux;
    _capacity = size;
}

void EventSet::deallocate(){
    if (_events != nullptr){
        delete [] _events;
        _events = nullptr;
    }    
}

EventSet::EventSet() : _nEvents(0), _events(nullptr), _capacity(0) {
}

EventSet::EventSet(const EventSet & orig){
    _nEvents=orig._nEvents;
    _capacity = orig._capacity;
    _events = new Event[_capacity];
    copy(orig);
    /*
    for (int i = 0; i < _nEvents; i++){
        _events[i]= orig._events[i];
    }  */
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
    _capacity = 0;
    deallocate();
}

int EventSet::add(const Event & e) {
    //cerr << " capacity " << _capacity << " ";
    if (_nEvents == _capacity) {
        reallocate(2*_capacity + 1);
        //cerr <<  "... update capacity"<< endl;
    } 
    _events[_nEvents] = e;
    _nEvents++;
    //cerr << " size " << _nEvents;
    return 1;
}

int EventSet::add(const std::string& line) {
    Event e(line);
    return add(e);
}

const Event & EventSet::at(int pos) const {
    if (0 <= pos && pos < size())
        return _events[pos];
    else {
        return NULL_EVENT;
    }
}

void EventSet::write(ofstream &os) const {
    for (int i = 0; i < size(); i++) {
        at(i).write(os);
        os << endl;
    }
}

EventSet & EventSet::operator=(const EventSet & one) {
    if (this != &one) { // to avoid one = one
        clear();
        reallocate(one._capacity);
        _nEvents = one._nEvents;
        copy(one);
    }
    return *this;
}

EventSet::~EventSet(){
    deallocate();
}

bool EventSet::read(ifstream &is, int nelements) {
    bool success = true;
    Event one;
    clear();
    for (int i = 0; i < nelements && success; i++) {
        one.read(is);
        if (is.eof())
            success = false;
        if (!one.isEmpty()) // whenever all data are correct
            success = add(one); // check if the event fit int the eventSet
    }
    return success;
}
// external functions

float sumPrice(const EventSet & evSet) {
    float result = 0;
    float price;
    for (int i = 0; i < evSet.size(); i++) {
        price = evSet.at(i).getPrice();
        if (price >-1) //WARNING IS IT NECESSARY ??
            result += price;
    }
    return result;
}


void findUnique(const EventSet& es, const std::string &field, std::string values[], int & n_values) {
    string value;
    n_values = 0;
    for (int i = 0; i < es.size(); i++) {
        value = es.at(i).getField(field);
        if (field != "DateTime") {
            if (findString(values, n_values, value) == -1)
                values[n_values++] = value;
        } else {
            DateTime dtValue(value);
            bool found=false;
            for (int d=0;d<n_values && !found; d++) {
                DateTime dtRecord;
                dtRecord.set(values[d]);
                if (dtRecord.sameDay(dtValue))
                    found=true;
            }
            if (! found) {
                value[11] = value[12] = value[14] = value[15] = value[17] = value[18] = '0';
                values[n_values++] = value;
            }
        }
    }
}
