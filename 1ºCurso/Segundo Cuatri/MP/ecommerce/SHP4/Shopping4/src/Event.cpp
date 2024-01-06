/**
 * @file Event.cpp
 * @author MP-Team DECSAI
 * @warning Update the class. Methods print and read To be implemented by students 
 * 
 */
#include <fstream>
#include <string>
#include "Event.h"
using namespace std;


Event::Event() {
    initDefault();
}

void Event::initDefault() {
    set(EVENT_DEFAULT);
}

Event::Event(const string &line) {
    set(line);
}

DateTime Event::getDateTime() const {
    return _dateTime;
}

string Event::getType() const {
    return _type;
}

string Event::getProductID() const {
    return _prod_id;
}

string Event::getCategoryID() const {
    return _cat_id;
}

string Event::getCategoryCode() const {
    return _cat_cod;
}

string Event::getBrand() const {
    return _brand;
}

double Event::getPrice() const {
    return _price;
}

string Event::getUserID() const {
    return _user_id;
}

string Event::getSession() const {
    return _session;
}

void Event::setDateTime(const string & time) {
    _dateTime.set(time);
}

void Event::setType(const std::string & type) {
    if (type == "purchase" || type == "view" || type == "cart" || type == "remove_from_cart")
        _type = type;
    else
        _type = "view";
}

void Event::setProductID(const std::string & prod_id) {
    if (prod_id == "")
        _prod_id = EMPTY_FIELD;
    else _prod_id = prod_id;
}

void Event::setCategoryID(const std::string & cat_id) {
    _cat_id = cat_id;
}

void Event::setCategoryCode(const std::string & cat_cod) {
    _cat_cod = cat_cod;
}

void Event::setBrand(const std::string & brand) {
    _brand = brand;
}

void Event::setPrice(double price) {
    if (price >= 0)
        _price = price;
    else _price = -1;
}

void Event::setUserID(const std::string & user_id) {
    if (user_id == "")
        _user_id = EMPTY_FIELD;
    else _user_id = user_id;
}

void Event::setSession(const std::string & session) {
    if (session == "")
        _session = EMPTY_FIELD;
    else _session = session;
}

void Event::set(const std::string& line) {
    string date, time, data;
    int pos, posn; // aux for the beginning of the fields

    pos = 0;
    posn = line.find(',', pos); // beginning of the next field
    for (int nfield = 0; nfield < 8 && posn != string::npos; nfield++) {
        data = line.substr(pos, posn - pos);
        pos = posn + 1;
        switch (nfield) {
            case 0:
                setDateTime(data);
                break;
            case 1:
                setType(data);
                break;
            case 2:
                setProductID(data);
                break;
            case 3:
                setCategoryID(data);
                break;
            case 4:
                setCategoryCode(data);
                break;
            case 5:
                setBrand(data);
                break;
            case 6:
                setPrice(stod(data));
                break;
            case 7:
                setUserID(data);
                break;
        }
        posn = line.find(',', pos); // beginning of the next field
    }
    // the last field does not have comma
    posn = line.length();
    data = line.substr(pos, posn - pos);
    setSession(data);
}

bool Event::isEmpty() const {
    bool empty = (_prod_id == EMPTY_FIELD || _price < 0 || _user_id == EMPTY_FIELD || _session == EMPTY_FIELD);
    return empty;
}

string Event::to_string() const {
    string salida;
    salida += _dateTime.to_string();
    salida += "," + _type;
    salida += "," + _prod_id;
    salida += "," + _cat_id;
    salida += "," + _cat_cod;
    salida += "," + _brand;
    salida += "," + std::to_string(_price);
    salida += "," + _user_id;
    salida += "," + _session;
    return salida;
}

string Event::getField(const string & field) const {
    string result = EMPTY_FIELD;
    if (field == "DateTime") {
        result = getDateTime().to_string();
    } else if (field == "Type") {
        result = getType();
    } else if (field == "ProductID") {
        result = getProductID();
    } else if (field == "CategoryID") {
        result = getCategoryID();
    } else if (field == "CategoryCode") {
        result = getCategoryCode();
    } else if (field == "Brand") {
        result = getBrand();
    } else if (field == "Price") {
        result = std::to_string(getPrice());
    } else if (field == "UserID") {
        result = getUserID();
    } else if (field == "Session") {
        result = getSession();
    }
    return result;
}

void Event::write(ostream &os) const {
    os << this->to_string();    
}

void Event::read(istream &is) {
    string line;
    getline(is,line); 
    set(line);       // load the event with the data from a line  
}

Event &Event::operator= (const Event &one){
    _dateTime = one._dateTime;
    _type = one._type;
    _prod_id = one._prod_id; // NOTNULL
    _cat_id = one._cat_id;
    _cat_cod = one._cat_cod;
    _brand = one._brand;
    _price = one._price;
    _user_id = one._user_id; //NOTNULL
    _session = one._session; //NOTNULL

    return *this;
}