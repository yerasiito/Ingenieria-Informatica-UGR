/**
 * @file DateTime.cpp
 * @author estudiante1: Velázquez Ortuño, Diego 
 * @author estudiante2: López Ramírez, Yeray 
 * @note To be implemented by students 
 * 
 */

#include <iostream>
#include <cstring>
#include <sstream>
#include "DateTime.h"
using namespace std;

//Metodos Privados

void DateTime::initDefault() {
    split(DATETIME_DEFAULT,_year,_month,_day,_hour,_min,_sec);
}

int DateTime::DefaultSize(){
    size_t tama = strlen(DATETIME_DEFAULT); // size_t y strlen son funciones no vistas pero son mas simples y eficientes que un bucle
    return tama;
}

//Constructores

DateTime::DateTime(){
    initDefault();
}

DateTime::DateTime(const string & line) 
{   
    set(line);
}

//Getters

int DateTime::year() const {
    return _year;
}

int DateTime::month() const {
    return _month;
}

int DateTime::day() const {
    return _day;
}

int DateTime::hour() const {
    return _hour;
}

int DateTime::min() const {
    return _min;
}

int DateTime::sec() const {
    return _sec;
}

//Setter

void DateTime::set(const std::string & line) {
    //Comprueba el tamaño para verificar el formato de la linea. Si no es correcto se pone por defecto
    if(line.size() == DefaultSize()){    
        split(line, _year,_month,_day,_hour,_min,_sec);
        if(!isCorrect(_year,_month,_day,_hour,_month,_sec))
            initDefault();
    }
    else
        initDefault();
}

//Otros Metodos

bool DateTime::isBefore(const DateTime & one) const{
    bool is_before = true;
    
    //calculamos los segundos a partir de las horas minutos y segundos
    int s_total = _hour*3600+_min*60+_sec;
    int one_s_total = one.hour()*3600 + one.min()*60 + one.sec();
    
    //Comparamos si es menor entonces "false" y si es igual tenemos en cuenta el resto de variables
    if(one.year() < _year)
        is_before = false;
    else if(one.year() == _year && one.month() < _month)
        is_before = false;
    else if(one.month() == _month && one.day() < _day)
        is_before = false;
    else if(one.day() == _day && one_s_total < s_total)
        is_before = false;
    else if(one_s_total == s_total)
        is_before = false;

    
    return is_before;
}

int DateTime::weekDay() const{
    
        int h, q = _day, m = _month, y = _year;
	
        //Tenemos en cuenta el caso de enero y febrero
        if(_month <= 2){
		m = _month + 12;
                y -= 1;
        }

	//Aplicamos la fórmula.
	h = (q + (13 *(m + 1))/5 + y + y/4 - y/100 + y/400 -1 ) % 7;	
		
	//Devolvemos el resultado.
	return(h);

}

//Funciones Externas

void split( const std::string & line, int & y, int  & m, int  & d, int  & h, int & mn, int & s) {
    //Se substrae apartir del formato YYYY-MM-DD HH-mm-SS y se pasa a entero
    y = stoi(line.substr(0,4));
    m = stoi(line.substr(5,2));
    d = stoi(line.substr(8,2));
    h = stoi(line.substr(11,2));
    mn = stoi(line.substr(14,2));
    s = stoi(line.substr(17,2));
        
}

bool isCorrect(int year, int month, int day, int hour, int min, int sec) {

    bool is_correct = true;
    int month_days[12] {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};


    //Comprobar horas, minutos y segundos
    if(min >= 60 || sec >= 60 || hour >= 24)
        is_correct = false;

    //Comprobar si el año es bisiesto
    if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
        month_days[1]++;


    //Comprobar si el mes es válido
    if(month < 1 || month > 12)
        is_correct = false;

    //Comprobar si el dia es válido
    int m = month - 1;
    if(day < 0 || day > month_days[m])
        is_correct = false;

    //Si ha pasado todas las condiciones, la fecha es valida
    
    return is_correct;
}


bool DateTime::sameDay(const DateTime & other) const{
    bool _sameDay = false;
    if(_year == other.year() && _month == other.month() && _day == other.day())
        _sameDay = true;
    
    return _sameDay;
}

string DateTime::to_string() const {
    char local[64];
    sprintf(local, "%04i-%02i-%02i %02i:%02i:%02i UTC", _year, _month, _day, _hour, _min, _sec);
    return local;
}

