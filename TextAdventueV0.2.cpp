#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>

#include "Room.h"
#include "Player.h"

using namespace std;

#define NUMBER_OF_ROOMS 21
#define SAVE1 "save1.txt"
#define SAVE2 "save2.txt"
#define SAVE3 "save3.txt"

int loopCounter = 0;

void displayRooms();
void setRooms();

void displayGameMenu();
void processGameMenu();

void displayGameScreen();
void processGameChoices();
void doorUnlock();

void saveGame();
void loadGame();

string displayExits(int currentRoom);
string displayInventory();

void pickup();
void drop();
int inventoryPos = 0;

//About
void about();
//Help
void help();
//Utility
void cls();
void setTextColour(int colour);

//Room myRoom;

Room theDungeon[NUMBER_OF_ROOMS];
Player thePlayer;


int main()
{
    setRooms();

    processGameMenu();
    //displayRooms();

    return 0;
}

void displayRooms()
{
    for (int loop = 0; loop < NUMBER_OF_ROOMS; loop++)
    {
        cout << "Loop  = " << loop << endl;
        cout << "Title = " << theDungeon[loop].getTitle() << endl;
        cout << "North = " << theDungeon[loop].getNorth() << endl;
        cout << "East  = " << theDungeon[loop].getEast() << endl;
        cout << "South = " << theDungeon[loop].getSouth() << endl;
        cout << "West  = " << theDungeon[loop].getWest() << endl;
        cout << "Description = " << theDungeon[loop].getDesc() << endl;
        cout << "Room Inventory = " << theDungeon[loop].getInventory() << endl;

    }
}

void setRooms()
{
    fstream filestr;
    string line;
    int pos = 0;

    filestr.open("level.txt");
    while (!filestr.eof())
    {
        getline(filestr, line);
        theDungeon[pos].setTitle(line);

        getline(filestr, line);
        theDungeon[pos].setNorth(stoi(line));

        getline(filestr, line);
        theDungeon[pos].setEast(stoi(line));

        getline(filestr, line);
        theDungeon[pos].setSouth(stoi(line));

        getline(filestr, line);
        theDungeon[pos].setWest(stoi(line));

        getline(filestr, line);
        theDungeon[pos].setDesc(line);

        getline(filestr, line);
        if (line == "empty")
        {
            theDungeon[pos].setInventory(NOTHING);

        }
        else
        {
            theDungeon[pos].setInventory(line);
        }
        

        pos++;

    }
    filestr.close();
}//setRooms
void displayGameMenu()
{
    cls();
    cout << "   MainMenu\n**************\n";
    cout << "P - New Game\n";
    cout << "L - Load Game\n";
    cout << "A - About Game\n";
    cout << "H - Help\n";
    cout << "X - Exit Game\n";
    
    cout << "\n Choice: ";

}

void processGameMenu()
{
    char choice;

    displayGameMenu();
    choice = toupper(_getwch());

    while (choice != 'X')
    {
        if (choice == 'P')
        {
            cls();
            thePlayer.setPlayerPos(0);
            setRooms();
            for (int loop = 0; loop < 3; loop++)
            {
                thePlayer.setInventory(NOTHING, loop);
            }
            inventoryPos = 0;
            processGameChoices();
        }
        else if (choice == 'L')
        {
            loadGame();
        }
        else if (choice == 'A')
        {
            about();
        }
        else if (choice == 'H')
        {
            help();
        }
        cls();
        displayGameMenu();
        choice = toupper(_getwch());

    }

}

void displayGameScreen()
{
    

    cout << "Location : " << theDungeon[thePlayer.getPlayerPos()].getTitle() << endl;
    cout << theDungeon[thePlayer.getPlayerPos()].getDesc() << endl;
    doorUnlock();
    cout << "Room Inventory = " << theDungeon[thePlayer.getPlayerPos()].getInventory() << endl;
    cout << "Player Inventory = " << displayInventory() << endl;
    cout << "Exits : " << displayExits(thePlayer.getPlayerPos()) << endl;

    cout << "\nN-orth\n";
    cout << "E-ast\n";
    cout << "S-outh\n";
    cout << "W-est\n";
    cout << "\nP-ickup\n";
    cout << "D-rop\n";
    cout << "\nK - Save Game";
    cout << "\nQ-uit\n";

    cout << "Choice : ";

}//displayGameScreen
//processGameChoices
void processGameChoices()
{
    char choice;

    displayGameScreen();
    choice = toupper(_getwch());

    while (choice != 'Q')
    {
        if (choice == 'N')
        {
            cls();
            if (thePlayer.getPlayerPos() == 20)
            {
                setRooms();
                cout << "As I pass through the mirror, it's almost like waking from a dream. This has happened " << loopCounter << " times so far. I'm back in my office with the journal once again laid on my desk unopened. Maybe it was just a dream.";
                loopCounter++;
            }
            if (theDungeon[thePlayer.getPlayerPos()].getNorth() != NO_EXIT)
            {
                thePlayer.setPlayerPos(theDungeon[thePlayer.getPlayerPos()].getNorth());
            }
        }//North
        else if (choice == 'E')
        {
            cls();
            if (theDungeon[thePlayer.getPlayerPos()].getEast() != NO_EXIT)
            {
                thePlayer.setPlayerPos(theDungeon[thePlayer.getPlayerPos()].getEast());
            }
        }//East
        else if (choice == 'S')
        {
            cls();
            if (theDungeon[thePlayer.getPlayerPos()].getSouth() != NO_EXIT)
            {
                thePlayer.setPlayerPos(theDungeon[thePlayer.getPlayerPos()].getSouth());
            }
        }//South
        else if (choice == 'W')
        {
            cls();
            if (theDungeon[thePlayer.getPlayerPos()].getWest() != NO_EXIT)
            {
                thePlayer.setPlayerPos(theDungeon[thePlayer.getPlayerPos()].getWest());
            }
        }//West
        else if (choice == 'P')
        {
            cls();
            pickup();
        } //Pickup
        else if (choice == 'D')
        {
            cls(); 
            drop();
        }//Drop
        else if (choice == 'K')
        {
            cls();
            saveGame();
        }//SaveGame
        
        displayGameScreen();
        choice = toupper(_getwch());
    }//while (choice != 'Q')

}
void doorUnlock()
{
    if ((thePlayer.getPlayerPos() == 2) && theDungeon[3].getInventory() == "Golden Idol")
    {
        cout << "A wall opens before you, it seems putting the idol on the pedastal openned this\n";
        theDungeon[thePlayer.getPlayerPos()].setNorth(5);
        theDungeon[3].setInventory(NOTHING);
    }
    if ((thePlayer.getPlayerPos() == 5) && theDungeon[7].getInventory() == "Silver Egg" && theDungeon[6].getInventory() == "Cat's Claws" && theDungeon[8].getInventory() == "Hawk's Feather" && theDungeon[9].getInventory() == "Dog Bone")
    {
        cout << "The wall opens before you, this time it was multiple pedastals\n";
        theDungeon[thePlayer.getPlayerPos()].setNorth(12);
        theDungeon[7,6,8,9].setInventory(NOTHING);
    }
    if ((thePlayer.getPlayerPos() == 17) && theDungeon[14].getInventory() == "Spiky Ball" && theDungeon[18].getInventory() == "Axe" && theDungeon[19].getInventory() == "Necklace" && theDungeon[16].getInventory() == "Chalice")
    {
        cout << "The wall opens before you, a passageway opens to the central atrium\n";
        theDungeon[thePlayer.getPlayerPos()].setNorth(20);
        theDungeon[14, 16, 18, 19].setInventory(NOTHING);
    }
}


void saveGame()
{
    char choice;
    cout << "Which file would you like to save to?(1,2,3)";
    choice = _getwch();
    if (choice == '1')
    {
        fstream saveFile;
        saveFile.open(SAVE1,fstream::out);
        saveFile << thePlayer.getPlayerPos() << "\n";
        saveFile << thePlayer.getInventory(0) << "\n";
        saveFile << thePlayer.getInventory(1) << "\n";
        saveFile << thePlayer.getInventory(2) << "\n";
        saveFile << theDungeon[2].getNorth() << "\n";
        saveFile << theDungeon[5].getNorth() << "\n";
        saveFile << theDungeon[17].getNorth() << "\n";
        saveFile << loopCounter << "\n";
        saveFile << inventoryPos << "\n";

        saveFile.close();
    }
    else if (choice == '2')
    {
        fstream saveFile;
        saveFile.open(SAVE2, fstream::out);
        saveFile << thePlayer.getPlayerPos() << "\n";
        saveFile << thePlayer.getInventory(0) << "\n";
        saveFile << thePlayer.getInventory(1) << "\n";
        saveFile << thePlayer.getInventory(2) << "\n";
        saveFile << theDungeon[2].getNorth() << "\n";
        saveFile << theDungeon[5].getNorth() << "\n";
        saveFile << theDungeon[17].getNorth() << "\n";
        saveFile << loopCounter << "\n";
        saveFile << inventoryPos << "\n";

        saveFile.close();
    }
    else if (choice == '3')
    {
        fstream saveFile;
        saveFile.open(SAVE3, fstream::out);
        saveFile << thePlayer.getPlayerPos() << "\n";
        saveFile << thePlayer.getInventory(0) << "\n";
        saveFile << thePlayer.getInventory(1) << "\n";
        saveFile << thePlayer.getInventory(2) << "\n";
        saveFile << theDungeon[2].getNorth() << "\n";
        saveFile << theDungeon[5].getNorth() << "\n";
        saveFile << theDungeon[17].getNorth() << "\n";
        saveFile << loopCounter << "\n";
        saveFile << inventoryPos << "\n";

        saveFile.close();
    }
    
    
    cout << "\nGame Saved...";
}

void loadGame()
{
    cout << "Which file would you like to load?(1,2,3)";
    char choice = toupper(_getwch());
    if (choice == '1')
    {
        string line;
        fstream saveFile;
        saveFile.open(SAVE1,fstream::in);
        getline(saveFile, line);
        thePlayer.setPlayerPos(stoi(line));
        for (int loop = 0; loop < 3; loop++)
        {
            getline(saveFile, line);
            thePlayer.setInventory(line, loop);
        }
        getline(saveFile, line);
        theDungeon[2].setNorth(stoi(line));
        getline(saveFile, line);
        theDungeon[5].setNorth(stoi(line));
        getline(saveFile, line);
        theDungeon[17].setNorth(stoi(line));
        getline(saveFile, line);
        loopCounter = stoi(line);
        getline(saveFile, line);
        inventoryPos = stoi(line);

        saveFile.close();
    }
    else if (choice == '2')
    {
        string line;
        fstream saveFile;
        saveFile.open(SAVE2, fstream::in);
        getline(saveFile, line);
        thePlayer.setPlayerPos(stoi(line));
        for (int loop = 0; loop < 3; loop++)
        {
            getline(saveFile, line);
            thePlayer.setInventory(line, loop);
        }
        getline(saveFile, line);
        theDungeon[2].setNorth(stoi(line));
        getline(saveFile, line);
        theDungeon[5].setNorth(stoi(line));
        getline(saveFile, line);
        theDungeon[17].setNorth(stoi(line));
        getline(saveFile, line);
        loopCounter = stoi(line);
        getline(saveFile, line);
        inventoryPos = stoi(line);

        saveFile.close();
    }
    else if (choice == '3')
    {
        string line;
        fstream saveFile;
        saveFile.open(SAVE3, fstream::in);
        getline(saveFile, line);
        thePlayer.setPlayerPos(stoi(line));
        for (int loop = 0; loop < 3; loop++)
        {
            getline(saveFile, line);
            thePlayer.setInventory(line, loop);
        }
        getline(saveFile, line);
        theDungeon[2].setNorth(stoi(line));
        getline(saveFile, line);
        theDungeon[5].setNorth(stoi(line));
        getline(saveFile, line);
        theDungeon[17].setNorth(stoi(line));
        getline(saveFile, line);
        loopCounter = stoi(line);
        getline(saveFile, line);
        inventoryPos = stoi(line);

        saveFile.close();
    }    
    cls();
    processGameChoices();
}

string displayExits(int currentRoom)
{
    string AvailableExits = "";

    if (theDungeon[currentRoom].getNorth() != NO_EXIT)
    {
        AvailableExits = AvailableExits + "North,";
    }
    if (theDungeon[currentRoom].getEast() != NO_EXIT)
    {
        AvailableExits = AvailableExits + "East,";
    }
    if (theDungeon[currentRoom].getSouth() != NO_EXIT)
    {
        AvailableExits = AvailableExits + "South,";
    }
    if (theDungeon[currentRoom].getWest() != NO_EXIT)
    {
        AvailableExits = AvailableExits + "West,";
    }

    return AvailableExits;
}

string displayInventory()
{
    string Inventory = "";
    for (int loop=0;loop< 3; loop++)
    {
        if (thePlayer.getInventory(loop)!=NOTHING)
        {
            Inventory = Inventory + thePlayer.getInventory(loop) + ",";
        }
    }
    if (Inventory == "")
    {
        Inventory = NOTHING;
    }

    return Inventory;
}

void pickup()
{
    if (thePlayer.getPlayerPos() == 0)
    {
        cout << "A journal from my client, it seems to contain some of their research as well as a single entry on thier expedition:\n\nWell it seems I've discovered something odd here, despite my best attempts at researching this culture it's much different to other cultures in the area.\nI'm almost certain this temple contains something special, considering how hard it was to get past the first 'door',it's clear it's not a tomb judging by the few markings I've been able to decipher.\nThis is probably the best time to consider calling in a favour with an old friend of mine, especially if we aren't able to progress anymore anytime soon\n\nOn the front is a note addressed to me asking me to investigate. Well there's no time like the present I should probably head on my way ";
        theDungeon[thePlayer.getPlayerPos()].setNorth(1);
        theDungeon[thePlayer.getPlayerPos()].setInventory(NOTHING);
    }
    if (theDungeon[thePlayer.getPlayerPos()].getInventory() != NOTHING
        && thePlayer.getInventory(inventoryPos) ==NOTHING && inventoryPos <3)
    {
        thePlayer.setInventory(theDungeon[thePlayer.getPlayerPos()].getInventory(), inventoryPos);
        theDungeon[thePlayer.getPlayerPos()].setInventory(NOTHING);
        inventoryPos++;        
    }

}

void drop()
{
    
    if (theDungeon[thePlayer.getPlayerPos()].getInventory() == NOTHING 
        && inventoryPos > 0)
    {
        
        if (inventoryPos == 1)
        {
            theDungeon[thePlayer.getPlayerPos()].setInventory(thePlayer.getInventory(0));
            thePlayer.setInventory(NOTHING, 0);
            inventoryPos--;
        }
        else if (inventoryPos == 2)
        {
            cout << "Which item would you like to drop?\n1: " << thePlayer.getInventory(0) << "\n2:" << thePlayer.getInventory(1) << endl;
            char choice = toupper(_getwch());
            if (choice =='1')
            {
                theDungeon[thePlayer.getPlayerPos()].setInventory(thePlayer.getInventory(0));
                thePlayer.setInventory(thePlayer.getInventory(1), 0);
                thePlayer.setInventory(NOTHING, 1);
                inventoryPos--;
            }
            else if (choice =='2')
            {
                theDungeon[thePlayer.getPlayerPos()].setInventory(thePlayer.getInventory(1));
                thePlayer.setInventory(NOTHING, 1);
                inventoryPos--;
            }

        }
        else if (inventoryPos == 3)
        {
            cout << "Which item would you like to drop?\n1:" << thePlayer.getInventory(0) << "\n2:" << thePlayer.getInventory(1) << "\n3:" << thePlayer.getInventory(2) << endl;;
            char choice = toupper(_getwch());
            if (choice =='1')
            {
                theDungeon[thePlayer.getPlayerPos()].setInventory(thePlayer.getInventory(0));
                thePlayer.setInventory(thePlayer.getInventory(1), 0);
                thePlayer.setInventory(thePlayer.getInventory(2), 1);
                thePlayer.setInventory(NOTHING, 2);
                inventoryPos--;
            }
            else if (choice =='2')
            {
                theDungeon[thePlayer.getPlayerPos()].setInventory(thePlayer.getInventory(1));
                thePlayer.setInventory(thePlayer.getInventory(2), 1);
                thePlayer.setInventory(NOTHING, 2);
                inventoryPos--;
            }
            else if (choice =='3')
            {
                theDungeon[thePlayer.getPlayerPos()].setInventory(thePlayer.getInventory(2));
                thePlayer.setInventory(NOTHING, 2);
                inventoryPos--;
            }
        }
    }

    
}

void about()
{
    cls();

    cout << "Created for COM439 - Problem solving with programming \nby Richard Wride - S22005298";

    cout << "\n\n Press any key to return to menu...";
    _getwch();
}

void help()
{
    cls();
    cout << "\bHow to play\n-----------";
    cout << "\n # - XXXXXXXX\n Use the keyboard to navigate and solve puzzles, \nwhere # is the key and XXXXXXXX is what it does.";
    cout << "\n\n Press any key to return to menu...";
    _getwch();
}

void cls()
{
    HANDLE hStdout; // handle to console screen
    COORD coordScreen = { 0, 0 }; // home for the cursor
    DWORD cCharsWritten; //
    CONSOLE_SCREEN_BUFFER_INFO csbi; //
    DWORD dwConSize; // Used to store size of screen

    hStdout = GetStdHandle(STD_OUTPUT_HANDLE); // Get handle to output screen.
    // Get the number of character cells in the current buffer.
    if (!GetConsoleScreenBufferInfo(hStdout, &csbi))
    {
        return;
    }

    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

    // Fill the entire screen with blanks.
    if (!FillConsoleOutputCharacter(hStdout, // Handle to console screen buffer
        (TCHAR)' ', // Space Character to write to the buffer
        dwConSize, // Number of cells to write
        coordScreen, // Coordinates of first cell
        &cCharsWritten)) // Receive number of characters written
    {
        return;
    }

    // Get the current text attribute.
    if (!GetConsoleScreenBufferInfo(hStdout, &csbi))
    {
        return;
    }

    // Set the buffer's attributes accordingly.
    if (!FillConsoleOutputAttribute(hStdout, // Handle to console screen buffer
        csbi.wAttributes, // Character attributes to use
        dwConSize, // Number of cells to set attribute
        coordScreen, // Coordinates of first cell
        &cCharsWritten)) // Receive number of characters written
    {
        return;
    }

    // Put the cursor at its home coordinates.
    SetConsoleCursorPosition(hStdout, coordScreen);

    setTextColour(2);
    cout << "Text Adventure\n";
    cout << "**************\n";
    setTextColour(15);
}

void setTextColour(int colour)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, colour);
}


