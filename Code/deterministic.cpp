#include "deterministic.hpp"

Frame::~Frame()
{
    delete this->s;
    exit(EXIT_SUCCESS);
} 

Frame::Frame() : wxFrame(nullptr, wxID_ANY, "Random Surfer", wxDefaultPosition, wxSize(350, 500)), s(nullptr)
{
    this->gs = new wxBoxSizer(wxVERTICAL);
    this->gs->AddSpacer(3);
    string desc = "Random Surfing Algorithm using Random visits per Page";
    wxStaticText *st = new wxStaticText(this, wxTEXT_ALIGNMENT_CENTER, desc, wxDefaultPosition, wxSize(340, 30), wxCENTRE);
    st->SetForegroundColour(wxColor("#ff0055"));
    this->SetBackgroundColour(wxColor("#ffccff"));
    this->gs->Add(st);
    this->panel1();
    this->panel2();
    this->panel3();
    this->panel4();
    this->results = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(340, 270), wxTE_MULTILINE);
    this->gs->Add(this->results);
    this->SetSizer(this->gs);
}

void Frame::panel1()
{
    wxPanel *panel = new wxPanel(this, wxID_ANY);
    panel->SetBackgroundColour(wxColor("#ffb3ff"));
    wxGridSizer *sizer = new wxGridSizer(0, 2, 4, 4);
    wxStaticText *st = new wxStaticText(panel, wxID_ANY, "PAGES", wxDefaultPosition, wxSize(100, 20));
    this->pages = new wxTextCtrl(panel, wxID_ANY, "10", wxDefaultPosition, wxSize(140, 20));
    sizer->Add(st);
    sizer->Add(this->pages);
    panel->SetSizer(sizer);
    this->gs->Add(panel);
}

void Frame::panel2()
{
    wxPanel *panel = new wxPanel(this, wxID_ANY);
    panel->SetBackgroundColour(wxColor("#ffb3ff"));
    wxGridSizer *sizer = new wxGridSizer(0, 2, 4, 4);
    wxStaticText *st = new wxStaticText(panel, wxID_ANY, "DAMPING FACTOR", wxDefaultPosition, wxSize(100, 20));
    this->damping_factor = new wxTextCtrl(panel, wxID_ANY, "0.85", wxDefaultPosition, wxSize(140, 20));
    sizer->Add(st);
    sizer->Add(this->damping_factor);
    panel->SetSizer(sizer);
    this->gs->Add(panel);
}

void Frame::panel3()
{
    wxPanel *panel = new wxPanel(this, wxID_ANY);
    panel->SetBackgroundColour(wxColor("#ffb3ff"));
    wxGridSizer *sizer = new wxGridSizer(0, 2, 4, 4);
    wxStaticText *st = new wxStaticText(panel, wxID_ANY, "VISITORS", wxDefaultPosition, wxSize(100, 20));
    this->visitors = new wxTextCtrl(panel, wxID_ANY, "3", wxDefaultPosition, wxSize(140, 20));
    sizer->Add(st);
    sizer->Add(this->visitors);
    panel->SetSizer(sizer);
    this->gs->Add(panel);
}

void Frame::panel4()
{
    wxPanel *panel = new wxPanel(this, wxID_ANY);
    wxGridSizer *sizer = new wxGridSizer(0, 2, 4, 4);
    panel->SetBackgroundColour(wxColor("#ffb3ff"));
    wxButton *b1 = new wxButton(panel, wxID_ANY, "SURFING", wxDefaultPosition, wxSize(60, 20));
    wxButton *b2 = new wxButton(panel, wxID_ANY, "RANKING", wxDefaultPosition, wxSize(60, 20));
    b1->Bind(wxEVT_BUTTON, &Frame::surfing, this);
    b2->Bind(wxEVT_BUTTON, &Frame::ranking, this);
    sizer->Add(b1);
    sizer->Add(b2);
    panel->SetSizer(sizer);
    this->gs->Add(panel);
}

void Frame::surfing(wxCommandEvent &ev)
{
    string number_of_pages = this->pages->GetValue().ToStdString();
    string number_of_visitors = this->visitors->GetValue().ToStdString();
    string number_of_dmp = this->damping_factor->GetValue().ToStdString();
    if (number_of_pages.empty() || number_of_visitors.empty() || number_of_dmp.empty())
    {
        wxMessageBox("Fill all the blanks");
        return;
    }
    int nop = stoi(number_of_pages);
    int nov = stoi(number_of_visitors);
    double nod = stod(number_of_dmp);
    this->s = new Surfer(nop);
    this->results->SetValue(this->s->Surfing(nov, nod));
}

void Frame::ranking(wxCommandEvent &ev)
{
    if (this->s == nullptr)
    {
        wxMessageBox("No Web Surfing made!! \n Please make a web Surf");
        return;
    }
    string web_ranking = this->s->find_ranking();
    wxMessageBox(web_ranking, "Ranking");
}
