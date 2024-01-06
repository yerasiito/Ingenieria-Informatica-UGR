/* 
 * File:   EventSet.cpp
 * @author estudiante1: López Ramírez, Yeray
 * @author estudiante2: Velázquez Ortuño, Diego
 * @note To be implemented by students 
 */


#include <unordered_map>
#include "EventSet.h"
#include <fstream>
#include <iostream>
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
    for(int i = 0; i < n_array; i++)
        if(array[i] == name)
            pos = i;
    
    return pos;
}
std::string EventSet::to_string() const {
    string result;
    result = std::to_string(_nEvents) + " ";
    for (int i = 0; i < _nEvents; i++)
        result += _events[i].to_string() + "\n";
    return result;
}

EventSet::EventSet() {
    clear();
}

int EventSet::size() const {
    return _nEvents;
}


void EventSet::clear() {
    for( int i = 0; i < _nEvents; i++)
        _events[i].set(EVENT_DEFAULT);
    _nEvents = 0;
}

int EventSet::add(const Event & e) {
    int valid;
    if(_nEvents < MAXEVENT){
        _events[_nEvents] = e;
        _nEvents++;
        valid = 1; //sucessful
    }
    else
        valid = 0; //failed
    
    
    return valid;
}

int EventSet::add(const std::string & line) {
    Event e(line);
    
    return add(e);
}

const Event & EventSet::at(int pos) const {
    if(pos >= 0 && pos < _nEvents)
        return _events[pos];
    else
        return NULL_EVENT;
}

Event & EventSet::at(int pos) {
    if(pos >= 0 && pos < _nEvents)
        return _events[pos];
    else
        return NULL_EVENT;
}


EventSet rawFilterEvents(const EventSet & es, const std::string & field, const std::string & value) {
    EventSet subSet;
    
    //Añade una nueva cadena a subSet cuando el valor del campo en "EventSet es" es igual al valor pasado como parámetro
    for(int i = 0; i < es.size(); i++){
        if(es.at(i).getField(field) == value){
            subSet.add(es.at(i));
        }
    }
    
    return subSet;
}

void findUnique(const EventSet & es, const std::string & field, std::string values[], int & n_values) {
    n_values = 0;
    for (int i=0; i<es.size(); i++){
        if(field == "DateTime"){ //En el caso de ser el campo DateTime, comprueba si los dias son iguales 
            DateTime fecha = es.at(i).getDateTime();
            if(!fecha.sameDay(values[n_values-1])){
                values[n_values++] = fecha.to_string().erase(10,25) + " 00:00:00 UTC";
            }
        }
                
        if (field != "DateTime" && findString(values,n_values,es.at(i).getField(field)) == -1){
            values[n_values++] = es.at(i).getField(field);
        }
    }   
}

float sumPrice(const EventSet & evSet) {
    double total = 0;
    for(int i = 0; i < evSet.size(); i++)
        total += evSet.at(i).getPrice();
    return total;
}

void EventSet::write(ofstream & os) const {
    ostream &e = os;
    
    for(int i = 0; i < _nEvents; i++){
        _events[i].write(e);
    }
}

bool EventSet::read(ifstream & is, int nelements) {
    bool is_correct = true;
    istream &a = is;
    _nEvents = 0;
    
    for(int i = 0; i < nelements && is_correct; i++){
        _events[i].read(is);
        if(_events[i].isEmpty())
            is_correct = false;
        else
           _nEvents++;
    }
    return is_correct;
}
