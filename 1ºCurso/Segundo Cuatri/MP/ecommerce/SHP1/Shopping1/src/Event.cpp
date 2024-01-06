/**
 * @file Event.cpp
 * @author DECSAI
 * @author estudiante1: López Ramírez, Yeray 
 * @author estudiante2: Velázquez Ortuño, Diego 
 * @note To be implemented by students 
 * 
 */

#include <string>
#include "Event.h"
using namespace std;

//Funciones Privadas

/* Separa las cadenas que le pasamos en variables por referencia.
 * Usaremos const &line para ahorrar espacio.
 */
void Event::split( string const &line, string &dateTime, string &type, string &prod_id, string &cat_id, 
                   string &cat_cod, string &brand, string &price, string &user_id, string &session){
    
    string cadenas[9];
    int posicion = 0;
    int pos[10];
    int j = 0;
    
    //Busca en la cadena las posiciones de las comas y las guarda en el vector pos[].
    for (int i = 1; i < 9; i++){
        pos[i] = line.find(',', posicion);
        //La posicion de inicio será ahora la siguiente a la coma anterior.
        posicion = pos[i] + 1;
    }
    
    //*
    pos[0] = -1;
    pos[9] = line.size();
    
    //Se almacenan en un vector para despues asignar a las variables cada subcadena.
    //* Se necesitan la posicion anterior a 0 y la final para que el algoritmo funcione correctamente.
    for (int i = 0; i < 9; i++)
        //Este algoritmo hace que se ignoren las posiciones de las comas.
        cadenas[i] = line.substr(pos[i]+1, pos[i+1]-pos[i]-1);
    
    dateTime = cadenas[0];
    type     = cadenas[1];
    prod_id  = cadenas[2];
    cat_id   = cadenas[3];
    cat_cod  = cadenas[4];
    brand    = cadenas[5];
    price    = cadenas[6];
    user_id  = cadenas[7];
    session  = cadenas[8];
}

void Event::initDefault() {
    set(EVENT_DEFAULT);
}

//Constructores

Event::Event() {
    initDefault();
}

Event::Event(string line) {
    set(line);
}

//Getters

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

//Setters

void Event::setDateTime( string  time) {
    _dateTime.set(time);
}

void Event::setType( string  type) {
    //Establece el tipo al defecto "view".
    _type = VALID_TYPES[0];
    
    //Comprueba si es alguno de los 4 tipos es el que nos dan y si es así lo cambia.
    for (int i = 0; i < 4; i++)
        if (type == VALID_TYPES[i])
            _type = type;
}

void Event::setProductID( string  prod_id) {
    //Comprueba si es el valor vacío y si no le asigna el dado.
    if (prod_id == "")
        _prod_id = EMPTY_FIELD;
    else
        _prod_id = prod_id;
 }

void Event::setCategoryID( string  cat_id) {
    _cat_id = cat_id;
}

void Event::setCategoryCode( string  cat_cod) {
    _cat_cod = cat_cod;
}

void Event::setBrand( string  brand) {
    _brand = brand;
}

void Event::setPrice(double price) {
    //Comprueba si el precio dado es menor que cero y si es así le asigna el defecto.
    if(price >= 0)
        _price = price;
    else
        _price = -1.000000;
}

void Event::setUserID( string  user_id) {
    //Comprueba si es el valor vacío y si no le asigna el dado.
    if (user_id == "")
        _user_id = EMPTY_FIELD;
    else
        _user_id = user_id;
}

void Event::setSession( string  session) {
    //Comprueba si es el valor vacío y si no le asigna el dado.
    if (session == "")
        _session = EMPTY_FIELD;
    else
        _session = session;
}

//Asigna mediante los setters a cada variable el valor que ha sido devuelto por referencia del split. 
void Event::set( string line) {
    string dateTime, type, prod_id, cat_id, cat_cod, brand, price, user_id, session;
    split(line, dateTime, type, prod_id, cat_id, cat_cod, brand, price, user_id, session);
    
    setDateTime(dateTime);
    setType(type);
    setProductID(prod_id);
    setCategoryID(cat_id);
    setCategoryCode(cat_cod);
    setBrand(brand);
    setPrice(stod(price));
    setUserID(user_id);
    setSession(session);
}

//Otros Metodos

bool Event::isEmpty() {
    bool is_empty = false;
    
    //Comprueba si alguna de las 3 variables que NO deben estar vacías lo están, y si es así devuelve true.
    if (_prod_id == EMPTY_FIELD || _user_id == EMPTY_FIELD || _session == EMPTY_FIELD)
        is_empty = true;
    
    return is_empty;
}

string Event::to_string() const {
    std::string salida;
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