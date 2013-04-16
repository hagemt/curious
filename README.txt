HOMEWORK 8: BIDIRECTIONAL MAPS

NAME: Tor E Hagemann <hagemt@rpi.edu>

COLLABORATORS AND OTHER RESOURCES: Lots of C++11 and STL reference.

ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT: 24

ORDER NOTATION ANALYSIS:

n = the number of elements
k = maximum number of links stored in a single node
    (for extra credit, non- one-to-one associations)

// TODO update when complete...
size:        O(1)
insert:      O(log(n))
erase:       O(log(n))
find:        O(log(n))
operator[]:  O(log(n))

// FIXME can *_end be constant time?
key_begin:   O(1)
key_end:     O(log(n))
value_begin: O(1)
value_end:   O(log(n))

follow_link: O(1)

key iterator++/--:   O(log(n))
value iterator++/--: O(log(n))

default constructor: O(1)
copy constructor:    O(n)
destructor:          O(n)
assignment operator: O(n)

MISC. COMMENTS TO GRADER: N/A
