
#ifndef ECFlightItinerary_h
#define ECFlightItinerary_h

#include <vector>
#include <string>

class ECFlight;
class ECAirlineFinancial;

// ****************************************************************************
// Flight itineary: consisting segments of flights so to go from one airport to another airport

class ECFlightItinerary
{
public:
    ECFlightItinerary();
    
    // access/edit segments
    // Return the number of segments of the itineary
    int GetNumSegments() const;
    
    // Return a segment
    ECFlight *GetSegment(int segIndex) const;
    
    // Get flight time: from departure to arrival
    double GetFlightTime() const;
    
    // Get segment time: add the time of all segments (not needed according to piazza)
    //double GetTimeAllSegments() const;
    
    // Get departure time
    double GetDepartTime() const;
    
    // Get arrival time
    double GetArrivalTime() const;
    
    // Price 
    double GetPrice() const;

    //added methods

    // Set estimated price of the itinerary
    void SetPrice(double price);
    // Add a flight segment to the itinerary
    void AddSegment(const ECFlight &flight);

    void Dump() const;
    
    friend bool operator==(const ECFlightItinerary& lhs, const ECFlightItinerary& rhs);
    
private:
    // your code
    std::vector<ECFlight> segment; // Vector of flights making up the itinerary
    double estimatedPrice; // Estimated price for the whole itinerary
};

#endif /* ECFlightItinerary_h */
