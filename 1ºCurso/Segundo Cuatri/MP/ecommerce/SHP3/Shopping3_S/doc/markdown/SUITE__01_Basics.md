## _01_Basics

###  DateTime_Constructors
1. A newly create instance of DateTime gives the default date
1. A newly created instance of DateTime by using a string gives the same string

###  DateTime_getters
1. The year of the default datetime must be 2021
1. The month of the default datetime must be 1
1. The day of the default datetime must be 1
1. The hour of the default datetime must be 0
1. The minutes of the default datetime must be 0
1. The seconds of the default datetime must be 0

###  DateTime_set
1. Setting an instance of DateTime with a valid string gives the same date" ;

###  DateTime_sameDay
1. SKIP_ASSERT_TRUE_R(dt1.sameDay(dt3));
1. SKIP_ASSERT_FALSE_R(dt1.sameDay(dt2));

###  Event_ConstructorBase
1. A newly created instance of Event gives the default event
1. A newly created instance of Event is consdered empty
1. A newly create instance of Event, initializaed with a string. gives the same string
1. Setting the productid of an event to a good value X gives X

###  Event_Setters_getters
1. Setting the datetime of an event to TODAY gives TODAY
1. Setting the type of an event to a good value X gives X
1. Setting the productid of an event to a good value X gives X
1. Setting the categoryID of an event to a good value X gives X
1. Setting the category code of an event to a good value X gives X
1. Setting the brand of an event to a good value X gives X
1. Setting the price of an event to a good value X gives X

###  EventSet_Constructor
1.  A newly created instance of EventSet must have size = 0
1.  A newly created instance of EventSet must ha a to_string empty '0'

###  EventSet_add_event
1.  Adding an event to a newly created instance of EventSet must have size = 1
1. Adding the default event to an empty event set must have a to_string equal to the default event
1.  Adding 1 event to a filled EventSet increases its size in 1

###  EventSet_add_line
1.  Adding a line to a newly created instance of EventSet must have size = 1
1. Adding the default event, as a line, to an empty event set must have a to_string equal to the default event
1.  Adding 1 event, as a line, to a filled EventSet increases its size in 1

###  EventSet_at_basic
1. Querying the event at the 0 position should match with the first event added to the EventSet
1. Querying the event at the middle position should match with the event added which was added at that point

###  Pair_Constructors
1. After the creation of a new instance of Pair, it shows its default value
1. After the creation of a new instance of Pair by using a string and an int, it shows these two same values
1. After the creation of a new instance of Pair by using a string and NO int, it shows the string and -1 default value

### Pair_isEmpty
1.  Any newly created instance of Pair, without specifying any arguments, is considered to be empty
2.  Any instance of Pair with valid key and pos, could not be considered empty

###  Pair_setters
1. After the creation of a new instance of Pair and setting it by using a string and an int, it shows these two same values
1. After the creation of a new instance of Pair and setting the key to a given string, it sohows this same string
1. After the creation of a new instance of Pair and setting the value to a given number, it sohows this same umber

###  Pair_getters
1. After the creation of a new instance of Pair and setting it by using a string and an int, getKey() returns the same string
1. After the creation of a new instance of Pair and setting it by using a string and an int, getPost() resturns the same integer
1. After the creation of a new instance of Pair and setting the key to a given string, getKey() returns this same string
1. After the creation of a new instance of Pair and setting the value to a given number, getPos() returns the same number

###  Index_Constructors
1.  A newly created instance of Index must have size = 0
1.  A newly created instance of Index must write as \": On brand? 0\"

###  Index_getIOnWhich
1. Building an index by Users reports 0
1. Building an index by brand reports 1

###  Index_clear
1. Clearing a brand new instance of Index leaves it empty
1. Clearing an instance of Index with existing records leaves it empty


###  Integrated_5_records
1. Execution of a simple test with five records only

###  Integrated_30_records
1. Execution of a test with 30 records only

###  Integrated_41_records
1. Execution of a test with 41 records only

###  Integrated_162_records
1. Execution of a test with 162 records only

###  Integrated_926_records
1. Execution of a test with 926 records only

###  Integrated_Args_5_records
1. Execution of a simple test with five records using main arguments

###  Integrated_Args_30_records
1. Execution of a test with 30 records using main arguments

###  Integrated_Args_41_records
1. Execution of a test with 41 records using main arguments

###  Integrated_Args_162_records
1. Execution of a test with 162 records using main arguments

###  Integrated_Args_926_records
1. Execution of a test with 926 records using main arguments
