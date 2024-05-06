// Test code for console UI
#include "ECTextViewImp.h"
#include "ECConsoleUIView.h"
#include "ECConsoleUITextLabel.h"
#include "ECConsoleUIListBox.h"
#include "ECConsoleUITextField.h"
#include "ECConsoleUIButton.h"

#include "ECAirport.h"
#include "ECFlight.h"
#include "ECAirlineOperation.h"
#include "ECAirlineTicketing.h"
#include "ECAirlineFinancial.h"
#include "ECFlightItinerary.h"
#include "ECAirlineSimulator.h"
#include <string>
#include <cmath>

#include <iostream>
#include <fstream>
#include <sstream>
#include <set>

using namespace  std;

void ReadData(const string& filename, set<string>& airports, ECAirlineOperation& airlineOps) {
    ECAirlineSimulator sim;
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        if (line.empty() || line[0] == '#') continue; 

        stringstream ss(line);
        int type;
        ss >> type;
        if (type == 1) {
            string code, desc;
            ss >> code;
            getline(ss, desc); 
            airports.insert(code); 
        } else if (type == 3) {
            string orig, dest;
            double time;
            int length;
            double cost;
            ss >> orig >> dest >> time >> length >> cost;
            airlineOps.AddFlight(orig, dest, time, length, cost);
            sim.DoneFlightAdding();
        }
    }
    file.close();
}

// construct a simple UI
static void Test1(ECConsoleUIView &viewTest, const set<string>& airports, ECAirlineOperation& airlineOps, ECAirlineTicketing& airlineTicketingSystem)
{

    ECConsoleUITextLabel *title = new ECConsoleUITextLabel(10, 1, "Raj's Airline Flight Reservation System");
    title->SetHighlight(true);
    viewTest.AddUIItem(title);

    string horizBar;
    for(int i=0; i<viewTest.GetColNumInView(); ++i)
    {
        horizBar += '-';
    }

    ECConsoleUITextLabel *pl4 = new ECConsoleUITextLabel(0, 0, horizBar);
    viewTest.AddUIItem(pl4);
    ECConsoleUITextLabel *pl5 = new ECConsoleUITextLabel(0, viewTest.GetRowNumInView()-1, horizBar);
    viewTest.AddUIItem(pl5);

    ECConsoleUITextLabel *originLabel = new ECConsoleUITextLabel(10, 4, "Origination");
    viewTest.AddUIItem(originLabel);
    ECConsoleUIListBox *originBox = new ECConsoleUIListBox(10, 6, 25, 8);
    for (const string& code : airports) {
        originBox->AddChoice(code);
    }
    originBox->Choose(0); 
    viewTest.AddUIItem(originBox);

    ECConsoleUITextLabel *destLabel = new ECConsoleUITextLabel(30, 4, "Destination");
    viewTest.AddUIItem(destLabel);
    ECConsoleUIListBox *destBox = new ECConsoleUIListBox(30, 6, 55, 8);
    for (const string& code : airports) {
        destBox->AddChoice(code);
    }
    destBox->Choose(0); 
    viewTest.AddUIItem(destBox);

    ECConsoleUITextLabel *flightsLabel = new ECConsoleUITextLabel(19, 15, "Flights");
    viewTest.AddUIItem(flightsLabel);
    ECConsoleUIListBox *flightsBox = new ECConsoleUIListBox(13, 17, 60, 20);
    flightsBox->AddChoice("Flight here");
    flightsBox->Choose(0); 

    ECConsoleUITextLabel *pl9 = new ECConsoleUITextLabel(13, 11, "---------------------");
    viewTest.AddUIItem(pl9);
    ECConsoleUIButton *searchButton = new ECConsoleUIButton(13, 12, 30, 12, "Search flights -->", originBox, destBox, flightsBox, &airlineTicketingSystem);
    viewTest.AddUIItem(searchButton);
    ECConsoleUITextLabel *pl10 = new ECConsoleUITextLabel(13, 13, "---------------------");
    viewTest.AddUIItem(pl10);
    viewTest.AddUIItem(flightsBox);


    ECConsoleUITextLabel *pl8 = new ECConsoleUITextLabel(10, 22, "Enter Passanger name:");
    viewTest.AddUIItem(pl8);
    ECConsoleUITextField *pt1 = new ECConsoleUITextField(viewTest.GetView(), 10, 24, 22);
    viewTest.AddUIItem(pt1);

    viewTest.Refresh();  
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <data_filename.txt>" << endl;
        return 1; 
    }

    string dataFilename = argv[1];

    ECTextViewImp wndTest;
    wndTest.AddStatusRow("Airline Reservation", "Raj Air", true);

    ECConsoleUIView viewUI(&wndTest);

    ECAirlineOperation airlineOps;
    set<string> airports;

    ReadData(dataFilename, airports, airlineOps);
   
    ECAirlineTicketing airlineTicketingSystem(&airlineOps); 

    Test1(viewUI, airports, airlineOps, airlineTicketingSystem);

    viewUI.Refresh();
    try {
        wndTest.Show();
    } catch(std::string ex) {
        cout << "Exception: " << ex << endl;
    }
    return 0;
}

