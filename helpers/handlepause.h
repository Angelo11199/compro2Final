#ifndef HANDLEPAUSE_H
#define HANDLEPAUSE_H
#include <iostream>
#include <string>
// check if os is windows
#ifdef _WIN32
/**
 * @brief clear the terminal for windows
 *
 */
void clear() {
    system("cls");
}
#endif
#ifdef __APPLE__
#include <stdlib.h>
#include <string.h>
/**
 * @brief clear the terminal for mac
 *
 */
void clear() {
    system("clear");
}
#endif
// check if os is unix or any other
#ifdef __unix__
#include <stdlib.h>
#include <string.h>
/**
 * @brief clear the terminal for unix
 *
 */
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

/**
 * @brief pauses the screen and waits for user to press enter
 *
 * @param message  message to be displayed
 */
void pauseScreen(std::string message = "Press enter to continue...") {
    std::cout << message;
    std::string s;
    getline(std::cin, s);
}
#endif