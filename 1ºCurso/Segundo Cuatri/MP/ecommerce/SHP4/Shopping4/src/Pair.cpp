/* 
 * File:   Pair.cpp
 * @author MP-Team DECSAI
 * @warning To be implemented by students
 */
#include <string>

#include "Pair.h"

using namespace std;

Pair NULL_PAIR = Pair();

Pair::Pair()  {
    initDefault();
}

bool Pair::isEmpty() const {
    return getKey()==EMPTY_FIELD && getPos()<0;
}
Pair::Pair(const std::string & key, int pos) {
    if (key != "") {
        _key = key;
        _pos = pos;
    } else initDefault();

}

const std::string & Pair::getKey() const {
    return _key;
}

const int Pair::getPos() const {
    return _pos;
}

void Pair::setKey(const std::string & key) {
    if (key != "") {
        _key = key;
    } else initDefault();
}

void Pair::setPos(int pos) {
    if (pos > -1) {
        _pos = pos;
    } else initDefault();
}

void Pair::set(const std::string & key, int pos) {
    setKey(key);
    setPos(pos);
}

std::string Pair::to_string() const { /** necessary ?*/
    string result;
    result = _key + " " + std::to_string(_pos);
    return result;
}

void Pair::initDefault() {
    _key = EMPTY_FIELD;
    _pos = -1;
}

Pair & Pair::operator=(const Pair & one) {
    _key = one._key;
    _pos = one._pos;
        
    return *this;
}

bool equalKey(const Pair & left, const Pair & right) {
    return left.getKey() == right.getKey();
}
