

#ifndef ECConsoleUITextField_h
#define ECConsoleUITextField_h

#include <string>
#include <vector>

#include "ECConsoleUIItem.h"
class ECTextViewImp;

using namespace std;

//*****************************************************************************
// Console UI list box: several rows (items) to choose from

class ECConsoleUITextField : public ECConsoleUIItem
{
public:
    // specifiy the starting point of the text field
    ECConsoleUITextField(ECTextViewImp *pTextView, int xpos, int ypos, int len);
    
    // Get displayed text at a specific row
    // Text is relative to the item portion (i.e., relative to (xLR, yLR))
    virtual std::string GetTextAtRow(int r) const override;
    
    // Get highlighted part (if any); return the row with highlight
    // if one, return -1; also store the highlightd portion (yLeft, yRight) of this row
    // Assume: at most a single row with highlighted part
    virtual int GetHighlightPosition(int &xLeft, int &xRight) const override;

    // Are there any other function you might need to override?

    // Handle key events: override to provide functionality
    virtual bool IsHandlingKeys() const override { return true; }
    virtual void HdlKeyEnter() override;
    virtual void HandleKey();

    // Activates the text field to allow editing
    void Activate();
    
private:
    ECTextViewImp* pTextView;   // Pointer to the text view for rendering and input handling
    string textContent;    // Current text content of the field
    bool isActive;              // Whether the text field is currently active for editing
    int maxLength;              // Maximum length of the text that can be entered
};

#endif /* ECConsoleUITextField_h */
