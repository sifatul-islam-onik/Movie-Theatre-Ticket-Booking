#include <iostream>
#include <map>
using namespace std;

class movie_theatre;
class hall;
class ticket;
class customer;
class displayCustomer; //to use as a friend class

customer get_assign(hall obj, int i); // to use as a friend function

class customer{
    string name;
    string phone_no;
    string seat_type;
    string hall_type;
    string movie_name;
    int hall_no;
    int seat_no;
    int ticket_price;

public:
    customer(){}
    customer(string nm,string ph,string mn,int st,int hn,int sn,int ht){
        name = nm;
        phone_no = ph;
        seat_no = sn;
        hall_no = hn;
        movie_name = mn;
        seat_type = (st == 1) ? "Premium" : "Regular";
        ticket_price = (st == 1) ? (ht == 1 ? 500 : 400) : (ht == 1 ? 400 : 300);
        hall_type = (ht == 1) ? "3D" : "2D";
    }
    string get_phone(){
        return phone_no;
    }
    friend class displayCustomer;
};

class displayCustomer{
    public:
    void display(customer c1){
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
};

class ticket{
    customer assigned_to;
public:
    int seat_no;
    string seat_type;
    bool assigned = true;
    ticket(){}
    ticket(int i){
        seat_no = i;
        if(i<=30)
            seat_type = "Premium";
        else
            seat_type = "Regular";
        assigned = false;
    }
    void set_assign(customer c1){
        assigned_to = c1;
    }
    friend customer get_assign(hall obj,int i);
};

class hall{
public:
    int hall_no;
    string hall_type;
    string cur_movie;
    ticket seats[60];
    hall(){}
    hall(int no,string mn){
        hall_no = no;
        cur_movie = mn;
        hall_type = (no <= 3) ? "3D" : "2D";
        for (int i = 1; i <= 60;++i){
            ticket s1(i);
            seats[i - 1] = s1;
        }
    }
    friend customer get_assign(hall obj,int i);
};

class movie_theatre{
public:
    hall halls[6];
    map<string, int> movies;
    movie_theatre(){
        for (int i = 1; i <= 6;++i){
            hall h1(i,"empty");
            halls[i - 1] = h1;
        }
    }
    bool bookTicket(string movie, int hallType,int seatType,int &seatNo,int &hallNo);
    void cancelTicket(string phonoNo);
    void addMovie(int hallno, string movieName,map<string, int>&movies);
    void removeMovie(int hallno, map<string, int> &movies);
};

movie_theatre abc;
displayCustomer d1;

bool movie_theatre :: bookTicket(string movie, int hallType,int seatType,int &seatNo,int &hallNo){
    int hs = (hallType == 1) ? 0 : 3;
    int ss = (seatType == 1) ? 0 : 30;
    for (int i = hs; i < hs + 3;++i){
        for (int j = ss; j < ss + 30;++j){
            if(abc.halls[i].cur_movie!=movie)
                continue;
            if(!(abc.halls[i].seats[j].assigned)){
                abc.halls[i].seats[j].assigned = true;
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
            if(abc.halls[i].seats[j].assigned){
                customer c1 = get_assign(abc.halls[i], j);
                if(c1.get_phone()==phoneNo){
                    flag = true;
                    d1.display(c1);
                    abc.halls[i].seats[j].assigned = false;
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
    if(abc.halls[hallno-1].cur_movie=="empty"){
        abc.halls[hallno - 1].cur_movie = movieName;
        movies[movieName]++;
        cout << "Movie assigned successfully!" << endl;
    }
    else
        cout << "Another movie is showing in this hall currently!" << endl;
}

void movie_theatre :: removeMovie(int hallno,map<string, int>&movies){
    if(abc.halls[hallno-1].cur_movie!="empty"){
        movies[abc.halls[hallno-1].cur_movie]--;
        if(!movies[abc.halls[hallno-1].cur_movie])
            movies.erase(abc.halls[hallno - 1].cur_movie);
        abc.halls[hallno - 1].cur_movie = "empty";
        cout << "Movie removed successfully!" << endl;
    }
    else
        cout << "No movie is showing in this hall currently!" << endl;
}

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
            cout << "Enter seat type:\n1.premium\n2.regular" << endl;
            cin >> seatType;
            if (!abc.bookTicket(movie, hallType, seatType, seatNo, hallNo))
                continue;
            customer c1(name, phone, movie, seatType, hallNo, seatNo, hallType);
            abc.halls[hallNo - 1].seats[seatNo - 1].set_assign(c1);
            cout << "Ticket booked successfully!" << endl;
            d1.display(c1);
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
                        d1.display(c1);
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
                                d1.display(c1);
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
                    d1.display(c1);
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