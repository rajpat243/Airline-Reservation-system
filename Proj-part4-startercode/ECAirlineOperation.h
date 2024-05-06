
#ifndef ECAirlineOperation_h
#define ECAirlineOperation_h

// put your code about airline operation here...

#include <vector>
#include <string>
#include "ECFlight.h"
using namespace std;


class ECAirport;
class ECAirlineOperation {
public:
    ECAirlineOperation();
    virtual ~ECAirlineOperation();
    
    void AddFlight(const string &source, const string &destination, double time, int passengers, double cost);

    vector<ECFlight*> GetAllFlights(const string& airportCode) const;
    
private:
    vector<ECFlight*> flights;
};

#endif
