/**********************************
 * File: Proj4.cpp
 * Project: CMSC 202 Project 4, Spring 2024
 * Author: Eden Zhang
 * Date: 4/9/2024
 * Section: 30/34
 * E-Mail: ezhang1@umbc.edu
 * 
 * Weapon.cpp
 * Child class for weapon type items
 * 
*****************************************************/
#include "Weapon.h"

// Weapon
// Main child constructor for weapon items
Weapon::Weapon(string name, string type, int value) : Item(name, type, value)
{

}

// Display
// Displays weapon items info
void Weapon::Display()
{
    cout << WEAPON << GetName() << '(' << GetValue() << ')' << endl;
}
