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
//LineManager.h

#ifndef LINEMANAGER_H
#define LINEMANAGER_H

#include "Workstation.h"
#include <vector>
#include <string>

namespace sdds {
    // Class declaration for LineManager
    class LineManager {
        // Private members of LineManager class
        std::vector<Workstation*> m_activeLine;
        size_t m_cntCustomerOrder;
        Workstation* m_firstStation;

    public:
        // Constructor for LineManager class
        LineManager(const std::string& file, const std::vector<Workstation*>& stations);

        // Method to reorder stations based on distance from the first station
        void reorderStations();

        // Method to run the simulation for one iteration
        bool run(std::ostream& os);

        // Method to display the status of each station in the active line
        void display(std::ostream& os) const;
    };
} // namespace sdds

#endif // LINEMANAGER_H
