# dynBitset

Simple header-only dynamic bitset implementation for when boost is not an option and you don't have time to implement your own.
Only includes the *cmath*, *vector*, *climits* and *iostream* headers.

Example:
```
    size_t n;
    
    /** get n somewhere **/
    ...
    
    /** bitset w/ dimension assigned at runtime **/
    dynBitset set(n);
    
    /** set each bit **/
    for (int iBit = 0; iBit < n; ++iBit) {
        set[iBit] = ...;
    }
    
    /** get last bit **/
    bool bitVal = set[--n];
``` 

