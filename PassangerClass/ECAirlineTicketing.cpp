
#include "ECAirlineTicketing.h"
#include "ECAirlineOperation.h"
#include "ECFlightItinerary.h"
#include "ECAirlineFinancial.h"
#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <string>
using namespace std;

ECAirlineTicketing::ECAirlineTicketing(ECAirlineOperation* op) : operation(op) {}

void ECAirlineTicketing::SearchForFlights(const std::string &source, const std::string &destination, vector<ECFlightItinerary> &itineraries) {
    vector<ECFlight*> currentPath;
    DepthFirstSearch(source, destination, itineraries, currentPath, 0.0);
}

void ECAirlineTicketing::DepthFirstSearch(const std::string &currentAirport, const std::string &destination, vector<ECFlightItinerary> &itineraries, vector<ECFlight*> &currentPath, double lastArrivalTime) const {
    if (any_of(currentPath.begin(), currentPath.end(), [&](ECFlight* flight){
        return flight->GetSource() == currentAirport;
    })) {
        return;
    }

    if (currentAirport == destination) {
        ECFlightItinerary newItinerary;
        for_each(currentPath.begin(), currentPath.end(), [&](ECFlight* flight){
            newItinerary.AddSegment(*flight);
        });

        ECAirlineFinancial financial;
        double price = financial.CalculatePrice(newItinerary);
        newItinerary.SetPrice(price);

        if (find_if(itineraries.begin(), itineraries.end(), [&](const ECFlightItinerary &existingItinerary){
            return existingItinerary == newItinerary;
        }) == itineraries.end()) {
            itineraries.push_back(newItinerary);
        }
        return;
    }

    const vector<ECFlight*> departingFlights = operation->GetFlightsFrom(currentAirport);
    for_each(departingFlights.begin(), departingFlights.end(), [&](ECFlight* flight){
        if (flight->GetDepartureTime() >= lastArrivalTime) {
            currentPath.push_back(flight);
            DepthFirstSearch(flight->GetDest(), destination, itineraries, currentPath, flight->GetArrivalTime());
            currentPath.pop_back();
        }
    });
}
