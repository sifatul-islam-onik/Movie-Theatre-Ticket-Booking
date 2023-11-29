#include <map>
#include <iostream>
using namespace std;

class hall;

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
    customer();
    customer(string nm, string ph, string mn, int st, int hn, int sn, int ht);
    string get_phone();
    friend class displayCustomer;
    friend customer get_assign(hall obj,int i);
};

class displayCustomer{
public:
    static void display(customer c1);
};

class ticket{
    customer assigned_to;
public:
    int seat_no;
    string seat_type;
    bool assigned = true;
    ticket();
    ticket(int i);
    void set_assign(customer c1);
    friend customer get_assign(hall obj,int i);
};

class hall{
public:
    int hall_no;
    string hall_type;
    string cur_movie;
    ticket seats[60];
    hall();
    hall(int no, string mn);
};

class movie_theatre{
public:
    hall halls[6];
    map<string, int> movies;
    movie_theatre();
    bool bookTicket(string movie, int hallType,int &seatNo,int &hallNo);
    void cancelTicket(string phonoNo);
    void addMovie(int hallno, string movieName,map<string, int>&movies);
    void removeMovie(int hallno, map<string, int> &movies);
};


customer get_assign(hall obj, int i); // to use as a friend function

