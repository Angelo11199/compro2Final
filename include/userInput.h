#ifndef USERINPUT_H
#define USERINPUT_H
#include <iostream>
/**
 * @brief Get the user input as string
 *
 * @param prompt message to be displayed
 * @return std::string user input
 */
std::string getStr(std::string prompt = "") {
    std::string s;
    std::cout << prompt;
    getline(std::cin, s);
    return s;
}
/**
 * @brief Get an integer from the user with error checking
 *
 * @param prompt  message to be displayed
 * @return int  user input
 */
int getNum(std::string prompt = "") {
    std::string num;
    char* p;
    while (true) {
        std::cout << prompt;
        std::cin >> num;
        int n = strtol(num.c_str(), &p, 10);
        // check if the string is a number
        if (*p) {
            std::cout << "Invalid input! Please enter a number." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        } else {
            std::cin.ignore(10000, '\n');
            return n;
        }
    }
    return 0;
}
/**
 * @brief Get the user input as char
 *
 * @param prompt message to be displayed
 * @return char user input
 */
char onCharInput(std::string prompt = "") {
    char c;
    // gets char  input without pressing enter
    std::cout << prompt;
    std::cin >> c;
    std::cin.ignore(10000, '\n');
    return c;
}
#ifdef _WIN32
#include <conio.h>
/**
 * @brief Get string input without echoing to the console
 *
 * @param prompt  message to be displayed
 * @return std::string user input
 */
std::string getStrPrivate(std::string prompt = "") {
    // get user input without echoing to the console for WINDOWS
    std::string s;
    print(prompt);
    char ch;
    while (true) {
        ch = _getch();
        if (ch == 13) {
            std::cout << std::endl;
            return s;
        } else if (ch == 8) {
            if (s.length() > 0) {
                std::cout << "\b \b";
                s.pop_back();
            }
        } else {
            s.push_back(ch);
            std::cout << "*";
        }
    }

    return s;
}
#endif
#ifdef __unix__
/**
 * @brief Get string input without echoing to the console
 *
 * @param prompt  message to be displayed
 * @return std::string user input
 */
std::string getStrPrivate(std::string prompt = "") {
    // get user input without echoing to the console for LINUX
    std::string s;
    std::cout << prompt;
    system("stty -echo");
    getline(std::cin, s);
    system("stty echo");
    std::cout << std::endl;
    return s;
}
#endif
#ifdef __APPLE__
/**
 * @brief Get string input without echoing to the console
 *
 * @param prompt  message to be displayed
 * @return std::string user input
 */
std::string getStrPrivate(std::string prompt = "") {
    // get user input without echoing to the console for LINUX
    std::string s;
    std::cout << prompt;
    system("stty -echo");
    getline(std::cin, s);
    system("stty echo");
    std::cout << std::endl;
    return s;
}
#endif
#endif