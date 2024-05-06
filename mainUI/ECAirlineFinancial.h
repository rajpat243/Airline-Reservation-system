
#ifndef ECAirlineFinancial_h
#define ECAirlineFinancial_h

// ****************************************************************************
// Airline finanical: budgetting, pricing and money bookkeeping

#include "ECFlightItinerary.h"

class ECAirlineFinancial {
public:
    ECAirlineFinancial();
    virtual ~ECAirlineFinancial();

    
    double CalculatePrice(const ECFlightItinerary &itinerary) const;

private:
    static constexpr double STANDARD_PRICE = 120.0;  // Constant factor for pricing
};

#endif
