#include "matrix.hpp"
#define DIFF 0.0001 // Δήλωση της διαφοράς

// Δημιουργία δικού μας χώρου ονομάτων math
namespace math
{
    double Abs(double k)
    {
        if (k < 0)
        {
            return -k;
        }
        return k;
    }
}; 

//Με βάση τα δύο ορίσματα που δέχεται δεσμέυει την μνήμη και αρχικοποιεί με τυχαίες τιμές τον πίνακα γειτνίασης
matrix::matrix(int r, int c) : rows(r), columns(c)
{
    
    //Γεννήτρια παραγωγής τυχαίων αριθμών
    mt19937 mt(chrono::high_resolution_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> dist(0, 1);

    //Δέσμευση μνήμης για πίνακα γειτνίασης
    p = new int *[r];
    this->visits = new int[r];

    //Πίνακας επισκέψεων
    for (int i = 0; i < r; i++)
    {
        this->visits[i] = 0;
        p[i] = new int[r];
    }

    //Δυσδιάστατος πίνακας
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            if (i == j)
            {
                p[i][j] = 0; //μηδενισμός κύριας διαγωνίου
                continue;
            }
            p[i][j] = dist(mt);
        }
    }
}

//Αποδεσμεύση της μνήμης του δείκτη που αποθηκέυεται ο πίνακας γειτνίασης
matrix::~matrix()
{
    for (int i = 0; i < this->rows; i++)
    {
        delete[] p[i];
    }
    delete[] p;
    p = 0;
}

void matrix::reset_visits()
{
    for (int i = 0; i < this->rows; i++)
    {
        this->visits[i] = 0;
    }
}

int matrix::nrows() const
{
    return this->rows;
}

int matrix::ncols() const
{ 
    return this->columns;
}

//Δέχεται μία κορυφή r και επιστρέφει τους γείτονές της (δηλ. όπου υπάρχει 1)
vector<int> matrix::neiborghs(int r)
{
    vector<int> n;
    for (int j = 0; j < this->columns; j++)
    {
        if (this->p[r][j] != 0)
        {
            n.push_back(j);
        }
    }
    return n;
}

//Εύρεση του βαθμού των ιστοσελίδων
string matrix::find_ranking()
{
    string res = "";

    //Αποθήκευση του προηγούμενου βαθμού
    if (this->rank.empty())
    {
        this->previous_rank = 0;
    }
    else
    {
        this->previous_rank = this->rank.at(0).grade;
    }

    this->rank.clear();

    const int summary = accumulate(this->visits, this->visits + this->rows, 0); //συνολικός αριθμός επισκέψεων
    for (int i = 0; i < this->rows; i++)
    {
        this->rank.push_back(pagerank{i, (double)this->visits[i] / summary}); //βαθμός ιστοσελίδας
    }

    //ταξινόμηση ιστοσελίδων κατά φθήνουσα σειρά
    sort(this->rank.begin(), this->rank.end(), [](const pagerank &p1, const pagerank &p2) { return p1.grade > p2.grade; });
    int counter = 1;
    for (auto &x : this->rank)
    {
        res += "Sthn thesh  " + to_string(counter) + " vrisketai h selida " + to_string(x.page) + " me vathmo " + to_string(x.grade) + "\n";
        counter++;
    }
    return res;
}

bool matrix::difference()
{
    if (this->rank.empty())
    {
        return false;
    }
    double value = this->rank.at(0).grade - this->previous_rank;
    value = math::Abs(value);
    return value <= DIFF;
}