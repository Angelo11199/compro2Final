#ifndef USERCLASS_H
#define USERCLASS_H
#include <string>

#include "../include/userInput.h"
#include "./handleFile.h"
#include "./linkedlist.h"
#include "./structures.h"
/**
 * @brief userClass is a class that handles the user data.
 *
 */
class userClass {
   private:
    User current;
    User loggedInUser[5];
    int count = 0;
    std::unordered_map<std::string, std::vector<std::string>> userCredentials;
    /**
     * @brief Set the Logged In User object
     *
     */

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
    /**
     * @brief Get the Logged In User object
     *
     * @param pos the position of the user to get
     * @return User the user object
     */
    User getLoggedInUser(int pos = 0) {
        return loggedInUser[pos];
    }
    /**
     * @brief Ghost function
     *
     * @param salt
     * @param content
     */
    void decrypt(std::string salt, std::string &content) {
        // Decrypt the content
    }
    /**
     * @brief Ghost function
     *
     * @param salt
     * @param content
     */
    void encrypt(std::string salt, std::string &content) {
        // Encrypt the content
    }

   public:
    userClass() {}
    /**
     * @brief Construct a new user Class object
     *
     * @param id
     * @param username
     * @param password
     * @param email
     * @param phone
     * @param dataSize
     * @param pos
     */
    userClass(int id, std::string username, std::string password, std::string email, std::string phone, int dataSize = 0, int pos = 0) {
        this->login(id, username, password, email, phone, dataSize);
        this->decrypt("salt", this->current.password);
    }
    /**
     * @brief login the user and set the current user to the logged in user
     *
     * @param id
     * @param username
     * @param password
     * @param email
     * @param phone
     * @param dataSize
     * @return true
     * @return false
     */
    bool login(int id, std::string username, std::string password, std::string email, std::string phone, int dataSize = 0) {
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
        this->setLoggedInUser(this->current);
        this->count++;
        checkFolder();
        init("./data/" + std::to_string(this->current.id) + ".csv", userCredentials, {0});
        pauseScreen();
        return true;
    }
    /**
     * @brief logs out the user and sets the current user to null
     *
     * @return true if logged out successfully
     * @return false if failed to logout
     */
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
    /**
     * @brief Generates a random password
     *
     * @param len the length of the password
     * @return std::string
     */
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
    /**
     * @brief gets the data of the current user and prints it
     *
     * @param offset the offset of the data
     * @param limit the limit of the data
     */
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
    /**
     * @brief Export the data to a csv file
     * @file date_time.csv
     *
     */
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
    /**
     * @brief Insert data to the userCredentials
     *
     * @return true if inserted successfully
     * @return false if failed to insert
     */
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
    /**
     * @brief search for the user and prints the data
     *
     * @param email the email to search for
     * @return std::string the result
     */
    std::string *search(std::string email = "") {
        std::string *result = nullptr;
        // search for all possible data
        print("Searching for " + email + "...");
        for (auto const &x : userCredentials) {
            // 1,test,password,email,origin
            if (x.second[3] == email) {
                print("Data found!");
                print("ID: " + x.second[0]);
                print("Username: " + x.first);
                print("Password: " + x.second[1]);
                print("Email: " + x.second[2]);
                print("Origin: " + x.second[3]);
            }
        }
        return result;
    }
    /**
     * @brief switches the logged in user
     *
     * @param id the id of the user to switch to
     * @return true if switched successfully
     * @return false if failed to switch user
     */
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
    /**
     * @brief Get the Logged In Users object
     *
     * @return User* the logged in users
     */
    User *getLoggedInUsers() {
        return loggedInUser;
    }

    ~userClass() {
        // Destructor
    }
};
#endif