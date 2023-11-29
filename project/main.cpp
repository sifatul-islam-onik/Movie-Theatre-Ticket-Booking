#include <iostream>
#include <map>
#include "classes.h"
using namespace std;

movie_theatre abc;

customer get_assign(hall obj,int i){
    return obj.seats[i].assigned_to;
}

int main(){

    while(true){
        int choice;
        cout << "--------------------------------" << endl;
        cout << "\n\tABC Cineplex" << endl;
        cout << "1.Add Movie" << endl;
        cout << "2.Remove Movie" << endl;
        cout << "3.Book ticket" << endl;
        cout << "4.View available tickets" << endl;
        cout << "5.View booked tickets info" << endl;
        cout << "6.View specific ticket information" << endl;
        cout << "7.Cancel ticket" << endl;
        cout << "0.Exit" << endl;
        cout << "--------------------------------" << endl;
        cin >> choice;
        if(choice==1){
            string movie;
            int hall;
            cout << "Enter hall no: " << endl;
            cin >> hall;
            cout << "Movie name: " << endl;
            cin.ignore();
            getline(cin, movie);
            abc.addMovie(hall, movie, abc.movies);
        }
        else if(choice==2){
            int hall;
            cout << "Enter hall no: " << endl;
            cin >> hall;
            abc.removeMovie(hall, abc.movies);
        }
        else if(choice==3){
            string name, phone, movie;
            int hallNo, seatNo, hallType, seatType;
            cout << "Now showing: \n" << endl;
            for(auto it:abc.movies){
                cout << "* " << it.first << endl;
            }
            cin.ignore();
            cout << "Enter movie name: " << endl;
            cin >> movie;
            if(abc.movies.find(movie)==abc.movies.end()){
                cout << "Invalid name!" << endl;
                continue;
            }
            cin.ignore();
            cout << "Enter customer name:" << endl;
            getline(cin, name);
            cout << "Enter customer phone no:" << endl;
            cin >> phone;
            cout << "Enter hall type:\n1. 3D\n2. 2D" << endl;
            cin >> hallType;
            if (!abc.bookTicket(movie, hallType, seatNo, hallNo))
                continue;
            customer c1(name, phone, movie, seatType, hallNo, seatNo, hallType);
            abc.halls[hallNo - 1].seats[seatNo - 1].set_assign(c1);
            cout << "Ticket booked successfully!" << endl;
            displayCustomer::display(c1);
        }
        else if(choice==4){
            map<string, pair<pair<int, int>, pair<int, int>>> m;
            int thp = 0, twp = 0, thr = 0, twr = 0;
            for (int i = 0; i < 6;++i){
                for (int j = 0; j < 60;++j){
                    if(!abc.halls[i].seats[j].assigned){
                        if(i<3 && j<30)
                            m[abc.halls[i].cur_movie].first.first++;
                        else if(i<3 && j>=30)
                            m[abc.halls[i].cur_movie].first.second++;
                        else if(i>=3 && j<30)
                            m[abc.halls[i].cur_movie].second.first++;
                        else
                            m[abc.halls[i].cur_movie].second.second++;
                    }
                }
            }
            for(auto [x,y]:m){
                if(x=="empty")
                    continue;
                cout << x << endl;
                cout << "3D Premium: " << y.first.first << "\t3D regular: " << y.first.second << endl;
                cout << "2D Premium: " << y.second.first << "\t2D regular: " << y.second.second << endl;
            }
        }
        else if(choice==5){
            bool flag = false;
            for (int i = 0; i < 6;++i){
                for (int j = 0; j < 60;++j){
                    if(abc.halls[i].seats[j].assigned){
                        flag = true;
                        customer c1 = get_assign(abc.halls[i], j);
                        displayCustomer::display(c1);
                    }
                }
            }
            if(!flag)
                cout << "No ticket found!" << endl;
        }
        else if(choice==6){
            int queryType;
            string phn;
            cout << "1.By customer phone no " << endl;
            cout << "2.By booked seat no " << endl;
            cin >> queryType;
            if(queryType==1){
                bool flag = false;
                cout << "Enter phone no: " << endl;
                cin >> phn;
                for (int i = 0; i < 6;++i){
                    for (int j = 0; j < 60;++j){
                        if(abc.halls[i].seats[j].assigned){
                            customer c1 = get_assign(abc.halls[i], j);
                            if(c1.get_phone()==phn){
                                flag = true;
                                displayCustomer::display(c1);
                            }
                        }
                    }
                }
                if(!flag)
                    cout << "No ticket found!" << endl;
            }
            else{
                int hall, seat;
                cout << "Enter hall no: " << endl;
                cin >> hall;
                cout << "Enter seat no: " << endl;
                cin >> seat;
                if(abc.halls[hall-1].seats[seat-1].assigned){
                    customer c1 = get_assign(abc.halls[hall - 1], seat - 1);
                    displayCustomer::display(c1);
                }
                else{
                    cout << "Seat not booked!" << endl;
                }
            }
        }
        else if(choice==7){
            string phn;
            cout << "Enter phone no: " << endl;
            cin >> phn;
            abc.cancelTicket(phn);
        }
        else if(choice==0){
            break;
        }
        else{
            cout << "Invalid input!" << endl;
        }
    }
}
