# dslib

## General

dslib is a data structure library that implements stacks, queues, singly linked
lists and doubly linked lists. It also provides iterators and a crude exception
handling system.

Iterators are used to access individual elements of slists and lists, providing
all of the usual iterator functionality as iterators to the beginning and
end of containers, incrementing, decrementing and deferencing.

There's also a global dslib_error variable that stores an error code that most
functions "throw". If error checking is needed, it's possible to check if
`ds_lib != DSLIB_SUCCESS`. If that is true, then an error occured and must be
dealt with accordingly.

All functions assert whether the container passed to them is NULL or not. The
reason for that is to avoid NULL pointer deferencing.

## Documentation
dslib is documented using Doxygen. To create a documentation page, enter the
following in a terminal:

```
doxygen /doc/doxyfile
```

It will generate a `html` folder. The documentation is located in the
`index.html` file.
