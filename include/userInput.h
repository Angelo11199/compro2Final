#ifndef USERINPUT_H
#define USERINPUT_H
#include <iostream>
std::string getStr(std::string prompt = "") {
    std::string s;
    std::cout << prompt;
    getline(std::cin, s);
    return s;
}
double getNum(std::string prompt = "") {
    std::string num;
    char* p;
    while (true) {
        std::cout << prompt;
        std::cin >> num;
        double convertedNum = strtod(num.c_str(), &p);
        if (*p) {
            std::cout << "Invalid input" << std::endl;
        } else {
            std::cin.ignore();
            return convertedNum;
        }
    }
    return 0;
}
#ifdef _WIN32
#include <conio.h>
std::string getStrPrivate(std::string prompt = "") {
    std::string s;
    std::cout << prompt;
    s = _getch();
    while (s != "\r") {
        std::cout << "*";
        s += _getch();
    }
    std::cout << std::endl;
    return s;
}

#endif
#ifdef __unix__
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