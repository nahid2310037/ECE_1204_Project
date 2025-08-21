#include <bits/stdc++.h>
using namespace std;

class Buyer {
    string name;
    int age;
    string contact;
public:
    Buyer();
    void displayInfo();
    void setInfo();
    int getAge();
};

class Ticket {
protected:
    string ticketID, selectedRoute, departureTime;
    double baseFair, finalFare;
    Buyer buyer;
public:
    Ticket(string _ticketID);
    virtual double calculateFair() = 0;
    int returnFair(string str[], int fair[], int len);
    virtual void setTime();
    virtual void displayTicketInfo();
    void setTicketInfo();
};

class BusTicket : public Ticket {
    string routes[5] = {"Rajshahi-Dhaka","Rajshahi-Kushtia","Rajshahi-Barishal","Rajshahi-Rangpur","Rajshahi-Natore"};
    int fair[5] = {500, 90, 450, 200, 40};
public:
    BusTicket(string _ticketID);
    double calculateFair() override;
};

class TrainTicket : public Ticket {
    string routes[5] = {"Rajshahi-Dhaka","Rajshahi-Kushtia","Rajshahi-Bogura","Rajshahi-Rangpur","Rajshahi-Natore"};
    int fair[5] = {500, 90, 370, 200, 40};
public:
    TrainTicket(string _ticketID);
    double calculateFair() override;
    void setTime() override;
};

class MovieTicket : public Ticket {
    string movies[5] = {"Movie A","Movie B","Movie C","Movie D","Movie E"};
    int fair[5] = {100, 70, 90, 250, 150};
public:
    MovieTicket(string _ticketID);
    void setTime() override;
    void displayTicketInfo() override;
    double calculateFair() override;
};

string randStr();


// Buyer definitions
Buyer::Buyer() {
    name = "";
    age = 0;
    contact = "";
}

void Buyer::displayInfo() {
    cout << "Name: " << name << endl;
    cout << "Age: " << age << endl;
    cout << "Contact: " << contact << endl;
}

void Buyer::setInfo() {
    cout << "We need some information to complate." << endl;
    cout << "Enter name: ";
    getchar();
    getline(cin, name);
    cout << "Enter age: ";
    cin >> age;
    cout << "Enter contact: ";
    cin >> contact;
}

int Buyer::getAge() {
    return age;
}


// Ticket definitions
Ticket::Ticket(string _ticketID) {
    ticketID = _ticketID;
}

int Ticket::returnFair(string str[], int fair[], int len) {
    int routeIndex;
    for (int i = 0; i < 5; i++) {
        cout << i + 1 << ". " << str[i] << " - Fare: " << fair[i] + baseFair << " BDT" << endl;
    }
    cout<<"---------------------------------------------------------"<<endl;
    cout << "Press 0 to Exit if do not want to buy." << endl;
    cout << "Select a route (1-5): "<<endl;
    cin >> routeIndex;
    if (routeIndex == 0) {
        cout << "Exiting..." << endl;
        exit(0);
    }
    if (routeIndex < 1 || routeIndex > 5) {
        cout << "Invalid route selection." << endl;
        return 0;
    }
    return routeIndex - 1;
}

void Ticket::setTime() {
    cout << "Select departure time: "<<endl;
    cout<<"1. 8:15 AM"<<endl;
    cout<<"2. 10:15 AM"<<endl;
    cout<<"3. 12:15 PM"<<endl;
    cout<<"4. 2:15 PM"<<endl;
    cout<<"5. 4:15 PM"<<endl;
    cout << "Enter your choice (1-5): ";
    int choice;
    cin >> choice;
    switch (choice) {
        case 1: departureTime = "8:15 AM"; break;
        case 2: departureTime = "10:15 AM"; break;
        case 3: departureTime = "12:15 PM"; break;
        case 4: departureTime = "2:15 PM"; break;
        case 5: departureTime = "4:15 PM"; break;
        default: cout << "Invalid choice." << endl; break;
    }
}

void Ticket::setTicketInfo() {
    finalFare = calculateFair();
    setTime();
    buyer.setInfo();
}

void Ticket::displayTicketInfo() {
    cout << "=========================================================" << endl;
    cout << "Ticket purchase complete" << endl;
    cout << "=========================================================" << endl;
    buyer.displayInfo();
    cout << "Ticket ID: " << ticketID << endl;
    cout << "Selected Route: " << selectedRoute << endl;
    cout << "Departure Time: " << departureTime << endl;
    cout << "Final Fare: " << finalFare << " BDT" << endl;
}


// BusTicket definitions
BusTicket::BusTicket(string _ticketID) : Ticket(_ticketID) {
    baseFair = 250;
}

double BusTicket::calculateFair() {
    cout << "Available Routes : " << endl;
    int ind = returnFair(routes, fair, 5);
    selectedRoute = routes[ind];
    return fair[ind] + baseFair;
}


// TrainTicket definitions
TrainTicket::TrainTicket(string _ticketID) : Ticket(_ticketID) {
    baseFair = 60;
}

double TrainTicket::calculateFair() {
    cout << "Available Routes : " << endl;
    int ind = returnFair(routes, fair, 5);
    selectedRoute = routes[ind];
    return fair[ind] + baseFair;
}
void TrainTicket::setTime() {
    cout << "Select departure time: "<<endl;
    cout<<"1. 8:00 AM"<<endl;
    cout<<"2. 12:00 PM"<<endl;
    cout<<"3. 4:00 PM"<<endl;
    cout << "Enter your choice (1-3): ";
    int choice;
    cin >> choice;
    switch (choice) {
        case 1: departureTime = "8:00 AM"; break;
        case 2: departureTime = "12:00 PM"; break;
        case 3: departureTime = "4:00 PM"; break;
        default: cout << "Invalid choice." << endl; break;
    }
}

// MovieTicket definitions
MovieTicket::MovieTicket(string _ticketID) : Ticket(_ticketID) {
    baseFair = 100;
}

void MovieTicket::setTime() {
    cout << "Select show time: "<<endl;
    cout<<"1. 9:00 AM"<<endl;
    cout<<"2. 12:00 PM"<<endl;
    cout<<"3. 3:00 PM"<<endl;
    cout<<"4. 6:00 PM"<<endl;
    cout<<"5. 9:00 PM"<<endl;
    cout << "Enter your choice (1-5): ";
    int choice;
    cin >> choice;
    switch (choice) {
        case 1: departureTime = "9:00 AM"; break;
        case 2: departureTime = "12:00 PM"; break;
        case 3: departureTime = "3:00 PM"; break;
        case 4: departureTime = "6:00 PM"; break;
        case 5: departureTime = "9:00 PM"; break;
        default: cout << "Invalid choice." << endl; break;
    }
}
void MovieTicket::displayTicketInfo() {
    cout << "=========================================================" << endl;
    cout << "Ticket purchase complete" << endl;
    cout << "=========================================================" << endl;
    buyer.displayInfo();
    cout << "Ticket ID: " << ticketID << endl;
    cout << "Selected Movie: " << selectedRoute << endl;
    cout << "Show Time: " << departureTime << endl;
    cout << "Final Fare: " << finalFare << " BDT" << endl;
}

double MovieTicket::calculateFair() {
    cout << "Available Movies : " << endl;
    int ind = returnFair(movies, fair, 5);
    selectedRoute = movies[ind];
    return fair[ind] + baseFair;
}


// Utility function
string randStr() {
    const string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    string result;
    for (int i = 0; i < 5; ++i) {
        result += chars[rand() % chars.size()];
    }
    return result;
}


// Main
int main() {
    cout << "Which type ticket do you want to buy?" << endl;
    cout << "1. Bus Ticket" << endl;
    cout << "2. Train Ticket" << endl;
    cout << "3. Movie Ticket" << endl;
    cout << "Enter your choice (1-3): " << endl;

    int choice;
    cin >> choice;
    string ticketID;
    switch (choice) {
        case 1: {
            ticketID = "BU" + randStr();
            BusTicket busTicket(ticketID);
            busTicket.setTicketInfo();
            busTicket.displayTicketInfo();
            break;
        }
        case 2: {
            ticketID = "TR" + randStr();
            TrainTicket trainTicket(ticketID);
            trainTicket.setTicketInfo();
            trainTicket.displayTicketInfo();
            break;
        }
        case 3: {
            ticketID = "MV" + randStr();
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
