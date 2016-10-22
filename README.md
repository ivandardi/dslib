dslib
------

## General

dslib is a data structure library that implements stacks, queues, singly linked
lists, doubly linked lists and graphs. It also provides iterators.

Iterators are used to access individual elements of lists, providing all of the
usual iterator functionality, such as iterators to the beginning and end of
containers, incrementing, decrementing, etc.

The dslib follows the principle of "garbage in, garbage out". It will not
perform safety checks, nor it will cleanup dynamic memory allocated by the user.
It's the user's responsibility to ensure the validity of the arguments passed
to the dslib functions.
