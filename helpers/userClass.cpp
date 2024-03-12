#ifndef USERCLASS_H
#define USERCLASS_H
#include <string>

#include "../include/userInput.h"
#include "./handleFile.h"
#include "./linkedlist.h"
#include "./structures.h"
class userClass {
   private:
    int id;
    std::string username;
    std::string password;
    std::string email;
    std::string phone;
    int dataSize;
    std::unordered_map<std::string, std::vector<std::string>> userCredentials;
    // create a structure to hold the data with dynamic size
    void decrypt(std::string salt, std::string &content) {
        // Decrypt the content
    }
    void encrypt(std::string salt, std::string &content) {
        // Encrypt the content
    }

   public:
    userClass(int id, std::string username, std::string password, std::string email, std::string phone, int dataSize = 0) {
        this->id = id;
        this->username = username;
        this->password = password;
        this->email = email;
        this->phone = phone;
        this->decrypt("salt", this->password);
        this->dataSize = dataSize ? dataSize : 0;
    }
    userClass() {
        this->id = 0;
        this->username = "";
        this->password = "";
        this->email = "";
        this->phone = "";
        this->dataSize = 0;
    }
    bool login(int id, std::string username, std::string password, std::string email, std::string phone, int dataSize) {
        this->id = id;
        this->username = username;
        this->password = password;
        this->email = email;
        this->phone = phone;
        this->dataSize = dataSize;
        init("./data/" + std::to_string(this->id) + ".csv", userCredentials, {3});
        return true;
    }
    bool logout() {
        // Logout the user
        this->id = 0;
        this->username = "";
        this->password = "";
        this->email = "";
        this->phone = "";
        return true;
    }
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
        newData.id = dataSize + 1;
        newData.username = getStr("Enter username: ");
        newData.password = getStr("Enter password: ");
        newData.email = getStr("Enter email: ");
        newData.origin = getStr("Enter origin: ");
        // append the data to the array
        userCredentials[newData.email] = {std::to_string(newData.id), newData.password, newData.email, newData.origin};
        // apend to the file
        std::string filename = "./data/" + std::to_string(this->id) + ".csv";
        bool isAdded = appendFile(filename, std::to_string(newData.id) + "," + newData.username + "," + newData.password + "," + newData.email + "," + newData.origin + "\n");
        if (!isAdded) {
            print("Failed to register!");
            return false;
        } else {
            print("Data added successfully!");
        }
        dataSize++;
        return true;
    }
};
#endif