/**********************************
 * File: Proj4.cpp
 * Project: CMSC 202 Project 4, Spring 2024
 * Author: Eden Zhang
 * Date: 4/9/2024
 * Section: 30/34
 * E-Mail: ezhang1@umbc.edu
 * 
 * Game.cpp file
 * The main driver that sets up the game, loads files info, 
 * constructs the planet, item, and ship objects
 * and runs the game.
 * 
*****************************************************/
#include "Game.h"

// Game
// Main constructor for the game and gets the files
Game::Game(string itemFile, string planetFile)
{
    m_fileItems = itemFile;
    m_filePlanets = planetFile;
}

// ~Game
// Destructor, deletes all the new created objects that need to be deallocated
Game::~Game()
{
    // Loops through items and deletes all the objects
    for (vector<Item*>::iterator it = m_items.begin(); it != m_items.end(); it++)
    {
        delete *it;
    }

    // Same thing as above but with planets
    for (vector<Planet*>::iterator it = m_planets.begin(); it != m_planets.end(); it++)
    {
        delete *it;
    }

    // Finally, deallocates the ship object
    delete m_ship;
}

// LoadItems
// Loads in the data from the item file 
// and puts it in a vector for later use
void Game::LoadItems()
{
    string const ARMOR = "armor"; // Constant for checking if item is armor
    string const WEAPON = "weapon"; // Constant for checking if item is weapon
    string const ENGINE = "engine"; // Constant for checking if item is engine

    // File I/O variables
    ifstream items;
    string data;
    
    // Item variables
    string name;
    string type;
    int value;

    // Opens file
    items.open(m_fileItems);

    // Checks file is open
    if (items.is_open())
    {
        // In order gets the data for the appropriate sections and
        // assigns it to correct variables
        while (getline(items, data, DELIMITER))
        {
            name = data;

            getline(items, data, DELIMITER);
            type = data;

            getline(items, data);
            value = stoi(data); // Converts variable to integer before assigning to value

            // Checks the type and calls the right constructor
            if (type == ARMOR)
            {
                m_items.push_back(new Armor(name, type, value));
            } else if (type == WEAPON)
            {
                m_items.push_back(new Weapon(name, type, value));
            } else if (type == ENGINE)
            {
                m_items.push_back(new Engine(name, type, value));
            }
        }
    }

    items.close();

    cout << m_items.size() << " items loaded." << endl;
}

// LoadPlanets
// Loads in planet file and adds the info 
// into a vector for later use
void Game::LoadPlanets()
{
    string const MINING = "mining"; // Constant for checking if item is mining
    string const GAS = "gas"; // Constant for checking if item is gas
    string const ENEMY = "enemy"; // Constant for checking if item is enemy

    // File I/O variables
    ifstream planets;
    string data;
    
    // Item variables
    string name;
    string type;
    int challenge;

    // Opens file
    planets.open(m_filePlanets);

    // Checks file is open
    if (planets.is_open())
    {
        // In order, gets the data for the appropriate sections and
        // assigns it to correct variables
        while (getline(planets, data, DELIMITER))
        {
            name = data;

            getline(planets, data, DELIMITER);
            type = data;

            getline(planets, data);
            challenge = stoi(data); // Converts variable to integer before assigning to value

            // Checks the type and calls the right constructor
            if (type == MINING)
            {
                m_planets.push_back(new Mining(name, challenge));
            } else if (type == GAS)
            {
                m_planets.push_back(new Gas(name, challenge));
            } else if (type == ENEMY)
            {
                m_planets.push_back(new Enemy(name, challenge));
            }
        }
    } else
    {
        cout << "Could not open file." << endl;
    }

    planets.close();

    cout << m_planets.size() << " planets loaded." << endl;
}

// ShipCreation
// Creates the ship object and sets up some info
// Displays a formatted info to user
void Game::ShipCreation()
{
    // Asks the user to name their ship
    string name;
    cout << "Please enter a name for your ship: " << endl;
    getline(cin, name);

    // Constructs the ship object with the given name
    m_ship = new Ship(name);
    cout << "Ship Name: " << m_ship->GetName() << endl;

    // Adds the starting items to the ship
    m_ship->AddItem(m_items.at(START_ARMOR));
    m_ship->AddItem(m_items.at(START_ENGINE));
    m_ship->AddItem(m_items.at(START_WEAPON));
}

// StartGame
// Starts the game, sets up variables, 
// and calls functions to set more things up
void Game::StartGame()
{
    // Loads file
    LoadPlanets();
    LoadItems();

    // Creates ship
    ShipCreation();

    // Sets up beginning
    m_curPlanet = m_planets.at(START_PLANET);

    // Sets up win condition
    m_winEngine = (rand() % (UTOPIA_MAX + 1 - UTOPIA_MIN)) + UTOPIA_MIN;

    // Displays the beginning planet
    cout << *m_curPlanet << endl;

    // Calls main menu for user's actions
    Action();
}

// Action
// Main Menu for user to choose what they want to do
void Game::Action()
{
    int user = -1;
    int winCondition = 0;

    while (user != 6)
    {
        // Display menu
        cout << "What would you like to do?" << endl;
        cout << "1. Examine Items" << endl;
        cout << "2. Move" << endl;
        cout << "3. Attack Planet" << endl;
        cout << "4. Travel to Utopia" << endl;
        cout << "5. Check Stats" << endl;
        cout << "6. Quit" << endl;
        cin >> user;

        // Bound checking
        while (user < 1 || user > 6)
        {
            cout << "Please choose a valid option from the menu." << endl;
            cin >> user;
        }

        // Switch statement to manage different results for user's choice
        switch (user)
        {
            case 1:
            m_ship->DisplayItems();
            break;
            
            case 2:
            Move();
            break;

            case 3:
            AttackPlanet();
            break;

            // WinConditions for Utopia
            case 4:
            winCondition = TravelUtopia();
            if (winCondition == -1)
            {
                cout << "You ran out of fuel and failed to reach Utopia. Game Over." << endl;
                user = 6;
            } else if (winCondition == 1)
            {
                cout << "You successfully reached Utopia! Congratulations!" << endl;
                user = 6;
            } else if (winCondition == 0)
            {
                cout << "You are not prepared to travel to Utopia yet." << endl;
                cout << "Develop your engines more." << endl;
            }
            break;

            case 5:
            m_ship->DisplayShip();
            break;

            case 6:
            cout << "Thanks for playing!" << endl;
            break;
        }

        // Checks if user's ship has run out of fuel and ends game if yes
        // Extra con: Only if not already lost or win
        if (m_ship->GetFuel() <= 0 && winCondition == 0)
        {
            cout << "You have run out of fuel. Game Over." << endl;
            user = 6;
        }
    }
}

// Move
// Picks a random planet in the planets vector
void Game::Move()
{
    cout << "You travel to the next planet." << endl;

    // Assigns a new planet within the range of planets vector
    m_curPlanet = m_planets.at(rand() % (int(m_planets.size()) + 1));
    cout << *m_curPlanet << endl;

    // Modifying fuel appropriately
    m_ship->ModifyFuel(MOVE_FUEL);
}

// AttackPlanet
// Checks if the planet hasn't been attacked yet and calls Battle()
// Prints results and finds new item if win
void Game::AttackPlanet()
{
    // Checking if the planet has already been attacked or not
    if (m_curPlanet->GetIsExplored() == true)
    {
        cout << "This planet has already been defeated." << endl;
        cout << "You should move to another planet." << endl;
    } else
    {
        // Goes through battle results
        if (m_curPlanet->Battle(m_ship))
        {
            cout << "Your planetary bombardment worked. You win!" << endl;
            IdentifyItem(m_curPlanet->GetChallenge());
        } else 
        {
            cout << "Your plantary attack failed. You lost." << endl;
        }
    }
}

// IdentifyItem
// Finds a new random item of the same 
// challenge and adds the item to ship
void Game::IdentifyItem(int challenge)
{
    Item* newItem; // New item pointer for finding the new item
    
    // Finds a new random item and checks that its of the same challenge value
    do {
        newItem = m_items.at(rand() % (int(m_items.size()) + 1));
    } while (int(newItem->GetValue()) != int(m_curPlanet->GetChallenge()));

    m_ship->AddItem(newItem);

    // Notifies the user that they found a new item
    cout << "You have found: ";
    newItem->Display();
}

// Stats
// Calls the function to display the ship's info
void Game::Stats()
{
    m_ship->DisplayShip();
}

// TravelUtopia
// Manages the conditions for victory, loss, or continue
int Game::TravelUtopia()
{
    string const ENGINE = "engine"; // string const for the item type engine

    // Checks that the ship has enough fuel for the minimum
    if (int(m_ship->GetTotal(ENGINE)) < UTOPIA_MIN)
    {
        return 0;
    } else
    {   
        // Checks if the ship really does have enough fuel to win or lose if not
        if (int(m_ship->GetTotal(ENGINE)) >= m_winEngine)
        {
            return 1;
        } else 
        {
            return -1;
        }
    }
}

// DisplayShipItems
// Displays the ship's current items in format or signals if no items
void Game::DisplayShipItems()
{
    // Checks if any there are any items
    if (int(m_items.size()) == 0)
    {
        cout << "No Items Found." << endl;
    } else // otherwise displays the ship's items as normal
    {
        m_ship->DisplayItems();
    }
}
