#include <xc.inc>
    ////////////////////////////////////////////////////////////////////////////////
    // Exercise 6.1:
    //     Set up the global and memory sections
    //     for these two functions
    ////////////////////////////////////////////////////////////////////////////////
    GLOBAL _incFunction                     // Delcare _incFunction to be Global
    GLOBAL _decFunction                     // Declare _decFunction to be Global
    PSECT text0,local,class=CODE,delta=1    //  Set the PSECT for these functions
_incFunction:       ; Add two char numbers and return the result
    INCF WREG,w
    return
	
_decFunction:  ; Subtract two char numbers and return the result
    decf WREG,w
    return
