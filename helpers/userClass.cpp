#ifndef USERCLASS_H
#define USERCLASS_H
#include <string>

#include "../include/userInput.h"
#include "./handleFile.h"
#include "./linkedlist.h"
#include "./structures.h"
class userClass {
   private:
    User current;
    User loggedInUser[5];
    int count = 0;
    std::unordered_map<std::string, std::vector<std::string>> userCredentials;
    void setLoggedInUser(User user) {
        // set the count to the number of filled users in loggedInUser
        if (this->count > 5 || this->count < 0) {
            for (int i = 0; i < 5; i++) {
                if (!loggedInUser[i].username.empty()) {
                    count++;
                }
            }
        }
        loggedInUser[this->count] = user;
        this->count++;
    }
    User getLoggedInUser(int pos = 0) {
        return loggedInUser[pos];
    }

   public:
    userClass(int id, std::string username, std::string password, std::string email, std::string phone, int dataSize = 0, int pos = 0) {
        this->login(id, username, password, email, phone, dataSize);
    }
    bool login(int id, std::string username, std::string password, std::string email, std::string phone, int dataSize = 0) {
        for (int i = 0; i < 5; i++) {
            if (loggedInUser[i].id == id) {
                print("User already logged in...");
                return true;
            }
        }
        print(username);
        this->current.id = id;
        this->current.username = username;
        this->current.password = password;
        this->current.email = email;
        this->current.phone = phone;
        this->current.dataSize = dataSize;
        print(this->current.username);
        this->setLoggedInUser(this->current);
        this->count++;
        checkFolder();
        init("./data/" + std::to_string(this->current.id) + ".csv", userCredentials, {3});
        pauseScreen();
        return true;
    }

    bool logout() {
        for (int i = 0; i < 5; i++) {
            if (loggedInUser[i].id != this->current.id)
                continue;
            else
                loggedInUser[i] = {};
        }
        updateRow("auth.csv", std::to_string(this->current.id), std::to_string(this->current.dataSize), 5);
        // set the current user to null
        this->current = {};
        this->count--;
        return true;
    }
    userClass() {}
    std::string generatePassword(int len = 20) {
        std::string s;
        static const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz"
            "!@#$%^&*";
        for (int i = 0; i < len; ++i) {
            s += alphanum[rand() % (sizeof(alphanum) - 1)];
        }
        return s;
    }
    void getDataPaginated(int offset = 0, int limit = 20) {
        linkedlist list;
        tableData data;
        while (true) {
            list.deleteAll();
            int count = 0;
            for (auto const &x : userCredentials) {
                if (count < offset) {
                    count++;
                    continue;
                }
                if (count >= offset + limit) {
                    break;
                }
                data.id = std::stoi(x.second[0]);
                data.username = x.first;
                data.password = x.second[1];
                data.email = x.second[2];
                data.origin = x.second[3];
                list.insert(data);
                count++;
            }
            list.display();
            char result = onCharInput("[N] Next page [P] Previous page [E] Exit");
            result = std::toupper(result);
            if (result == 'N') {
                offset += limit;
            } else if (result == 'P' && offset >= limit) {
                offset -= limit;
            } else if (result == 'E') {
                break;
            }
        }
    }
    void exportData() {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        std::string date = std::to_string(1900 + ltm->tm_year) + "-" + std::to_string(1 + ltm->tm_mon) + "-" + std::to_string(ltm->tm_mday);
        std::string time = std::to_string(ltm->tm_hour) + ":" + std::to_string(ltm->tm_min) + ":" + std::to_string(ltm->tm_sec);
        std::string filename = date.append("_").append(time).append(".csv");
        // loop through the data and append to the file
        for (auto const &x : userCredentials) {
            std::string content = x.second[0] + "," + x.first + "," + x.second[1] + "," + x.second[2] + "," + x.second[3] + "\n";
            appendFile(filename, content);
        }
        // open print wizard
        print("Data exported to " + filename);
    }
    bool insertData() {
        tableData newData;
        newData.id = this->current.dataSize + 1;
        newData.username = getStr("Enter username: ");
        newData.password = getStr("Enter password: ");
        newData.email = getStr("Enter email: ");
        newData.origin = getStr("Enter origin: ");
        // append the data to the array
        userCredentials[newData.email] = {std::to_string(newData.id), newData.password, newData.email, newData.origin};
        // apend to the file
        std::string filename = "./data/" + std::to_string(this->current.id) + ".csv";
        bool isAdded = appendFile(filename, std::to_string(newData.id) + "," + newData.username + "," + newData.password + "," + newData.email + "," + newData.origin + "\n");
        if (!isAdded) {
            print("Failed to register!");
            return false;
        } else {
            updateRow("auth.csv", std::to_string(this->current.id), std::to_string(this->current.dataSize + 1), 5);
            print("Data added successfully!");
        }
        this->current.dataSize++;
        return true;
    }
    std::string search(std::string email = "") {
        // search for all possible data
        print("Searching for " + email + "...");
        for (auto const &x : userCredentials) {
            if (x.second[2] == email) {
                print("Data found!");
                print("ID: " + x.second[0]);
                print("Username: " + x.first);
                print("Password: " + x.second[1]);
                print("Email: " + x.second[2]);
                print("Origin: " + x.second[3]);
                return "Data found!";
            }
        }

        return "Data not found!";
    }
    bool switchUser(int id) {
        // search for the user
        for (int i = 0; i < 5; i++) {
            if (loggedInUser[i].id != id) continue;
            // prompt for password
            std::string password = getStrPrivate("Enter your password: ");
            int tries = 0;
            while (password != loggedInUser[i].password) {
                print("Invalid password!");
                tries++;
                if (tries > 3) {
                    print("You have reached the maximum number of tries!");
                    return false;
                }
                password = getStrPrivate("Enter your password: ");
                if (password == loggedInUser[i].password) break;
            }
            this->current = loggedInUser[i];
            init("./data/" + std::to_string(this->current.id) + ".csv", userCredentials, {3});
        }
        return true;
    }
    User *getLoggedInUsers() {
        return loggedInUser;
    }

    ~userClass() {
        // Destructor
    }
};
#endif