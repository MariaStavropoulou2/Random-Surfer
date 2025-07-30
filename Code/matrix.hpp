#include <iostream>
#include <random>
#include <chrono>
#include <algorithm>
#include <vector>
#include <numeric>
#include <string>

using namespace std;

//Δομή αποθήκευσης αριθμού σελίδας και βαθμού της
struct pagerank
{
   int page;
   double grade; 
};

//Δήλωση κλάσσης κατασκευής πίνακα γειτνίασης 2 διαστάσεων
class matrix 
{
protected:
   int rows;              //Γραμμές
   int columns;           //Στήλες
   int **p;               //Δείκτης σε δείκτη για την δήλωση δυναμικού δυσδιάστατου πίνακα
   int *visits;           //Πίνακας επισκεψεων μονοδιάστατος
   double previous_rank;  //Αποθήκευση του προηγούμενου βαθμού
   vector<pagerank> rank; //Διάνυσμα που αποθηκεύει τους βαθμους των ιστοσελίδων

public:
   matrix(int r, int c);         //Constructor
   ~matrix();                    //Destructor
   void reset_visits();          //Διαγραφει τις προηγούμενες τιμές του πίνακα επισκέψεων
   int nrows() const;            //Getter για γραμμές
   int ncols() const;            //Getter για στήλες
   vector<int> neiborghs(int r); //Διάνυσμα που βρίσκει τις γειτονικές κορυφές της r
   string find_ranking();        //Βαθμός των ιστοσελίδων
   bool difference();            //Εύρεση διαφοράς τωρινού και προηγούμενου βαθμού
};