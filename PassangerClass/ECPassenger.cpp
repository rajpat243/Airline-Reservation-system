//


#include "ECPassenger.h"
#include "ECAirlineTicketing.h"
#include "ECAirlineFinancial.h"
#include "ECFlight.h"

#include <vector>
#include <iostream>
using namespace std;

ECPassenger::ECPassenger(const std::string &srcAirportIn, const std::string &destAirportIn)
    : srcAirport(srcAirportIn), destAirport(destAirportIn), status(EC_PASSENGER_UNBOOKED) {}

bool ECPassenger::Book(ECAirlineTicketing &airlineTicketing) {

    // bool booked = airlineTicketing.BookTicket(srcAirport, destAirport, itin);
    // if (booked) {
    //     status = EC_PASSENGER_BOOKED;
    //     return true;
    // } else {
    //     return false;
    // }
}

void ECPassenger::Dump() const {
    std::cout << "Passenger Info:" << std::endl;
    std::cout << "Source Airport: " << srcAirport << std::endl;
    std::cout << "Destination Airport: " << destAirport << std::endl;
    std::cout << "Status: " << (status == EC_PASSENGER_UNBOOKED ? "Unbooked" : "Booked") << std::endl;
    std::cout << "Itinerary Details:" << std::endl;
    itin.Dump(); // Assuming ECFlightItinerary has a Dump method for outputting its details
}

ECPassengerBudget::ECPassengerBudget(const std::string &srcAirportIn, const std::string &destAirportIn, double budgetIn)
    : ECPassenger(srcAirportIn, destAirportIn), maxBudget(budgetIn) {}

bool ECPassengerBudget::Book(ECAirlineTicketing &airlineTicketing) {

    // if (maxBudget >= airlineTicketing.CalculatePrice(srcAirport, destAirport)) {
    //     return ECPassenger::Book(airlineTicketing);
    // } else {
    //     return false;
    // }
}

ECPassengerBusiness::ECPassengerBusiness(const std::string &srcAirportIn, const std::string &destAirportIn, double tmArrivalLatestIn)
    : ECPassenger(srcAirportIn, destAirportIn), latestArrivalTime(tmArrivalLatestIn) {}

bool ECPassengerBusiness::Book(ECAirlineTicketing &airlineTicketing) {

    if (itin.GetArrivalTime() <= latestArrivalTime) {
        return ECPassenger::Book(airlineTicketing);
    } else {
        return false;
    }
}

ECPassengerComfort::ECPassengerComfort(const std::string &srcAirportIn, const std::string &destAirportIn, double tmEarliestDepartIn, double maxFlightTimeIn, int maxSegmentsIn)
    : ECPassenger(srcAirportIn, destAirportIn), earliestDepartTime(tmEarliestDepartIn), maxFlightTime(maxFlightTimeIn), maxSegments(maxSegmentsIn) {}

bool ECPassengerComfort::Book(ECAirlineTicketing &airlineTicketing) {

    if (itin.GetDepartTime() >= earliestDepartTime && itin.GetFlightTime() <= maxFlightTime && itin.GetNumSegments() <= maxSegments) {
        return ECPassenger::Book(airlineTicketing);
    } else {
        return false;
    }
}
