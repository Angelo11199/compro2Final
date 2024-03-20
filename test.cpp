#include <iostream>
#include <fstream>
#include <unistd.h>
#include <string>
#include <iomanip>

using namespace std;

void clearScreen() {
#ifdef _WIN32
system("cls");
#else
system("clear");
#endif
}

const int ARRAY_SIZE = 20;
int arr[ARRAY_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                       11, 12, 13, 14, 15, 16, 17, 18, 19, 20};

void printCentered(const string& text);

void displayArray() {
    clearScreen();
    printCentered("Array Contents:");

    string arrayContents;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        arrayContents += to_string(arr[i]) + " ";
    }

    printCentered(arrayContents);
    cout << endl;
}


void insertElement(int position, int value) {
    if (position < 0 || position >= ARRAY_SIZE) {
        cout << "Invalid position!" << endl;
        return;
    }
    for (int i = ARRAY_SIZE - 1; i > position; --i) {
        arr[i] = arr[i - 1];
    }
    arr[position] = value;
}

void deleteElement(int position) {
    if (position < 0 || position >= ARRAY_SIZE) {
        cout << "Invalid position!" << endl;
        return;
    }
    for (int i = position; i < ARRAY_SIZE - 1; ++i) {
        arr[i] = arr[i + 1];
    }
    arr[ARRAY_SIZE - 1] = 0; // Assuming 0 as a default value after deletion
}

void swapElements(int pos1, int pos2) {
    if (pos1 < 0 || pos1 >= ARRAY_SIZE || pos2 < 0 || pos2 >= ARRAY_SIZE) {
        cout << "Invalid positions!" << endl;
        return;
    }
    int temp = arr[pos1];
    arr[pos1] = arr[pos2];
    arr[pos2] = temp;
}

void reverseArray() {
    for (int i = 0; i < ARRAY_SIZE / 2; ++i) {
        swap(arr[i], arr[ARRAY_SIZE - 1 - i]);
    }
}

int findElement(int value) {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (arr[i] == value) {
            return i;
        }
    }
    return -1; // Element not found
}

void printToFile() {
    ofstream outputFile("array_contents.txt");
    if (outputFile.is_open()) {
        for (int i = 0; i < ARRAY_SIZE; ++i) {
            outputFile << arr[i] << " ";
        }
        outputFile.close();
        cout << "Array contents printed to file 'array_contents.txt'" << endl;
    } else {
        cout << "Unable to open file for writing." << endl;
    }
}

void printCentered(const string& text) {
    int totalWidth = 130;
    int padding = (totalWidth - text.length()) / 2;

    if (padding > 0) {
        cout << string(padding, ' ') << text << endl;
    } else {
        cout << text << endl;
    }
}

void centerLoadingWithText(int LINELENGTH) {
    int spaces = (LINELENGTH - 20) / 2;

    if (spaces > 0) {
        for (int i = 1; i <= 2; i++) {
            cout << string(spaces, ' ') << "EXITING" << endl;
            cout << string(spaces, ' ') << "0000oooooooooooooooo" << flush;

            usleep(250000);
            clearScreen(); // Clear the screen after displaying each "0000oooooooooooooooo" line
            cout << "\r\r";
            cout << string(spaces, ' ') << "EXITING" << endl;
            cout << string(spaces, ' ') << "ooooo0000ooooooooooo" << flush;

            usleep(250000);
            clearScreen(); // Clear the screen after displaying each "ooooo0000ooooooooooo" line
            cout << "\r\r";
            cout << string(spaces, ' ') << "EXITING" << endl;
            cout << string(spaces, ' ') << "oooooooo0000oooooooo" << flush;

            usleep(250000);
            clearScreen(); // Clear the screen after displaying each "oooooooo0000oooooooo" line
            cout << "\r\r";
            cout << string(spaces, ' ') << "EXITING" << endl;
            cout << string(spaces, ' ') << "oooooooooooo0000oooo" << flush;

            usleep(250000);
            clearScreen(); // Clear the screen after displaying each "oooooooooooo0000oooo" line
            cout << "\r\r";
            cout << string(spaces, ' ') << "EXITING" << endl;
            cout << string(spaces, ' ') << "oooooooooooooooo0000" << flush;

            usleep(250000);
            clearScreen(); // Clear the screen after displaying each "oooooooooooooooo0000" line
            cout << "\r\r";
            cout << string(spaces, ' ') << "EXITING" << endl;
            cout << string(spaces, ' ') << "0000oooooooooooooooo" << flush;

            usleep(250000);
            clearScreen(); // Clear the screen after displaying each "0000oooooooooooooooo" line
            cout << "\r\r";
        }
    }
}

int main() {
    char continueChoice;
    int choice;
    do {
        printCentered("  __________________________________________________________________________________________________________________ ");
        printCentered(" |                                                                                                                  |");
        printCentered(" |                                                       MENU                                                       |");
        printCentered(" |__________________________________________________________________________________________________________________|");
        printCentered("                                                                                                                     ");
        printCentered("   _______________________________          _______________________________          _______________________________ ");
        printCentered("  |                               |        |                               |        |                               |");
        printCentered("  |   Display Array Contents [1]  |        |       Insert Element [2]      |        |       Delete Element [3]      |");
        printCentered("  |_______________________________|        |_______________________________|        |_______________________________|");
        printCentered("                                                                                                                     ");
        printCentered("   _______________________________          _______________________________          _______________________________ ");
        printCentered("  |                               |        |                               |        |                               |");
        printCentered("  |       Swap Elements [4]       |        |       Reverse Array [5]       |        |         Find Element [6]      |");
        printCentered("  |_______________________________|        |_______________________________|        |_______________________________|");
        printCentered("                                                                                                                     ");
        printCentered("   _______________________________                                                   _______________________________ ");
        printCentered("  |                               |                                                 |                               |");
        printCentered("  |        Print File [7]         |                                                 |        Exit Program [8]       |");
        printCentered("  |_______________________________|                                                 |_______________________________|");
        printCentered("                                                                                                                     ");
        printCentered("                                                                                                                     ");

        cout << "\t\tEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayArray();
                cin.get(); // Wait for any key press
                printCentered("Press any key to continue...");
                cin.ignore(); 
              //  cin.get(); 
                clearScreen();
                break;

            case 2:
                clearScreen();
                int pos, val;
                printCentered(" ");
                printCentered("Enter position to insert: ");
                cout << setw(30) << left << "";
                cin >> pos;
                printCentered("Enter value to insert: ");
                cout << setw(30) << left << "";
                cin >> val;
                insertElement(pos, val);
                clearScreen();
                printCentered(" ");
                printCentered("Added Successfully.");
                printCentered("Press any key to continue...");
                cin.ignore(); 
                cin.get();
                clearScreen();
                break;
            case 3:
                int delPos;
                cout << "Enter position to delete: ";
                cin >> delPos;
                deleteElement(delPos);
                break;
            case 4:
                int swapPos1, swapPos2;
                cout << "Enter positions to swap: ";
                cin >> swapPos1 >> swapPos2;
                swapElements(swapPos1, swapPos2);
                break;
            case 5:
                reverseArray();
                break;
            case 6:
                int searchVal;
                cout << "Enter value to find: ";
                cin >> searchVal;
                cout << "Position of " << searchVal << " in the array: " << findElement(searchVal) << endl;
                break;
            case 7:
                printToFile();
                break;
            case 8:
                centerLoadingWithText(130); // Pass the value of LINELENGTH as an argument
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
                break;
        }
    } while (choice != 8);

    return 0;
}

