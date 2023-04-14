#ifndef MENU_H
#define MENU_H

struct piatto
{
    char category[10 + 1]; // category (max 10 chars)
    char name[20 + 1];     // name (max 20 chars)
    double price;          // price in euros
    bool vegan;            // suitable for vegans (usually false)
};

#include <iostream>
using namespace std;

// overload dell'operatore << per output CSV format
ostream &operator<<(ostream &os, const piatto &p)
{
    os << p.category;
    os << "," << p.name;
    os << "," << p.price;
    os << "," << (p.vegan ? "vegan" : "non vegan");
    return os;
}

const piatto menu[] = {
    {"antipasto", "Caprese", 5.50, false},
    {"dessert", "tiramisu", 4.50, false},
    {"antipasto", "Erba di campo", 1.50, true},
    {"antipasto", "Ostriche", 15.00, false},
    {"secondo", "Grigliata mista", 16.00, false},
    {"primo", "Carbonara", 7.50, false}};

const size_t numPiatti = sizeof(menu) / sizeof(piatto);

#endif