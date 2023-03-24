#ifndef PLANETC_H
#define PLANETC_H

/**
 *  Purpose:    planet data type
 *  Author:     Emanuele Rizzolo
 *  Class:      3XIN
 *  Date:       2020/04/26
 *  Note:
*/

// planet data type
typedef struct
{
    char name[10 + 1]; // planet name (max 10 chars)
    double mass;       // mass in kg
    double distance;   // distance from Sun in km
    char inhabited;    // inhabited (usually false)
    int numSatellites; // number of satellites
} planet;

#define true 1
#define false 0
#include <stdint.h>

const planet planets[] = {
    {"Mars", 6.4171E23, 206700000, false, 2},
    {"Jupiter", 1.8982E27, 740520000, false, 79},
    {"Mercury", 3.3011E23, 46001200, false, 0},
    {"Venus", 4.8675E24, 107477000, false, 0},
    {"Earth", 5.9726E24, 147098074, true, 1},
    {"Saturn", 5.6834E26, 1352550000, false, INT32_MAX},
    {"Uranus", 8.6810E25, 2.742E9, false, 27},
    {"Neptune", 1.02413E26, 4.5E9, false, 14}};

const int numPlanets = sizeof(planets) / sizeof(planet);

#endif