#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
using namespace std;



string generateTicketID();
int isPremium(int ticketChoice);
void buyTicket();
void displayBuyerDetailsByTicketID(const string &searchTicketID);



template <typename T>
T roundUp(T num, T multiple = 10);




class Passenger {
private:
    string name;
    int age;
    string contact;

public:
    Passenger();
    int getAge();
    void setInfo();      
    void displayInfo();

    friend class FileSystem; // to allow inspector to access private fields
};




// -------------------- Ticket (Abstract) --------------------
class Ticket {
protected:
    static int totalTicketsSold;
    int ticketType;     // 1: Bus, 2: Train, 3: Flight
    int isPremium;      // 1: Premium, 0: Regular
    string ticketID;
    string selectedRoute;
    int selectedDistance;
    string departureTime;
    string routes[6]   = {"Rajshahi - Dhaka", "Rajshahi - Khulna" , "Rajshahi - Rangpur",
                          "Rajshahi - Kushtia", "Rajshahi - Barisal", "Rajshahi - Bogura"};
    int distance[6]    = {280, 250, 200, 90, 300, 150};
    int fare;

public:
    Ticket(int type, int premium);
    void applyDiscount(double percentage);
    void applyDiscount(int amount);
    void checkDiscount(string coupon);
    virtual int calculateFare() = 0;
    virtual string setTime() = 0;
    void selectRoute();     
    void showTicketInfo();  

    friend class FileSystem; // to let inspector access internals
};

// -------------------- BusTicket --------------------
class BusTicket : public Ticket {
public:
    BusTicket(int premium);
    int calculateFare() override;
    string setTime() override;  
};

// -------------------- TrainTicket --------------------
class TrainTicket : public Ticket {
public:
    TrainTicket(int premium);
    int calculateFare() override;
    string setTime() override;  
};

// -------------------- FlightTicket --------------------
class FlightTicket : public Ticket {
public:
    FlightTicket(int premium);
    int calculateFare() override;
    string setTime() override;  
};


// -------------------- FileSystem --------------------
class FileSystem {
public:
    void storeTicketInformation(Ticket* ticket, Passenger& passenger);
};





template <typename T>
T roundUp(T num, T multiple) {
    return ceil(num / multiple) * multiple; 
}

Passenger::Passenger() {
    name = "";
    age = 0;
    contact = "";
}

int Passenger::getAge() {
    return age;
}

void Passenger::setInfo() {
    try {
        cout << "Enter passenger name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter passenger age: ";
        cin >> age;
        if (age <= 0 || age > 120) {
            throw "Invalid age. Must be between 1 and 120.";
        }

        cout << "Enter passenger contact: ";
        cin >> contact;
        if (contact.size() != 11 || contact.substr(0, 2) != "01") {
            throw "Invalid mobile number. Must start with 01 and be 11 digits.";
        }
    }
    catch (const char *e) {
        cout << "Error: " << e << endl;
        cout << "Please re-enter passenger details correctly.\n";
        setInfo();
    }
}

void Passenger::displayInfo() {
    cout << "Passenger Name: " << name << endl;
    cout << "Passenger Age: " << age << endl;
    cout << "Passenger Contact: " << contact << endl;
}

int Ticket::totalTicketsSold = 0;

Ticket::Ticket(int type, int premium) {
    ticketType = type;
    isPremium = premium;
}

void Ticket::applyDiscount(double percentage) {
    fare -= (int)(fare * percentage / 100.0);
}

void Ticket::applyDiscount(int amount) {
    fare -= amount;
}

void Ticket::checkDiscount(string coupon) {
    if (coupon == "ECE") {
        cout << "You have got 11.11% discount!" << endl;
        applyDiscount((double)11.11);
    } else if (coupon == "first") {
        cout << "First customer get flat 50 taka discount!" << endl;
        applyDiscount(50);
    } else {
        cout << "Invalid coupon code." << endl;
    }
}

void Ticket::selectRoute() {
    int len;
    if (ticketType == 1) {
        ticketID = "BU" + generateTicketID();
        len = 6;
    } else if (ticketType == 2) {
        ticketID = "TR" + generateTicketID();
        len = 4;
    } else if (ticketType == 3) {
        ticketID = "FL" + generateTicketID();
        len = 1;
    } else {
        cout << "Invalid ticket type." << endl;
        return;
    }

    cout << "Select a route:" << endl;
    for (int i = 0; i < len; i++) {
        cout << i + 1 << ". " << routes[i] << endl;
    }

    int routeChoice;
    cout << "Enter your choice (1-" << len << "): ";
    cin >> routeChoice;

    try {
        if (routeChoice < 1 || routeChoice > len) {
            throw "Invalid route selection.";
        }
        selectedRoute = routes[routeChoice - 1];
        selectedDistance = distance[routeChoice - 1];
    }
    catch (const char* e) {
        cout << "Error: " << e << endl;
        cout << "Defaulting to route 1.\n";
        selectedRoute = routes[0];
        selectedDistance = distance[0];
    }

    departureTime = setTime();
}

void Ticket::showTicketInfo() {
    cout << "=========================================================" << endl;
    cout << "Ticket ID: " << ticketID << endl;
    cout << "Selected Route: " << selectedRoute << endl;
    cout << "Ticket Type: " << (ticketType == 1 ? "Bus" : ticketType == 2 ? "Train" : "Flight") << endl;
    cout << "Departure Time: " << departureTime << endl;
    cout << "Is Premium: " << (isPremium ? "Yes" : "No") << endl;

    float addPremiumFare = 1;
    if (isPremium) addPremiumFare = 1.5;
    fare = (calculateFare() * addPremiumFare);

    cout << "Fare: " << roundUp(fare) << endl;

    cout << "Do you have any Coupon Code? (1. Yes  --- 2. No): ";
    int hasCoupon;
    cin >> hasCoupon;
    if (hasCoupon == 1) {
        string couponCode;
        cout << "Enter coupon code: ";
        cin >> couponCode;
        checkDiscount(couponCode);
    }
    if (totalTicketsSold == 0) {
        checkDiscount("first");
    }

    cout << "Final Fare: " << roundUp(fare) << endl;
    cout << "=========================================================" << endl;
    totalTicketsSold++;
}

// -------- BusTicket --------
BusTicket::BusTicket(int premium) : Ticket(1, premium) {}

int BusTicket::calculateFare() {
    return selectedDistance * 3;
}

string BusTicket::setTime() {
    cout << "Select your departure time : " << endl;
    cout << "1. 08:00 AM" << endl;
    cout << "2. 09:00 AM" << endl;
    cout << "3. 12:00 PM" << endl;
    cout << "4. 03:00 PM" << endl;
    cout << "5. 04:00 PM" << endl;
    cout << "6. 07:00 PM" << endl;
    cout << "Enter your choice: ";
    int timeChoice;
    cin >> timeChoice;

    try {
        switch (timeChoice) {
            case 1: return "08:00 AM";
            case 2: return "09:00 AM";
            case 3: return "12:00 PM";
            case 4: return "03:00 PM";
            case 5: return "04:00 PM";
            case 6: return "07:00 PM";
            default: throw "Invalid time selection.";
        }
    }
    catch (const char* e) {
        cout << "Error: " << e << endl;
        cout << "Defaulting to 08:00 AM.\n";
        return "08:00 AM";
    }
}

TrainTicket::TrainTicket(int premium) : Ticket(2, premium) {}

int TrainTicket::calculateFare() {
    return selectedDistance * 2;
}

string TrainTicket::setTime() {
    cout << "Select your departure time : " << endl;
    cout << "1. 08:00 AM" << endl;
    cout << "2. 12:00 PM" << endl;
    cout << "3. 04:00 PM" << endl;
    cout << "Enter your choice: ";
    int timeChoice;
    cin >> timeChoice;

    try {
        switch (timeChoice) {
            case 1: return "08:00 AM";
            case 2: return "12:00 PM";
            case 3: return "04:00 PM";
            default: throw "Invalid time selection.";
        }
    }
    catch (const char* e) {
        cout << "Error: " << e << endl;
        cout << "Defaulting to 08:00 AM.\n";
        return "08:00 AM";
    }
}


FlightTicket::FlightTicket(int premium) : Ticket(3, premium) {}

int FlightTicket::calculateFare() {
    return 5500;
}

string FlightTicket::setTime() {
    cout << "Select your departure time : " << endl;
    cout << "1. 10:00 AM" << endl;
    cout << "2. 08:00 PM" << endl;
    cout << "Enter your choice: ";
    int timeChoice;
    cin >> timeChoice;

    try {
        switch (timeChoice) {
            case 1: return "10:00 AM";
            case 2: return "08:00 PM";
            default: throw "Invalid time selection.";
        }
    }
    catch (const char* e) {
        cout << "Error: " << e << endl;
        cout << "Defaulting to 10:00 AM.\n";
        return "10:00 AM";
    }
}

string generateTicketID() {
    const string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    string result;
    for (int i = 0; i < 5; ++i) {
        result += chars[rand() % chars.size()];
    }
    return result;
}

int isPremium(int ticketChoice) {
    (void)ticketChoice; // unused, kept to preserve original signature/flow
    cout << "Do you want a Premium ticket? (1: Yes, 2: No): ";
    int premiumChoice;
    cin >> premiumChoice;
    if (premiumChoice == 1) {
        return 1; // Premium ticket selected
    }
    return 0; // Regular ticket selected
}


void FileSystem::storeTicketInformation(Ticket* ticket, Passenger& passenger) {
    ofstream fout("buyer_details.txt", ios::app);
    if (!fout) {
        cout << "Error opening file!" << endl;
        return;
    }

    fout << passenger.name << ","
         << passenger.age << ","
         << passenger.contact << ","
         << ticket->ticketID << ","
         << ticket->selectedRoute << ","
         << ticket->departureTime << ","
         << (ticket->isPremium ? "Premium" : "Regular") << ","
         << roundUp(ticket->fare) << "\n";

    fout.close();
    cout << "Ticket verified and saved successfully!" << endl;
}


void displayBuyerDetailsByTicketID(const string &searchTicketID) {
    ifstream fin("buyer_details.txt");
    if (!fin) {
        cout << "No buyer details found.\n";
        return;
    }

    string line;
    bool found = false;
    const int boxWidth = 50;

    while (getline(fin, line)) {
        stringstream ss(line);

        string name, age, contact, ticketID, route, time, type, fare;
        getline(ss, name, ',');
        getline(ss, age, ',');
        getline(ss, contact, ',');
        getline(ss, ticketID, ',');
        getline(ss, route, ',');
        getline(ss, time, ',');
        getline(ss, type, ',');
        getline(ss, fare, ',');

        if (ticketID == searchTicketID) {
            found = true;

            string top    = "+" + string(boxWidth, '-') + "+";
            string bottom = "+" + string(boxWidth, '-') + "+";

            cout << top << "\n";
            cout << "|              BUYER DETAILS               |\n";
            cout << top << "\n";

            cout << "| Name        : " << setw(33) << left << name     << "|\n";
            cout << "| Age         : " << setw(33) << left << age      << "|\n";
            cout << "| Contact     : " << setw(33) << left << contact  << "|\n";
            cout << "| TicketID    : " << setw(33) << left << ticketID << "|\n";
            cout << "| Route       : " << setw(33) << left << route    << "|\n";
            cout << "| Time        : " << setw(33) << left << time     << "|\n";
            cout << "| Ticket Type : " << setw(33) << left << type     << "|\n";
            cout << "| Total Fare  : " << setw(33) << left << fare + string(" BDT") << "|\n";

            cout << bottom << "\n";
            break;
        }
    }

    if (!found)
        cout << "No details found for TicketID: " << searchTicketID << endl;

    fin.close();
}

void buyTicket() {
    Ticket* ticket = nullptr;
    cout << "Which type of ticket you want to buy?" << endl;
    cout << "1. Bus Ticket" << endl;
    cout << "2. Train Ticket" << endl;
    cout << "3. Flight Ticket" << endl;
    cout << "Enter your choice: ";
    int ticketChoice;
    cin >> ticketChoice;

    switch (ticketChoice) {
        case 1:
            cout << "You have selected Bus Ticket." << endl;
            ticket = new BusTicket(isPremium(ticketChoice));
            ticket->selectRoute();
            break;
        case 2:
            cout << "You have selected Train Ticket." << endl;
            ticket = new TrainTicket(isPremium(ticketChoice));
            ticket->selectRoute();
            break;
        case 3:
            cout << "You have selected Flight Ticket." << endl;
            ticket = new FlightTicket(isPremium(ticketChoice));
            ticket->selectRoute();
            break;
        default:
            cout << "Invalid choice." << endl;
            return;
    }

    Passenger passenger;
    passenger.setInfo();

    cout << "=================== Ticket Information ===================" << endl;
    passenger.displayInfo();
    ticket->showTicketInfo();

    FileSystem inspector;
    inspector.storeTicketInformation(ticket, passenger);

    delete ticket;
}


int main() {
    while (1) {
        cout << "1. Buy Ticket" << endl;
        cout << "2. Check Ticket" << endl;
        cout << "To exit enter 0" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            buyTicket();
        } else if (choice == 2) {
            string searchID;
            cout << "Enter TicketID: ";
            cin >> searchID;
            displayBuyerDetailsByTicketID(searchID);
        } else {
            break;
        }
    }
    return 0;
}
