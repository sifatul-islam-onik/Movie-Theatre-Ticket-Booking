#include <iostream>
#include "classes.h"
using namespace std;


void displayCustomer :: display(customer c1){
    cout << "--------------------------------" << endl;
    cout << "Name: " << c1.name << endl;
    cout << "Phone No: " << c1.phone_no << endl;
    cout << "Movie name: " << c1.movie_name << endl;
    cout << "Hall No: " << c1.hall_no << endl;
    cout << "Hall type: " << c1.hall_type << endl;
    cout << "Seat No: " << c1.seat_no << endl;
    cout << "Seat type: " << c1.seat_type << endl;
    cout << "Ticket Price: " << c1.ticket_price << " BDT including vat" << endl;
    cout << "--------------------------------" << endl;
}
