#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <random>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25, MAX_AGE = 20;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);
int main_menu();

int main() {
    srand(time(0));
    bool again;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();


    return 0;
}
int main_menu() {
    int choice;
    cout << "\n *** GOAT MANAGER 3001 *** \n"
         << "[1] Add a goat\n"
         << "[2] Delete a goat\n"
         << "[3] List goats\n"
         << "[4] Quit\n"
         << "Choice --> ";
    // validate input
    cin >> choice;
    while (choice < 1 || choice > 4) {
        cout << "Invalid choice. Please enter a number between 1 and 4: ";
        cin >> choice;
    }

    return choice;
}
int add_goat(list<Goat> &trip, string n[], string c[]) {
    // generate random variables from mains arrays
    string n = n[rand() % SZ_NAMES];
    int age = rand() % MAX_AGE + 1;
    string c = c[rand() % SZ_COLORS];
    Goat new_goat(n, age, c);
    trip.push_back(new_goat);

    return 0;
}

