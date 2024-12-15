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
//CustomerOrder.h

#ifndef SDDS_CUSTOMER_ORDER_H
#define SDDS_CUSTOMER_ORDER_H

#include <iostream>
#include "Station.h"
#include "Utilities.h"
#include "Station.h"

namespace sdds{

    class CustomerOrder: public Utilities{
        // Item structure to represent items in the order
        struct Item{
            std::string m_itemName;
            size_t m_serialNumber{0};
            bool m_isFilled{false};

            // Constructor to initialize Item with a name
            Item(const std::string& src) : m_itemName(src) {};
        };

        // Private member variables
        std::string m_name{""};
        std::string m_product{""};
        size_t m_cntItem{0};
        Item** m_lstItem{};

        // Static member variable to store the maximum field width
        static size_t m_widthField;

    public:
        // Default constructor
        CustomerOrder();
        
        // Constructor that takes a string as input
        CustomerOrder(std::string&);

        // Copy constructor (throws exception)
        CustomerOrder(const CustomerOrder&);

        // Copy assignment operator (disallowed)
        CustomerOrder& operator=(const CustomerOrder&) = delete;

        // Move constructor
        CustomerOrder(CustomerOrder&&) noexcept;

        // Move assignment operator
        CustomerOrder& operator=(CustomerOrder&&) noexcept;

        // Destructor
        ~CustomerOrder();

        // Check if the entire order is filled
        bool isOrderFilled()const;

        // Check if a specific item is filled
        bool isItemFilled(const std::string & itemName)const;

        // Fill an item in the order using a station
        void fillItem(Station&, std::ostream&);

        // Display the customer order
        void display(std::ostream& os)const;

        // Helper function to set the object to an empty state
        void setEmpty();
    };

}

#endif
