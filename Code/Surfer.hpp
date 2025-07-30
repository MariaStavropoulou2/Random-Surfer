#include "matrix.hpp"

//Δήλωση κλάσης πλοήγησης στις ιστολελίδες που κληρονομεί την matrix
class Surfer : public matrix 
{
public:
  Surfer(int pages);                                   //Constructor
  ~Surfer();                                           //Destructor
  string Surfing(int visitors, double DAMPING_FACTOR); //Πλοήγηση
  double getTop() const;                               //Αποθήκευση του μέγιστου βαθμού
}; 