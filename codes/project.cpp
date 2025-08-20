#include <bits/stdc++.h>
using namespace std;



class Buyer{
    string name;
    int age;
    string contact;
public:
    Buyer() {
        name = "";
        age = 0;
        contact = "";
    }
    void displayInfo() {
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Contact: " << contact << endl;
    }
    void setInfo() {
        cout<<"We need some information to complate."<<endl;
        cout<<"Enter name: ";
        cin>>name;
        cout<<"Enter age: ";

        cin>>age;
        cout<<"Enter contact: ";
        cin>>contact;
    }
    int getAge(){
        return age;
    }
};




class Ticket{
protected:
    string ticketID, selectedRoute, departureTime;
    double baseFair ,finalFare;
    Buyer buyer;
public:
    Ticket(string _ticketID){
        ticketID = _ticketID;
    }
    
    virtual double calculateFair() = 0;

    int returnFair(string str[], int fair[], int len){
        int routeIndex;
        for (int i = 0; i < 5; i++) {
            cout << i + 1 << ". " << str[i] << " - Fare: " << fair[i] + baseFair<< " BDT" << endl;
        }
        cout << "Select a route (1-5): ";
        cin >> routeIndex;
        if (routeIndex < 1 || routeIndex > 5) {
            cout << "Invalid route selection." << endl;
            return 0;
        }
        return routeIndex-1;
    };

    virtual void setTime(){
        cout << "Enter departure time: ";
        cin >> departureTime;
    }

    void setTicketInfo(){
        setTime();
        finalFare = calculateFair();
        buyer.setInfo();
    }

    void displayTicketInfo() {
        cout<<"========================================================="<<endl;
        cout << "Ticket purchase complete" << endl;
        cout<<"========================================================="<<endl;
        buyer.displayInfo();
        cout << "Ticket ID: " << ticketID << endl;
        cout << "Selected Route: " << selectedRoute << endl;
        cout << "Departure Time: " << departureTime << endl;
        cout << "Final Fare: " << finalFare << " BDT" << endl;
    }
};


class BusTicket: public Ticket{
    string routes[5] = {"Rajshahi-Dhaka","Rajshahi-Kushtia","Rajshahi-Barishal","Rajshahi-Rangpur","Rajshahi-Natore"};
    int fair[5] = {500, 90, 450, 200, 40};
    
public:
    BusTicket(string _ticketID) : Ticket(_ticketID) {
        baseFair = 250;
    }
    double calculateFair() override {
        cout<<"Available Routes : "<<endl;
        int ind = returnFair(routes, fair, 5);
        selectedRoute = routes[ind];
        return fair[ind] + baseFair;
    }
    
};


class TrainTicket: public Ticket{
    string routes[5] = {"Rajshahi-Dhaka","Rajshahi-Kushtia","Rajshahi-Bogura","Rajshahi-Rangpur","Rajshahi-Natore"};
    int fair[5] = {500, 90, 370, 200, 40};

public:
    TrainTicket(string _ticketID) : Ticket(_ticketID) {
        baseFair = 60;
    }
    double calculateFair() override {
        cout<<"Available Routes : "<<endl;
        int ind = returnFair(routes, fair, 5);
        selectedRoute = routes[ind];
        return fair[ind] + baseFair;
    }
};

class MovieTicket: public Ticket{
    string movies[5] = {"Movie A","Movie B","Movie C","Movie D","Movie E"};
    int fair[5] = {100, 70, 90, 250, 150};

public:
    MovieTicket(string _ticketID) : Ticket(_ticketID) {
        baseFair = 100;
    }
    void setTime() {
        cout << "Enter show time: ";
        cin >> departureTime;
    }
    double calculateFair() override {
        cout<<"Available Movies : "<<endl;
        int ind = returnFair(movies, fair, 5);
        selectedRoute = movies[ind];
        return fair[ind] + baseFair;
    }
};


int main(){
    cout<<"Which type ticket do you want to buy?"<<endl;
    cout << "1. Bus Ticket" << endl;
    cout << "2. Train Ticket" << endl;
    cout << "3. Movie Ticket" << endl;

    int choice;
    cin >> choice;
    string ticketID;
    switch (choice) {
        case 1: {
            ticketID = "BU" + to_string(rand() % 10000 + 1);
            BusTicket busTicket(ticketID);
            busTicket.setTicketInfo();
            busTicket.displayTicketInfo();
            break;
        }
        case 2: {
            ticketID = "TR" + to_string(rand() % 10000 + 1);
            TrainTicket trainTicket(ticketID);
            trainTicket.setTicketInfo();
            trainTicket.displayTicketInfo();
            break;
        }
        case 3: {
            ticketID = "MV" + to_string(rand() % 10000 + 1);
            MovieTicket movieTicket(ticketID);
            movieTicket.setTicketInfo();
            movieTicket.displayTicketInfo();
            break;
        }
        default:
            cout << "Invalid choice." << endl;
    }

    return 0;
}