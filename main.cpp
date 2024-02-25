#include <iostream>

#include "./helpers/handleFile.h"
#include "./helpers/handleLogin.h"
#include "./helpers/handlepause.h"
#include "./include/print.h"
#include "./include/userInput.h"
using namespace std;
struct User {
    string username;
    string password;
    string email;
    string phone;
};
unordered_map<string, vector<string>> users;
int main(int argc, char const* argv[]) {
    string content;
    init("users.csv", users, {0});
    pause();
    clear();
    while (true) {
        print("Welcome to the system");
        print("1. Login");
        print("2. Register");
        print("3. Exit");
        int choice = getNum("Enter your choice: ");
        if (choice == 1) {
            bool loggedIn = login(users);
            if (!loggedIn) {
                print("Login failed! Exiting...");
                return 0;
            }
        } else if (choice == 2) {
            User user;
            user.username = getStr("Enter your username: ");
            user.password = getStrPrivate("Enter your password: ");
            user.email = getStr("Enter your email: ");
            user.phone = getStr("Enter your phone: ");
            vector<string> userDetails = {user.password, user.email, user.phone};
            users[user.username] = userDetails;
            appendFile("users.csv", user.username + "," + user.password + "," + user.email + "," + user.phone);
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
