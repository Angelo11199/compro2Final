#ifndef structures_H
#define structures_H
#include <string>
struct tableData {
    int id;
    std::string username;
    std::string password;
    std::string email;
    std::string origin;
};

struct User {
    int id;
    std::string username;
    std::string password;
    std::string email;
    std::string phone;
    int dataSize;
    int pos;
};

#endif
