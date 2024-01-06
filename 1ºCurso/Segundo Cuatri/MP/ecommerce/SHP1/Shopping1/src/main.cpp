/**
 * @file main.cpp
 * @author DECSAI
 * @author estudiante1: López Ramírez, Yeray 
 * @author estudiante2: Velázquez Ortuño, Diego 
 * @note To be implemented by students 
 * 
 */

#include <string>
#include <cassert>
#include <iostream>
#include "Event.h"

#include "MPTests.h"

using namespace std;

/**
 * @brief displays the content of the array by using the method to_string that easy to transfer data to stream.  The content remains constant
 * @param array of the Events
 * @param nEvent number of events in the array
 */
void print(const Event array[], int & nEvent);

/**
 * @brief Update the counter per week day (value in 0..6) for every event found . 
 * It also shows the computed values on the screen in the following format
 * ~~~~
 *      SUNDAY(0) MONDAY(0) TUESDAY(0) WEDNESDAY(0) THURSDAY(0) FRIDAY(0) SATURDAY(0)
 *      +----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+ 
 *      |    |    |    |    |    |
 *      0    5    10   15   20   25
 * ~~~~
 * 
 * @param arrayE an Event input array
 * @param nEvents number of events in arrayE
 * @param arrayA an int output array
 */
void computeActivity(Event arrayE[], int  nEvents,  int arrayA[]);

/**
 * @brief Compute the  max number of activity events, and the day on which is produced
 * @param arrayA the counter of activities, an input array
 * @param ndays number of days
 * @param maxDay
 * @return maxActivity the counter of events of 
 */
int computeMaxActivityDay(const int arrayA[], int & maxDay, int ndays=7);

/**
 * @brief Transform the weekday number to the day name;
 * @param nWeekDay input int
 * @param day_name output string
 */
void DayName(int nWeekDay, string &day_name);

/**
 * @brief The main function of the program carries out the following procedure
 *   - It uses a static array of Events to store a sequence of events read from 
 * keyboard (likely to be redirected from a data file in the ./tests folder)
 *   - It reads the maximum number of valid records to be stored in the array.
 *   - If the event read is right (use the method isEmpty() to detect non-valid
 * records), it is stored in the array, otherwise, it is dismissed. Only valid records count.
 *   - Next, it computes the number of events found at each day of the week (complete the implementation
 * of the local function computeActivity() which also shows the result)
 *   - Next, it finds which is the day of highest activity recorded and show it on screen
 */

/**
 * @brief Read input data and process it.
 * @param nEventos intput int
 * @param Eventos output Event array
 */
void read(int nEventos, Event Eventos[]);

int main(int argc, char** argv) {
    
    int dias_semana[7] {};
    int nEventos;
    int max_day;
    string cad;
    
    //Leemos el numero de eventos
    getline(cin,cad);
    nEventos = stoi(cad); 
   /* Otra opcion seria leer con cin >> nEventos seguido de cin.ignore() para
    * borrar el \n del buffer y leer bien las cadenas. Sin embargo, nos da error
    */
    
    Event eventos[nEventos];
    read(nEventos,eventos);
        
    computeActivity(eventos,nEventos,dias_semana);
    computeMaxActivityDay(dias_semana,max_day,7);
}

void read(int nEventos, Event eventos[]){
    string cadenas;
    for( int i = 0; i < nEventos ; i++){
        getline(cin,cadenas);
        eventos[i].set(cadenas);
    }
}

void print(const Event array[], int & nEvent) {
    for (int i=0; i<nEvent; i++)
        cout << array[i].to_string() << endl;
}

void DayName(int nWeekDay, string &day_name){
    if(nWeekDay == 0)
        day_name = DAYNAME[0];
    if(nWeekDay == 1)
        day_name = DAYNAME[1];
    if(nWeekDay == 2)
        day_name = DAYNAME[2];
    if(nWeekDay == 3)
        day_name = DAYNAME[3];
    if(nWeekDay == 4)
        day_name = DAYNAME[4];
    if(nWeekDay == 5)
        day_name = DAYNAME[5];
    if(nWeekDay == 6)
        day_name = DAYNAME[6];
}

void computeActivity(Event arrayE[], int  nEvents,  int arrayA[]){
    int total_val = 0;
    int dia_actividad;
    
    for (int i=0; i<nEvents; i++){
        if(!arrayE[i].isEmpty()){
            dia_actividad = arrayE[i].getDateTime().weekDay();
            
            arrayA[dia_actividad]++;
            total_val++;
        }
    }

    CVAL << "Activity found:";
    
    for (int day=0; day<7; day++) 
        CVAL << " " << DAYNAME[day] << "(" << arrayA[day] << ")";
    
    CVAL << endl;
    CVAL << " Records read: " << nEvents << " Valid records: " << total_val;
}

int computeMaxActivityDay(const int arrayA[], int &maxDay, int ndays){
    int MaxActivity = 0;
    string Day;
    
    for(int i = 0; i < ndays; i++)
        if(arrayA[i] > MaxActivity){
            MaxActivity = arrayA[i];
            maxDay = i;
        }
    
    DayName(maxDay,Day);
        
    CVAL << " Max activity: " << MaxActivity << " Day of Max activity: " << Day;

    return MaxActivity;
}
