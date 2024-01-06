3
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
