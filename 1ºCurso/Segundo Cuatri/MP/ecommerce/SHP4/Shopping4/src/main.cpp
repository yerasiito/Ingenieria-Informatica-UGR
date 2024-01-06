/*
 * File:   main.cpp
 * Author: MP-team 
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
 * @brief Update the counter per week day (value in 0..6) for every event found.
 * It also shows the computed values on the screen
 * @param evSet an input EventSet  
 * @param arrayA an int output array
 */
void computeActivity(const EventSet & evSet, int arrayA[]);

/**
 * @brief Breaks the program execution if an error is encountered during execution
 * @param errorcode Integer marking the type of error encountered (1 for arguments
 * error, 2 for open file error and 3 for data reading error, see ERROR_ARGUMENTS,
 * ERROR_OPEN and ERROR_DATA definitions above)
 * @param errordata String representing where the error has been produced (mainly
 * used to indicate the file that produced the error)
 */
void errorBreak(int errorcode, const string & errordata);

/**
 * @brief Given anEventSet and a filtered Index over that dataset, build the
 * Event set with only the indexed events
 * @param es The original EventSet
 * @param indx The reduced Index
 * @return The subset of the EventSet referenced by the Index
 */
EventSet extractEventSet(const EventSet & es, const Index & indx);

/**
 * @brief Helper function that prints information about main parameters when the
 * program is not called properly. Should be called from @see errorBreak when the
 * errorcode is equal to 1
 */
void showHelp();

void f(EventSet e){
    cout<< e.to_string() << endl;
}

/**
 * Main block of the program. The full explanation of the behavior is given in
 * the comment above
 * @param argc Number of arguments passed to main
 * @param argv Strings representing those arguments
 * @return 
 */
int main(int argc, char** argv) {

    string ifilename = "", ofilename = "", indexby = "", reportby = "";
    string sarg;
    int n2Read = -1, nEvents = 0;
    ifstream ifile;
    ofstream ofile;
    EventSet originalES, filteredES, bestES;
    Index mainIndex, filteredIndex, bestIndex;
    // Report
    bool noargs = false;
    double dcounter[MAXEVENT];
    int icounter[MAXEVENT], nlabels, bestValue;
    string labels[MAXEVENT], bestLabel;
    DataVector weeklyData, hitsData, amountData;
    string display = "Plain";

    // 1.- Process the input arguments
    for (int i = 1; i < argc;) { // load of the arguments
        sarg = argv[i];
        if (sarg == "-input") {
            i++;
            if (i >= argc) errorBreak(ERROR_ARGUMENTS, "");
            ifilename = argv[i++];
        } else if (sarg == "-output") {
            i++;
            if (i >= argc) errorBreak(ERROR_ARGUMENTS, "");
            ofilename = argv[i++];
        } else if (sarg == "-report-by") {
            i++;
            if (i >= argc) errorBreak(ERROR_ARGUMENTS, "");
            reportby = argv[i++];
        } else if (sarg == "-index-by") {
            i++;
            if (i >= argc) errorBreak(ERROR_ARGUMENTS, "");
            indexby = argv[i++];
        } else if (sarg == "-events") {
            i++;
            if (i >= argc) errorBreak(ERROR_ARGUMENTS, "");
            n2Read = atoi(argv[i++]);
        } else if (sarg == "-display") {
            i++;
            if (i >= argc) errorBreak(ERROR_ARGUMENTS, "");
            display = argv[i++];
        } else if (sarg == "-noargs") {
            i++;
            noargs = true;
        } else
            errorBreak(ERROR_ARGUMENTS, ""); // any other parameters
    } // end check syntax

    
    // 2.- If the execution is a non-argument execution, read information from
    // cin
    if (!noargs) {
        // Process arguments
        if (reportby == "")
            reportby = "Brand";

        if (n2Read < 0 || ifilename == "" || indexby == "" ||
                (indexby != "UserID" && indexby != "Brand") ||
                (reportby != "Brand" && reportby != "UserID" && reportby != "Type" && reportby != "DateTime"))
            errorBreak(ERROR_ARGUMENTS, "");
    } else {
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
    }
    
    // 3.- Try to open the proposed input file
    ifile.open(ifilename); // ifilename != ""  already check 
    if (!ifile) {
        errorBreak(ERROR_OPEN, ifilename);
    }
    cout << endl << "Reading from " << ifilename << endl;

    // 4.- Read the events from the input file and load them in a EventSet.
    //     Only the correct ones will be charged on the EventSet
    if (!originalES.read(ifile, n2Read)) {
        errorBreak(ERROR_DATA, ifilename);
    }

    // 5.- Build the main index, depending on the input argument
    if (indexby == "UserID") {
        mainIndex.build(originalES, 0);
    } else {
        mainIndex.build(originalES, 1);
    }

    // 6.- Print the amount of events read and events indexed. Keep in mind that
    // the size of the index can be lesser than the size of the EventSet, since
    // the Events with empty Brand cannot be indexed
    cout << endl << "Read " << originalES.size() << " records from file " << ifilename;
    cout << endl << "Main Index by " << indexby << endl << mainIndex.size() << " pairs ";
    if (originalES.size() != mainIndex.size()) {
        cout << endl << originalES.size() - mainIndex.size() << " records could not be indexed";
    }

    // 7.- Filter the original EventSet using the main Index. The filtered EventSet
    // will contain only the indexed Events (if the Index is built by user, the
    // original and the filtered EventSets will be identical, since every event
    // must have an associated UserID. If the index is built by brand, the filtered
    // EventSet can be smaller than the original dataset, since there are Events
    // without Brand, which cannot be indexed
    filteredES = extractEventSet(originalES, mainIndex);
    cout << endl << "amount :" << sumPrice(originalES, mainIndex) << endl;

    // 8.- Compute activity by weekday
    cout << endl;
    computeActivity(filteredES, icounter);

    weeklyData.alloc(7);
    weeklyData.setTitle("Events/day");
    weeklyData.loadLabels(DAYNAME);
    weeklyData.loadValues(icounter);


    // 9.- Generate reports (traffic and money amount) grouped by the corresponding
    // field (indicated by parameter -report-by, Brand by default). Also, save
    // the value, the amount of traffic and the index of the element that generated
    // most traffic
    findUnique(filteredES, reportby, labels, nlabels);

    // Traffic & Amount
    bestValue = -1;
    for (int i = 0; i < nlabels; i++) {
        filteredIndex = rawFilterIndex(originalES, mainIndex, reportby, labels[i]);
        icounter[i] = filteredIndex.size();
        if (icounter[i] > bestValue) {
            bestValue = icounter[i];
            bestIndex = filteredIndex;
            bestLabel = labels[i];
        }
        dcounter[i] = sumPrice(originalES, filteredIndex);
    }

    hitsData.alloc(nlabels);
    hitsData.setTitle(reportby + " (traffic)");
    hitsData.loadLabels(labels);
    hitsData.loadValues(icounter);

    amountData.alloc(nlabels);
    amountData.setTitle(reportby + " (amount)");
    amountData.loadLabels(labels);
    amountData.loadValues(dcounter);
    
    // 10.- Display information, depending on the display mode specified by
    // -display (Plain mode by default). Also, print the information about the
    // element with highest traffic (its value and the number of events generated)
    if (display == "Fancy") {
        cout << endl << weeklyData.showFancyReportH(0) << endl;
        cout << endl << hitsData.showFancyReportH(0) << endl;
        cout << endl << amountData.showFancyReportH(0) << endl;
    } else if (display == "Framed") {
        cout << endl << weeklyData.showFramedReportH(0) << endl;
        cout << endl << hitsData.showFramedReportH(0) << endl;
        cout << endl << amountData.showFramedReportH(0) << endl;
    } else {
        cout << endl << weeklyData.showPlainReportH(0) << endl;        
        cout << endl << hitsData.showPlainReportH(0) << endl;        
        cout << endl << amountData.showPlainReportH(0) << endl;
    }
    cout << endl << "Highest traffic choice (" << bestLabel << ") with " << bestValue << " hits " << endl;

    // 11. Save the EventSet corresponding to the element with highest traffic in
    // the output file, if specified
    if (ofilename != "") {
        cout << endl << "Saving on " << ofilename << endl;
        ofile.open(ofilename);
        if (!ofile) {
            errorBreak(ERROR_OPEN, ofilename);
        }
        write(ofile, originalES, bestIndex);
        //cout << extractEventSet(*originalES, bestIndex)->to_string();
        ofile.close();
    }
    
    // 12.- Report everything to the tests suite using REPORT_DATA2
    // REPORT_DATA2(originalES, "Original read from dataset");
    // REPORT_DATA2(filteredES, "Events indexed");
    // REPORT_DATA2(hitsData, "Report traffic");
    // REPORT_DATA2(amountData, "Report amount");
    
    REPORT_DATA2(originalES, "Original read from dataset");
    REPORT_DATA2(filteredES, "Events indexed");
    REPORT_DATA2(hitsData, "Report traffic");
    REPORT_DATA2(amountData, "Report amount");
    
    return 0;
}

void errorBreak(int errorcode, const string & errordata) {
    switch (errorcode) {
        case ERROR_ARGUMENTS:
            CVAL << endl <<"Error in call" << endl;
            showHelp();
            break;
        case ERROR_OPEN:
            CVAL << endl << "Error opening file " << errordata << endl;
            break;
        case ERROR_DATA:
            CVAL << endl <<"Data error in file " << errordata << endl;
            break;
    }
    std::exit(1);
}

void computeActivity(const EventSet & evSet, int arrayA[]) {
    for (int day = 0; day < 7; day++) {
        arrayA[day] = 0;
    }
    for (int i = 0; i < evSet.size(); i++) {
        arrayA[evSet.at(i).getDateTime().weekDay()] += 1;
    }
    cout << "Activity found:";
    for (int day = 0; day < 7; day++) {
        cout << " " << DAYNAME[day] << "(" << arrayA[day] << ")";
    }
    cout << endl;
}

EventSet extractEventSet(const EventSet & es, const Index & indx) {
    EventSet res;

    for (int i = 0; i < indx.size(); i++) {
        res.add(es.at(indx.at(i).getPos()));
    }
    return res;
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