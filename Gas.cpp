/**********************************
 * File: Proj4.cpp
 * Project: CMSC 202 Project 4, Spring 2024
 * Author: Eden Zhang
 * Date: 4/9/2024
 * Section: 30/34
 * E-Mail: ezhang1@umbc.edu
 * 
 * Gas.cpp
 * Child class for Gas type planets
 * 
*****************************************************/
#include "Gas.h"

// Gas
// Main child constructor for Gas planets
Gas::Gas(string name, int challenge) : Planet(name, challenge)
{
}

// GetType
// Getter function for planet type
string Gas::GetType()
{
    string const gasType = "gas"; // String const for gas type planet
    return gasType;
}
