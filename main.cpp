#include <iostream>

#include "./helpers/handleFile.h"
#include "./helpers/handleLogin.h"
#include "./helpers/handlepause.h"
#include "./helpers/structures.h"
#include "./helpers/userClass.cpp"
#include "./include/print.h"
#include "./include/userInput.h"
using namespace std;
unordered_map<string, vector<string>> users;
int main(int argc, char const* argv[]) {
    string content;
    userClass user;
    init("auth.csv", users, {1});
    pause();
    clear();
    //! authentication
    while (true) {
        print("Welcome to the system");
        print("1. Login");
        print("2. Register");
        print("3. Exit");
        int choice = getNum("Enter your choice: ");
        if (choice == 1) {
            bool loggedIn = login(users, user);
            if (!loggedIn) {
                print("Login failed! Exiting...");
                return 0;
            }
            break;
        } else if (choice == 2) {
            bool isAdded = registerUser(users, user);
            if (!isAdded) {
                print("Failed to register!");
                pause();
                clear();
                continue;
            }
            print("Registered successfully!");
            pause();
            clear();
            break;
        } else if (choice == 3) {
            print("Exiting...");
            return 0;
        } else {
            print("Invalid choice!");
            pause();
            clear();
        }
    }
    // main menu
    while (true) {
        print("Welcome to the system");
        print("1. View data");
        print("2. insert data");
        print("3. Logout");
        print("4. Export passwords to csv");
        print("5. Search data via email");
        print("6. Switch user");
        print("9. Exit");
        int choice = getNum("Enter your choice: ");
        if (choice == 1) {
            user.getDataPaginated();
            pause();
            clear();
        } else if (choice == 2) {
            user.insertData();
            pause();
            clear();
        } else if (choice == 3) {
            bool isLoggedOut = user.logout();
            if (!isLoggedOut) {
                print("Failed to logout!");
                pause();
                clear();
                continue;
            } else {
                print("Logged out successfully!");
                return main(argc, argv);
            }
        } else if (choice == 4) {
            user.exportData();
            print("Data exported successfully!");
            pause();
            clear();
        } else if (choice == 5) {
            string email = getStr("Enter the email to search: ");
            print(user.search(email));
            pause();
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
            if (id == 0) continue;
            if (id == 6) {
                bool loggedIn = login(users, user);
                if (!loggedIn) {
                    print("Login failed!");
                }
                continue;
            }
            bool isSwitched = user.switchUser(loggedInUsers[id - 1].id);
            if (!isSwitched) {
                print("Failed to switch user!");
                pause();
                clear();
                continue;
            }
            print("User switched successfully!");
            pause();
            clear();
        } else if (choice == 9) {
            print("Exiting...");
            return 0;

        } else {
            print("Invalid choice!");
            pause();
            clear();
        }
    }
    return 0;
}
