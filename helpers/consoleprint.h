#ifndef CONSOLEPRINT_H
#define CONSOLEPRINT_H
#include <iomanip>
#include <string>

#include "../include/print.h"
#ifdef _WIN32
#include <windows.h>  // Include the necessary header file
int getWidth() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    return columns;
}
int getHeight() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int rows;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    return rows;
}
#endif
#ifdef __unix__
#include <sys/ioctl.h>
#include <unistd.h>
int getWidth() {
    // get total characters that can fit in a row
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    return size.ws_col;
}
int getHeight() {
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    return size.ws_row;
}
#endif

#ifdef __APPLE__
// get the width of the terminal
#include <sys/ioctl.h>
#include <unistd.h>
int getWidth() {
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    return size.ws_col;
}
int getHeight() {
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    return size.ws_row;
}

#endif
std::string centerText(const std::string& text, int maxWidth = 0, char sideChar = ' ') {
    maxWidth = getWidth();
    int totalPadding = maxWidth - text.size() - 2;  // subtract 2 for the side characters
    if (totalPadding < 0) totalPadding = 0;         // prevent negative padding
    int leftPadding = totalPadding / 2;
    int rightPadding = totalPadding - leftPadding;  // in case totalPadding is odd
    return sideChar + std::string(leftPadding, ' ') + text + std::string(rightPadding, ' ') + sideChar;
}
// create a funtion that shorten the text
std::string shortenText(const std::string& text, int maxTextWidth) {
    if (text.size() <= maxTextWidth) return text;
    return text.substr(0, maxTextWidth) + "...";
}
#include <vector>  // Add the missing include directive

void printCenterScreen(const std::vector<std::string>& lines, int maxWidth = 0, char sideChar = ' ') {
    int width = getWidth();
    int height = getHeight();
    // Calculate the vertical padding
    int verticalPadding = (height - lines.size()) / 2;
    // Print the vertical padding
    for (int i = 0; i < verticalPadding; i++) {
        std::cout << std::endl;
    }
    // Print each line of text centered
    for (const auto& line : lines) {
        std::cout << centerText(line, width, sideChar) << std::endl;
    }
}
void printLowerCenter(const std::vector<std::string>& lines, int maxWidth = 0, char sideChar = ' ') {
    int width = getWidth();
    int height = getHeight();
    // Calculate the vertical padding
    int verticalPadding = height - lines.size();
    // Print the vertical padding
    for (int i = 0; i < verticalPadding; i++) {
        std::cout << std::endl;
    }
    // Print each line of text centered
    for (const auto& line : lines) {
        std::cout << centerText(line, width, sideChar) << std::endl;
    }
}
class tablePrint {
   private:
    int numColumns;
    std::string* headers;
    int maxRows = 20;
    char sideChar = '|';
    char headerChar = '|';
    char rowChar = '|';

   public:
    tablePrint(int numColumns, int maxWidth, std::string* headers) {
        this->numColumns = numColumns;
        this->headers = headers;
    }
    void setMaxRows(int maxRows) {
        this->maxRows = maxRows;
    }
    void printHeaders() {
        std::string header = "";
        int maxWidth = getWidth();
        int maxRowWidth = (maxWidth / (numColumns));
        for (int i = 0; i < numColumns; i++) {
            header += centerText(headers[i], maxRowWidth, i % 2 == 1 ? ' ' : headerChar);
        }
        // print a line after the header
        std::string line = "";
        for (int i = 0; i < maxWidth; i++) {
            line += "-";
        }
        print(header);
        print(line);
    }

    void printRow(std::string row[]) {
        std::string rowStr = "";
        std::string line = "";
        int maxWidth = getWidth();
        int maxRowWidth = (maxWidth / numColumns);
        for (int i = 0; i < numColumns; i++) {
            rowStr += centerText(row[i], maxRowWidth, i % 2 == 1 ? ' ' : rowChar);
        }
        for (int i = 0; i < maxWidth; i++) {
            line += "-";
        }
        print(rowStr);
        // print a line after each row
        print(line);
    }
    ~tablePrint() {
        delete[] headers;
    }
};
void printBox(std::string text, int boxWidth = 15, int boxHeight = 1) {
    int textWidth = text.size();
    int textHeight = 1;
    if (textWidth > boxWidth - 2) {
        textWidth = boxWidth - 2;
        text = shortenText(text, textWidth - 5);
        textHeight = text.size() / (boxWidth - 2);
    }
    if (textHeight > boxHeight - 2) {
        textHeight = boxHeight - 2;
    }
    std::string line = "";
    for (int i = 0; i < boxWidth; i++) {
        line += "-";
    }
    print(line);
    for (int i = 0; i < boxHeight - 2; i++) {
        if (i == (boxHeight - 2) / 2) {
            print("|" + centerText(text, boxWidth - 2) + "|");
        } else {
            print("|" + std::string(boxWidth - 2, ' ') + "|");
        }
    }
    print(line);
}
#endif
