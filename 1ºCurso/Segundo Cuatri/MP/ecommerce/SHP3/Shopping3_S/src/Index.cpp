/* 
 * File:   Index.cpp
 * @author estudiante1: López Ramírez, Yeray
 * @author estudiante2: Velázquez Ortuño, Diego
 * @warning To be implemented by students 
 */
#include <string>
#include <iostream>
#include <cassert>
#include <fstream>
#include "Index.h"

using namespace std;

Index::Index() {
    _nEntries = 0;
    _onBrand = 0;
}

Index::Index(int onBrand) {
    _nEntries = 0;
    _onBrand = onBrand;
}

void Index::setIOnWhich(int val) {
    if(val == 1 || val == 0)
        _onBrand = val;
}

int Index::size() const{
    return _nEntries;
}

void Index::clear() {
    for(int i = 0; i < _nEntries; i++)
        _entries[i].initDefault();
    _nEntries = 0;
}

int Index::getIOnWhich() const {
    return _onBrand;
}


int Index::add(const Pair & pair) {
    string key = pair.getKey();
    int is_valid = 1;
    
    int pos = upper_bound(key);
    if(key >= _entries[pos].getKey() && !_entries[pos].isEmpty())
        pos++;
     
    for(int i = _nEntries; i > pos; i--)
        _entries[i] = _entries[i-1];  
    _entries[pos].set(key,pair.getPos());  
        
    _nEntries++;
    
    return is_valid;
}

/**
 * @brief Build the index using the Brand o the userID as searching key
 * @param evSet origin
 */
void Index::build(const EventSet & evSet, int onBrand) {
    clear();
    string on_brand = "";
        
    setIOnWhich(onBrand);
    if (onBrand == 0)
        on_brand = "UserID";
    if (onBrand == 1)
        on_brand = "Brand";
    for (int i = 0; i < evSet.size(); i++){
        if(evSet.at(i).getField(on_brand) != ""){ //Las marcas vacias no se indexan
            Pair pair(evSet.at(i).getField(on_brand), i);
            add(pair);
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
int Index::lower_bound(const string & key) {
    int izda = 0;
    int dcha = _nEntries-1;
    int centro, pos;
    bool encontrado1 = false, encontrado2 = false;
    
    if (_nEntries == 0)
        pos = 0;
    else{
        while (izda <= dcha && !encontrado1){ //Metodo binario
            centro = (izda + dcha) /2;
            if (_entries[centro].getKey() == key){
                pos = centro;
                encontrado1 = true;
            }
            else if (_entries[centro].getKey() < key)
                izda = centro +1;
            else if (_entries[centro].getKey() > key)
                dcha = centro -1;
        }
        if (encontrado1){
            for (int i=pos-1; i>=0 && !encontrado2; i--)
                if (_entries[i].getKey() != key){
                    pos = i+1;
                    encontrado2 = true;
                }
            if (!encontrado2)
                pos =0;
        }
        else 
            pos = dcha;
    }
    
    return pos;
}

/**
 * @brief Returns the position to the first element in the Index which is considered to go after val.
 * look at the example.
 * example: // 10 20 30 30 40 50 60 70
 * upper_bound(30) ........^
 * upper_bound(35) ........^
 * @param key the searching key a string
 * @return a position in the Index
 */
int Index::upper_bound(const string & key) {

    int izda = 0;
    int dcha = _nEntries-1;
    int centro, pos;
    bool encontrado1 = false, encontrado2 = false;
    
    while (izda <= dcha && !encontrado1){ //Metodo binario
            centro = (izda + dcha) /2;
            if (_entries[centro].getKey() == key){
                pos = centro;
                encontrado1 = true;
            }
            else if (_entries[centro].getKey() < key)
                izda = centro +1;
            else if (_entries[centro].getKey() > key)
                dcha = centro -1;
        }
    if (encontrado1){
        for (int i=pos; i<_nEntries && !encontrado2; i++)
            if (_entries[i].getKey() != key){
                pos = i;
                encontrado2 = true;
            }
        if (!encontrado2)
            pos = _nEntries;
    }
    else 
        pos = izda;
    
    return pos;
}

const Pair & Index::at(int pos) const {
    return _entries[pos];
}

Pair & Index::at(int pos) {
    if(pos > -1)
        return _entries[pos];
    else
        return NULL_PAIR;
}

void Index::print()const {
    for(int i = 0; i < _nEntries; i++)
        cout << at(i).to_string() << endl;
}

// external functions

Event getEvent(const EventSet& evSet, Index indx, int pos) {
    int event_pos = indx.at(pos).getPos();
    
    return evSet.at(event_pos);    
}

void write(ofstream & os, const EventSet& evSet, const Index& indx) {
    for(int i = 0; i < indx.size(); i++)
        os << indx.at(i).to_string() << endl;
}
Index rawFilterIndex(const EventSet & evSet, const Index & indx, std::string field, std::string value) {
    int j = 0;
    Index subindx;
    Event aux;;
    
    for (int i = 0; i < indx.size(); i++){
        aux = getEvent(evSet, indx, i);
        if (aux.getField(field) == value || aux.getDateTime().sameDay(value)){ //Si es DateTime comprueba si son el mismo dia
            Pair pair(value, indx.at(i).getPos());
            subindx.add(pair);
            j++;
        }
    }
    return subindx; 
}

float sumPrice(const EventSet& evSet, const Index& indx) {
    float price = 0;

    for (int i = 0; i < indx.size(); i++)
        price += getEvent(evSet, indx, i).getPrice();
    
    return price;
}