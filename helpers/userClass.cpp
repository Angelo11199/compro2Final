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
    void setLoggedInUser(User user, int pos = 0) {
        loggedInUser[pos] = user;
    }
    User getLoggedInUser(int pos = 0) {
        return loggedInUser[pos];
    }
    // create a structure to hold the data with dynamic size
    void decrypt(std::string salt, std::string &content) {
        // Decrypt the content
    }
    void encrypt(std::string salt, std::string &content) {
        // Encrypt the content
    }

   public:
    userClass(int id, std::string username, std::string password, std::string email, std::string phone, int dataSize = 0, int pos = 0) {
        this->login(id, username, password, email, phone, dataSize);
        this->decrypt("salt", this->current.password);
    }
    bool login(int id, std::string username, std::string password, std::string email, std::string phone, int dataSize = 0) {
        // check if the user is already logged in
        for (int i = 0; i < 5; i++) {
            if (loggedInUser[i].id == id) {
                print("User already logged in...");
                return true;
            }
        }
        this->current.id = id;
        this->current.username = username;
        this->current.password = password;
        this->current.email = email;
        this->current.phone = phone;
        this->current.dataSize = dataSize;
        this->count++;
        this->setLoggedInUser(this->current, this->count - 1);
        this->decrypt("salt", this->current.password);
        init("./data/" + std::to_string(this->current.id) + ".csv", userCredentials, {3});
        return true;
    }

    bool logout() {
        // Logout the current user
        for (int i = 0; i < 5; i++) {
            if (loggedInUser[i].id != this->current.id) continue;
            // delete the user from the loggedInUser array
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
        for (auto const &x : userCredentials) {
            tableData data;
            data.id = std::stoi(x.second[0]);
            data.username = x.first;
            data.password = x.second[1];
            data.email = x.second[2];
            data.origin = x.second[3];
            print("ID: " + std::to_string(data.id) + " Username: " + data.username + " Password: " + data.password + " Email: " + data.email + " Origin: " + data.origin);
        }
        // print
        list.display();
        // Get data from the database
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
        if (userCredentials.find(email) != userCredentials.end()) {
            return "ID: " + userCredentials[email][0] + " Username: " + email + " Password: " + userCredentials[email][1] + " Email: " + userCredentials[email][2] + " Origin: " + userCredentials[email][3];
        }
        return "Data not found!";
    }
    bool switchUser(int id) {
        // search for the user
        for (int i = 0; i < 5; i++) {
            if (loggedInUser[i].id != id) continue;
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