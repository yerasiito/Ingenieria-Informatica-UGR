/*
 * File:   main.cpp
 * @author estudiante1: López Ramírez, Yeray
 * @author estudiante2: Velázquez Ortuño, Diego
 * @warning To be implemented by students. Follow the instructions given in the headers
 */

/**
 * @brief This program must load a sample dataset given as parameters to the program.
 * 
 * The main() function has three mandatory parameters:  
 * "-input <input_file>"  "-events <number_events>"  "-index-by Brand|UserID"
 *    - input_file is the path to the file used as input
 *    - number_events is the number of events to be read from the input_file
 *    - Brand and UserID with the parameter index-by marks the field used to build
 *      the index
 *  there are also three optional parameters:
 * "-report-by Brand|UserID|Type|Datetime"  "-output <output_file>"  "-display Framed|Fancy"
 *    - report-by marks the column used for grouping the event when creating the reports
 *    - output_file is the file to store the output
 *    - display is used to choose the format of the DataTable output:
 *  *  * - If the parameter is absent, the report is shown in plain text, using DataTable::showPlainReportH(0)
 *  *  * - If the parameter is set to Framed, the report is shown using a table format, with DataTable::showFramedReportH(0)
 *  *  * - If the parameter is set to Fancy, the report is shown as histograms using an external library, with DataTable::showFancyReportH(0)
 * 
 * ALL THE PARAMETERS CAN BE GIVEN IN ANY ORDER
 * 
 * The following calls are correct and equivalent
 * shopping3 -input_file data/ECommerce41.dataset -events 30 -index-by Brand -report-by Brand -display Framed
 * shopping3 -events 30 -display Framed -report-by Brand -input_file data/ECommerce41.dataset -index-by Brand 
 *
 */

/**
 * NOTE: NO PARAMETERS EXECUTION
 * In order to modularize the development of this assignment, a simplified execution
 * mode is proposed, where only one parameter is employed. The execution of the
 * program using:
 * 
 * shopping3 -noargs
 * 
 * is intended to be used with input redirection. 
 * To this end, several input files have been prepared. They are placed in folder
 * tests/validation, with name <dataset.keyboard>. This files always contain the
 * same structure:
 * - Path to the input file
 * - Number of events to read from input
 * - Field used to build the index (Brand or UserID)
 * - Field used to group the reports (Brand, UserID, Type or DateTime)
 * 
 * The proper way to call the program using this structure is the following (using
 * ECommerce30.keyboard as input, for example)
 * dist/Debug/GNU-Linux/shopping3 -noargs < tests/validation/ECommerce30.keyboard
 */

#include <string>
#include <cassert>
#include <iostream>
#include <fstream>

#include "Event.h"
#include "EventSet.h"
#include "Index.h"
#include "DataVector.h"

#include "MPTests.h"

#define ERROR_ARGUMENTS 1
#define ERROR_OPEN 2
#define ERROR_DATA 3


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
void computeActivity(EventSet es, int arrayA[]);

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
 * @brief Breaks the program execution if an error is encountered during execution
 * @param errorcode Integer marking the type of error encountered (1 for arguments
 * error, 2 for open file error and 3 for data reading error, see ERROR_ARGUMENTS,
 * ERROR_OPEN and ERROR_DATA definitions above)
 * @param errordata String representing where the error has been produced (mainly
 * used to indicate the file that produced the error)
 */
void errorBreak(int errorcode, string errordata);

/**
 * @brief Given anEventSet and a filtered Index over that dataset, build the
 * Event set with only the indexed events
 * @param es The original EventSet
 * @param indx The reduced Index
 * @return The subset of the EventSet referenced by the Index
 */
EventSet & extractEventSet(const EventSet &es,const Index & indx);

/**
 * @brief Helper function that prints information about main parameters when the
 * program is not called properly. Should be called from @see errorBreak when the
 * errorcode is equal to 1
 */
void showHelp();

int main(int argc, char** argv) {
    //Los tests tardan bastante pero acaban pasando(hasta 42 segundos en el de 926 records)
    
    string ifilename = "", ofilename = "", indexby = "", reportby = "", display = "";
    string curr_arg;
    int n2Read = 0;
    ifstream ifile;
    ofstream ofile;
    EventSet originalES;

    bool noargs = false;
    
    //check the number of arguments
    if(argc != 2 && argc != 3 && argc != 5 && argc != 7 && argc != 9 && argc != 11)
        errorBreak(ERROR_ARGUMENTS, "");
    
    // 1.- Read the input arguments from argv
    for (int i = 1; i < argc && !noargs; i++) { 
        curr_arg = argv[i];
        if (curr_arg == "-noargs") {
            i++;
            noargs = true;
        }
        else if(curr_arg == "-input"){
            i++;
            ifilename = argv[i];
        } 
        else if(curr_arg == "-events"){
            i++;
            n2Read = stoi(argv[i]);
        } 
        else if(curr_arg == "-index-by"){
            i++;
            indexby = argv[i];
        }
        else if(curr_arg == "-output"){
            i++;
            ofilename = argv[i];
        }
        else if(curr_arg == "-report-by" ){
            i++;
            reportby = argv[i];
        }
        else if(curr_arg == "-display"){
            i++;
            display = argv[i];
        }
        else
            errorBreak(ERROR_ARGUMENTS, "");
    } // end check syntax

    // 2.- If the execution is a non-argument execution, read information from
    // cin, else check that the arguments provided are correct
    if (noargs) {
        cout << endl << "Please type the input file name: ";
        cin >> ifilename;
        cout << endl << "Please type the number of records to read: ";
        cin >> n2Read;
        cout << "Please select the field to index for (UserID, Brand): ";
        cin >> indexby;
        cout << endl << "Please select the field to filter with (DateTime, UserID, Brand, Type): ";
        cin >> reportby;
        cout << endl << "Please indicate the output file (empty for no output file): ";
        cin >> ofilename;
        cout << endl;
    } 
    else if(n2Read == 0 || ifilename == "" || indexby == "")
        errorBreak(ERROR_ARGUMENTS,"");
    
    // 3.- Try to open the proposed input file
    // 4.- Read the events from the input file and load them in a EventSet.
    //     Only the correct ones will be charged on the EventSet  
    ifile.open(ifilename); ////////
    if(ifile.is_open()){
        if(!originalES.read(ifile,n2Read))
            errorBreak(ERROR_DATA, ifilename);
        else
            ifile.close();
    }
    else
        errorBreak(ERROR_OPEN, ifilename);
    /*
    cout << "El original es: " << endl;    
    for(int i = 0; i < originalES.size(); i++)
         cout << i << " " << originalES.at(i).to_string() << endl;       
    */

    // 5.- Build the main index, depending on the input argument
    Index indx;
    int onBrand = 0;
    if(indexby == "Brand")
        onBrand = 1;
    
    indx.build(originalES, onBrand);

    // 6.- Print the amount of events read and events indexed. Keep in mind that
    // the size of the index can be lesser than the size of the EventSet, since
    // the Events with empty Brand cannot be indexed
    
    cout << "El numero de eventos leidos son: " << originalES.size() << endl <<
            "El numero de eventos indexados son: " << indx.size() << endl;

    // 7.- Filter the original EventSet using the main Index. The filtered EventSet
    // will contain only the indexed Events (if the Index is built by user, the
    // original and the filtered EventSets will be identical, since every event
    // must have an associated UserID. If the index is built by brand, the filtered
    // EventSet can be smaller than the original dataset, since there are Events
    // without Brand, which cannot be indexed
    
    EventSet filteredES;
    filteredES = extractEventSet(originalES,indx);   
    
    // 8.- Compute activity by weekday
    int countWeekDay[7] {};
    computeActivity(filteredES, countWeekDay);
    
    // 9.- Generate reports (traffic and money amount) grouped by the corresponding
    // field (indicated by parameter -report-by, Brand by default). Also, save
    // the value, the amount of traffic and the index of the element that generated
    // most traffic
    Index filteredIndx;
    EventSet aux;
    string OnBrandV[indx.size()];
    string hitsOnBrand;
    int util = 0;
    int mostTraffic = 0;
    int contador;
    findUnique(filteredES,reportby,OnBrandV,util);
    

    int traffic[util] {};
    
    for(int i = 0; i < util; i++){
        
        filteredIndx = rawFilterIndex(originalES,indx,reportby,OnBrandV[i]);
        aux = extractEventSet(originalES,filteredIndx);
        contador = 0;

        for(int j = 0; j < filteredIndx.size(); j++){
        //Comprobamos segun el reportby
            if(reportby == "DateTime"){
                if(aux.at(j).getDateTime().sameDay(OnBrandV[i]))
                    contador++;
            }
            else if(OnBrandV[i] == aux.at(j).getField(reportby))
                contador++;
        }
        
        if(mostTraffic < contador){
            hitsOnBrand = OnBrandV[i];
            mostTraffic = contador;
        }
        traffic[i] = contador;
    }
    filteredIndx = rawFilterIndex(originalES,indx,reportby,hitsOnBrand);
    aux = extractEventSet(originalES,filteredIndx);
    
    double Sales[util] {};
    
    for(int i = 0; i < util; i++){
        filteredIndx = rawFilterIndex(originalES,indx,reportby,OnBrandV[i]);
        Sales[i] = sumPrice(originalES,filteredIndx);
    }
    
    // 10.- Display information, depending on the display mode specified by
    // -display (Plain mode by default). Also, print the information about the
    // element with highest traffic (its value and the number of events generated)
    DataVector weeklyData;
    weeklyData.alloc(7);
    
    weeklyData.setTitle("Sales/Day");
    weeklyData.loadLabels(DAYNAME);
    weeklyData.loadValues(countWeekDay);
    if(display == "")
        cout << weeklyData.showPlainReportH(0);
    else if (display == "Framed")
        cout << weeklyData.showFramedReportH(0);
    else if (display == "Fancy"){}
        //cout << endl << weeklyData.showFancyReportH(0); //No funciona
    
    // 11. Save the EventSet corresponding to the element with highest traffic in
    // the output file, if specified
    ofile.open(ofilename);
    aux.write(ofile);
    ofile.close();

    // 12.- Report everything to the tests suite using REPORT_DATA2
    
    //hitsData
    DataVector hitsData;
    hitsData.alloc(util);
    
    hitsData.setTitle(indexby + "/Traffic");
    hitsData.loadLabels(OnBrandV);
    hitsData.loadValues(traffic);
    cout << endl << hitsData.showFramedReportH(0);
    
    //amountData
    DataVector amountData;
    amountData.alloc(util);
    
    amountData.setTitle(indexby + "/Sales");
    amountData.loadLabels(OnBrandV);
    amountData.loadValues(Sales);
    
    cout << endl << amountData.showFramedReportH(2);
    
    
    REPORT_DATA2(originalES, "Original read from dataset");
    REPORT_DATA2(filteredES, "Events indexed");
    REPORT_DATA2(hitsData, "Report traffic");
    REPORT_DATA2(amountData, "Report amount");
    
    return 0;
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

void computeActivity(EventSet es, int arrayA[]){
    int total_val = 0;
    int dia_actividad;
    
    for (int i = 0; i < es.size(); i++){
        if(!es.at(i).isEmpty()){
            dia_actividad = es.at(i).getDateTime().weekDay();
            
            arrayA[dia_actividad]++;
            total_val++;
        }
    }
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

void errorBreak(int errorcode, string errordata) {
    if (errorcode == ERROR_ARGUMENTS){
        showHelp();
        CVAL << "Error in call " << endl;
        std::exit(-1);
    }
    else if (errorcode == ERROR_OPEN){
        CVAL << "Error opening file " << errordata << endl;
        std::exit(-1);
    }
    else if (errorcode == ERROR_DATA){
        CVAL << "Data error in file " << errordata << endl;
        sfd:exit(-1);
    }
}

EventSet & extractEventSet(const EventSet &es, const Index & indx) {
    static EventSet Subset;
    Subset.clear();
    for(int i = 0; i < indx.size(); i++)
        Subset.add(getEvent(es,indx,i));
   
    return Subset;
}

void showHelp() {
    cout << "Please use: -input <filename> -events <number> -index-by UserID|Brand [-report-by UserID|Brand|Type|DateTime -output <filename>]" << endl;
    cout << "\n-input <filename>\n\tRead events from dataset in <filename>";
    cout << "\n-events <number>\n\tNumber of events to read";
    cout << "\n-index-by <field>\n\tField to index by. It can only be UserID or Brand";
    cout << "\n\nOptional arguments";
    cout << "\n-report-by <field>\n\tField to report by. It can only be UserID, Brand, Type or DateTime. The default value is Brand";
    cout << "\n-output <filename>\n\tFile to save the dataset of the field selected with -index-by with maximum traffic. If not specified, it does not save anything" << endl << endl;
}
