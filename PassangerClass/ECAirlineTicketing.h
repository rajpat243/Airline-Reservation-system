
#ifndef ECAirlineTicketing_h
#define ECAirlineTicketing_h

// ****************************************************************************
// Airline ticketing: search for flights, issue tickets, etc

#include <vector>
#include <string>
#include "ECFlightItinerary.h"
#include "ECAirlineOperation.h"

class ECAirlineTicketing {
public:
    explicit ECAirlineTicketing(ECAirlineOperation* operation);

    void SearchForFlights(const std::string &source, const std::string &destination, std::vector<ECFlightItinerary> &itineraries);

private:
    ECAirlineOperation* operation; 
    void DepthFirstSearch(const std::string &currentAirport, const std::string &destination, std::vector<ECFlightItinerary> &itineraries, std::vector<ECFlight*> &currentPath, double lastArrivalTime) const;

};
#endif /* ECAirlineTicketing_h */