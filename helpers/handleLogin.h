#include <string>
#include <unordered_map>
#include <vector>

#include "../include/print.h"
#include "../include/userInput.h"
#include "handlepause.h"
#ifndef HANDLELOGIN_H
#define HANDLELOGIN_H
bool login(std::unordered_map<std::string, std::vector<std::string>>& users) {
    bool isLoggedin = false;
    int tries = 0;
    while (!isLoggedin) {
        std::string username = getStr("Enter your username: ");
        std::string password = getStrPrivate("Enter your password: ");
        if (users.find(username) != users.end()) {
            if (users[username][1] == password) {
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
#endif
