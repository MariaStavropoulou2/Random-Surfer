#include "deterministic.hpp"

class app : public wxApp
{
    bool OnInit() wxOVERRIDE
    {
        Frame *f = new Frame;
        f->Show();
        return true;
    } 
};

wxIMPLEMENT_APP(app);