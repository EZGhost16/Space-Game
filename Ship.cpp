/**********************************
 * File: Proj4.cpp
 * Project: CMSC 202 Project 4, Spring 2024
 * Author: Eden Zhang
 * Date: 4/9/2024
 * Section: 30/34
 * E-Mail: ezhang1@umbc.edu
 * 
 * Ship.cpp
 * Main ship class file that holds important functions
 * handling ship info, actions, etc.
 * 
*****************************************************/
#include "Ship.h"

// Ship
// Main constructor
Ship::Ship(string name)
{
    m_name = name;
    m_fuel = STARTING_FUEL;
}

// GetName
// Getter function for name
string Ship::GetName()
{
    return m_name;
}

// GetTotal
// Getter function that calculates the total value
// of an item type that the ship has in the item vector
int Ship::GetTotal(string type)
{
    int total = 0;

    // Iterates through the Ship's items vector
    for (vector<Item*>::iterator it = m_shipItems.begin(); it != m_shipItems.end(); it++)
    {
        // When it finds an item of the given type increases the total
        if ((*it)->GetType() == type)
        {
            total += (*it)->GetValue();
        }
    }

    return total;
}

// AddItem
// Adds an item to the ship's item vector
// If the vector at its maximum items, then calls ReplaceItem()
void Ship::AddItem(Item* item)
{
    // If there's room in ship's items adds it
    if (GetItemCount() < MAX_ITEMS)
    {
        m_shipItems.push_back(item);
    } else 
    { // otherwise replaces an existing item
        ReplaceItem(item);
    }
}

// ReplaceItem
// Displays Items and asks the user for which 
// item to replace the new item with
void Ship::ReplaceItem(Item* item)
{
    int user = 0;
    // Prompts user for item to replace
    cout << "Which item would you like to replace?" << endl;
    DisplayItems();
    cin >> user;
    
    // Bound checking
    while (user > MAX_ITEMS || user < 1)
    {
        cout << "Please pick an item from the list." << endl;
        cin >> user;
    }

    // Replaces item
    m_shipItems.at(user - 1) = item;
}

// GetFuel
// Getter function for fuel
int Ship::GetFuel()
{
    return m_fuel;
}

// ModifyFuel
// Adds or subtracts fuel 
void Ship::ModifyFuel(int modifier)
{
    m_fuel += modifier;
    cout << "Your fuel has been modified by " << modifier << " fuel." << endl;
}

// DisplayItems
// Prints the ship's items in a numbered list
void Ship::DisplayItems()
{
    int numList = 1; // Used for formatting numbered list

    // Looping through the ship items vector and displaying the info
    for (vector<Item*>::iterator it = m_shipItems.begin(); it != m_shipItems.end(); it++)
    {
        cout << numList << ". ";
        (*it)->Display();
        numList++;
    }
}

// GetItemCount
// Getter function for the number of items the ship has in vector
int Ship::GetItemCount()
{
    return int(m_shipItems.size());
}

// DisplayShip
// Displays all of the ship's stats: name, fuel, attack, defense, etc.
// And items in proper format
void Ship::DisplayShip()
{
    string const weapon = "weapon"; // Used to get the ship's total weapons and calculate attack
    string const armor = "armor";  // Used to get the ship's total armor and calculate defense
    string const engine = "engine"; // Used to get the ship's total engine
    cout << "*******************" << endl;
    cout << "Name: " << m_name << endl;
    cout << "Fuel: " << m_fuel << endl;
    cout << "Attack: " << GetTotal(weapon) << endl;
    cout << "Defense: " << GetTotal(armor) << endl;
    cout << "Engine: " << GetTotal(engine) << endl;
    cout << "*******************" << endl;
    DisplayItems();
}
