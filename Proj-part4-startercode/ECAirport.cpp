

#include "ECAirport.h"
#include <stdexcept>
#include <utility>

using namespace std;

// ****************************************************************************
// Implementations for ECAirport

ECAirport::ECAirport() : name(""), code(""), operating(false) {
    
}

ECAirport::ECAirport(const string &nameAP, const string &codeIATA)
    : name(nameAP), code(codeIATA), operating(true) {}

ECAirport::ECAirport(const ECAirport &rhs) : name(rhs.name), code(rhs.code), operating(rhs.operating) {}

string ECAirport::GetName() const {return name;}

string ECAirport::GetCode() const {return code;}

bool ECAirport::IsOperating() {return operating;}

void ECAirport::SetOperating(bool f) {operating = f;}

// ****************************************************************************
// Implementations for ECAirportInfo

void ECAirportInfo::CreateAirport(const string &name, const string &code) {
    if (airports.find(code) == airports.end()) {
        airports[code] = ECAirport(name, code);
    }
}

ECAirport &ECAirportInfo::GetAirport(const string &code) const {
    auto it = airports.find(code);
    return const_cast<ECAirport&>(it->second); 
}

void ECAirportInfo::SetDistanceBtw(const string &ap1Code, const string &ap2Code, int dist) {
    distances[std::make_pair(ap1Code, ap2Code)] = dist;
    distances[std::make_pair(ap2Code, ap1Code)] = dist; 
}

int ECAirportInfo::GetDistanceBtw(const string &ap1Code, const string &ap2Code) const {
    auto it = distances.find(make_pair(ap1Code, ap2Code));
    return it->second;
}

double ECAirportInfo::CalculateFlightTime(const string &ap1Code, const string &ap2Code) const {
    int distance = GetDistanceBtw(ap1Code, ap2Code);
    return static_cast<double>(distance) / 500.0; // Assuming 500 from instsruction
}
