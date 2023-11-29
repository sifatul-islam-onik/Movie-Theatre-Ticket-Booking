#include <iostream>
using namespace std;
#include "classes.h"
hall::hall(){}
hall::hall(int no,string mn){
    hall_no = no;
    cur_movie = mn;
    hall_type = (no <= 3) ? "3D" : "2D";
    for (int i = 1; i <= 60;++i){
        ticket s1(i);
        seats[i - 1] = s1;
    }
};
