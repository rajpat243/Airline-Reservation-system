

#include "ECConsoleUIListBox.h"

using namespace std;

ECConsoleUIListBox::ECConsoleUIListBox(int xUL, int yUL, int xLR, int yLR)
: ECConsoleUIItem(xUL, yUL, xLR, yLR), indexChoice(0), firstVisibleChoice(0) {
    visibleItemCount = GetHeight();  
}

void ECConsoleUIListBox::AddChoice(const string &text) {
    choices.push_back(text);
}

void ECConsoleUIListBox::Choose(int rIndex) {
    if (rIndex >= 0 && rIndex < choices.size()) {
        indexChoice = rIndex;
    }
}

string ECConsoleUIListBox::GetTextAtRow(int r) const {
    int relativeRow = r - GetYUL(); 
    int itemIndex = firstVisibleChoice + relativeRow;
    if (itemIndex >= firstVisibleChoice && itemIndex < firstVisibleChoice + visibleItemCount) {
        if (itemIndex == indexChoice) {
            return choices[itemIndex];  // Return the text of the selected item
        }
        return choices[itemIndex];
    }
    return "";  
}

int ECConsoleUIListBox::GetHighlightPosition(int &xLeft, int &xRight) const {
    if (indexChoice >= firstVisibleChoice && indexChoice < firstVisibleChoice + visibleItemCount) { 
        xLeft = 0;  
        xRight = GetWidth(); 
        return indexChoice - firstVisibleChoice; 
    }
    return -1; 
}

void ECConsoleUIListBox::HdlKeyUp() {
    if (indexChoice > 0) {
        indexChoice--;
        if (indexChoice < firstVisibleChoice) {
            firstVisibleChoice = indexChoice;  
        }
    }
}

void ECConsoleUIListBox::HdlKeyDown() {
    if (indexChoice < choices.size() - 1) {
        indexChoice++;
        if (indexChoice >= firstVisibleChoice + visibleItemCount) {
            firstVisibleChoice = indexChoice - visibleItemCount + 1;  
        }
    }
}

void ECConsoleUIListBox::ClearChoices() {
    choices.clear();
    indexChoice = -1;
}

std::string ECConsoleUIListBox::GetSelectedText() const {
    if (indexChoice >= 0 && indexChoice < choices.size()) {
        return choices[indexChoice];  // Return the text of the currently selected item
    }
    return "";  // Return an empty string if no valid choice is selected
}