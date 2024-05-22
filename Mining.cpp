/**********************************
 * File: Proj4.cpp
 * Project: CMSC 202 Project 4, Spring 2024
 * Author: Eden Zhang
 * Date: 4/9/2024
 * Section: 30/34
 * E-Mail: ezhang1@umbc.edu
 * 
 * Mining.cpp
 * Child class for Mining type planets
 * 
*****************************************************/
#include "Mining.h"

// Mining
// Main child constructor for mining planets
Mining::Mining(string name, int challenge) : Planet(name, challenge)
{
}

// GetType
// Getter function for planet's type
string Mining::GetType()
{
    string const miningType = "mining"; // string const for mining type planet
    return miningType;
}
