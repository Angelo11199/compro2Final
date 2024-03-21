#ifndef CONSOLEPRINT_H
#define CONSOLEPRINT_H
#include <iomanip>
#include <string>
#include <vector>

#include "../include/print.h"
#ifdef _WIN32
#include <windows.h>  // Include the necessary header file
/**
 * @brief Get the Width of the terminal
 *
 * @return int width of the terminal
 */
int getWidth() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    return columns;
}
/**
 * @brief Get the Height of the terminal
 *
 * @return int height of the terminal
 */
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
/**
 * @brief Get the Width of the terminal
 *
 * @return int width of the terminal
 */
int getWidth() {
    // get total characters that can fit in a row
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    return size.ws_col;
}
/**
 * @brief Get the Height of the terminal
 *
 * @return int height of the terminal
 */
int getHeight() {
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    return size.ws_row;
}
#endif

#ifdef __APPLE__
#include <sys/ioctl.h>
#include <unistd.h>
/**
 * @brief Get the Width of the terminal
 *
 * @return int width of the terminal
 */
int getWidth() {
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    return size.ws_col;
}
/**
 * @brief Get the Height of the terminal
 *
 * @return int height of the terminal
 */
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
/**
 * @brief Shorten the text to fit the given width
 *
 * @param text The text to be shortened
 * @param maxTextWidth The maximum width of the text
 * @return string The shortened text
 */
std::string shortenText(const std::string& text, int maxTextWidth) {
    if (text.size() <= maxTextWidth) return text;
    return text.substr(0, maxTextWidth) + "...";
}
// for apple usrs
/**
 * @brief Print the text in the center of the terminal
 *
 * @param lines lines to be printed
 * @param maxWidth the maximum width of the terminal. Default is 0
 * @param sideChar side character to be used. Default is empty space
 */
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
/**
 * @brief Print the text in the center horizontally and lower vertically of the terminal
 *
 * @param lines lines to be printed (Vector)
 * @param maxWidth the maximum width of the terminal. Default is 0
 * @param sideChar side character to be used. Default is empty space
 */
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
/**
 * @brief Print the text in the center horizontally and upper vertically of the terminal
 *
 * @param lines lines to be printed (Vector)
 * @param maxWidth the maximum width of the terminal. Default is 0
 * @param sideChar side character to be used. Default is empty space
 */
class tablePrint {
   private:
    int numColumns;
    std::string* headers;
    int maxRows = 20;
    char sideChar = '|';
    char headerChar = '|';
    char rowChar = '|';

   public:
    /**
     * @brief Construct a new table Print object
     *
     * @param numColumns maximum number of columns
     * @param maxWidth maximum width of the terminal
     * @param headers headers of the table
     */
    tablePrint(int numColumns, int maxWidth, std::string* headers) {
        this->numColumns = numColumns;
        this->headers = headers;
    }
    /**
     * @brief Construct a new table Print object
     *
     * @param numColumns maximum number of columns
     * @param headers headers of the table
     */
    void setMaxRows(int maxRows) {
        this->maxRows = maxRows;
    }
    /**
     * @brief Print the table headers
     *
     * @param rows rows to be printed
     */
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
    /**
     * @brief Print the table rows
     *
     * @param rows rows to be printed
     */
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
    /**
     * @brief Print the table rows
     *
     * @param rows rows to be printed
     */
    ~tablePrint() {
        delete[] headers;
    }
};
/**
 * @brief Print the text in the center horizontally and upper vertically of the terminal
 *
 * @param text The text to be printed
 * @param maxWidth the maximum width of the terminal. Default is 0
 * @param sideChar side character to be used. Default is empty space
 */
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
