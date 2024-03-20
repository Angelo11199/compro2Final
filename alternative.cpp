#include <unistd.h>

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#include "./helpers/consoleprint.h"
#include "./helpers/handlepause.h"
#include "./include/print.h"
#include "./include/userInput.h"
using namespace std;

const int ARRAY_SIZE = 20;
int arr[ARRAY_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                       11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
/**
 * @brief Display the array contents
 * @details Display the array contents in a formatted manner
 *
 */
void displayArray() {
    clear();
    print(centerText("Array Contents"));
    string arrayContents;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        arrayContents += to_string(arr[i]) + " ";
    }
    printCenterScreen({arrayContents});
    print("");
    pauseScreen(centerText("Press enter key to continue..."));
}
/**
 * @brief Insert an element at a given position
 *
 * @param position The position to insert the element
 * @param value The value to insert
 */
void insertElement(int position, int value) {
    if (position < 0 || position >= ARRAY_SIZE) {
        print(centerText("Invalid position!"));
        return;
    }
    for (int i = ARRAY_SIZE - 1; i > position; --i) {
        arr[i] = arr[i - 1];
    }
    arr[position] = value;
}
/**
 * @brief delete an element at a given position
 *
 * @param position the position to delete the element
 */
void deleteElement(int position) {
    if (position < 0 || position >= ARRAY_SIZE) {
        print(centerText("Invalid position!"));
        return;
    }
    for (int i = position; i < ARRAY_SIZE - 1; ++i) {
        arr[i] = arr[i + 1];
    }
    arr[ARRAY_SIZE - 1] = 0;  // Assuming 0 as a default value after deletion
}
/**
 * @brief swap two elements at given positions
 *
 * @param pos1 Position 1 to swap
 * @param pos2 Position 2 to swap
 */
void swapElements(int pos1, int pos2) {
    if (pos1 < 0 || pos1 >= ARRAY_SIZE || pos2 < 0 || pos2 >= ARRAY_SIZE) {
        print(centerText("Invalid positions!"));
        return;
    }
    int temp = arr[pos1];
    arr[pos1] = arr[pos2];
    arr[pos2] = temp;
}
/**
 * @brief Reverse the array contents
 *
 * @return int* The reversed array
 */
int *reverseArray() {
    for (int i = 0; i < ARRAY_SIZE / 2; ++i) {
        swap(arr[i], arr[ARRAY_SIZE - 1 - i]);
    }
    return arr;
}

/**
 * @brief Find an element in the array
 *
 * @param value The value to find
 * @return int The position of the element
 * @return -1 If the element is not found
 */
int findElement(int value) {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (arr[i] == value) {
            return i;
        }
    }
    return -1;  // Element not found
}
/**
 * @brief Print the array contents to a file
 *
 * @return true If the file is printed successfully
 * @return false If the file is not printed
 */
bool printToFile() {
    ofstream file;
    time_t now = time(0);
    tm *ltm = localtime(&now);
    string fileName = "array" + to_string(ltm->tm_mday) + to_string(ltm->tm_mon) +
                      to_string(ltm->tm_year) + to_string(ltm->tm_hour) +
                      to_string(ltm->tm_min) + to_string(ltm->tm_sec) + ".txt";
    file.open(fileName, ios::out | ios::app);
    if (file.is_open()) {
        for (int i = 0; i < ARRAY_SIZE; i++) {
            file << arr[i] << " ";
        }
        print(centerText("Exported to file: " + fileName));  // print array to file

        file.close();
        return true;
    } else
        return false;
}
/**
 * @brief Center loading animation with text
 *
 * @param LINELENGTH The length of the line
 */
void centerLoadingWithText(int LINELENGTH) {
    for (int i = 1; i <= 2; i++) {
        // Rest of the code...
        clear();
        printLowerCenter({"EXITING", "oooooooooooooooo0000"});
        usleep(250000);
        clear();
        printLowerCenter({"EXITING", "0000oooooooooooooooo"});
        usleep(250000);
        clear();
        printLowerCenter({"EXITING", "ooooo0000ooooooooooo"});
        usleep(250000);
        clear();
        printLowerCenter({"EXITING", "oooooooo0000oooooooo"});
        usleep(250000);
        clear();
        printLowerCenter({"EXITING", "oooooooooooo0000oooo"});
        usleep(250000);
        clear();
        printLowerCenter({"EXITING", "oooooooooooooooo0000"});

        usleep(250000);
        clear();
        printLowerCenter({"EXITING", "0000oooooooooooooooo"});
    }
}

int main() {
    bool running = true;
    char continueChoice;
    int choice;
    do {
        int maxWidth = getWidth();
        if (maxWidth < 120) {
            printCenterScreen({"Please resize the terminal to a larger size."});
            pauseScreen();
            continue;
        }

        print(centerText("  __________________________________________________________________________________________________________________ "));
        print(centerText(" |                                                                                                                  |"));
        print(centerText(" |                                                       MENU                                                       |"));
        print(centerText(" |__________________________________________________________________________________________________________________|"));
        print(centerText("                                                                                                                     "));
        print(centerText("   _______________________________          _______________________________          _______________________________ "));
        print(centerText("  |                               |        |                               |        |                               |"));
        print(centerText("  |   Display Array Contents [1]  |        |       Insert Element [2]      |        |       Delete Element [3]      |"));
        print(centerText("  |_______________________________|        |_______________________________|        |_______________________________|"));
        print(centerText("                                                                                                                     "));
        print(centerText("   _______________________________          _______________________________          _______________________________ "));
        print(centerText("  |                               |        |                               |        |                               |"));
        print(centerText("  |       Swap Elements [4]       |        |       Reverse Array [5]       |        |         Find Element [6]      |"));
        print(centerText("  |_______________________________|        |_______________________________|        |_______________________________|"));
        print(centerText("                                                                                                                     "));
        print(centerText("   _______________________________                                                   _______________________________ "));
        print(centerText("  |                               |                                                 |                               |"));
        print(centerText("  |        Print File [7]         |                                                 |        Exit Program [8]       |"));
        print(centerText("  |_______________________________|                                                 |_______________________________|"));
        print(centerText("                                                                                                                     "));
        print(centerText("                                                                                                                     "));
        char choice = getch();
        switch (choice) {
            case '1': {
                displayArray();
                clear();
                break;
            }
            case '2': {
                clear();
                int pos, val;
                pos = getNum("Enter position to insert:  ");
                val = getNum("Enter value to insert:  ");
                insertElement(pos, val);
                clear();
                print(centerText(" "));
                print(centerText("Added Successfully."));
                pauseScreen();
                clear();
                break;
            }
            case '3': {
                int delPos = getNum("Enter position to delete: ");
                deleteElement(delPos);
                break;
            }
            case '4': {
                int swapPos1, swapPos2;
                swapPos1 = getNum("Enter position 1 to swap: ");
                swapPos2 = getNum("Enter position 2 to swap: ");
                swapElements(swapPos1, swapPos2);
                break;
            }
            case '5': {
                reverseArray();
                print(centerText("Array Reversed Successfully."));
                pauseScreen();
                clear();

                break;
            }
            case '6': {
                int searchVal = getNum("Enter value to search: ");
                int arrayLocation = findElement(searchVal);
                if (arrayLocation == -1) {
                    print(centerText("Element not found!"));
                } else {
                    print(centerText("Element found at position: " + to_string(arrayLocation)));
                }
                break;
            }
            case '7': {
                printToFile();
                pauseScreen(centerText("Array printed to file successfully!"));
                clear();
                break;
            }
            case '8': {
                running = false;
                centerLoadingWithText(130);  // Pass the value of LINELENGTH as an argument
                break;
            }
            default: {
                print(centerText("Invalid choice!"));
                pauseScreen();
                clear();
                break;
            }
        }
    } while (running);
    return 0;
}
