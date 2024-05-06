
#include "ECAirlineSimulator.h"
#include "ECAirlineOperation.h"
#include "ECAirlineTicketing.h"
#include "ECAirlineFinancial.h"
#include "ECFlightItinerary.h"
#include "ECAirport.h"
#include "ECFlight.h"

#include <iostream>
#include <vector>
#include <string>
using namespace std;

ECAirlineSimulator::ECAirlineSimulator() {
    pAirlineOp = new ECAirlineOperation();
    pAirlineFin = new ECAirlineFinancial();
    pAirlineTicket = new ECAirlineTicketing(pAirlineOp);
}

ECAirlineSimulator::~ECAirlineSimulator() {
    delete pAirlineOp;
    delete pAirlineFin;
    delete pAirlineTicket;
}

// *****************************************************
// Configuration
    
void ECAirlineSimulator::AddAirport(const std::string &name, const std::string &code) {
    ECAirportInfo &airportInfo = ECAirportInfo::GetInstance();
    airportInfo.CreateAirport(name, code);
}

void ECAirlineSimulator::AddFlight(const std::string &srcAirport, const std::string &destAirport, double tmDepart, int maxPassengers, double costOperate) {
    pAirlineOp->AddFlight(srcAirport, destAirport, tmDepart, maxPassengers, costOperate);
}

void ECAirlineSimulator::SetDistBtwAirports(const std::string &srcAirport, const std::string &destAirport, int dist) {
    ECAirportInfo &airportInfo = ECAirportInfo::GetInstance();


    airportInfo.SetDistanceBtw(srcAirport, destAirport, dist);
    airportInfo.SetDistanceBtw(destAirport, srcAirport, dist);
}

void ECAirlineSimulator::DoneFlightAdding() {
    flightAddingDone = true;
}

// *****************************************************
// Flight search

void ECAirlineSimulator::SearchForFlights(const std::string &src, const std::string &dest, std::vector<ECFlightItinerary> &listItineraries) const {
    pAirlineTicket->SearchForFlights(src, dest, listItineraries);
    if (listItineraries.empty()) {
    } else {
        for (const auto& itinerary : listItineraries) {
            itinerary.Dump(); 
        }
    }
}


void ECAirlineSimulator::PreferEarlyArrival() {

}

void ECAirlineSimulator::PreferLowPrice() {

}

void ECAirlineSimulator::PreferShortTime() {
    
}
