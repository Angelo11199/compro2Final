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
        print("5. Exit");
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
            }
        } else if (choice == 4) {
            user.exportData();
            print("Data exported successfully!");
            pause();
            clear();

        } else if (choice == 5) {
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
