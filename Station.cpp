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
//Station.cpp

#include <iostream>
#include <iomanip>
#include <string>
#include "Station.h"
#include "Utilities.h"

namespace sdds{
    // Initialize static member variables.
    size_t Station::m_widthField = 0;
    size_t Station::m_idGenerator = 0;

    // Parameterized constructor for the Station class.
    Station::Station(const std::string &record)
    {
        // Create an instance of the Utilities class for token extraction.
        Utilities util;

        // Initialize variables for token extraction.
        size_t next_pos = 0;
        bool moreTokens = true;

        // Extract and set values for member variables from the record string.
        m_itemName = util.extractToken(record, next_pos, moreTokens);
        m_serialNumber = std::stoul(util.extractToken(record, next_pos, moreTokens));
        m_quantity = std::stoul(util.extractToken(record, next_pos, moreTokens));
        m_description = util.extractToken(record, next_pos, moreTokens);

        // Update m_widthField if necessary.
        if (Station::m_widthField < m_itemName.length()) {
            Station::m_widthField = m_itemName.length();
        }

        // Assign a unique ID to the station using m_idGenerator.
        m_id = ++Station::m_idGenerator;
    }

    // Getter function to retrieve the item name.
    const std::string &Station::getItemName() const
    {
        return m_itemName;
    }

    // Function to get the next serial number and increment it.
    size_t Station::getNextSerialNumber()
    {
        return m_serialNumber++;
    }

    // Getter function to retrieve the quantity.
    size_t Station::getQuantity() const
    {
        return m_quantity;
    }

    // Function to update the quantity by decrementing it if possible.
    void Station::updateQuantity()
    {
        if (m_quantity - 1 >= 0) {
            --m_quantity;
        }
    }

    // Function to display information about the Station.
    void Station::display(std::ostream &os, bool full) const
    {
        // Format and output the information to the provided ostream.
        os << std::setw(3) << std::setfill('0') << m_id << " | " 
            << std::left << std::setfill(' ') << std::setw(m_widthField) << m_itemName <<  " | "
            << std::setfill('0') << std::setw(6) << std::right << m_serialNumber  << " | ";

        // Display additional information if the 'full' parameter is true.
        if (full) {
            os << std::setw(4) << std::setfill(' ') << std::right << m_quantity << " | " << m_description;
        }

        // Output a newline character at the end.
        os << std::endl;
    }
}
