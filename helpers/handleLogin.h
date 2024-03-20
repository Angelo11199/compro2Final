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
/**
 * @brief Login the user.
 *
 * @param users used to search for the user.
 * @param user  the user to searched for.
 * @return true if logged in successfully
 * @return false if failed to login
 */
bool login(std::unordered_map<std::string, std::vector<std::string>>& users, userClass& user) {
    bool isLoggedin = false;
    int tries = 0;
    while (!isLoggedin) {
        std::string username = getStr("Enter your username: ");
        std::string password = getStrPrivate("Enter your password: ");
        int id = 0, dataSize = 0;
        if (users.find(username) != users.end()) {
            if (users[username][2] == password) {
                try {
                    /*
                    0: id
                    1: username
                    2: password
                    3: email
                    4: phone
                    5: dataSize
                    */
                    id = stoi(users[username][0]);
                    dataSize = stoi(users[username][5]);
                } catch (const std::exception& e) {
                    print("Data Error! Please contact the administrator!");
                    pauseScreen();
                    return false;
                }
                user.login(id, username, password, users[username][3], users[username][4], dataSize);
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
        pauseScreen();
        clear();
        if (tries > 3) {
            print("You have reached the maximum number of tries!");
            pauseScreen();
            clear();
            return false;
        }
    }
    return false;
}
/**
 * @brief Registers the user to the system.
 *
 * @param users used to store the user data.
 * @param user the user to be registered.
 * @return true if registered successfully
 * @return false if failed to register
 */
bool registerUser(std::unordered_map<std::string, std::vector<std::string>>& users, userClass& user) {
    std::string username, password, email, phone;
    // loop until the username is unique and not empty
    while (true) {
        username = getStr("Enter your username: ");
        if (username.empty()) {
            print("Username cannot be empty!");
            pauseScreen();
            clear();
            continue;
        }
        // check if the username is already taken
        if (users.find(username) != users.end()) {
            print("Username already taken!");
            pauseScreen();
            clear();
            continue;
        }
        break;
    }
    while (true) {
        password = getStrPrivate("Enter your password: ");
        if (password.empty()) {
            print("Password cannot be empty!");
            pauseScreen();
            clear();
            continue;
        }
        email = getStr("Enter your email: ");
        if (email.empty()) {
            print("Email cannot be empty!");
            pauseScreen();
            clear();
            continue;
        }
        phone = getStr("Enter your phone number: ");
        if (phone.empty()) {
            print("Phone number cannot be empty!");
            pauseScreen();
            clear();
            continue;
        }

        break;
    }
    int id = users.size() + 1;
    std::vector<std::string> userDetails = {std::to_string(id), password, email, phone};
    users[username] = userDetails;
    bool isAdded = appendFile("auth.csv", std::to_string(id) + "," + username + "," + password + "," + email + "," + phone + ",0\n");
    if (!isAdded) {
        print("Failed to register!");
        pauseScreen();
        clear();
        return false;
    }
    return user.login(id, username, password, email, phone, 0);
}
/**
 * @brief Used to delete the user from the system.
 *
 * @param users used to store the user data.
 * @param user the user to be deleted.
 * @return true if deleted successfully
 * @return false if failed to delete
 */
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
/**
 * @brief Used to logout the user from the system.
 *
 * @param users used to store the user data.
 * @param user the user to be logged out.
 * @return true if logged out successfully
 * @return false
 */
bool logout(std::unordered_map<std::string, std::vector<std::string>>& users, userClass& user) {
    user.logout();
    print("Logged out successfully!");
    return true;
}
#endif
