
#include "ECAirlineOperation.h"
#include "ECFlightItinerary.h"
#include "ECAirlineFinancial.h"

#include <iostream>
#include <string>
#include "ECFlight.h"
#include <algorithm>
#include <vector>
using namespace std;

ECAirlineOperation::ECAirlineOperation() {}

ECAirlineOperation::~ECAirlineOperation() {}

void ECAirlineOperation::AddFlight(const std::string &source, const std::string &destination, double time, int passengers, double cost) {
    ECFlight* newflight = new ECFlight(source, destination, time, passengers);
    flights.push_back(newflight);
}

std::vector<ECFlight*> ECAirlineOperation::GetFlightsFrom(const std::string& airportCode) const {
    std::vector<ECFlight*> Flightfrom;
    for (ECFlight* flight : flights) {
        if (flight->GetSource() == airportCode) {
            Flightfrom.push_back(flight);
        }
    }
    return Flightfrom;
}

void ECAirlineOperation::Dump() const {

}






