/**********************************
 * File: Proj4.cpp
 * Project: CMSC 202 Project 4, Spring 2024
 * Author: Eden Zhang
 * Date: 4/9/2024
 * Section: 30/34
 * E-Mail: ezhang1@umbc.edu
 * 
 * Engine.cpp
 * Child class for engine type items
 * 
*****************************************************/
#include "Engine.h"

// Engine
// Main child constructor for engine items
Engine::Engine(string name, string type, int value) : Item(name, type, value)
{

}

// Display
// Displays engine info
void Engine::Display()
{
    cout << ENGINE << GetName() << '(' << GetValue() << ')' << endl;
}
