#include <iostream>
#include "classes.h"
using namespace std;

customer::customer(){}
customer::customer(string nm,string ph,string mn,int st,int hn,int sn,int ht){
    name = nm;
    phone_no = ph;
    seat_no = sn;
    hall_no = hn;
    movie_name = mn;
    seat_type = (st == 1) ? "Premium" : "Regular";
    ticket_price = (st == 1) ? (ht == 1 ? 500 : 400) : (ht == 1 ? 400 : 300);
    hall_type = (ht == 1) ? "3D" : "2D";
}
string customer::get_phone(){
    return phone_no;
}
