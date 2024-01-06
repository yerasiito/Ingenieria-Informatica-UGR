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
