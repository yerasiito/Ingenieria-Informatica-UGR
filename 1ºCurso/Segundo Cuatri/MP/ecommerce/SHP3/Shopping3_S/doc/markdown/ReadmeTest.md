# TEST SUITE FOR PROJECT Shopping3

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

## _02_Intermediate

###  DateTime_isBefore
1. A DateTime cannot be before itself
1. Default date is before today
1. Today is not before the Default date

###  DateTime_weekDay
1. Today must be Thursday
1. Tomorrow is Friday
1. Yesterday was Wednesday

###  Event_getField
1. getField(\"DateTime\") on any Event, must be equal to getDateTime()
1. In any row, querying the Event for field \"Price\" will produce the same string than getDateTime
1. In any case, querying the Event for field \"UserID\" will produce the same string than the former getUserID()
1. In any row, querying the EventS a mandatory field cannot give an empty string
1. In any row, querying an optional field will produce the same string than the former event added to the EvenSet

###  EventSet_add_event_partial
1.  Adding MAXEVENT events to a newly created EventSet increases its size in MAXEVENT

###  EventSet_at_intermediate
1. Querying the event at the last position should match with the last event added to the EventSet
1. Accessing EventSet at() a certain position and changing the user ID of the event, this change will remain in the EventSet itself
1. Accessing EventSet at() a certain position and changing the brand of the event, this change will remain in the EventSet itself

###  Index_10x10_just_build
1. In any case, building the same index twice gives the same result

###  Index_B_BxU_build_at
1.  The index by brand built within experiment BxU is the same key during U consecutive positions
1.  The index by brand built within experiment BxU two consecutive indexes of the same brand differ in B units
1.  The index by user built within experiment BxU changes the key at point U

###  Index_U_BxU_build_at
1.  The index by user built within experiment BxU is the same key during B consecutive positions
1.  The index by user built within experiment BxU indexes B consecutive positions for the same key
1.  The index by user built within experiment BxU changes the key at point B

###  Integrated_EMPTY
1. Execution of a simple test with an empty set of records

###  Integrated_ErrorLoading
1. Execution of a simple test with an error when opening the data file

## _03_Advanced

###  DateTime_BadValues
1. Setting a bad date or time gives the default datetime
1. Setting a bad date or time gives the default datetime
1. Setting a bad date or time gives the default datetime
1. Setting a bad date or time gives the default datetime
1. Setting a bad date or time gives the default datetime
1. Setting a bad date or time gives the default datetime
1. Setting a bad date or time gives the default datetime
1. Setting a bad date or time gives the default datetime
1. Setting a bad date or time gives the default datetime
1. Setting a date with the incorrect format throws an exception

###  Event_setType_Bad_Values
1. Setting the type of an event to a good value X gives X
1. Setting the type of an event to a good value X gives X

###  Event_Others_Bad_Values
1. Setting the productid of an event to a good value X gives X
1. Setting the productid of an event to a good value X gives X
1. Setting the productid of an event to a good value X gives X

###  EventSet_add_event_full
1.  Adding one single Event events to a partly filled EventSet must return 1
1.  Adding one single Event events to a completely filled EventSet does not produce any change in the EventSet
1.  Adding one single Event events to a completely filled EventSet must return 0

###  EventSet_at_advanced
1.  Querying an EventSet beyond its legal limits gives an EMPTY event
2.  Querying an EventSet beyond its legal limits gives an EMPTY event
3.  Querying an EventSet within its legal limits always gives a NON-EMPTY event

###  EventSet_externalfunctions
1. sumPrice must give the sum of all prices of a given EventSet, and it doesnt
1. UniqueBrands() must give the number of different brands, but it doesnt
1. UniqueUsers() must give the number of different users, but it doesnt

###  EventSet_write
1. Any EventSet writes into a disk file exactly its to_string() without the number of events

###  EventSet_read
1. Any EventSet read from a disk file must have a to_string(), without the number of events, comparable to the content of the file

###  Index_U_BxU_bounds
1.  The index by user built within experiment BxU lower bounds User u with u*B
2.  The index by brand built within experiment BxU upper bounds Brand b with (b+1)*U

###  Index_B_BxU_bounds
1.  The index by brand built within experiment BxU lower bounds Brand b with b*U
2.  The index by brand built within experiment BxU upper bounds Brand b with (b+1)*U

###  Index_add
1.  Inserting any pair in any index increases its size in one
2.  Adding a  key at the end of the index places the new key in its previous upperbound
3.  Adding a  key at the beginning of the index gives a lower bound equals to 0 after the insertion

###  Index_B_BxU_rawFilterIndex
1.   In an Index BxU , filtering the index by brand-i produces an index with exactly size U

###  Index_U_BxU_rawFilterIndex
1.   In an Index BxU , filtering the index by user-i produces an index with exactly size B

###  Index_Type_BxU_rawFilterIndex
1.   In an Index BxU , filtering the index by Type=cart produces an index with exactly size B

###  Index_DateTime_BxU_rawFilterIndex
1.   In an Index BxU , filtering the index by DateTime equals to the first available date produces an index with exactly size B

###  Index_BxU_sumPrice
1.  Given a BxU Index filtered by user u, the sum of prices amounts to (u*B)/4*(1+B)/2
2.  Given a BxU Index filtered by brand b, the sum of prices amounts to U*(b+1)
3.  Given a BxU Index filtered by type view, the sum of prices amounts to (B*U)/4*(1+B)/2
4.  Given a BxU Index filtered by datetime day , the sum of prices amounts to U*day

### Integrated_ErrorData
1.  Execution of a simple test with an error when reading the data file

### Integrated_ErrorSaving
1.  Execution of a simple test with an error when saving the data file

### Integrated_Args_no_open
1.  Execution of a simple test with main args where the input file is not found

### Integrated_Args_error_data
1.  Execution of a simple test with main args where the number of specified events is greater than the total number of events in the data file

### Integrated_Args_missing_arg
1.  Execution of a test with main args where the input file is not specified

### Integrated_Args_error_bad_arg
1.  Execution of a test with main args where one of the arguments is not understood

# Experiment Index BxU

Build an EventSet ES with B different Brands {b0, b1, b2, ...}, being B>0, B=k'x4, and U different Users {u0, u1, u2, ...}, U>=,  U=k''x4, in such a way that every user in U buy every brand in B exactly once, hence, it is made up of BxU events in which the 
following holds for event _ei_ in ES with i={0,1,2, ..., n-1}
 
1. The brand is i%B
1. The user is i/B
1. The price is i%B+1
1. The operation is VALID_TYPE[((i*4)/(B*U))%4]
1. The day of datetime is i%B
 
Therefore, the following also holds
 
1. Building an index by user: There are U different users
      a. The index keeps the same key every B consecutive records
      a. During these B consecutive records, the position of the index increases in 1
      a. The index change the key bewteen every two consecutive B-blocks
1. Building an index by brand: There are B different brands
      a. The index keeps the same key every U consecutive records
      a. During these B consecutive records, the position of the index increases in B
      a. The index change the key bewteen every two consecutive U-blocks
1. Filtering an index by any brand B-i
   	a. The new index has exactly U size()
   	a. The sumPrice() is exactly BxU
1. Filtering an index by any user U-i
   	a. The new index has exactly B size()
   	a. The sumPrice() is exactly UxBx(1+B)/2
1. Filtering a Brand-Index index by Type (any) 
		a. Gives a new index of size B*U/4
		a. The sumPrice() is B(1+B)/2
1. Filtering a Brand-Index index by Date (any) 
		a. Gives a new index of size U
		a. The sumPrice() is B(1+B)/2
