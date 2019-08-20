#include <xc.inc>
    ////////////////////////////////////////////////////////////////////////////////
    // Exercise 6.1:
    //     Set up the global and memory sections
    //     for these two functions
    ////////////////////////////////////////////////////////////////////////////////
//### YOUR CODE HERE ###  // Delcare _incFunction to be Global
//### YOUR CODE HERE ###  // Declare _decFunction to be Global
//### YOUR CODE HERE ###  //  Set the PSECT for these functions
_incFunction:       ; Add two char numbers and return the result
    INCF WREG,w
    return
	
_decFunction:  ; Subtract two char numbers and return the result
    decf WREG,w
    return
