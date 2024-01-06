/* 
 * File:   Index.cpp
 * @author MP-Team DECSAI
 * @warning To be implemented by students 
 */
#include <string>
#include <iostream>
#include <cassert>
#include <fstream>
#include "Index.h"

using namespace std;

void Index::copy(Pair *dest){
    for (int i=0; i< size();i++)
        dest[i] = _entries[i]; // dest[i] = at(i); version
}

void Index::copy(const Index &orig){
    _nEntries = orig.size();
    for (int i=0; i<orig.size();i++)
        at(i) = orig.at(i); //_entries[i] = orig._entries[i]; version mas rapida
}

Index::Index(int onBrand) {
    _nEntries = 0;
    _capacity = 0;
    _entries = nullptr;
    _onBrand = onBrand;
}

Index::Index(const Index & orig){
    _nEntries=orig._nEntries;
    _capacity = orig._capacity;
    _entries = new Pair[_capacity];
    copy(orig);
}

void Index::setIOnWhich(int val) {
    _onBrand = (val > 0) ? 1 : 0;
}

void Index::reallocate(int size) {
    Pair *aux = new Pair[size];
    
    for (int i = 0; i < _nEntries; i++){
        aux[i] = _entries[i];
    }
    deallocate();
    
    _entries = aux;
    _capacity = size;    
}

void Index::deallocate() {
    if (_entries != nullptr) {
        delete [] _entries;
        _entries = nullptr;
    }
}

int Index::size() const {
    return _nEntries;
}

void Index::clear() {
    _nEntries = 0;
    _capacity = 0;
    deallocate();
}

int Index::getIOnWhich() const {
    return _onBrand;
}

int Index::add(const Pair & pair) {
    int i, pos;
    string key = pair.getKey();
    bool ok = true;
    
    if (_nEntries == _capacity) {
        reallocate(2*_capacity + 1);
        //cerr << _maxEntries << endl;
    }

    if ((key == "")) // may be the search key is empty
        ok = false;
    else {
        pos = upper_bound(key);
        for (i = _nEntries; i > pos; i--) { // making room 
            _entries[i] = _entries[i - 1];
        }
        _entries[pos] = pair; // insertion
        _nEntries++;
    }
    return ok;
}

/**
 * @brief Build the index using the Brand o the userID as searching key
 * @param evSet origin
 */
void Index::build(const EventSet & evSet, int onBrand) {
    Pair one;
    bool ok;
    string key, field;
    field = onBrand ? "Brand" : "UserID";
    clear();
    setIOnWhich(onBrand);

    for (int i = 0; i < evSet.size(); i++) {
        key = evSet.at(i).getField(field);
        if (key != "") { // in order not to include NULL in the index, possible in Brand
            one.set(key, i);
            add(one);
        }
    }
}

/**
 * @brief Returns the position to the first element in the Index
 * which is not considered to go before key (i.e., either it is equivalent is the first one
 * or it goes after), look at the example.
 * @param key the searching key a string
 * example: // 10 20 30 30 40 50 60 70
 * low_bound(30) ....^
 * low_bound(35) ..........^
 * @return a position in the Index
 */

/* la solucion propuesta está basada en la busqueda binaria pero con claves duplicadas*/
//int Index::lower_bound(const string & key) const {
//    int pos = -1;
//    bool found = false;
//    int low = 0, upp = _nEntries - 1, center;
//    while (0 <= upp && !found) {
//        if (_entries[upp].getKey() < key)
//            found = true;
//        else
//            upp--;
//    }
//    if (!found)
//        return 0;
//    else
//        return upp+1;
//}

int Index::lower_bound(const string & key) const {
    
    int low = 0, upp = _nEntries - 1, center;
    while (low <= upp ){ //&& !found) {
        center = (low + upp) / 2;
        if (_entries[center].getKey() < key) 
            low = center + 1;
        else 
            upp = center - 1;
    }

    return low;
}
//
/**
 * @brief Returns the position to the first element in the Index which is considered to go after val.
 * look at the example.
 * example: // 10 20 30 30 40 50 60 70
 * upper_bound(30) ........^
 * upper_bound(35) ........^
 * @param key the searching key a string
 * @return a position in the Index
 */

/* OJO la solucion propuesta está basada en la busqueda binaria ADAPTADA  con claves duplicadas*/

int Index::upper_bound(const string & key) const {
    int pos = -1;
    bool found = false;
    int low = 0, upp = _nEntries - 1, center;
    while (low <= upp && !found) {
        center = (low + upp) / 2;
        if (_entries[center].getKey() == key) {
            found = true;
            for (pos = center; pos < _nEntries && _entries[pos].getKey() == key; pos++)
                ; // pos goes down, increases until != key
        } else if (_entries[center].getKey() < key) low = center + 1;
        else upp = center - 1;
    }

    if (!found) {
        pos = low;
    }

    return pos;
}

const Pair & Index::at(int pos) const {
    if (pos >= 0 && pos < _nEntries)
        return _entries[pos];
    else 
        return NULL_PAIR;
    
}

Pair & Index::at(int pos) {
   if (pos >= 0 && pos < _nEntries)
        return _entries[pos];
    else 
        return NULL_PAIR;
}

void Index::print()const {
    cout << to_string() << endl;
}

Index & Index::operator=(const Index & one) {
    if (this != &one) {  // to avoid one = one
        clear();
        reallocate(one._capacity);
        _nEntries = one._nEntries;
        copy(one);
    }
    return *this;
}

Index::~Index() {
    deallocate();
}

// external functions

Event getEvent(const EventSet & evSet, const Index & indx, int pos) {
    Event one;
    int posInSet = indx.at(pos).getPos(); // to query the EventSet
    one = evSet.at(posInSet);
    return one;
}

void write(ofstream &os, const EventSet & evSet, const Index & indx) {
    Event one;
    for (int i = 0; i < indx.size(); i++) {
        one = getEvent(evSet, indx, i);
        one.write(os);
        os << endl;
    }
}
// external functions

Index rawFilterIndex(const EventSet & evSet, const Index & indx, const std::string &field, const std::string &value) {
    int posInSet, lower, upper;
    Event one;
    Index sub_indx(indx.getIOnWhich()); // build an indx on the same searching key
    DateTime filter_date;

    if ((field == "Brand" && indx.getIOnWhich() == 1) || (field == "UserID" && indx.getIOnWhich() == 0)) { // we are looking for entries in the Index
        lower = indx.lower_bound(value); // set the beginning 
        upper = indx.upper_bound(value); // set the end
        for (int i = lower; i < upper; i++)
            sub_indx.add(indx.at(i)); // query only the index
    } else if (field == "DateTime") {
        filter_date.set(value);
        for (int i = 0; i < indx.size(); i++) {
            one = getEvent(evSet, indx, i);
            if (one.getDateTime().sameDay(filter_date)) { // Cannot use getField since it returns a string
                sub_indx.add(indx.at(i)); // Add to index if  dates coincide up to day
            }
        }
    } else {
        for (int i = 0; i < indx.size(); i++) {
            one = getEvent(evSet, indx, i);
            if (one.getField(field) == value)
                sub_indx.add(indx.at(i));
        }
    }
    return sub_indx;
}

float sumPrice(const EventSet & evSet, const Index & indx) {
    Event one;
    float sum = 0;
    for (int i = 0; i < indx.size(); i++) {
        sum += evSet.at(indx.at(i).getPos()).getPrice();
    }
    return sum;
}