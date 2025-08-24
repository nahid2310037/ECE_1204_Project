// Including standard libraries for I/O, file handling, and string manipulation
#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
using namespace std;

// Function declarations for ticket generation and management
string generateTicketID(); // Generates unique ticket ID
int isPremium(int ticketChoice); // Checks if ticket is premium
void buyTicket(); // Handles ticket purchase process
void displayBuyerDetailsByTicketID(const string &searchTicketID); // Displays buyer details by ticket ID

// Template function to round up numbers
template <typename T>
T roundUp(T num, T multiple = 5); // Rounds up number to nearest multiple

// Passenger class to store passenger information
class Passenger {
private:
    string name; // Passenger's name
    int age; // Passenger's age
    string contact; // Passenger's contact number

public:
    Passenger(); // Default constructor
    int getAge(); // Getter for age
    void setInfo(); // Sets passenger information
    void displayInfo(); // Displays passenger information
    string getName() const { return name; }; // Getter for name

    friend class FileSystem; // Allows FileSystem to access private fields
};

// Abstract Ticket class for different ticket types
class Ticket {
protected:
    static int totalTicketsSold; // Tracks total tickets sold
    int ticketType; // 1: Bus, 2: Train, 3: Flight
    int isPremium; // 1: Premium, 0: Regular
    string ticketID; // Unique ticket identifier
    string selectedRoute; // Selected travel route
    int selectedDistance; // Distance of selected route
    string departureTime; // Departure time
    string routes[6] = {"Rajshahi - Dhaka", "Rajshahi - Khulna", "Rajshahi - Rangpur",
                        "Rajshahi - Kushtia", "Rajshahi - Barisal", "Rajshahi - Bogura"}; // Available routes
    int distance[6] = {280, 250, 200, 90, 300, 150}; // Distances for routes
    int fare; // Ticket fare

public:
    Ticket(int type, int premium); // Constructor with type and premium status
    void applyDiscount(double percentage); // Applies percentage discount
    void applyDiscount(int amount); // Applies fixed amount discount
    void checkDiscount(string coupon); // Checks and applies coupon code
    virtual int calculateFare() = 0; // Pure virtual function for fare calculation
    virtual string setTime() = 0; // Pure virtual function for setting time
    void selectRoute(); // Allows user to select route
    void showTicketInfo(); // Displays ticket information
    int getFare() const { return fare; } // Getter for fare

    friend class FileSystem; // Allows FileSystem to access protected fields
};

// BusTicket class derived from Ticket
class BusTicket : public Ticket {
public:
    BusTicket(int premium); // Constructor
    int calculateFare() override; // Calculates fare for bus
    string setTime() override; // Sets departure time for bus
};

// TrainTicket class derived from Ticket
class TrainTicket : public Ticket {
public:
    TrainTicket(int premium); // Constructor
    int calculateFare() override; // Calculates fare for train
    string setTime() override; // Sets departure time for train
};

// FlightTicket class derived from Ticket
class FlightTicket : public Ticket {
public:
    FlightTicket(int premium); // Constructor
    int calculateFare() override; // Calculates fare for flight
    string setTime() override; // Sets departure time for flight
};

// FileSystem class for handling file operations
class FileSystem {
public:
    void storeTicketInformation(Ticket* ticket, Passenger& passenger); // Stores ticket and passenger info
};

// Implementation of roundUp template function
template <typename T>
T roundUp(T num, T multiple) {
    return ceil(num / multiple) * multiple; // Rounds up to nearest multiple
}

// Passenger class implementation
Passenger::Passenger() {
    name = ""; // Initializes name
    age = 0; // Initializes age
    contact = ""; // Initializes contact
}

int Passenger::getAge() {
    return age; // Returns passenger's age
}

void Passenger::setInfo() {
    try {
        cout << "Enter passenger name: ";
        cin.ignore(); // Clears input buffer
        getline(cin, name); // Gets full name

        cout << "Enter passenger age: ";
        cin >> age; // Gets age
        if (age <= 0 || age > 120) {
            throw "Invalid age. Must be between 1 and 120."; // Validates age
        }

        cout << "Enter passenger contact: ";
        cin >> contact; // Gets contact number
        if (contact.size() != 11 || contact.substr(0, 2) != "01") {
            throw "Invalid mobile number. Must start with 01 and be 11 digits."; // Validates contact
        }
    }
    catch (const char *e) {
        cout << "Error: " << e << endl;
        cout << "Please re-enter passenger details correctly.\n";
        setInfo(); // Recursively prompts for valid input
    }
}

void Passenger::displayInfo() {
    cout << "Passenger Name: " << name << endl;
    cout << "Passenger Age: " << age << endl;
    cout << "Passenger Contact: " << contact << endl; // Displays passenger details
}

// Ticket class static member initialization
int Ticket::totalTicketsSold = 0;

Ticket::Ticket(int type, int premium) {
    ticketType = type; // Sets ticket type
    isPremium = premium; // Sets premium status
}

void Ticket::applyDiscount(double percentage) {
    fare -= (int)(fare * percentage / 100.0); // Applies percentage discount
}

void Ticket::applyDiscount(int amount) {
    fare -= amount; // Applies fixed amount discount
}

void Ticket::checkDiscount(string coupon) {
    if (coupon == "ECE") {
        cout << "You have got 11.11% discount!" << endl;
        applyDiscount((double)11.11); // Applies ECE coupon discount
    } else if (coupon == "first") {
        cout << "First customer get flat 50 taka discount!" << endl;
        applyDiscount(50); // Applies first customer discount
    } else {
        cout << "Invalid coupon code." << endl; // Handles invalid coupon
    }
}

void Ticket::selectRoute() {
    int len;
    if (ticketType == 1) {
        ticketID = "BU" + generateTicketID(); // Generates bus ticket ID
        len = 6; // Sets number of routes for bus
    } else if (ticketType == 2) {
        ticketID = "TR" + generateTicketID(); // Generates train ticket ID
        len = 4; // Sets number of routes for train
    } else if (ticketType == 3) {
        ticketID = "FL" + generateTicketID(); // Generates flight ticket ID
        len = 1; // Sets number of routes for flight
    } else {
        cout << "Invalid ticket type." << endl;
        return; // Handles invalid ticket type
    }

    cout << "\nSelect a route:" << endl;
    for (int i = 0; i < len; i++) {
        cout << i + 1 << ". " << routes[i] << endl; // Displays available routes
    }

    int routeChoice;
    cout << "Enter your choice (1-" << len << "): ";
    cin >> routeChoice; // Gets route choice

    try {
        if (routeChoice < 1 || routeChoice > len) {
            throw "Invalid route selection."; // Validates route choice
        }
        selectedRoute = routes[routeChoice - 1]; // Sets selected route
        selectedDistance = distance[routeChoice - 1]; // Sets route distance
    }
    catch (const char* e) {
        cout << "Error: " << e << endl;
        cout << "Defaulting to route 1.\n";
        selectedRoute = routes[0]; // Defaults to first route
        selectedDistance = distance[0]; // Defaults to first route distance
    }
    cout << endl;
    departureTime = setTime(); // Sets departure time
    cout << endl;
}

void Ticket::showTicketInfo() {
    cout << "==========================================================" << endl;
    cout << "Ticket ID: " << ticketID << endl;
    cout << "Selected Route: " << selectedRoute << endl;
    cout << "Ticket Type: " << (ticketType == 1 ? "Bus" : ticketType == 2 ? "Train" : "Flight") << endl;
    cout << "Departure Time: " << departureTime << endl;
    cout << "Is Premium: " << (isPremium ? "Yes" : "No") << endl; // Displays ticket details

    float addPremiumFare = 1;
    if (isPremium) addPremiumFare = 1.5; // Applies premium fare multiplier
    fare = (calculateFare() * addPremiumFare); // Calculates total fare
    fare = roundUp(fare-5); // Rounds up fare 
    cout << "Fare: " << fare << endl; // Displays rounded fare

    cout << "\nDo you have any Coupon Code? (1. Yes  --- 2. No): ";
    int hasCoupon;
    cin >> hasCoupon; // Checks for coupon
    if (hasCoupon == 1) {
        string couponCode;
        cout << "Enter coupon code: ";
        cin >> couponCode; // Gets coupon code
        checkDiscount(couponCode); // Applies discount if valid
    }
    if (totalTicketsSold == 0) {
        checkDiscount("first"); // Applies first customer discount
    }
    fare = roundUp(fare); // Rounds up final fare
    cout << "Final Fare: " << fare << endl; // Displays final fare
    cout << "==========================================================\n" << endl;
    totalTicketsSold++; // Increments ticket counter
}

// BusTicket class implementation
BusTicket::BusTicket(int premium) : Ticket(1, premium) {} // Constructor

int BusTicket::calculateFare() {
    return selectedDistance * 3; // Calculates bus fare
}

string BusTicket::setTime() {
    cout << "Select your departure time (1-6): " << endl;
    cout << "1. 08:00 AM" << endl;
    cout << "2. 09:00 AM" << endl;
    cout << "3. 12:00 PM" << endl;
    cout << "4. 03:00 PM" << endl;
    cout << "5. 04:00 PM" << endl;
    cout << "6. 07:00 PM" << endl;
    cout << "Enter your choice: ";
    int timeChoice;
    cin >> timeChoice; // Gets time choice

    try {
        switch (timeChoice) {
            case 1: return "08:00 AM";
            case 2: return "09:00 AM";
            case 3: return "12:00 PM";
            case 4: return "03:00 PM";
            case 5: return "04:00 PM";
            case 6: return "07:00 PM";
            default: throw "Invalid time selection."; // Validates time choice
        }
    }
    catch (const char* e) {
        cout << "Error: " << e << endl;
        cout << "Defaulting to 08:00 AM.\n";
        return "08:00 AM"; // Defaults to 08:00 AM
    }
}

// TrainTicket class implementation
TrainTicket::TrainTicket(int premium) : Ticket(2, premium) {} // Constructor

int TrainTicket::calculateFare() {
    return selectedDistance * 2; // Calculates train fare
}

string TrainTicket::setTime() {
    cout << "Select your departure time : (1-3)" << endl;
    cout << "1. 08:00 AM" << endl;
    cout << "2. 12:00 PM" << endl;
    cout << "3. 04:00 PM" << endl;
    cout << "Enter your choice: ";
    int timeChoice;
    cin >> timeChoice; // Gets time choice

    try {
        switch (timeChoice) {
            case 1: return "08:00 AM";
            case 2: return "12:00 PM";
            case 3: return "04:00 PM";
            default: throw "Invalid time selection."; // Validates time choice
        }
    }
    catch (const char* e) {
        cout << "Error: " << e << endl;
        cout << "Defaulting to 08:00 AM.\n";
        return "08:00 AM"; // Defaults to 08:00 AM
    }
}

// FlightTicket class implementation
FlightTicket::FlightTicket(int premium) : Ticket(3, premium) {} // Constructor

int FlightTicket::calculateFare() {
    return 5500; // Fixed fare for flight
}

string FlightTicket::setTime() {
    cout << "Select your departure time : (1-2)" << endl;
    cout << "1. 10:00 AM" << endl;
    cout << "2. 08:00 PM" << endl;
    cout << "Enter your choice: ";
    int timeChoice;
    cin >> timeChoice; // Gets time choice

    try {
        switch (timeChoice) {
            case 1: return "10:00 AM";
            case 2: return "08:00 PM";
            default: throw "Invalid time selection."; // Validates time choice
        }
    }
    catch (const char* e) {
        cout << "Error: " << e << endl;
        cout << "Defaulting to 10:00 AM.\n";
        return "10:00 AM"; // Defaults to 10:00 AM
    }
}

// Generates random ticket ID
string generateTicketID() {
    const string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    string result;
    for (int i = 0; i < 5; ++i) {
        result += chars[rand() % chars.size()]; // Builds 5-character ID
    }
    return result;
}

// Checks if user wants premium ticket
int isPremium(int ticketChoice) {
    (void)ticketChoice; // Unused parameter
    cout << "Do you want a Premium ticket? (1: Yes, 2: No): ";
    int premiumChoice;
    cin >> premiumChoice; // Gets premium choice
    if (premiumChoice == 1) {
        return 1; // Premium ticket
    }
    return 0; // Regular ticket
}

// Stores ticket and passenger info in file
void FileSystem::storeTicketInformation(Ticket* ticket, Passenger& passenger) {
    ofstream fout("buyer_details.txt", ios::app); // Opens file in append mode
    if (!fout) {
        cout << "Error opening file!" << endl;
        return; // Handles file open error
    }

    fout << passenger.name << ","
         << passenger.age << ","
         << passenger.contact << ","
         << ticket->ticketID << ","
         << ticket->selectedRoute << ","
         << ticket->departureTime << ","
         << (ticket->isPremium ? "Premium" : "Regular") << ","
         << roundUp(ticket->fare) << "\n"; // Writes ticket info to file

    fout.close(); // Closes file
    cout << "Ticket verified and saved successfully!\n" << endl;
}

// Displays buyer details by ticket ID
void displayBuyerDetailsByTicketID(const string &searchTicketID) {
    ifstream fin("buyer_details.txt"); // Opens file for reading
    if (!fin) {
        cout << "No buyer details found.\n";
        return; // Handles file open error
    }

    string line;
    bool found = false;
    const int boxWidth = 50; // Box width for display

    while (getline(fin, line)) {
        stringstream ss(line); // Parses line

        string name, age, contact, ticketID, route, time, type, fare;
        getline(ss, name, ','); // Gets name
        getline(ss, age, ','); // Gets age
        getline(ss, contact, ','); // Gets contact
        getline(ss, ticketID, ','); // Gets ticket ID
        getline(ss, route, ','); // Gets route
        getline(ss, time, ','); // Gets time
        getline(ss, type, ','); // Gets ticket type
        getline(ss, fare, ','); // Gets fare

        if (ticketID == searchTicketID) {
            found = true;

            string top = "=================================================="; // Top border
            string bottom = "==================================================\n"; // Bottom border
            cout <<  endl;
            cout << top << "\n";
            cout << "|                  BUYER DETAILS                 |\n"; // Header
            cout << top << "\n";

            cout << "| Name        : " << setw(33) << left << name << "|\n";
            cout << "| Age         : " << setw(33) << left << age << "|\n";
            cout << "| Contact     : " << setw(33) << left << contact << "|\n";
            cout << "| TicketID    : " << setw(33) << left << ticketID << "|\n";
            cout << "| Route       : " << setw(33) << left << route << "|\n";
            cout << "| Time        : " << setw(33) << left << time << "|\n";
            cout << "| Ticket Type : " << setw(33) << left << type << "|\n";
            cout << "| Total Fare  : " << setw(33) << left << fare + string(" BDT") << "|\n";

            cout << bottom << "\n";
            break; // Exits loop after finding ticket
        }
    }

    if (!found)
        cout << "No details found for TicketID: " << searchTicketID << endl; // Handles ticket not found

    fin.close(); // Closes file
}

// Payment class hierarchy for handling payments
class Payment {
protected:
    double amount; // Payment amount
public:
    Payment(double amt = 0.0) : amount(amt) {} // Constructor
    void processPayment(){
        cout << " Processing Payment of " << amount << " BDT..." << endl;
        cout<< " Transaction id: " << getTransactionID() << endl;

    } 
    string getTransactionID() const {
        return "TXN" + to_string(rand() % 10000); // Generates a random transaction ID
    }
    virtual ~Payment() {} // Virtual destructor
};

// Bkash payment class
class Bkash : virtual public Payment {
public:
    Bkash(double amt = 0.0) : Payment(amt) {} // Constructor
    void startTransaction() {
        cout << " Starting Bkash Transaction..." << endl;
        cout << " Bkash Transaction Completed!" << endl;
    }
};

// Nagad payment class
class Nagad : virtual public Payment {
public:
    Nagad(double amt = 0.0) : Payment(amt) {} // Constructor
    void startTransaction() {
        cout << " Starting Nagad Transaction..." << endl;
        cout << " Nagad Transaction Completed!" << endl;
    }
};

// Bank payment class
class Bank : virtual public Payment {
public:
    Bank(double amt = 0.0) : Payment(amt) {} // Constructor
    void startTransaction() {
        cout << " Starting Bank Transaction..." << endl;
        cout << " Bank Transaction Completed!" << endl;
    }
};

// PassengerPayment class to handle payment methods
class PassengerPayment : public Bkash, public Nagad, public Bank {
    string passengerName; // Passenger's name
public:
    PassengerPayment(string name, double amt)
        : Payment(amt), Bkash(0), Nagad(0), Bank(0), passengerName(name) {} // Constructor

    void makePayment() {
        cout << "\n=========== PAYMENT GATEWAY ===========" << endl;
        cout << "Passenger: " << passengerName << endl;
        cout << "Total Amount: " << amount << " BDT" << endl;
        cout << "Choose Payment Method:" << endl;
        cout << "1. Bkash\n2. Nagad\n3. Bank" << endl;
        cout << "Enter choice: ";
        int choice;
        cin >> choice; // Gets payment method choice

        cout << "\n---------------------------------------" << endl;
        switch (choice) {
            case 1: Bkash::processPayment(); Bkash::startTransaction(); // Processes Bkash payment
            case 2: Nagad::processPayment(); Nagad::startTransaction(); break; // Processes Nagad payment
            case 3: Bank::processPayment(); Bank::startTransaction(); break; // Processes Bank payment
            default: cout << " Invalid choice!" << endl; return; // Handles invalid choice
        }
        cout << " Payment Completed Successfully!" << endl;
        cout << "=======================================\n" << endl;
    }
};

// Handles ticket purchase process
void buyTicket() {
    Ticket* ticket = nullptr; // Pointer for ticket object
    cout << "\nWhich type of ticket you want to buy?" << endl;
    cout << "1. Bus Ticket" << endl;
    cout << "2. Train Ticket" << endl;
    cout << "3. Flight Ticket" << endl;
    cout << "Enter your choice: ";
    int ticketChoice;
    cin >> ticketChoice; // Gets ticket type choice

    switch (ticketChoice) {
        case 1:
            cout << "You have selected Bus Ticket.\n" << endl;
            ticket = new BusTicket(isPremium(ticketChoice)); // Creates bus ticket
            ticket->selectRoute(); // Selects route
            break;
        case 2:
            cout << "You have selected Train Ticket.\n" << endl;
            ticket = new TrainTicket(isPremium(ticketChoice)); // Creates train ticket
            ticket->selectRoute(); // Selects route
            break;
        case 3:
            cout << "You have selected Flight Ticket.\n" << endl;
            ticket = new FlightTicket(isPremium(ticketChoice)); // Creates flight ticket
            ticket->selectRoute(); // Selects route
            break;
        default:
            cout << "Invalid choice." << endl;
            return; // Handles invalid choice
    }

    Passenger passenger; // Creates passenger object
    passenger.setInfo(); // Sets passenger info

    cout << "\n=================== Ticket Information ===================" << endl;
    passenger.displayInfo(); // Displays passenger info
    ticket->showTicketInfo(); // Displays ticket info
    PassengerPayment payment(passenger.getName(), ticket->getFare()); // Creates payment object

    payment.makePayment(); // Processes payment

    FileSystem inspector; // Creates FileSystem object
    inspector.storeTicketInformation(ticket, passenger); // Stores ticket info

    delete ticket; // Frees ticket memory
}

// Main function with menu-driven interface
int main() {
    while (1) {
        cout << "1. Buy Ticket" << endl;
        cout << "2. Check Ticket" << endl;
        cout << "To exit enter 0" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice; // Gets user choice

        if (choice == 1) {
            generateTicketID(); //To intialize randomness
            buyTicket(); // Calls buyTicket function
        } else if (choice == 2) {
            string searchID;
            cout << "Enter TicketID: ";
            cin >> searchID; // Gets ticket ID to search
            displayBuyerDetailsByTicketID(searchID); // Displays ticket details
        } else {
            break; // Exits loop
        }
    }
    return 0; // Exits program
}