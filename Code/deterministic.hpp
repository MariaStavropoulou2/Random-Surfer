#include <wx/wx.h>
#include "Surfer.hpp"

class Frame : public wxFrame
{
private:
  Surfer *s;
  ~Frame();
  wxTextCtrl *visitors, *pages, *damping_factor, *results;
  wxBoxSizer *gs;
  void panel1();
  void panel2();
  void panel3();
  void panel4(); 

public:
  Frame();
  void surfing(wxCommandEvent &ev);
  void ranking(wxCommandEvent &ev);
};