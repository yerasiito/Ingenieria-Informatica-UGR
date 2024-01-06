/* 
 * File:   Pair.cpp
 * @author estudiante1: López Ramírez, Yeray
 * @author estudiante2: Velázquez Ortuño, Diego
 * @warning To be implemented by students
 */
#include <string>

#include "Pair.h"

using namespace std;

Pair NULL_PAIR = Pair();

Pair::Pair()  {
    initDefault();
}

Pair::Pair(const std::string & key, int pos) {
    if (isEmpty())
        initDefault();
    else{
        _key = key;
        _pos = pos;
    }
}

bool Pair::isEmpty() const{
    bool is_empty = false;
    if (_key==EMPTY_FIELD && _pos==-1)
        is_empty = true;
    
    return is_empty;
}

std::string Pair::getKey() const {
    return _key;
}

int Pair::getPos() const {
    return _pos;
}

void Pair::setKey(const std::string & key) {
    _key = key;
}

void Pair::setPos(int pos) {
    _pos = pos;
}

void Pair::set(const std::string & key, int pos) {
    if (key == EMPTY_FIELD && pos>-1)
        initDefault();
    else{
        setKey(key);
        setPos(pos);
    }
}

std::string Pair::to_string() const { 
    std::string _pair = _key + " " + std::to_string(_pos);
    
    return _pair;
}

void Pair::initDefault() {
    _key = EMPTY_FIELD;
    _pos = -1;
}

bool equalKey(const Pair & left, const Pair & right) {
    bool equal_key = false;
    if (left.getKey() == right.getKey())
        equal_key = true;
    
    return equal_key;
}
