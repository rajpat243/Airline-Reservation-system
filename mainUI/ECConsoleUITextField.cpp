

#include "ECConsoleUITextField.h"
#include "ECTextViewImp.h"

using namespace std;

ECConsoleUITextField::ECConsoleUITextField(ECTextViewImp *pTextView, int xpos, int ypos, int length)
    : ECConsoleUIItem(xpos, ypos, xpos + length - 1, ypos), pTextView(pTextView), isActive(false), maxLength(10)
{
    textContent.reserve(maxLength);
}

string ECConsoleUITextField::GetTextAtRow(int r) const
{
    if (r == GetYUL()) {
        return ":" + textContent; 
    }
    return "";
}

int ECConsoleUITextField::GetHighlightPosition(int &xLeft, int &xRight) const
{
    if (isActive) {
        xLeft = GetXUL() + 1;
        xRight = xLeft + textContent.length() - 1;
        return GetYUL();
    }
    return -1;
}

void ECConsoleUITextField::Activate()
{
    isActive = true;
    pTextView->Init();  
    pTextView->SetCursorX(GetXUL() + 1 + textContent.size()); 
    pTextView->SetCursorY(GetYUL());
    pTextView->Refresh();  
}

void ECConsoleUITextField::HdlKeyEnter()
{
    Activate();
}

void ECConsoleUITextField::HandleKey()
{
    int key = pTextView->GetPressedKey();
    if (isActive == true) 
    switch (key) {
        case BACKSPACE:
            if (!textContent.empty()) {
                textContent.pop_back();
                pTextView->SetCursorX(pTextView->GetCursorX() - 1);
            }
            break;
        case CTRL_C:
            isActive = false;
            //pTextView->WndAtExit();
            break;
        default:
            textContent += pTextView->GetPressedKey();
            // if (key >= ' ' && key <= '~' && textContent.length() < maxLength) {
            //     textContent.push_back(static_cast<char>(key));
            pTextView->SetCursorX(pTextView->GetCursorX() + 1);
            pTextView->Refresh(); 
            // }
            break;
    }
    pTextView->Refresh(); 
}