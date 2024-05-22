/**********************************
 * File: Proj4.cpp
 * Project: CMSC 202 Project 4, Spring 2024
 * Author: Eden Zhang
 * Date: 4/9/2024
 * Section: 30/34
 * E-Mail: ezhang1@umbc.edu
 * 
 * Planet.cpp
 * Planet parent class that holds functions for battle
 * Basic info and accessor functions for planets
 * 
*****************************************************/
#include "Planet.h"

// Planet
// Main constructor for planet objects
Planet::Planet(string name, int challenge)
{
    m_name = name;
    m_challenge = challenge;
    m_isExplored = false;
}

// ~Planet
// Destructor
Planet::~Planet()
{
}

// Battle
// Runs the battle process, calculating attack/defense values, difficulty
// compares the stats and determines outcome, 
// then calls function to modify fuel accordingly
bool Planet::Battle(Ship* ship)
{
    string const weapon = "weapon"; // Used to get the ship's total weapons and calculate attack
    string const armor = "armor";  // Used to get the ship's total armor and calculate defense

    cout << "Engaging Battle!" << endl;

    // Generates the planet's random difficulty
    int difficulty = rand() % m_challenge + 1;

    // Calculates the ships's attack and defense stats
    int shipAttack = ship->GetTotal(weapon);
    int shipDefense = ship->GetTotal(armor);

    // Compares the ships stats with the planet's stats
    if (difficulty <= shipAttack)
    {
        // If ship wins
        ship->ModifyFuel(m_challenge * FUEL_MULTI_WIN);
        SetIsExplored();
        return true;
    } else 
    {
        // If ship lost
        int delta = (difficulty - shipAttack) - shipDefense;
        ship->ModifyFuel(FUEL_COST_DELTA * delta);
        return false;
    }
}

// GetName
// Getter function for name
string Planet::GetName()
{
    return m_name;
}

// SetIsExplored
// Changes explored status to true
void Planet::SetIsExplored()
{
    m_isExplored = true;
}

// GetIsExplored
// Getter function for planet's explored status
bool Planet::GetIsExplored()
{
    return m_isExplored;
}

// GetChallenge
// Getter function for challenge value
int Planet::GetChallenge()
{
    return m_challenge;
}

// Overloaded Operator <<
// Used to concisely display the Planet's info in format
ostream& operator<<(ostream& output, Planet& myPlanet)
{
    output << myPlanet.GetName() << '(' << myPlanet.GetType() 
    << ") Challenge: " << myPlanet.GetChallenge() << endl;

    return output;
}
