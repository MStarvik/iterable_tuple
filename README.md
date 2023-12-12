# iterable_tuple
A fixed-size container that provides compile-time indexing of elements of different types, like a tuple, as well as runtime indexing and iteration, like an array. Implemented as an an array of variants of the element types. Runtime indexing simply return the variant, while compile-time indexing returns the element type. Might come in handy some day.

Relies on mp_unique from boost's metaprogramming library to find the set of unique element types. If boost is not available, there are [equivalent templates](https://stackoverflow.com/a/62108334) available online.
