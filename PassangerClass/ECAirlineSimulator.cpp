
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
#include <algorithm>
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
            std::sort(listItineraries.begin(), listItineraries.end(), [this](const ECFlightItinerary &a, const ECFlightItinerary &b) {
            for (auto &pref : preferences) {
                if (pref(a, b)) return true;
                if (pref(b, a)) return false;
            }
            return false; 
        });
        for (const auto& itinerary : listItineraries) {
            itinerary.Dump(); 
        }
    }
}

void ECAirlineSimulator::PreferLowPrice() {
    preferences.push_back([](const ECFlightItinerary &a, const ECFlightItinerary &b) {
        return a.GetPrice() < b.GetPrice();
    });
}

void ECAirlineSimulator::PreferShortTime() {
    preferences.push_back([](const ECFlightItinerary &a, const ECFlightItinerary &b) {
        return a.GetFlightTime() < b.GetFlightTime();
    });
}

void ECAirlineSimulator::PreferSmallestSegments() {
    preferences.push_back([](const ECFlightItinerary &a, const ECFlightItinerary &b) {
        return a.GetNumSegments() < b.GetNumSegments();
    });
}

void ECAirlineSimulator::PreferEarlyArrival() {
    preferences.push_back([](const ECFlightItinerary &a, const ECFlightItinerary &b) {
        return a.GetArrivalTime() < b.GetArrivalTime();
    });
}

void ECAirlineSimulator::ClearPreference() {
    preferences.clear();
}

void ECAirlineSimulator::Book() {
}

void ECAirlineSimulator::AddPassengerBudget(const std::string &src, const std::string &dest, int a) {
}

void ECAirlineSimulator::AddPassengerBusiness(const std::string &src, const std::string &dest, double a) {
}

void ECAirlineSimulator::AddPassengerComfort(const std::string &src, const std::string &dest, double a, double b, int c) {
}
void ECAirlineSimulator::GetPassengerItineraries(std::vector <ECFlightItinerary> &passengerItineraries) {
}


