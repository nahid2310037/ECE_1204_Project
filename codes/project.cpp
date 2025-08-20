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
    Buyer(string _name, int _age, string _contact) {
        name = _name;
        age = _age;
        contact = _contact;
    }
    void displayInfo() {
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Contact: " << contact << endl;
    }
    string getName() const {
        return name;
    }
    int getAge() const {
        return age;
    }
    string getContact() const {
        return contact;
    }
};
