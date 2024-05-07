

#include "ECFlightItinerary.h"
#include "ECFlight.h"
#include <iostream>
#include <string>
#include <set>
#include <numeric> // For std::accumulate
using namespace std;

ECFlightItinerary::ECFlightItinerary() : estimatedPrice(0.0) {}

void ECFlightItinerary::AddSegment(const ECFlight &flight) {
    segment.push_back(flight);
}

int ECFlightItinerary::GetNumSegments() const {
    return segment.size();
}

ECFlight *ECFlightItinerary::GetSegment(int segIndex) const {
    if (segIndex < 0 || segIndex >= static_cast<int>(segment.size()))
    return nullptr;
    return const_cast<ECFlight*>(&segment[segIndex]);
}
double ECFlightItinerary::GetFlightTime() const {
    return accumulate(segment.begin(), segment.end(), 0.0,[](double total, const ECFlight& flight) {
    return total + flight.GetArrivalTime() - flight.GetDepartureTime();
    });
}

double ECFlightItinerary::GetDepartTime() const {
    if (!segment.empty()) {
        return segment.front().GetDepartureTime();
    }
    return 0.0;
}

double ECFlightItinerary::GetArrivalTime() const {
    if (!segment.empty()) {
        return segment.back().GetArrivalTime();
    }
    return 0.0;
}

double ECFlightItinerary::GetPrice() const {
    return GetFlightTime() * 120.0;
}

void ECFlightItinerary::SetPrice(double price) {
    estimatedPrice = price;
}

bool operator==(const ECFlightItinerary& lhs, const ECFlightItinerary& rhs) {
    if (lhs.GetNumSegments() != rhs.GetNumSegments()) {
        return false;
    }
    for (int i = 0; i < lhs.GetNumSegments(); ++i) {
        if (*lhs.GetSegment(i) != *rhs.GetSegment(i)) {
            return false;
        }
    }return true;
}

void ECFlightItinerary::Dump() const {

}
