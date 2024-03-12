#include <string>
#include <unordered_map>
#include <vector>

#include "../include/print.h"
#include "../include/userInput.h"
#include "handleFile.h"
#include "handlepause.h"
#include "userClass.cpp"
#ifndef HANDLELOGIN_H
#define HANDLELOGIN_H

bool login(std::unordered_map<std::string, std::vector<std::string>>& users, userClass& user) {
    bool isLoggedin = false;
    int tries = 0;
    while (!isLoggedin) {
        std::string username = getStr("Enter your username: ");
        std::string password = getStrPrivate("Enter your password: ");
        if (users.find(username) != users.end()) {
            if (users[username][2] == password) {
                user.login(stoi(users[username][0]), username, password, users[username][2], users[username][3], 9);
                clear();
                print("Logged in successfully!");
                isLoggedin = true;
                return true;
            } else {
                print("Invalid password!");
                tries++;
            }

        } else {
            print("Invalid username!");
            tries++;
        }
        pause();
        clear();
        if (tries > 3) {
            print("You have reached the maximum number of tries!");
            pause();
            clear();
            return false;
        }
    }
    return false;
}
bool registerUser(std::unordered_map<std::string, std::vector<std::string>>& users, userClass& user) {
    std::string username = getStr("Enter your username: ");
    std::string password = getStrPrivate("Enter your password: ");
    std::string email = getStr("Enter your email: ");
    std::string phone = getStr("Enter your phone: ");
    int id = users.size() + 1;
    std::vector<std::string> userDetails = {std::to_string(id), password, email, phone};
    users[username] = userDetails;
    bool isAdded = appendFile("auth.csv", std::to_string(id) + "," + username + "," + password + "," + email + "," + phone + "\n");
    if (!isAdded) {
        print("Failed to register!");
        pause();
        clear();
        return false;
    }
    return user.login(id, username, password, email, phone, 0);
}
bool deleteUser(std::unordered_map<std::string, std::vector<std::string>>& users, userClass& user) {
    std::string username = getStr("Enter the username to delete: ");
    if (users.find(username) != users.end()) {
        // get the id of the user
        std::string id = users[username][0];
        users.erase(username);
        deleteRow("auth.csv", id);
        print("User deleted successfully!");
        return true;
    } else
        print("User not found!");
    return false;
}
bool logout(std::unordered_map<std::string, std::vector<std::string>>& users, userClass& user) {
    user.logout();
    print("Logged out successfully!");
    return true;
}
#endif
