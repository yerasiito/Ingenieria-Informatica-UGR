           
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

