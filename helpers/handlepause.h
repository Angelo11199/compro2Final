#ifndef HANDLEPAUSE_H
#define HANDLEPAUSE_H
#include <iostream>
#include <string>
// check if os is windows
#ifdef _WIN32
void clear() {
    system("cls");
}

#endif
// check if os is unix or any other
#ifdef __unix__
#include <stdlib.h>
#include <string.h>
void clear() {
    system("clear");
}
#endif
// check if os is mac
#ifdef __APPLE__
#include <stdlib.h>
#include <string.h>
void clear() {
    system("clear");
}
#endif

void pauseScreen(std::string message = "Press enter to continue...") {
    std::cout << message;
    std::string s;
    getline(std::cin, s);
}

#endif