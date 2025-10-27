#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <random>
#include <ctime>
#include <cstdlib>
#include <string>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25, MAX_AGE = 20;

int select_goat(const list<Goat> &trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string [], int, int);
void display_trip(list<Goat> trip);
int main_menu();

int main() {
    srand(static_cast<unsigned>(time(nullptr))); // seed random number generator using current time
    bool again;

    // read & populate arrays for names and , had to change slightly as I kept getting errors, turned out to be missing file checks
    // and scope errors as vscode needed the txt files to be in output directory
    ifstream fin("names.txt");
    if (!fin) {
        cerr << "Error: Could not open names.txt" << endl;
        return 1;
    }
    string names[SZ_NAMES];
    int nCount = 0;
    if (fin) { // added check for file open
        while (nCount < SZ_NAMES && (fin >> names[nCount])) { // added check for array bounds
            ++nCount;
        }   
    }
    fin.close();

    ifstream fin1("colors.txt");
    if (!fin1) {
        cerr << "Error: Could not open names.txt" << endl;
        return 1;
    }
    string colors[SZ_COLORS];
    int cCount = 0;
    if (fin1) { // added check for file open
        while (cCount < SZ_COLORS && (fin1 >> colors[cCount])) { // added check for array bounds
            ++cCount;
        }
    }    
    fin1.close();

    // main program loop
    list<Goat> trip;
    do {
        int choice = main_menu(); // get user menu choice
        switch (choice) {
            case 1:
                add_goat(trip, names, colors, nCount, cCount);
                break;
            case 2:
                delete_goat(trip);
                break;
            case 3:
                display_trip(trip);
                break;
            case 4:
                cout << "Goodbye!" << endl;
                return 0;
        }
        cout << "Would you like to perform another operation? (1 for yes / 0 for no): ";
        cin >> again;
        // validate input
        while (again != 0 && again != 1) {
            cout << "Invalid input. Please enter 1 for yes or 0 for no: ";
            cin >> again;
        };
    } while (again);

    return 0;
}
int main_menu() { // display menu and get user choice
    int choice;
    cout << "\n *** GOAT MANAGER 3001 *** \n"
         << "[1] Add a goat\n"
         << "[2] Delete a goat\n"
         << "[3] List goats\n"
         << "[4] Quit\n"
         << "Choice --> ";
    // validate input
    cin >> choice; 
    // checks for valid input including non-integer
    while (choice < 1 || choice > 4 || cin.fail()) {
        cout << "Invalid choice. Please enter a number between 1 and 4: ";
        cin.clear(); 
        cin >> choice;
    }

    return choice;
}
void add_goat(list<Goat> &trip, string n[], string c[], int nCount, int cCount) { // add a new goat to the trip, used the count variables to avoid going out of bounds
    // empty bounds check 
    if (nCount == 0 || cCount == 0) {
        cout << "Error: Name or color list is empty. Cannot add goat." << endl;
        return;
    } 
    // generate random variables from mains arrays
    string name = n[rand() % nCount];
    int age = rand() % MAX_AGE + 1;
    string color= c[rand() % cCount];

    Goat new_goat(name, age, color);
    trip.push_back(new_goat);

}
int select_goat(const list<Goat> &trip) { // select a goat to delete
    cout << "Select a goat to delete:\n";
    int i = 1;
    for (const Goat &goat : trip) {
        cout << "[" << i++ << "] "
             << "Name: " << goat.get_name() << ", "
             << "Age: " << goat.get_age() << ", "
             << "Color: " << goat.get_color() << endl;
    }
    int choice;
    cin >> choice;
    // validate input
    while (choice < 0 || choice >= trip.size()) {
        cout << "Invalid choice. Please enter a valid index: ";
        cin >> choice;
    }
    return choice;
}
void delete_goat(list<Goat> &trip) { // delete a goat from the trip uses select_goat function
    if (trip.empty()) {
        cout << "No goats to delete." << endl;
        return;
    }
    int i = select_goat(trip);
    list<Goat>::iterator it = trip.begin();
    advance(it, i);
    trip.erase(it);
    cout << "Goat deleted." << endl;
}
void display_trip(list<Goat> trip) { // display all goats in the trip
    if (trip.empty()) {
        cout << "No goats in the trip." << endl;
        return;
    }
    cout << "\n *** GOAT TRIP LIST *** \n";
    for (const Goat &goat : trip) {
        cout << "Name: " << goat.get_name() << ", "
             << "Age: " << goat.get_age() << ", "
             << "Color: " << goat.get_color() << endl;
    }

