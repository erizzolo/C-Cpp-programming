#ifndef PLANET_H
#define PLANET_H

struct planet
{
    char name[10 + 1]; // planet name (max 10 chars)
    double mass;       // mass in kg
    double distance;   // distance from Sun in km
    bool inhabited;    // inhabited (usually false)
    int numSatellites; // number of satellites
};

#include <iostream>
using namespace std;

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

const planet planets[] = {
    {"Mars", 6.4171E23, 206700000, false, 2},
    {"Jupiter", 1.8982E27, 740520000, false, 79},
    {"Mercury", 3.3011E23, 46001200, false, 0},
    {"Venus", 4.8675E24, 107477000, false, 0},
    {"Earth", 5.9726E24, 147098074, true, 1},
    {"Saturn", 5.6834E26, 1352550000, false, 1'000'000},
    {"Uranus", 8.6810E25, 2.742E9, false, 27},
    {"Neptune", 1.02413E26, 4.5E9, false, 14}};

const size_t numPlanets = sizeof(planets) / sizeof(planet);

#endif