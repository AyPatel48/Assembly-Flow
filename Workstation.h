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
//Workstation.h

#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H

#include <deque>
#include "CustomerOrder.h"
#include "Station.h"

namespace sdds{

    // External deques to store pending, completed, and incomplete orders
    extern std::deque<CustomerOrder> g_pending;
    extern std::deque<CustomerOrder> g_completed;
    extern std::deque<CustomerOrder> g_incomplete;

    // Workstation class definition, inheriting from Station
    class Workstation : public Station{
        std::deque<CustomerOrder> m_orders; // Queue of orders at the workstation
        Workstation* m_pNextStation = nullptr; // Pointer to the next station in the assembly line
    public:
        // Rule of 5: no copying and moving allowed
        Workstation(const Workstation&) = delete;
        Workstation(Workstation&&) = delete;
        Workstation& operator=(const Workstation&) = delete;
        Workstation& operator=(Workstation&&) = delete;    

        // Custom constructor for Workstation
        Workstation(const std::string&);

        // Member functions for filling items, moving orders, setting/getting next station, and displaying information
        void fill(std::ostream& os);
        bool attemptToMoveOrder();
        void setNextStation(Workstation* station = nullptr);
        Workstation* getNextStation() const;
        void display(std::ostream& os) const;

        // Operator overload for adding a new order to the workstation
        Workstation& operator+=(CustomerOrder&& newOrder);   
    };
}
#endif
