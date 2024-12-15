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
//Utilities.cpp


#include <iostream>
#include "Utilities.h"

namespace sdds{

    // Initialize the static class variable for the delimiter.
    char Utilities::m_delimiter = '\0';

    // Function to set the width field.
    void Utilities::setFieldWidth(size_t newWidth)
    {
        m_widthfield = newWidth;
    }

    // Function to get the current width field.
    size_t Utilities::getFieldWidth() const
    {
        return m_widthfield;
    }

    // Function to extract a token from a string, updating the position and indicating if there are more tokens.
    std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
    {
        std::string token; // Token string
        size_t startPos = next_pos; // Initial position

        // Trim the leading and trailing spaces of the input string
        std::string strTrim = trimSpace(str);

        // Find the position of the delimiter starting from the current position
        size_t endPos = strTrim.find(m_delimiter, startPos);

        // If the delimiter is not found in the remaining string
        if (endPos == std::string::npos) {
            // Extract the token from the remaining string
            token = strTrim.substr(startPos);
            more = false; // No more tokens to extract
        } else {
            // If the delimiter is found
            // Extract the token from the trimmed string
            token = strTrim.substr(startPos, endPos - startPos);

            // If the extracted token is empty, there are no more tokens to extract
            if (token.empty()) {
                more = false;

                // Check if the delimiter is found at the next position
                if (!more) {
                    throw std::string("Delimiter found next pos");
                }
            }

            more = (next_pos < str.length()); // Update if there is more to extract
            next_pos = endPos + 1; // Update the next position to the character after the delimiter
        }

        // Trim the extracted token
        token = trimSpace(token);

        // Update the maximum width field based on the length of the current token
        if (token.length() > m_widthfield) {
            m_widthfield = token.length();
        }

        return token; // Return the extracted token
    }

    // Function to set the delimiter for all instances of the class.
    void Utilities::setDelimiter(char newDelimiter)
    {
        m_delimiter = newDelimiter;
    }

    // Function to get the current delimiter.
    char Utilities::getDelimiter()
    {
        return m_delimiter;
    }

    // Function to trim leading and trailing spaces from a string.
    std::string Utilities::trimSpace(const std::string& str)
    {
        size_t firstSpace = str.find_first_not_of(' ');
        if (std::string::npos == firstSpace) {
            return str;
        }
        size_t lastSpace = str.find_last_not_of(' ');
        return str.substr(firstSpace, (lastSpace - firstSpace + 1));
    }

}
