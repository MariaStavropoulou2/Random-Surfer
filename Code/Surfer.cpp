#include "Surfer.hpp"

//Δημιουργία πίνακα γειτνίασης με κλήση του constructor της matrix.cpp
Surfer::Surfer(int pages) : matrix(pages, pages) {} 

Surfer::~Surfer() {}

//Τυχαία πλοήγηση σε ιστοσελίδες
string Surfer::Surfing(int visitors, double DAMPING_FACTOR)
{
    string res = ""; 
    this->reset_visits();

    //Γεννήτρια παραγωγής τυχαίων αριθμών
    mt19937 mt(chrono::high_resolution_clock().now().time_since_epoch().count());
    uniform_int_distribution<int> go(0, this->rows - 1); //Ορισμός όριων για τους visitors
    uniform_real_distribution<double> ran(0.0, 1.0);     //Ορισμός όριων για το DAMPING_FACTOR

    int *startingpage = new int[visitors]; //Αρχική τοποθέτηση επισκεπτών σε σελίδα

    //Κατασκευή πίνακα τοποθέτησης των επισκεπτών σε τυχαίες ιστοσελίδες
    for (int i = 0; i < visitors; i++)
    {
        startingpage[i] = go(mt);
        res += "O episkepths " + to_string(i + 1) + " topothetithike sthn istoselida " + to_string(startingpage[i]) + "\n";
        this->visits[startingpage[i]]++;
    }
    res += "\n";

    vector<int> nbs;
    int nextpage;
    while (!this->difference())
    {
        for (int j = 0; j < visitors; j++)
        {
            if (ran(mt) <= DAMPING_FACTOR) //Αν ran(mt)<=0.85 τότε μεταφερόμαστε σε γειτονική σελίδα
            {
                nbs = this->neiborghs(startingpage[j]); //Εύρεση γειτόνων
                if (nbs.empty())
                {
                    res += "Dead End!! ";
                    nextpage = go(mt);
                    while (nextpage == startingpage[j])
                    {
                        nextpage = go(mt);
                    }
                }
                else
                {
                    nextpage = nbs[go(mt) % nbs.size()]; //Ακέραιο υπόλοιπο της διαίρεσης της τυχαίας τιμής με το μέγεθος του πίνακα (0 ή 1)
                }
            }
            else
            {
                nextpage = go(mt);
                while (nextpage == startingpage[j])
                {
                    nextpage = go(mt);
                }
            }
            this->visits[nextpage]++;
            res += "O episkepths " + to_string(j + 1) + " tha metakinithei apo thn istoselida " + to_string(startingpage[j]) + " sthn istoselida " + to_string(nextpage) + "\n";
            startingpage[j] = nextpage;
        }
        res += "\n";
        this->find_ranking();//Εύρεση βαθμού
    }
     
    return res;
}

//Αποθηκεύει τον μεγαλύτερο βαθμό
double Surfer::getTop() const
{
    if (this->rank.empty())
    {
        return -1.0;
    }
    return this->rank.at(0).grade;
}