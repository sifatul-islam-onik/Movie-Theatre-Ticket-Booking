
#include <iostream>
#include <iomanip>
#include <map>
#include "classes.h"
using namespace std;


movie_theatre::movie_theatre(){
    for (int i = 1; i <= 6;++i){
        hall h1(i,"empty");
        halls[i - 1] = h1;
    }
}

bool movie_theatre :: bookTicket(string movie, int hallType,int &seatNo,int &hallNo){
    string ht = (hallType == 1) ? "3D" : "2D";
    bool flag = false;
    for (int i = 0; i < 6;++i){
        if(halls[i].cur_movie!=movie || halls[i].hall_type!=ht)
            continue;
        cout << "Hall no: " << halls[i].hall_no << '\t' << "Hall type: " << halls[i].hall_type << endl;
        cout << "Current movie playing: " << halls[i].cur_movie << endl;
        cout << "Premium: 1-30 \t Regular: 31-60 \t B: Booked" << endl;
        for (int j = 0; j < 6;++j){
            for (int k = 0; k < 10;++k){
                if(!(halls[i].seats[(j*10)+k].assigned)){
                    cout << setw(2) << halls[i].seats[(j * 10) + k].seat_no << "  ";
                    flag = true;
                }
                else
                    cout << " B  ";
            }
            cout << endl;
        }
        cout << endl;
    }
    if(!flag){
        cout << "No seats available for this movie!" << endl;
        return false;
    }
    int choice;
    cout << "Choose seat? (1.Yes / 0.No)" << endl;
    cin >> choice;
    if(choice){
        cout << "Enter hall no: " << endl;
        cin >> hallNo;
        cout << "Enter seat no: " << endl;
        cin >> seatNo;
        if(!halls[hallNo-1].seats[seatNo-1].assigned){
            halls[hallNo-1].seats[seatNo-1].assigned=true;
            cout<<"Seat booked successfully!"<<endl;
            return true;
        }
        else{
            cout<<"Seat is booked already!"<<endl;
            return false;
        }
    }
    else{
        cout << "No seat chosen!" << endl;
        return false;
    }
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
