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
std::string centerText(const std::string& text, int maxWidth, char sideChar = ' ') {
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
        print("");
        for (int i = 0; i < numColumns; i++) {
            header += centerText(headers[i], maxWidth / numColumns, headerChar);
        }
        print(centerText(header, maxWidth, sideChar));
    }
    void printRow(std::string row[]) {
        std::string rowStr = "";
        std::string line = "";
        int maxWidth = getWidth();
        for (int i = 0; i < maxWidth; i++) {
            line += "-";
        }
        for (int i = 0; i < numColumns; i++) {
            rowStr += centerText(shortenText(row[i], (maxWidth / numColumns) - 5), maxWidth / numColumns, rowChar);
        }
        print(centerText(rowStr, maxWidth, sideChar));
        // print a line after each row
        print(line);
    }
    ~tablePrint() {
        delete[] headers;
    }
};
#endif
