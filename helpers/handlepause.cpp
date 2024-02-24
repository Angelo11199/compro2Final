#include <string>
// check if os is windows
#ifdef _WIN32
void clear() {
    system("cls");
}

void pause(std::string message = "") {
    std::cout << message;
    system("pause");
}
#endif
// check if os is unix or any other
#ifdef __unix__ || __linux__ || __APPLE__
#include <stdlib.h>
#include <string.h>
void clear() {
    system("clear");
}
void pause(std::string message = "Press any key to continue...") {
    std::string command = "read -n 1 -s -p \"" + message + "\"";
    char charCommand[command.length() + 1];
    strcpy(charCommand, command.c_str());
    system(charCommand);
    system("read -n 1 -s -p \"Press any key to continue...\"");
}
#endif
