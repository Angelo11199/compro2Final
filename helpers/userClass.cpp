#ifndef USERCLASS_H
#define USERCLASS_H

#include <string>
class userClass {
    private:
        int id;
        std::string username;
        std::string password;
        std::string email;
        std::string phone;
    void decrypt(std::string salt, std::string&content) {
        // Decrypt the content
    }
    void encrypt(std::string salt, std::string&content) {

        // Encrypt the content
    }
    public:
    void getDataPaginated(int offset=0, int limit= 20) {
        // Get data from the database
    }
    userClass(int id, std::string username, std::string password, std::string email, std::string phone, std::string fileName="user.csv") {
        this->id = id;
        this->username = username;
        this->password = password;
        this->email = email;
        this->phone = phone;
        this->decrypt("salt", this->password);
    }
    userClass() {
        this->id = 0;
        this->username = "";
        this->password = "";
        this->email = "";
        this->phone = "";
    }
    bool login(int id, std::string username, std::string password, std::string email, std::string phone) {
        // Login the user
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
    

};
#endif