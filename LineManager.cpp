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
//LineManager.cpp

#include "LineManager.h"
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <unordered_map>

using namespace std;
namespace sdds {
    // Constructor for LineManager class
    LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {
        // Open the input file
        fstream FILE(file);
        // Check if the file is successfully opened
        if (!FILE.is_open()) throw "File cannot be opened";

        string buffer;
        // Read each line from the file
        while (getline(FILE, buffer)) {
            // Find the delimiter '|' in the line
            size_t delimeter = buffer.find('|');
            // Extract the current station and the next station from the line
            string _station = buffer.substr(0, delimeter);
            string nextStation = (delimeter != std::string::npos) ? buffer.substr(delimeter + 1) : "";

            // Find the current station in the vector of stations
            auto stationNow = std::find_if(stations.begin(), stations.end(), [&](const Workstation* station) {
                return station->getItemName() == _station;
            });

            // Check if the current station is found
            if (stationNow == stations.end()) {
                cerr << "STATION NOT FOUND: " << _station << endl;
                continue;
            }

            // Add the current station to the active line
            m_activeLine.push_back(*stationNow);

            // If the next station is specified, find it in the vector of stations
            if (delimeter != std::string::npos) {
                auto stationAfter = std::find_if(stations.begin(), stations.end(), [&](const Workstation* station) {
                    return station->getItemName() == nextStation;
                });

                // If the next station is found, set it as the next station for the current station
                if (stationAfter != stations.end()) (*stationNow)->setNextStation(*stationAfter);
                else cerr << "NEXT STATION NOT FOUND: " << nextStation << endl;
            }
        }

        // Find the first station in the active line
        m_firstStation = *std::find_if(stations.begin(), stations.end(), [&](Workstation* station) {
            // Check if there is no other station pointing to it
            return std::none_of(stations.begin(), stations.end(), [&](Workstation* other) {
                return other != station && other->getNextStation() == station;
            });
        });

        // Check if the first station is found
        if (!m_firstStation) cerr << "FIRST STATION NOT FOUND" << endl;
        // Count the total number of customer orders in the pending list
        m_cntCustomerOrder = g_pending.size();
    }

    // Reorder the active line based on the distance from the first station
    void LineManager::reorderStations() {
        unordered_map<Workstation*, unsigned> totalDistance;
        // Calculate the distance of each station from the first station
        for_each(m_activeLine.begin(), m_activeLine.end(), [this, &totalDistance](Workstation* station) {
            unsigned distanceCounter = 0;
            // Iterate through the stations to find the distance
            for (Workstation* _station = m_firstStation; _station != nullptr; _station = _station->getNextStation(), ++distanceCounter) {
                if (_station == station) {
                    totalDistance[station] = distanceCounter;
                    break;
                }
            }
        });
        // Sort the active line based on the calculated distances
        sort(m_activeLine.begin(), m_activeLine.end(), [&totalDistance](Workstation* first, Workstation* second) { return totalDistance[first] < totalDistance[second]; });
    }

    // Run the simulation for one iteration
    bool LineManager::run(std::ostream& os) {
        static size_t count = 0;

        // Output the current iteration count
        os << "Line Manager Iteration: " << ++count << endl;

        // If there are pending orders, move the first order to the first station in the active line
        if (!g_pending.empty()) {
            *m_firstStation += std::move(g_pending.front());
            g_pending.pop_front();
        }

        // Fill each station in the active line
        for_each(m_activeLine.begin(), m_activeLine.end(), [&os](Workstation* station) { station->fill(os); });
        // Attempt to move orders through each station in the active line
        for_each(m_activeLine.begin(), m_activeLine.end(), [](Workstation* station) { station->attemptToMoveOrder(); });

        // Check if all customer orders are completed
        bool checkOrders = (g_completed.size() + g_incomplete.size()) == m_cntCustomerOrder;
        return checkOrders;
    }

    // Display the status of each station in the active line
    void LineManager::display(std::ostream& os) const {
        for_each(m_activeLine.begin(), m_activeLine.end(), [&](const Workstation* station) { station->display(os); });
    }
}
