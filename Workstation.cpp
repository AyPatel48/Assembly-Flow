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
//Workstation.cpp

#include <iostream>
#include "Workstation.h"

using namespace std;
namespace sdds {
    
    // Constructor: initializes a Workstation with a given name
    Workstation::Workstation(const std::string& str) : Station(str){}
    
    // Fill the current station's item (if orders are present)
    void Workstation::fill(std::ostream &os) {
        if (!m_orders.empty()) 
            m_orders.front().fillItem(*this, os);
    }

    // Set the next station in the assembly line
    void Workstation::setNextStation(Workstation *station) {
        m_pNextStation = station;
    }

    // Get the next station in the assembly line
    Workstation *Workstation::getNextStation() const {
        return m_pNextStation;
    }

    // Display the current station and its next station (if any)
    void Workstation::display(std::ostream &os) const {
        if (m_pNextStation)
            os << getItemName() << " --> " << m_pNextStation->getItemName() << endl;
        else
            os << getItemName() << " --> " << "End of Line" << endl;
    }

    // Add a new order to the current station
    Workstation &Workstation::operator+=(CustomerOrder &&newOrder) {
        m_orders.push_back(std::move(newOrder));
        return *this;
    }
    
    // Attempt to move an order to the next station in the assembly line
    bool Workstation::attemptToMoveOrder() {
        bool ok = false;
        if (m_orders.empty()){
            ok = false;
        }else{
            // Check if the order can be moved to the next station
            bool checkOrder = m_orders.front().isItemFilled(getItemName()) || this->getQuantity() == 0;

            if (!checkOrder){
                ok = false;
            }else{
                // Move the order to the next station or mark it as completed/incomplete
                if (!m_pNextStation){
                    if(m_orders.front().isOrderFilled()){
                        g_completed.push_back(std::move(m_orders.front()));
                    }else{
                        g_incomplete.push_back(std::move(m_orders.front()));
                    }
                }else{
                    m_pNextStation->operator+=(std::move(m_orders.front()));
                }
                
                m_orders.pop_front(); // Remove the processed order from the current station
                ok = true;
            }
        }
        return ok;
    }

    // Global deques to store pending, completed, and incomplete orders
    deque<CustomerOrder> g_pending;
    deque<CustomerOrder> g_completed;
    deque<CustomerOrder> g_incomplete;
}
