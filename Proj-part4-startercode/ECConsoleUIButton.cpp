
#include "ECConsoleUIButton.h"
#include "ECFlightItinerary.h"
#include "ECAirlineTicketing.h"
#include "ECConsoleUIListBox.h"
#include "map"
#include <vector>
#include <string>

using namespace std;

//*****************************************************************************
// Console UI button: 

// specifiy the portion of the view for this list box
// ECConsoleUIButton :: ECConsoleUIButton(int xUL, int yUL, int xLR, int yLR, const std::string &strButIn ) : ECConsoleUIItem(xUL, yUL, xLR, yLR), strButton(strButIn)
// {
// }

// Get displayed text at a specific row
// Text is relative to the item portion (i.e., relative to (xLR, yLR))
std::string ECConsoleUIButton :: GetTextAtRow(int r) const
{
    // there is only one line
    std::string str;
    int rconv = r - GetYUL();

    if( rconv <0 || /*rconv >= 1 ||*/ rconv >= GetHeight() )
    {
        return str;
    }

    // add a row of '----' right above/below
    if( rconv == 0 || rconv == GetHeight()-1 )
    {
        str += '-';
        for( int i=1 ; i<GetWidth() - 1; ++i)
        {
            str += '-';
        }
        str += '-';
    }
    else
    {
        // begin with a '|'
        //str += '|';

        // align to the center
        if( strButton.size() < GetWidth())
        {
            str += ' ';
            for(int i=1; i < (GetWidth()- strButton.size())/2; ++i )
            {
                str += ' ';
            }
        }

        str += strButton;
        for(int i=1; i < (GetWidth()- strButton.size())/2; ++i )
            {
                str += ' ';
            }
            str += ' ';

        // end with a '|'
        //str += '|';
    }

    // ensure the str is not too long
    str = str.substr(0, GetWidth());
    return str;
}

// Get highlighted part (if any); return the row with highlight
// if one, return -1; also store the highlightd portion (yLeft, yRight) of this row
// Assume: at most a single row with highlighted part
int ECConsoleUIButton :: GetHighlightPosition(int &xLeft, int &xRight) const
{
    return -1;
}

// Handle enter key
// void ECConsoleUIButton::HdlKeyEnter() {
//     if (originBox && destBox && flightsBox && ticketing) {
//         string source = originBox->GetTextAtRow(originBox->GetChoice());
//         string destination = destBox->GetTextAtRow(destBox->GetChoice());
//         vector<ECFlightItinerary> itineraries;
//         ticketing->SearchForFlights("ORD", "SFO", itineraries);

//         flightsBox->ClearChoices();
//         for (const auto&itinerary : itineraries) {
//             flightsBox->AddChoice(itinerary.GetDescription()); 
//         }
//         flightsBox->Choose(0);  
//     }
// }

void ECConsoleUIButton::HdlKeyEnter() {
    if (originBox && destBox && flightsBox && ticketing) {
        string source = originBox->GetSelectedText();
        string destination = destBox->GetSelectedText();

        vector<ECFlightItinerary> itineraries;
        ticketing->SearchForFlights(source, destination, itineraries);

        flightsBox->ClearChoices();
        for (const auto& itinerary : itineraries) {
            flightsBox->AddChoice(itinerary.GetDescription());
        }
        if (!itineraries.empty()) {
            flightsBox->Choose(0);  // Select the first flight in the list
        }
    }
}


