#include <iostream>
#include "classes.h"
using namespace std;

ticket::ticket(){}
ticket::ticket(int i){
    seat_no = i;
    if(i<=30)
        seat_type = "Premium";
    else
        seat_type = "Regular";
    assigned = false;
}
void ticket :: set_assign(customer c1){
    assigned_to = c1;
}
