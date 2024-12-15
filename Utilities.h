/**************************************************
Full Name  : AYUSHKUMAR VIPULBHAI PATEL
Student ID#: 114473226
Email      : apatel574@myseneca.ca
Section    : NFF
Date	   : 03/12/2023
Authenticity Declaration:
I confirm that I am the only author of this file
and the content was created entirely by me.
**************************************************/
//Utilities.h

#pragma once

#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H

#include <iostream>

namespace sdds{

    // Declaration of the Utilities class.
    class Utilities{
        // Instance variable for the width field.
        size_t m_widthfield = 1;
        
        // Class variable for the delimiter.
        static char m_delimiter; 

    public:
        // Member Functions
        
        // Function to set the width field.
        void setFieldWidth(size_t newWidth);
        
        // Function to get the current width field.
        size_t getFieldWidth() const;
        
        // Function to extract a token from a string, updating the position and indicating if there are more tokens.
        std::string extractToken(const std::string& str, size_t& next_pos, bool& more);

        // Class Functions
        
        // Static function to set the delimiter for all instances of the class.
        static void setDelimiter(char newDelimiter);
        
        // Static function to get the current delimiter.
        static char getDelimiter();

        // Function to trim leading and trailing spaces from a string.
        std::string trimSpace(const std::string& str);
    };

}

// End of the conditional compilation directive.
#endif
