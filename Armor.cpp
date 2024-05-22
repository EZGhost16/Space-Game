/**********************************
 * File: Proj4.cpp
 * Project: CMSC 202 Project 4, Spring 2024
 * Author: Eden Zhang
 * Date: 4/9/2024
 * Section: 30/34
 * E-Mail: ezhang1@umbc.edu
 * 
 * Armor.cpp
 * Child class for Armor type Items
 * 
*****************************************************/
#include "Armor.h"

// Armor
// Main child constructor for armor items
Armor::Armor(string name, string type, int value) : Item(name, type, value)
{
}

// Display
// Displays the armor info
void Armor::Display()
{
    cout << ARMOR << GetName() << '(' << GetValue() << ')' << endl;
}
