
#include "ECFlightItinerary.h"
#include "ECFlight.h"
#include <iostream>
#include <string>
#include <set>
#include <numeric> 
#include <sstream>
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
    // cout << "Itinerary Details:" << endl;
    // for (int i = 0; i < GetNumSegments(); ++i) {
    //     ECFlight* segment = GetSegment(i);
    //     if (segment) {
    //         cout << "Segment " << i + 1 << ":" << endl;
    //         cout << "  Source: " << segment->GetSource() << endl;
    //         cout << "  Destination: " << segment->GetDest() << endl;
    //         cout << "  Departure: " << segment->GetDepartureTime() << endl;
    //         cout << "  Arrival: " << segment->GetArrivalTime() << endl;
    //     }
    // }
    // cout << "Total price:$" << GetPrice() << endl;
    // cout << "Total flight Time: " << GetFlightTime() << " hours" << endl;
}

std::string ECFlightItinerary::GetDescription() const {
    std::stringstream desc;
    if (!segment.empty()) {
        // Start with the origin of the first segment and the destination of the last segment
       desc << segment.front().GetSource() << " to " << segment.back().GetDest();
       //desc << GetPrice() << " to " << GetFlightTime();
       //desc << "flights found";

        // Add total flight time and total price
        //desc << " | Time: " << GetFlightTime() << " hrs";
        //desc << " | Price: $" << GetPrice();
    } else {
        desc << "No flights available";
    }
    return desc.str();
}

