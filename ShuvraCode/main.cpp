#include <bits/stdc++.h>
#include <windows.h>
#include <string>
#include <sstream>
#include <locale>
#include <codecvt>
using namespace std;

// ===== Buyer Class =====
class Buyer {
    string name;
    int age;
    string contact;
public:
    Buyer();
    void displayInfo();
    void setInfo();
    int getAge();
    friend class TicketInspector;
};

// ===== Diamond Services =====
class Service {
protected:
    set<string> services; 
public:
    Service() { services.clear(); }
    void addService(const string& s) { services.insert(s); }
    virtual void displayServices() const {
        if(services.empty()) { cout << "No extra services selected.\n"; return; }
        cout << "Extra Services: ";
        for(auto &s: services) cout << s << " ";
        cout << endl;
    }
    double calculateExtraCost() const {
        double cost = 0;
        for(auto &s: services){
            if(s=="AC Seat") cost+=200;
            else if(s=="Food Package") cost+=100;
            else if(s=="WiFi Access") cost+=50;
            else if(s=="Lounge Access") cost+=150;
        }
        return cost;
    }
};

class ACService : virtual public Service {
public:
    void selectAC() { addService("AC Seat"); }
};
class FoodService : virtual public Service {
public:
    void selectFood() { addService("Food Package"); }
};
class WiFiService : virtual public Service {
public:
    void selectWiFi() { addService("WiFi Access"); }
};
class LoungeService : virtual public Service {
public:
    void selectLounge() { addService("Lounge Access"); }
};

class ExtraServiceTicket : public ACService, public FoodService, public WiFiService, public LoungeService {
public:
    void selectAllServices() {
        int choice;
        cout << "Select extra services (0 to finish):\n1. AC Seat\n2. Food Package\n3. WiFi Access\n4. Lounge Access\n";
        while(true){
            cout << "Choice: "; cin >> choice;
            if(choice==0) break;
            switch(choice){
                case 1: selectAC(); break;
                case 2: selectFood(); break;
                case 3: selectWiFi(); break;
                case 4: selectLounge(); break;
                default: cout << "Invalid choice.\n"; break;
            }
        }
    }
};

// ===== Ticket Class =====
class Ticket {
protected:
    string ticketID, selectedRoute, departureTime;
    double baseFair, finalFare;
    Buyer buyer;
    ExtraServiceTicket extraServices;
public:
    Ticket(string _ticketID);
    virtual double calculateFair() = 0;
    int returnFair(string str[], int fair[], int len);
    virtual void setTime();
    virtual void displayTicketInfo();
    void setTicketInfo();
    void addExtraServices();
    friend class TicketInspector;
};

// ===== Generic Discount =====
template <typename T>
T applyDiscount(T price, T percent) { return price - (price*percent/100); }

// ===== TicketInspector =====
class TicketInspector {
public:
    void verifyTicket(const Ticket &t) {
        // Save buyer details to file
        ofstream fout("buyer_details.txt", ios::app);
        if(fout.is_open()) {
            fout << t.buyer.name << "," 
                 << t.buyer.age << "," 
                 << t.buyer.contact << "," 
                 << t.ticketID << "," 
                 << t.selectedRoute << "," 
                 << t.departureTime << "," 
                 << t.extraServices.calculateExtraCost() << "," 
                 << t.finalFare << "\n";
            fout.close();
        }

        // Output confirmation
        cout << "\n======= Ticket Confirmation =======\n";
        cout << "Route / Movie: " << t.selectedRoute << endl;
        cout << "Time: " << t.departureTime << endl;
        t.extraServices.displayServices();
        cout << "Extra Services Cost: " << t.extraServices.calculateExtraCost() << " BDT\n";
        cout << "Total Fare: " << t.finalFare << " BDT\n";
        cout << "==================================\n";
    }
};

// ===== BusTicket =====
class BusTicket : public Ticket {
    string routes[5] = {"Rajshahi-Dhaka","Rajshahi-Kushtia","Rajshahi-Barishal","Rajshahi-Rangpur","Rajshahi-Natore"};
    int fair[5] = {500,90,450,200,40};
public:
    BusTicket(string _ticketID);
    double calculateFair() override;
};

// ===== TrainTicket =====
class TrainTicket : public Ticket {
    string routes[5] = {"Rajshahi-Dhaka","Rajshahi-Kushtia","Rajshahi-Bogura","Rajshahi-Rangpur","Rajshahi-Natore"};
    int fair[5] = {500,90,370,200,40};
public:
    TrainTicket(string _ticketID);
    double calculateFair() override;
    void setTime() override;
};

// ===== MovieTicket =====
class MovieTicket : public Ticket {
    string movies[5] = {"Movie A","Movie B","Movie C","Movie D","Movie E"};
    int fair[5] = {100,70,90,250,150};
public:
    MovieTicket(string _ticketID);
    void setTime() override;
    void displayTicketInfo() override;
    double calculateFair() override;
};

// ===== Random Ticket ID =====
string randStr() {
    const string chars="ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    string result;
    for(int i=0; i<5; i++) 
        result += chars[rand() % chars.size()];
    return result;
}

// ===== Buyer Methods =====
Buyer::Buyer(){ name=""; age=0; contact=""; }
void Buyer::displayInfo(){ cout<<"Name: "<<name<<"\nAge: "<<age<<"\nContact: "<<contact<<endl; }
void Buyer::setInfo(){ cout<<"Enter buyer information:\nName: "; getchar(); getline(cin,name); cout<<"Age: "; cin>>age; cout<<"Contact: "; cin>>contact; }
int Buyer::getAge(){ return age; }

// ===== Ticket Methods =====
Ticket::Ticket(string _ticketID){ ticketID=_ticketID; }
int Ticket::returnFair(string str[], int fair[], int len){
    int routeIndex;
    for(int i=0;i<len;i++)
        cout << i+1 << ". " << str[i] << " - Fare: " << fair[i]+baseFair << " BDT" << endl;
    cout<<"--------------------------------\n";
    cout << "Press 0 to Exit\nSelect (1-" << len << "): "; cin>>routeIndex;
    if(routeIndex==0){ cout<<"Exiting...\n"; exit(0); }
    if(routeIndex<1||routeIndex>len){ cout<<"Invalid selection.\n"; return 0; }
    return routeIndex-1;
}

void Ticket::setTime(){
    cout << "Select departure time: "<<endl;
    cout<<"1. 8:15 AM\n2. 10:15 AM\n3. 12:15 PM\n4. 2:15 PM\n5. 4:15 PM\n";
    cout<<"Enter choice (1-5): "; int choice; cin>>choice;
    switch(choice){
        case 1: departureTime="8:15 AM"; break;
        case 2: departureTime="10:15 AM"; break;
        case 3: departureTime="12:15 PM"; break;
        case 4: departureTime="2:15 PM"; break;
        case 5: departureTime="4:15 PM"; break;
        default: cout<<"Invalid choice.\n"; break;
    }
}

void Ticket::addExtraServices(){
    cout<<"Do you want extra services? 1. Yes 0. No: "; int ch; cin>>ch;
    if(ch==1) extraServices.selectAllServices();
}

void Ticket::setTicketInfo(){
    finalFare = calculateFair();
    setTime();
    buyer.setInfo();
    addExtraServices();
    finalFare += extraServices.calculateExtraCost();
    if(buyer.getAge()>60) finalFare=applyDiscount(finalFare,20.0);
}

void Ticket::displayTicketInfo(){
    cout<<"==================================================\n";
    cout<<"Ticket purchase complete\n";
    cout<<"==================================================\n";
    buyer.displayInfo();
    cout<<"Ticket ID: "<<ticketID<<endl;
    cout<<"Selected Route / Movie: "<<selectedRoute<<endl;
    cout<<"Time: "<<departureTime<<endl;
    extraServices.displayServices();
    cout<<"Total Fare: "<<finalFare<<" BDT\n";
}

// ===== BusTicket Methods =====
BusTicket::BusTicket(string _ticketID):Ticket(_ticketID){ baseFair=250; }
double BusTicket::calculateFair(){
    cout<<"Available Routes:\n";
    int ind = returnFair(routes,fair,5);
    selectedRoute = routes[ind];
    return fair[ind]+baseFair;
}

// ===== TrainTicket Methods =====
TrainTicket::TrainTicket(string _ticketID):Ticket(_ticketID){ baseFair=60; }
double TrainTicket::calculateFair(){
    cout<<"Available Routes:\n";
    int ind = returnFair(routes,fair,5);
    selectedRoute = routes[ind];
    return fair[ind]+baseFair;
}
void TrainTicket::setTime(){
    cout<<"Select departure time:\n1. 8:00 AM\n2. 12:00 PM\n3. 4:00 PM\nEnter choice (1-3): ";
    int choice; cin>>choice;
    switch(choice){
        case 1: departureTime="8:00 AM"; break;
        case 2: departureTime="12:00 PM"; break;
        case 3: departureTime="4:00 PM"; break;
        default: cout<<"Invalid choice.\n"; break;
    }
}

// ===== MovieTicket Methods =====
MovieTicket::MovieTicket(string _ticketID):Ticket(_ticketID){ baseFair=100; }
void MovieTicket::setTime(){
    cout<<"Select show time:\n1. 9:00 AM\n2. 12:00 PM\n3. 3:00 PM\n4. 6:00 PM\n5. 9:00 PM\nEnter choice (1-5): ";
    int choice; cin>>choice;
    switch(choice){
        case 1: departureTime="9:00 AM"; break;
        case 2: departureTime="12:00 PM"; break;
        case 3: departureTime="3:00 PM"; break;
        case 4: departureTime="6:00 PM"; break;
        case 5: departureTime="9:00 PM"; break;
        default: cout<<"Invalid choice.\n"; break;
    }
}
void MovieTicket::displayTicketInfo(){
    cout<<"==================================================\n";
    cout<<"Ticket purchase complete\n";
    cout<<"==================================================\n";
    buyer.displayInfo();
    cout<<"Ticket ID: "<<ticketID<<endl;
    cout<<"Selected Movie: "<<selectedRoute<<endl;
    cout<<"Show Time: "<<departureTime<<endl;
    extraServices.displayServices();
    cout<<"Total Fare: "<<finalFare<<" BDT\n";
}
double MovieTicket::calculateFair(){
    cout<<"Available Movies:\n";
    int ind = returnFair(movies,fair,5);
    selectedRoute = movies[ind];
    return fair[ind]+baseFair;
}




void displayBuyerDetailsByTicketID(const string &searchTicketID) {
    ifstream fin("buyer_details.txt");
    if(!fin) { 
        cout << "No buyer details found.\n"; 
        return; 
    }

    string line;
    bool found = false;
    const int boxWidth = 50;   // বক্সের ভেতরের প্রস্থ

    while(getline(fin,line)) {
        stringstream ss(line);
        string name, age, contact, ticketID, route, time, extra, total;
        getline(ss,name,',');
         getline(ss,age,',');
          getline(ss,contact,',');
        getline(ss,ticketID,','); 
        getline(ss,route,','); getline(ss,time,',');
        getline(ss,extra,','); getline(ss,total,',');

        if(ticketID == searchTicketID) {
            found = true;

            string top    = "+" + string(boxWidth, '-') + "+";
            string bottom = "+" + string(boxWidth, '-') + "+";

            cout << top << "\n";
            cout << "|              BUYER DETAILS               |\n";
            cout << top << "\n";

            cout << "| Name        : " << setw(33) << left << name    << "|\n";
            cout << "| Age         : " << setw(33) << left << age     << "|\n";
            cout << "| Contact     : " << setw(33) << left << contact << "|\n";
            cout << "| TicketID    : " << setw(33) << left << ticketID<< "|\n";
            cout << "| Route/Movie : " << setw(33) << left << route   << "|\n";
            cout << "| Time        : " << setw(33) << left << time    << "|\n";
            cout << "| Extra Cost  : " << setw(33) << left << extra + " BDT" << "|\n";
            cout << "| Total Fare  : " << setw(33) << left << total + " BDT" << "|\n";

            cout << bottom << "\n";
            break;
        }
    }

    if(!found) cout << "No details found for TicketID: " << searchTicketID << endl;
    fin.close();
}





// ===== Main =====
int main(){
    srand(time(0)); 
    cout<<"Select ticket type:\n1. Bus Ticket\n2. Train Ticket\n3. Movie Ticket\nEnter choice (1-3): "; 
    int choice; cin>>choice;
    string ticketID;

    switch(choice){
        case 1:{
            ticketID="BU"+randStr();
            BusTicket bus(ticketID);
            bus.setTicketInfo();
            bus.displayTicketInfo();
            TicketInspector inspector; inspector.verifyTicket(bus);
            break;
        }
        case 2:{
            ticketID="TR"+randStr();
            TrainTicket train(ticketID);
            train.setTicketInfo();
            train.displayTicketInfo();
            TicketInspector inspector; inspector.verifyTicket(train);
            break;
        }
        case 3:{
            ticketID="MV"+randStr();
            MovieTicket movie(ticketID);
            movie.setTicketInfo();
            movie.displayTicketInfo();
            TicketInspector inspector; inspector.verifyTicket(movie);
            break;
        }
        default: cout<<"Invalid choice.\n"; break;
    }
   cout << "\nDo you want to view buyer details by TicketID? 1.Yes 0.No: "; 
   int view; cin >> view;
    if(view==1) {
    string searchID;
    cout << "Enter TicketID: "; 
    cin >> searchID;
    displayBuyerDetailsByTicketID(searchID);
}

    return 0;
}
