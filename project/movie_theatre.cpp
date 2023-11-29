
#include <iostream>
#include <map>
#include "classes.h"
using namespace std;


movie_theatre::movie_theatre(){
    for (int i = 1; i <= 6;++i){
        hall h1(i,"empty");
        halls[i - 1] = h1;
    }
}

bool movie_theatre :: bookTicket(string movie, int hallType,int seatType,int &seatNo,int &hallNo){
    int hs = (hallType == 1) ? 0 : 3;
    int ss = (seatType == 1) ? 0 : 30;
    for (int i = hs; i < hs + 3;++i){
        for (int j = ss; j < ss + 30;++j){
            if(halls[i].cur_movie!=movie)
                continue;
            if(!(halls[i].seats[j].assigned)){
                halls[i].seats[j].assigned = true;
                seatNo = j + 1;
                hallNo = i + 1;
                return true;
            }
        }
    }
    cout << "No ticket available!" << endl;
    return false;
}

void movie_theatre :: cancelTicket(string phoneNo){
    bool flag = false;
    for (int i = 0; i < 6;++i){
        for (int j = 0; j < 60;++j){
            if(halls[i].seats[j].assigned){
                customer c1 = get_assign(halls[i], j);
                if(c1.get_phone()==phoneNo){
                    flag = true;
                    displayCustomer::display(c1);
                    halls[i].seats[j].assigned = false;
                }
            }
        }
    }
    if(!flag)
        cout << "No ticket found for this number!" << endl;
    else
        cout << "Ticket cancelled successfully!" << endl;
}

void movie_theatre :: addMovie(int hallno,string movieName,map<string, int>&movies){
    if(halls[hallno-1].cur_movie=="empty"){
        halls[hallno - 1].cur_movie = movieName;
        movies[movieName]++;
        cout << "Movie assigned successfully!" << endl;
    }
    else
        cout << "Another movie is showing in this hall currently!" << endl;
}

void movie_theatre :: removeMovie(int hallno,map<string, int>&movies){
    if(halls[hallno-1].cur_movie!="empty"){
        movies[halls[hallno-1].cur_movie]--;
        if(!movies[halls[hallno-1].cur_movie])
            movies.erase(halls[hallno - 1].cur_movie);
        halls[hallno - 1].cur_movie = "empty";
        cout << "Movie removed successfully!" << endl;
    }
    else
        cout << "No movie is showing in this hall currently!" << endl;
}
