#include <bits/stdc++.h>
using namespace std;

static int totalTicketsSold = 0;
string generateTicketID();

template <typename T>
T roundUp(T num, T multiple = 10) {
    return ceil(num / multiple) * multiple; // use ceil for float-safe rounding
}


class Passenger{
private:
    string name;
    int age;
    string contact;
public:
    Passenger(){
        name = "";
        age = 0;
        contact = "";
    };
    int getAge(){
        return age;
    }
    void setInfo(){
        cout << "Enter passenger name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter passenger age: ";
        cin >> age;
        cout << "Enter passenger contact: ";
        cin >> contact;
    };
    void displayInfo(){
        cout << "Passenger Name: " << name << endl;
        cout << "Passenger Age: " << age << endl;
        cout << "Passenger Contact: " << contact << endl;
    };
};

class Ticket {
protected:
    int ticketType; // 1: Bus, 2: Train, 3: Flight
    int isPremium;  // 1: Premium, 0: Regular
    string ticketID;    
    string selectedRoute;
    int selectedDistance;
    string departureTime;
    string routes[6] = {"Rajshahi - Dhaka", "Rajshahi - Khulna" , "Rajshahi - Rangpur", "Rajshahi - Kushtia", "Rajshahi - Barisal", "Rajshahi - Bogura"};
    int distance[6] = {280,250,200,90,300,150};
    int fare;
public:
    Ticket(int type, int premium) {
        ticketType = type;
        isPremium = premium;
    }

    void applyDiscount(double percentage) {
        fare -= (fare * percentage / 100);
    }
    void applyDiscount(int amount) {
        fare -= amount;
    }
    void checkDiscount(string coupon) {
        if(coupon == "ECE"){
            cout<< "You have got 11.1\% discount!" << endl;
            applyDiscount((double)11.1);
        } else if (coupon == "first"){
            cout << "First customer get flat 50 taka discount!" << endl;
            applyDiscount(50);
        } else {
            cout << "Invalid coupon code." << endl;
        }
    }
    virtual int calculateFare() = 0;
    virtual string setTime() = 0;

    void selectRoute() {
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
        if (routeChoice >= 1 && routeChoice <= len) {
            selectedRoute = routes[routeChoice - 1];
            selectedDistance = distance[routeChoice - 1];
        } else {
            cout << "Invalid route selection." << endl;
        }
        departureTime = setTime();
    }
    void showTicketInfo(){
        cout << "=========================================================" << endl;  
        cout << "Ticket ID: " << ticketID << endl;
        cout << "Selected Route: " << selectedRoute << endl;
        cout << "Ticket Type: " << (ticketType == 1 ? "Bus" : ticketType == 2 ? "Train" : "Flight") << endl;
        cout << "Departure Time: " << departureTime << endl;
        cout << "Is Premium: " << (isPremium ? "Yes" : "No") << endl;
        float addPremiumFare = 1;
        if (isPremium) addPremiumFare = 1.5; 
        fare = calculateFare() * addPremiumFare;
        cout << "Fare: " << roundUp(fare) << endl;
        cout<<"Do you have any Coupon Code? (1. Yes / 0. No): ";
        int hasCoupon;
        cin >> hasCoupon;
        if (hasCoupon == 1) {
            string couponCode;
            cout << "Enter coupon code: ";
            cin >> couponCode;
            checkDiscount(couponCode);
        }
        if(totalTicketsSold == 0){
            checkDiscount("first");
        }
        cout << "Final Fare: " << roundUp(fare) << endl;
        cout << "=========================================================" << endl;  
        totalTicketsSold++;
    }
};

class BusTicket: public Ticket {
public:
    BusTicket(int premium) : Ticket(1, premium) {}
    int calculateFare(){
        return selectedDistance * 3;
    }
    string setTime(){
        cout<<"Select your departure time : "<<endl;
        cout<<"1. 08:00 AM"<<endl;
        cout<<"2. 09:00 AM"<<endl;
        cout<<"3. 12:00 PM"<<endl;
        cout<<"4. 03:00 PM"<<endl;
        cout<<"5. 04:00 PM"<<endl;
        cout<<"6. 07:00 PM"<<endl;
        cout<<"Enter your choice: ";
        int timeChoice;
        cin>>timeChoice;
        switch(timeChoice){
            case 1: return "08:00 AM";
            case 2: return "09:00 AM";
            case 3: return "12:00 PM";
            case 4: return "03:00 PM";
            case 5: return "04:00 PM";
            case 6: return "07:00 PM";
            default: return "Invalid Time";
        }
    }

};

class TrainTicket: public Ticket {
public:
    TrainTicket(int premium) : Ticket(2, premium) {}
    int calculateFare(){
        return selectedDistance * 2;
    }
    string setTime(){
        cout<<"Select your departure time : "<<endl;
        cout<<"1. 08:00 AM"<<endl;
        cout<<"2. 12:00 PM"<<endl;
        cout<<"3. 04:00 PM"<<endl;
        cout<<"Enter your choice: ";
        int timeChoice;
        cin>>timeChoice;
        switch(timeChoice){
            case 1: return "08:00 AM";
            case 2: return "12:00 PM";
            case 3: return "04:00 PM";
            default: return "Invalid Time";
        }
    }
};

class FlightTicket: public Ticket {
public:
    FlightTicket(int premium) : Ticket(3, premium) {}
    int calculateFare(){
        return 5500;
    }
    string setTime(){
        cout<<"Select your departure time : "<<endl;
        cout<<"1. 10:00 AM"<<endl;
        cout<<"2. 08:00 PM"<<endl;
        cout<<"Enter your choice: ";
        int timeChoice;
        cin>>timeChoice;
        switch(timeChoice){
            case 1: return "10:00 AM";
            case 2: return "08:00 PM";
            default: return "Invalid Time";
        }
    }
};




string generateTicketID() {
    const string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    string result;
    for (int i = 0; i < 5; ++i) {
        result += chars[rand() % chars.size()];
    }
    return result;
}

int isPremium(int ticketChoice){
    cout<<"Do you want a Premium ticket? (1: Yes, 0: No): ";
    int premiumChoice;
    cin>>premiumChoice;
    if(premiumChoice == 1){
        return 1; // Premium ticket selected
    }
    return 0; // Regular ticket selected   
}

void buyTicket(){
    Ticket *ticket = nullptr;
    cout<<"Which type of ticket you want to buy?"<<endl;
    cout<<"1. Bus Ticket"<<endl;
    cout<<"2. Train Ticket"<<endl;
    cout<<"3. Flight Ticket"<<endl;
    cout<<"Enter your choice: ";
    int ticketChoice;
    cin>>ticketChoice;
    switch(ticketChoice){
        case 1:
            cout<<"You have selected Bus Ticket."<<endl;
            ticket = new BusTicket(isPremium(ticketChoice));
            ticket->selectRoute();
            break;
        case 2:
            cout<<"You have selected Train Ticket."<<endl;
            ticket = new TrainTicket(isPremium(ticketChoice));
            ticket->selectRoute();
            break;
        case 3:
            cout<<"You have selected Flight Ticket."<<endl;
            ticket = new FlightTicket(isPremium(ticketChoice));
            ticket->selectRoute();
            break;
        default:
            cout<<"Invalid choice."<<endl;
            break;
    }
    Passenger passenger;
    passenger.setInfo();
    cout<<"=================== Ticket Information ==================="<<endl;
    passenger.displayInfo();
    ticket->showTicketInfo();
}

int main(){
    while(1){
        cout<<"1. Buy Ticket"<<endl;
        cout<<"2. Check Ticket"<<endl;
        cout<<"To exit enter 0"<<endl;
        cout<<"Enter your choice: ";
        int choice;
        cin>>choice;
        if(choice == 1) {
            buyTicket();
        } else if(choice == 2) {
            // Check Ticket functionality
        } else {
            break;
        }
    }

    return 0;
}