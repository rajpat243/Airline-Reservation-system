//

#ifndef ECAirlineOperation_h
#define ECAirlineOperation_h

// put your code about airline operation here...

#include <vector>
#include <string>
#include "ECFlight.h"

class ECAirport;
class ECAirlineOperation {
public:
    ECAirlineOperation();
    virtual ~ECAirlineOperation();
    
    void AddFlight(const std::string &source, const std::string &destination, double time, int passengers, double cost);

    std::vector<ECFlight*> GetFlightsFrom(const std::string& airportCode) const;

    void Dump() const;
    
private:
    std::vector<ECFlight*> flights;
};

#endif
