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
//Station.h

#pragma once

#ifndef SDDS_STATION_H
#define SDDS_STATION_H

#include <iostream>

namespace sdds{

    // Declaration of the Station class.
    class Station{
        // Private member variables for the Station class.
        int m_id{};
        std::string m_itemName{};
        std::string m_description{};
        size_t m_serialNumber{};
        size_t m_quantity{};

        // Static member variables shared among all instances of the class.
        static size_t m_widthField;
        static size_t m_idGenerator;

    public:
        // Default constructor for the Station class.
        Station(){};
        
        // Parameterized constructor that initializes the Station object with the given record.
        Station(const std::string& record);

        // Getter function to retrieve the item name.
        const std::string& getItemName() const;

        // Function to get the next serial number.
        size_t getNextSerialNumber();

        // Getter function to retrieve the quantity.
        size_t getQuantity() const;

        // Function to update the quantity.
        void updateQuantity();

        // Function to display information about the Station.
        void display(std::ostream& os, bool full) const;
    };

}

// End of the conditional compilation directive.
#endif
