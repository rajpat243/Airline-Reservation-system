

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

void ECAirlineOperation::AddFlight(const string &source, const string &destination, double time, int passengers, double cost) {
    ECFlight* newflight = new ECFlight(source, destination, time, passengers);
    flights.push_back(newflight);
}

vector<ECFlight*> ECAirlineOperation::GetAllFlights(const string& airportCode) const {
    vector<ECFlight*> Flightfrom;
    for (ECFlight* flight : flights) {
        if (flight->GetSource() == airportCode) {
            Flightfrom.push_back(flight);
        }
    }
    return Flightfrom;
}





