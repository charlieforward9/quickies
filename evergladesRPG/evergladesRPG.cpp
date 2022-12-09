#include <iomanip>
#include <cstdlib>
#include <string>
#include <iostream>
#include <ctime>
using namespace std;
// Prototypes
void rules();
int returnToMainMenu(int);
int movingChoice();
int *nextChoiceRanger(int, int, int);
int *nextChoiceDanger(int, int, int);

void draw(char brd[][5], char dis[][5])
{
    // Create the board with a * in every slot
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            brd[i][j] = '*';
            dis[i][j] = '*';
        }
    }
}
void placeDangers(char brd[][5])
{
    // Randomly place the dangers around the board, but keep them hidden
    int x, y, i = 0;

    while (i < 10)
    {
        x = rand() % 5;
        y = rand() % 5;
        if ((brd[x][y] == '*') && (x != 0 || y != 0) && (x != 4 || y != 4))
        {
            brd[x][y] = 'd';
            i++;
        }
    }
}
// The main function of the project,
void play()
{
    // Constant variable
    char dangerFill[] = {'A', 'M', 'S', 'P'};

    // Set the board
    char brd[5][5];
    char dis[5][5];

    // Create the board and the objects on it
    draw(brd, dis);
    placeDangers(brd);
    dis[0][0] = 'R';
    dis[4][4] = 'T';

    // Variables of the board
    int point = 12, p = 0, x = 0, y = 0, invalid, x0, y0, choice;
    i while (p < 12)
    {
        if (x == 4 && y == 4)
            break;

        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
                cout << dis[i][j] << " ";
            cout << endl;
        }
        cout << "Gongs Left : " << (12 - p) << endl;

        choice = movingChoice();
        // previous ranger postion
        x0 = x;
        y0 = y;

        int *values;
        values = nextChoiceRanger(choice, x, y);
        x = values[0];
        y = values[1];
        invalid = values[2];

        if (invalid == 0)
        {
            dis[x0][y0] = ' '; // Show that the ranger has moved forward

            if (brd[x][y] == 'd')
            {
                int randomDanger = rand() % 3;
                int *dangerValues;
                dangerValues = nextChoiceDanger(x, y, randomDanger);
                x = dangerValues[0];
                y = dangerValues[1];
                p += dangerValues[2];
                dis[x][y] = dangerFill[randomDanger];
            }
            else
                p++;

            cout << endl
                 << endl;

            dis[x][y] = 'R'; // Reposition ranger
        }
    }

    // Game Outcome
    if (p >= 12)
        cout << "\n Game Over, you lost\n\n";
    else
        cout << "\n\nWon the game.\n\n";
}

int main()
{
    srand((unsigned int)time(NULL));
    // Variables
    int choice = -1, loop = 1;

    // Loop until they want to quit
    while (loop)
    {
        cout << "\n----------------------------------------------------------------" << endl
             << "\t\t\t Lost in the everglades RPG"
             << "\n------------------------------------------------------------------" << endl;
        choice = returnToMainMenu(choice);

        cout << "\n----------------------------------------------------------------" << endl;
        // Menu
        switch (choice)
        {
        case 1: // Show rules
            rules();
            break;
        case 2: // play game
            play();
            break;
        case 3:
            cout << "\n\t Thank you for playng. Good bye! " << endl
                 << endl;
            cout << "\n----------------------------------------------------------------" << endl;
            loop = 0;
            break;

        default: // Error for invalid entry
            cout << "\n\tError... try again " << endl
                 << "\n-----------------------------------------------------------------" << endl
                 << endl;
        }
    }
    return 0;
}
void rules()
{ // Shows the complete game rules
    cout << "\n----------------------------------------------------------------" << endl
         << "\t\t Lost in the everglades RPG"
         << "\n\t\t\t Game Rules "
         << "\n----------------------------------------------------------------" << endl;
    cout << "\n A group of tourists has been lost in the Everglades and a ranger must rescue them before time runs out."
         << "\n The Everglades are represented by a 5x5 matrix.The ranger(R) starts the rescue at the upperleft"
         << "\n corner of the park, the group of tourists(T) are lost at the lower - right corner.The ranger has"
         << "\n 12 gongs of time to find and rescue the tourists before they perish."
         << "\n During the journey, the ranger might find dangers(hungry alligator, swarm of giant mosquitoes, venomous spider or Python)."
         << "\n\n When the ranger finds a danger, they can choose to fight them or hide and wait for them to leave."
         << "\n\n\t• If the Ranger hides& waits"
         << "\n\to Moves to the desired cell"
         << "\n\to Loses 5 gongs of time"
         << "\n\n\t• If the Ranger fights & wins"
         << "\n\to Moves to the desired cell"
         << "\n\to Loses 2 gongs of time"
         << "\n\n\t• If the Ranger fights & loses"
         << "\n\to Goes back to the initial cell"
         << "\n\to Loses 3 gongs of time"
         << "\n\to The Danger remains in the cell"
         << endl;
}
int returnToMainMenu(int choice)
{
    cout << "\n\t1. See rules"
         << "\n\t2. Play"
         << "\n\t3. Quit"
         << "\n\n\tWhats your move? (1 - 3): ";
    cin >> choice;
    return choice;
}

int movingChoice()
{
    // All of the options the user has as the ranger
    cout << "\n1: up\n";
    cout << "2: down\n";
    cout << "3: left\n";
    cout << "4: right\n";
    cout << "5: up-right\n";
    cout << "6: down-right\n";
    cout << "7: up-left\n";
    cout << "8: down-left\n";
    cout << "\nChoose : ";

    int choice;
    cin >> choice;
    return choice;
}
int *nextChoiceRanger(int choice, int x, int y)
{
    // The logic behind the users inputs as the ranger, with error checking
    int invalid = 0;
    switch (choice)
    {
    case 1:
        if (x > 0)
            x--;
        else
        {
            cout << "invalid move.\n";
            invalid = 1;
        }
        break;
    case 2:
        if (x < 4)
            x++;
        else
        {
            cout << "invalid move.\n";
            invalid = 1;
        }
        break;
    case 3:
        if (y > 0)
            y--;
        else
        {
            cout << "invalid move.\n";
            invalid = 1;
        }
        break;
    case 4:
        if (y < 4)
            y++;
        else
        {
            cout << "invalid move.\n";
            invalid = 1;
        }
        break;
    case 5:
        if (x > 0 && y < 4)
        {
            x--;
            y++;
        }
        else
        {
            cout << "invalid move.\n";
            invalid = 1;
        }
        break;
    case 6:
        if (x < 4 && y < 4)
        {
            x++;
            y++;
        }
        else
        {
            cout << "invalid move.\n";
            invalid = 1;
        }
        break;
    case 7:
        if (x > 0 && y > 0)
        {
            x--;
            y--;
        }
        else
        {
            cout << "invalid move.\n";
            invalid = 1;
        }
        break;
    case 8:
        if (x < 4 && y > 0)
        {
            x++;
            y--;
        }
        else
        {
            cout << "invalid move.\n";
            invalid = 1;
        }
        break;
    default:
        cout << "Choose a valid move.\n";
        invalid = 1;
        break;
    }

    // Pointers are fancy
    int *outcome = new int[3];
    outcome[0] = x;
    outcome[1] = y;
    outcome[2] = invalid;
    return outcome;
}

int *nextChoiceDanger(int x, int y, int danger)
{
    // Runs when the ranger has encountered a danger
    string dangerName[] = {"Hungry Alligator", "Swarm of Giant Mosquitos", "Venomous Spider", "Python"};

    int p = 0, opt = -1;
    while (opt != 1 && opt != 2)
    {
        cout << "\n------ Ranger encountered a " << dangerName[danger] << ", what will you do? ------\n"
             << "1. Hide and Wait\n"
             << "2. Fight\n";
        cin >> opt;
        // Prompt to act on the danger
        switch (opt)
        {
        case 1:
        {
            p += 5;
            cout << "The ranger hid from the " << dangerName[danger];
            break;
        }
        case 2:
        {
            int fightOutcome = rand() % 3;
            if (fightOutcome == 1)
            {
                p += 3;
                cout << "The ranger fought the " << dangerName[danger] << " and lost. Retreat";
                x = 0, y = 0;
            }
            else
            {
                p += 2;
                cout << "The ranger fought the " << dangerName[danger] << " and won! Advance";
            }
            break;
        }
        default:
        {
            cout << "Choose a valid move.\n";
            break;
        }
        }
    }
    // Returns the amount of gongs elapsed and the position of the ranger
    int *outcome = new int[3];
    outcome[0] = x;
    outcome[1] = y;
    outcome[2] = p;
    return outcome;
}