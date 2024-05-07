//

#include "ECFlight.h"
#include "ECAirport.h"

#include <iostream>
using namespace std;

// Constructor
ECFlight::ECFlight(const std::string &srcIn, const std::string &destIn, double tmDepartIn, int maxPassengersIn)
    : src(srcIn), dest(destIn), tmDepart(tmDepartIn), maxPassengers(maxPassengersIn)
{}

//destructor
ECFlight::~ECFlight() {}

// Get the departure time of the flight
double ECFlight::GetDepartureTime() const
{
    return tmDepart;
}

// Get the arrival time of the flight
double ECFlight::GetArrivalTime() const
{
    // Assuming we can calculate the flight time based on the distance between airports
    ECAirportInfo& airportInfo = ECAirportInfo::GetInstance();
    double flightTime = airportInfo.CalculateFlightTime(src, dest);
    return tmDepart + flightTime;
}

// Set the maximum number of passengers for this flight
void ECFlight::SetMaxNumPassengers(int m)
{
    maxPassengers = m;
}

// Get the source airport code
std::string ECFlight::GetSource() const
{
    return src;
}

// Get the destination airport code
std::string ECFlight::GetDest() const
{
    return dest;
}

// Get the maximum number of passengers allowed on this flight
int ECFlight::GetMaxNumPassengers() const
{
    return maxPassengers;
}

bool operator==(const ECFlight& lhs, const ECFlight& rhs) {
    return lhs.GetSource() == rhs.GetSource() &&
           lhs.GetDest() == rhs.GetDest() &&
           lhs.GetDepartureTime() == rhs.GetDepartureTime();
}

bool operator!=(const ECFlight& lhs, const ECFlight& rhs) {
    return !(lhs == rhs);
}
