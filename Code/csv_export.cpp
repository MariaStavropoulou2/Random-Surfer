#include <iostream>
#include <fstream>
#include "Surfer.hpp"

int main() 
{
    //Εισαγωγή δεδομένων
    string filename;
    int visitors;
    int first_page = 10;
    int last_page = 1000;
    int page_step = 5;
    double first_damping_factor = 0.50;
    double last_damping_factor = 0.99;
    double damping_factor_step = 0.01;
    cout << "Dwse ton arithmo twn episkeptwn: ";
    cin >> visitors;
    cout << endl << "Dwse onoma arxeiou: ";
    cin >> filename;
    filename += ".csv";
    string path = "Exel_files/" + filename;

    //άνοιγμα αρχείου
    ofstream ofs;
    ofs.open(path, std::ios::out);
    for (double dp = first_damping_factor; dp <= last_damping_factor; dp += damping_factor_step)
    {
        ofs << ";DMP_" << dp;
    }
    ofs << endl;
    double top_rank_element;
    string top;
    double dp;
    for (int i = first_page; i <= last_page; i += page_step)
    {
        ofs << i;
        dp = first_damping_factor;
        while (dp <= last_damping_factor)
        {
            Surfer s(i);
            s.Surfing(visitors, dp);
            top_rank_element = s.getTop();
            top = to_string(top_rank_element);
            replace_if(top.begin(), top.end(), [](char &a) { return a == '.'; }, ',');
            ofs << ";" << top;
            dp = dp + damping_factor_step;
        }
        ofs << endl;
    }
    ofs.close();
    cout << endl << "At current folder at:" << __TIME__ << " file:" << path << " created!!!!!" << endl;
    return 0;
}