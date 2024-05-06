

#ifndef ECFlight_h
#define ECFlight_h

#include <string>


// ****************************************************************************
// Flight: service between two airports at a specific time;

class ECFlight 
{
public:
    ECFlight(const std::string &srcIn, const std::string &destIn, double tmDepartIn, int maxPassengersIn);
    virtual ~ECFlight();
    friend bool operator==(const ECFlight& lhs, const ECFlight& rhs);
    friend bool operator!=(const ECFlight& lhs, const ECFlight& rhs);
    
    // Get departure time
    double GetDepartureTime() const;
    
    // Get arrival time
    double GetArrivalTime() const;
    
    // Set max passenger for this flight
    void SetMaxNumPassengers(int m);
    
    // Get src airport code
    std::string GetSource() const;
    
    // Get destination code
    std::string GetDest() const;

    // more to add...    
    int GetMaxNumPassengers() const;

private:
    // your code
    std::string src;  // Source airport IATA code
    std::string dest;  // Destination airport IATA code
    double tmDepart;  // Departure time
    int maxPassengers;  // Maximum number of passengers
};

#endif /* ECFlight_h */
