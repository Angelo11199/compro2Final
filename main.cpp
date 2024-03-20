#include <iostream>

#include "./helpers/consoleprint.h"
#include "./helpers/handleFile.h"
#include "./helpers/handleLogin.h"
#include "./helpers/handlepause.h"
#include "./helpers/structures.h"
#include "./helpers/userClass.cpp"
#include "./include/print.h"
#include "./include/userInput.h"
/**
 * \mainpage Password Manager and Array manipulation Program By Aisukurimu
 *  \authors Angelo A. Maminta (Aisukurimu) and John Romar Francisco
 *  \section intro_sec Introduction
 *  This is a simple password manager that allows you to store and retrieve passwords.
 *  \section passwordManage Password Manager
 *  \subsection  features Features
 * - Login and register
 * - Insert data
 * - View data
 * - Export data to csv
 * - Search data via email
 * - Switch user
 * - Logout
 * - Exit
 * \subsection  how_to_use How to use
 * - Run the program
 * - Register or login
 * - Use the features
 * - Logout or exit
 *  \subsection supported_platforms Supported Platforms
 * - Windows
 * - Linux
 * - MacOS
 * \section  basic_array_manipulation Basic Array Manipulation
 * \subsection  features Features
 * - Insert data
 * - Delete data
 * - Update data
 * - Search data
 * - View data
 * - Export data to txt
 * - Exit
 * \subsection  how_to_use How to use
 * - Run the program
 * - Use the features
 * - Exit
 * \subsection supported_platforms Supported Platforms
 * - Windows
 * - Linux
 * - MacOS
 */
using namespace std;
unordered_map<string, vector<string>> users;
int main(int argc, char const* argv[]) {
    string content;
    userClass user;
    init("auth.csv", users, {1});
    pauseScreen();
    clear();
    //! authentication
    while (true) {
        printBox("Welcome to the system", 50, 5);
        printBox("1. Login", 15, 5);
        printBox("2. Register", 15, 5);
        printBox("3. Exit", 15, 5);
        int choice = getNum("Enter your choice: ");
        if (choice == 1) {
            bool loggedIn = login(users, user);
            print(loggedIn);
            if (!loggedIn) {
                print("Login failed! Exiting...");
                return 0;
            } else
                break;
        } else if (choice == 2) {
            bool isAdded = registerUser(users, user);
            if (!isAdded) {
                print("Failed to register!");
                pauseScreen();
                clear();
                continue;
            }
            pauseScreen();
            clear();
            break;
        } else if (choice == 3) {
            print("Exiting...");
            return 0;
        } else {
            print("Invalid choice!");
            pauseScreen();
            clear();
        }
    }
    // main menu
    while (true) {
        // check screen size
        int windowWidth = getWidth();
        if (windowWidth < 120) {
            print("Please resize the window to a smaller size and try again");
            pauseScreen();
            clear();
            continue;
        }
        print("                                     _____________________________________________                                   ");
        print("                                    |                                             |                                  ");
        print("                                    |            Welcome to the system            |                                  ");
        print("                                    |_____________________________________________|                                  ");
        print("   _______________________________          _______________________________          _______________________________ ");
        print("  |                               |        |                               |        |                               |");
        print("  |         View data [1]         |        |        Insert data [2]        |        |           Logout [3]          |");
        print("  |_______________________________|        |_______________________________|        |_______________________________|");
        print("   _______________________________          _______________________________          _______________________________ ");
        print("  |                               |        |                               |        |                               |");
        print("  |  Export passwords to csv [4]  |        |   Search data via email [5]   |        |         Switch User [6]       |");
        print("  |_______________________________|        |_______________________________|        |_______________________________|");
        print("                                            _______________________________                                          ");
        print("                                           |                               |                                         ");
        print("                                           |            Exit [9]           |                                         ");
        print("                                           |_______________________________|                                         ");
        User* loggedInUsers = user.getLoggedInUsers();
        if (loggedInUsers[0].id == 0) {
            print("No user logged in!");
            return main(argc, argv);
        }
        int choice = getNum("Enter your choice: ");
        if (choice == 1) {
            int offset = 0, limit = 20;
            user.getDataPaginated(offset, limit);
            pauseScreen();
            clear();
        } else if (choice == 2) {
            user.insertData();
            pauseScreen();
            clear();
        } else if (choice == 3) {
            bool isLoggedOut = user.logout();
            if (!isLoggedOut) {
                print("Failed to logout!");
                pauseScreen();
                clear();
                continue;
            } else {
                print("Logged out successfully!");
                return main(argc, argv);
            }
        } else if (choice == 4) {
            user.exportData();
            print("Data exported successfully!");
            pauseScreen();
            clear();
        } else if (choice == 5) {
            string email = getStr("Enter the email to search: ");
            user.search(email);
            pauseScreen();
            clear();
        } else if (choice == 6) {
            User* loggedInUsers = user.getLoggedInUsers();
            print("Logged in users: ");
            for (int i = 0; i < 5; i++) {
                // print the logged in users
                if (loggedInUsers[i].id != 0 && loggedInUsers[i].username != "") print(to_string(i + 1) + ". " + loggedInUsers[i].username);
            }
            print("6. login as another user");
            print("0. Cancel");
            int id = getNum("Enter the id of the user to switch to: ");
            if (id == 0) {
                pauseScreen();
                clear();
                continue;
            }
            if (id == 6) {
                bool loggedIn = login(users, user);
                if (!loggedIn) {
                    print("Login failed!");
                    user.logout();
                    return main(argc, argv);
                }
                continue;
            }
            bool isSwitched = user.switchUser(loggedInUsers[id - 1].id);
            if (!isSwitched) {
                print("Failed to switch user!");
                pauseScreen();
                clear();
                continue;
            }
            print("User switched successfully!");
            pauseScreen();
            clear();
        } else if (choice == 9) {
            print("Exiting...");
            return 0;

        } else {
            print("Invalid choice!");
            pauseScreen();
            clear();
        }
    }
    return 0;
}
