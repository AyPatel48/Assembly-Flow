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
//CustomerOrder.cpp

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include "CustomerOrder.h"

namespace sdds{

    // Static member initialization
    size_t CustomerOrder::m_widthField = 0u;

    // Default constructor
    CustomerOrder::CustomerOrder()
    {
        setEmpty();
    }

    // Constructor that takes a string as input
    CustomerOrder::CustomerOrder(std::string & str)
    {
        size_t pos = 0;
        bool more = false;

        try
        {
            // Extracting customer name and product
            m_name = extractToken(str, pos, more);
            m_product = extractToken(str, pos, more);

            // Counting the number of items in the order
            char delimiter = getDelimiter();
            m_cntItem = std::count(str.begin(), str.end(), delimiter) - 1;

            // Allocating memory for the array of Item pointers
            if(m_cntItem > 0){
                m_lstItem = new Item*[m_cntItem];

                // Populating the array with Item objects
                for(auto i = 0u; i < m_cntItem; i++){
                    m_lstItem[i] = new Item(std::move(trimSpace(extractToken(str, pos, more))));
                }
            }

            // Updating the widthField static member
            m_widthField = std::max(getFieldWidth(), m_widthField);
        }
        catch(const std::exception& e)
        {
            // Handling exceptions
            std::cerr << e.what() << '\n';
        }        
    }

    // Copy constructor (disallowed)
    CustomerOrder::CustomerOrder(const CustomerOrder &)
    {
        throw std::runtime_error("ERROR! Copies not allowed.");
    }

    // Move constructor
    CustomerOrder::CustomerOrder(CustomerOrder && order) noexcept
    {
        *this = std::move(order);
    }

    // Move assignment operator
    CustomerOrder &CustomerOrder::operator=(CustomerOrder && order) noexcept
    {
        if(this != &order){
            // Deleting existing resources if any
            if(m_lstItem){
                for(auto i = 0u; i < m_cntItem; i++){
                    delete m_lstItem[i];
                }
                setEmpty();
            }

            // Moving data from the source to the current object
            m_name = order.m_name;
            m_product = order.m_product;
            m_cntItem = order.m_cntItem;
            m_lstItem = order.m_lstItem;

            // Clearing the source object
            order.m_name = "";
            order.m_product = "";
            order.m_cntItem = 0u;
            order.m_lstItem = nullptr;

            // Deleting resources from the source object if any
            if(order.m_lstItem){
                for(auto i = 0u; i < m_cntItem; i++){
                    delete order.m_lstItem[i];
                }
                order.setEmpty();
            }
        }
        return *this;
    }

    // Destructor
    CustomerOrder::~CustomerOrder()
    {
        // Deleting dynamically allocated memory
        if(m_lstItem){
            for(auto i = 0u; i < m_cntItem; i++){
                delete m_lstItem[i];
            }
            setEmpty();
        }
    }

    // Check if the entire order is filled
    bool CustomerOrder::isOrderFilled() const
    {
        int count = 0;
		for (auto i = 0u; i < m_cntItem; ++i) {
			if (m_lstItem[i]->m_isFilled) {
				count++;
			}
		}
		return static_cast<int>(m_cntItem) == count;
    }

    // Check if a specific item is filled
    bool CustomerOrder::isItemFilled(const std::string &itemName) const
    {
        bool filled = true;
        for(auto i = 0u; i < m_cntItem; ++i){
            // Checking if the item with the given name is filled
            if(m_lstItem[i]->m_itemName == itemName){
                if(!m_lstItem[i]->m_isFilled){
                    filled = false;
                }
            }
        }
        return filled;
    }

    // Fill an item in the order using a station
    void CustomerOrder::fillItem(Station &station, std::ostream& os)
    {
        bool filled = true;

        // Iterating through each item in the order
        for(auto i = 0u; i < m_cntItem && filled; ++i){
            // Checking if the item matches the station
            if(m_lstItem[i]->m_itemName == station.getItemName() && !m_lstItem[i]->m_isFilled){
                // Checking if the station has enough quantity
                if(station.getQuantity() >= 1){
                    station.updateQuantity();
                    m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                    
                    m_lstItem[i]->m_isFilled = true;
                    filled = false;

                    // Outputting information about the filled item
                    os << std::setw(10) << "Filled" << " " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]";
                }else{
                    // Outputting information about unable to fill the item
                    os << std::setw(18) << "Unable to fill" << " " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]";
                }
                os << std::endl;
            }
        }
    }

    // Display the customer order
    void CustomerOrder::display(std::ostream &os) const
    {
        // Outputting customer name and product
        os << this->m_name << " - " << m_product << std::endl;

        // Outputting information about each item in the order
        for(auto i = 0u; i < m_cntItem; i++){
            os << "[" << std::setw(6) << std::setfill('0') << m_lstItem[i]->m_serialNumber << "] " << std::setw(m_widthField) << std::left << std::setfill(' ') << m_lstItem[i]->m_itemName << std::right << " - " << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << std::endl; 
        }
    }

    // Helper function to set the object to an empty state
    void CustomerOrder::setEmpty(){
        delete[] m_lstItem;
        m_lstItem = nullptr;
    }

}  // namespace sdds
