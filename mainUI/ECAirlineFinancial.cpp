
#include "ECAirlineFinancial.h"
#include "ECAirlineOperation.h"
#include "ECFlightItinerary.h"

#include <string>
#include <iostream>
using namespace std;

ECAirlineFinancial::ECAirlineFinancial() {}
ECAirlineFinancial::~ECAirlineFinancial() {}

double ECAirlineFinancial::CalculatePrice(const ECFlightItinerary &itinerary) const {
    double totalFlightTime = itinerary.GetFlightTime(); 
    double price = totalFlightTime * STANDARD_PRICE;
    return price;
}
