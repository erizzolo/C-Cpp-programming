#ifndef PLANET_H
#define PLANET_H

/**
 *  Purpose:    planet data type
 *  Author:     Emanuele Rizzolo
 *  Class:      3XIN
 *  Date:       2020/04/26
 *  Note:
*/

// planet data type
struct planet
{
    char name[10 + 1]; // planet name (max 10 chars)
    double mass;       // mass in kg
    double distance;   // distance from Sun in km
    bool inhabited;    // inhabited (usually false)
    int numSatellites; // number of satellites
};

// directive for standard io functions
#include <iostream>
// directive for io manipulation
#include <iomanip>
// directive for numeric limits
#include <limits>
// directive for C-style string functions
#include <cstring>

using namespace std;

#ifdef CSV

// overload dell'operatore << per output CSV format
ostream &operator<<(ostream &os, const planet &p)
{
    os << p.name;
    os << "," << p.mass;
    os << "," << p.distance;
    os << "," << p.inhabited;
    os << "," << p.numSatellites;
    return os;
}

// overload dell'operatore >> per input CSV format
istream &operator>>(istream &is, planet &p)
{
    char comma;
    // read at most sizeof(p.name) - 1 chars up to ','
    is.getline(p.name, sizeof(p.name), ',');
    is >> comma >> p.mass;
    is >> comma >> p.distance;
    is >> comma >> p.inhabited;
    is >> comma >> p.numSatellites;
    return is;
}

#else

// overload dell'operatore << per output JSON format
ostream &operator<<(ostream &os, const planet &p)
{
    os << "{";
    os << quoted("name") << ": " << quoted(p.name);
    os << ", " << quoted("mass") << ": " << p.mass;
    os << ", " << quoted("distance") << ": " << p.distance;
    os << ", " << quoted("inhabited") << ": " << (p.inhabited ? "true" : "false");
    os << ", " << quoted("numSatellites") << ": " << p.numSatellites;
    os << "}";
    return os;
}

// overload dell'operatore >> per input JSON format
istream &operator>>(istream &is, planet &p)
{
    static auto ignoreable = numeric_limits<streamsize>::max();
    char space;
    string name;
    is.ignore(ignoreable, ':').ignore(ignoreable, '"');
    is.unget();
    is >> quoted(name);
    strcpy(p.name, name.c_str());
    is.ignore(ignoreable, ':') >> p.mass;
    is.ignore(ignoreable, ':') >> p.distance;
    is.ignore(ignoreable, ':') >> space;
    p.inhabited = space == 't';
    is.ignore(ignoreable, ':') >> p.numSatellites;
    is.ignore(ignoreable, '}'); // final }
    return is;
}

const planet planets[] = {
    {"Mars", 6.4171E23, 206700000, false, 2},
    {"Jupiter", 1.8982E27, 740520000, false, 79},
    {"Mercury", 3.3011E23, 46001200, false, 0},
    {"Venus", 4.8675E24, 107477000, false, 0},
    {"Earth", 5.9726E24, 147098074, true, 1},
    {"Saturn", 5.6834E26, 1352550000, false, INT32_MAX},
    {"Uranus", 8.6810E25, 2.742E9, false, 27},
    {"Neptune", 1.02413E26, 4.5E9, false, 14}};

const size_t numPlanets = sizeof(planets) / sizeof(planet);

#endif

#endif