
#ifndef ECAirport_h
#define ECAirport_h

#include <string>
#include <set>
#include <map>


// ****************************************************************************
// Airport: start/end point of a flight

class ECAirport 
{
public:
    // by default, airport is operating (except in default constructor)
    ECAirport(); 
    ECAirport(const std::string &nameAP, const std::string &codeIATA);
    ECAirport(const ECAirport &rhs);
    
    // Get the name of the airport
    std::string GetName() const;
    
    // Get IATA code
    std::string GetCode() const;
    
    // Operating status: is it operating normally?
    bool IsOperating();
    
    // Set operating status
    void SetOperating(bool f);
    
private:
    // your ocde
    std::string name; // Airport name
    std::string code; // IATA code
    bool operating; // Operating status
};

// ****************************************************************************
// Airport info: access airport information
// Use singleton pattern

class ECAirportInfo
{
public:
    
    // Create a new airport in the system
    void CreateAirport(const std::string &name, const std::string &code);
    
    // Get airport by code
    // Throw exception (std::string) if there is no airport with the code
    ECAirport &GetAirport(const std::string &code) const;

    // Set distance (in miles) between airports
    void SetDistanceBtw(const std::string &ap1Code, const std::string &ap2Code, int dist);

    // more to add...
    int GetDistanceBtw(const std::string &ap1Code, const std::string &ap2Code) const;
    double CalculateFlightTime(const std::string &ap1Code, const std::string &ap2Code) const;

    static ECAirportInfo& GetInstance()
    {
        static ECAirportInfo instance;
        return instance;
    }

    ECAirportInfo(const ECAirportInfo&) = delete;
    void operator=(const ECAirportInfo&) = delete;
    
private:
   // your code 
    ECAirportInfo() {}  //private for Singleton
    std::map<std::string, ECAirport> airports; // Maps IATA code to ECAirport
    std::map<std::pair<std::string, std::string>, int> distances; // Maps pairs of IATA codes to distances
};

#endif /* ECAirport_h */
