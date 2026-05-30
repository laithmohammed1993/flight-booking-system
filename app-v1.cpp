#include <iostream>
#include <string>
using namespace std;

// Passenger Class
class Passenger {
private:
    string name;
    int passportNumber;
    string destination;

public:
    Passenger();

    // setters & getters
    void setData(string n, int p, string d);
    string getName();
    int getPassport();
    string getDestination();
};

Passenger::Passenger() {
    name = "";
    passportNumber = 0;
    destination = "";
}

void Passenger::setData(string n, int p, string d) {
    name = n;
    passportNumber = p;
    destination = d;
}

string Passenger::getName() {
    return name;
}

int Passenger::getPassport() {
    return passportNumber;
}

string Passenger::getDestination() {
    return destination;
}


// Flight Class
class Flight {
private:
    string flightNumber;
    string status;

public:
    Flight();

    void setData(string f, string s);
    string getFlightNumber();
    string getStatus();
};

Flight::Flight() {
    flightNumber = "";
    status = "";
}

void Flight::setData(string f, string s) {
    flightNumber = f;
    status = s;
}

string Flight::getFlightNumber() {
    return flightNumber;
}

string Flight::getStatus() {
    return status;
}


// Airline System Class
class AirlineSystem {
private:
    Passenger passengers[100];
    Flight flights[50];
    int pCount;
    int fCount;

public:
    AirlineSystem();
    ~AirlineSystem();

    void addPassenger(string, int, string);
    void addFlight(string, string);
    void showPassengers();
    void showFlights();
    Passenger* searchPassenger(string);
    void cancelBooking(string);
};


// Constructor
AirlineSystem::AirlineSystem() {
    pCount = 0;
    fCount = 0;
    cout << "Flight Booking & Tracking System Started.\n";
}

// Destructor
AirlineSystem::~AirlineSystem() {
    cout << "\nSystem Closed. Have a safe flight!\n";
}

// Add Passenger
void AirlineSystem::addPassenger(string name, int passport, string dest) {
    if (pCount >= 100) {
        cout << "Booking is full!\n";
        return;
    }

    passengers[pCount].setData(name, passport, dest);
    pCount++;

    cout << "Ticket booked successfully!\n";
}

// Add Flight
void AirlineSystem::addFlight(string flightNum, string status) {
    if (fCount >= 50) {
        cout << "Flight schedule is full!\n";
        return;
    }

    flights[fCount].setData(flightNum, status);
    fCount++;

    cout << "Flight added successfully!\n";
}

// Show Passengers
void AirlineSystem::showPassengers() {
    if (pCount == 0) {
        cout << "No passengers found!\n";
        return;
    }

    for (int i = 0; i < pCount; i++) {
        cout << "\nPassenger ID: " << i + 1 << endl;
        cout << "Name: " << passengers[i].getName() << endl;
        cout << "Passport: " << passengers[i].getPassport() << endl;
        cout << "Destination: " << passengers[i].getDestination() << endl;
    }
}

// Show Flights
void AirlineSystem::showFlights() {
    if (fCount == 0) {
        cout << "No flights found!\n";
        return;
    }

    for (int i = 0; i < fCount; i++) {
        cout << "\nFlight ID: " << i + 1 << endl;
        cout << "Flight Number: " << flights[i].getFlightNumber() << endl;
        cout << "Status: " << flights[i].getStatus() << endl;
    }
}

// Search Passenger (Pointer)
Passenger* AirlineSystem::searchPassenger(string name) {
    for (int i = 0; i < pCount; i++) {
        if (passengers[i].getName() == name) {
            return &passengers[i];
        }
    }
    return NULL;
}

// Cancel Booking
void AirlineSystem::cancelBooking(string name) {
    bool found = false;

    for (int i = 0; i < pCount; i++) {
        if (passengers[i].getName() == name) {

            for (int j = i; j < pCount - 1; j++) {
                passengers[j] = passengers[j + 1];
            }

            pCount--;
            found = true;

            cout << "Booking canceled successfully!\n";
            break;
        }
    }

    if (!found) {
        cout << "Passenger not found!\n";
    }
}
// Main
int main() {
    AirlineSystem sys;
    int choice;
    string name, destination, flightNum, status;
    int passport;

    while (true) {
       cout << "\n====================================\n";
        cout << "  FLIGHT BOOKING & TRACKING SYSTEM\n";
        cout << "====================================\n";
        cout << "1. Book Ticket (Add Passenger)\n";
        cout << "2. Schedule Flight (Add to Tracker)\n";
        cout << "3. Display All Passengers\n";
        cout << "4. Display Flight Board\n";
        cout << "5. Search Passenger\n";
        cout << "6. Cancel Booking (Delete Passenger)\n";
        cout << "7. Exit System\n\n";
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            cin.ignore();
            cout << "Enter Passenger Name: ";
            getline(cin, name);
            cout << "Enter Passport Number: ";
            cin >> passport;
            cin.ignore();
            cout << "Enter Destination: ";
            getline(cin, destination);
            sys.addPassenger(name, passport, destination);
            break;

        case 2:
            cin.ignore();
            cout << "Enter Flight Number: ";
            getline(cin, flightNum);
            cout << "Enter Flight Status (On Time / Delayed / Boarding): ";
            getline(cin, status);
            sys.addFlight(flightNum, status);
            break;

        case 3:
            sys.showPassengers();
            break;

        case 4:
            sys.showFlights();
            break;

        case 5: {
            cin.ignore();
            cout << "Enter Passenger Name To Search: ";
            getline(cin, name);

            Passenger* p = sys.searchPassenger(name);

            if (p != NULL) {
                cout << "Passenger Found!\n";
                cout << "Name: " << p->getName() << endl;
                cout << "Passport: " << p->getPassport() << endl;
                cout << "Destination: " << p->getDestination() << endl;
            } else {
                cout << "Passenger Not found!\n";
            }
            break;
        }

        case 6:
            cin.ignore();
            cout << "Enter Passenger Name To Cancel Booking: ";
            getline(cin, name);
            sys.cancelBooking(name);
            break;

        case 7:
            return 0;

        default:
            cout << "Invalid choice!\n";
        }
        cin.clear();
        cin.ignore();
    }
}