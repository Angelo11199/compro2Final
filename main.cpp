#include <iostream>

#include "./helpers/handleFile.h"
#include "./helpers/handleLogin.h"
#include "./helpers/handlepause.h"
#include "./helpers/userClass.cpp"
#include "./include/print.h"
#include "./include/userInput.h"
using namespace std;
struct User {
    int id;
    string username;
    string password;
    string email;
    string phone;
};
unordered_map<string, vector<string>> users;
int main(int argc, char const* argv[]) {
    string content;
    userClass user;
    init("auth.csv", users, {0});
    pause();

    clear();
    while (true) {
        print("Welcome to the system");
        print("1. Login");
        print("2. Register");
        print("3. Exit");
        int choice = getNum("Enter your choice: ");
        if (choice == 1) {
            bool loggedIn = login(users,user);
            if (!loggedIn) {
                print("Login failed! Exiting...");
                return 0;
            }
        } else if (choice == 2) {
            bool isAdded = registerUser(users);
            if (!isAdded) {
                print("Failed to register!");
                pause();
                clear();
                continue;
            }
            print("Registered successfully!");
            pause();
            clear();
        } else if (choice == 3) {
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
