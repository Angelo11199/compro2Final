#ifndef SNIPPETS_H
#define SNIPPETS_H

// Existing code in snippets.h

// #include <conio.h>

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#define SEPERATOR "|"  // the seperator used in the csv file to seperate the data

// the hashmap to store the data
std::unordered_map<std::string, std::vector<std::string>> csvData;

// prints in a new line
template <typename T>
void print(T Value) {
    std::cout << Value << std::endl;
}
// Prints in the same line
template <typename U>
void printLn(U s) {
    std::cout << s;
};
// gets a number from the user
double getNum(std::string prompt = "") {
    std::string num;
    char* p;
    do {
        std::cout << prompt;
        std::cin >> num;
        double convertedNum = strtod(num.c_str(), &p);
        if (*p) {
            std::cout << "Invalid input" << std::endl;
        } else {
            std::cin.ignore();
            return convertedNum;
        }
    } while (true);
    return 0;
}

// gets a string from the user
std::string getStr(std::string prompt = "") {
    std::string s;
    std::cout << prompt;
    getline(std::cin, s);
    return s;
}

// reads the file and returns in string content memory address. returns true if successful
bool readFile(std::string fileName, std::string& content) {
    std::ifstream file;
    file.open(fileName);
    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            content += line + "\n";
        }
        file.close();
        return true;
    } else {
        print("File not found! creating file...");
        std::ofstream file;
        file.open(fileName);
        if (file.is_open()) {
            print("File created successfully!");
            file << "sep=" + std::string(SEPERATOR) + "\n";
            file.close();
            return true;
        } else {
            return false;
        }
        return false;
    }
}

// adds data to the file. returns true if successful
bool appendFile(std::string fileName, std::string content) {
    std::ofstream file;
    // open the file in append mode
    file.open(fileName, std::ios::app);
    if (file.is_open()) {
        // write the content to the file
        file << content;
        file.close();
        return true;
    } else {
        return false;
    }
}
// splits the string into a vector
void splitData(std::string str, std::string delimiter, std::vector<std::string>& vec) {
    // split the string into a vector (just like an array but can change size)
    size_t pos = 0;
    std::string token;
    while ((pos = str.find(delimiter)) != std::string::npos) {
        token = str.substr(0, pos);
        vec.push_back(token);
        str.erase(0, pos + delimiter.length());
    }
    vec.push_back(str);
}
// gets the row from the csvData. Args : search value
std::vector<std::string> getRow(const std::string& value) {
    std::vector<std::string> contacts;
    // read csvData and check if the name is in the csvData
    if (csvData.find(value) != csvData.end()) {
        return csvData[value];
    }
    // if not found return empty vector
    return {};
}

// deletes the row. Args : filename, the name of the first column
bool deleteRow(std::string fileName, std::string rowName) {
    std::string contents;
    readFile(fileName, contents);
    std::vector<std::string> data;
    splitData(contents, "\n", data);
    // loop through the data and add the indexes element to the hashmap
    for (int i = 0; i < data.size() - 1; i++) {
        std::vector<std::string> row;
        splitData(data[i], SEPERATOR, row);
        if (row[0] == rowName) {
            data.erase(data.begin() + i);
            std::string newContent;
            for (int j = 0; j < data.size() - 1; j++) {
                newContent += data[j] + "\n";
            }
            std::ofstream file;
            file.open(fileName);
            if (file.is_open()) {
                file << newContent;
                file.close();
                return true;
            } else {
                return false;
            }
        }
    }
    return false;
}
// updates the row. Args : filename, the name of the first column, the new value, the index to update
bool updateRow(std::string fileName, std::string colName, std::string newValue, int indexToUpdate) {
    std::string contents;
    readFile(fileName, contents);
    std::vector<std::string> data;
    splitData(contents, "\n", data);
    // loop through the data and add the indexes element to row vector
    for (int i = 0; i < data.size() - 1; i++) {
        std::vector<std::string> row;
        splitData(data[i], SEPERATOR, row);
        if (row[0] != colName) continue;
        row[indexToUpdate] = newValue;
        data[i] = "";
        for (int j = 0; j < row.size() - 1; j++) data[i] += row[j] + SEPERATOR;
        data[i] += row[row.size() - 1];
        std::string newContent;
        for (int j = 0; j < data.size() - 1; j++) newContent += data[j] + "\n";
        // write the new content to the file
        std::ofstream file;
        file.open(fileName);
        if (!file.is_open()) return false;
        i == 0 && file << "sep=" + std::string(SEPERATOR) + "\n";
        file << newContent;
        file.close();
        return true;
    }
    return true;
}
// pauses the program and waits for the user to press a key before continuing
void pauseProgram() {
    print("press any key to continue...");
    // getch();
}

// initializes the csvData. Args : filename, the hashmap to store the data, the indexes used for searching
void init(std::string content, std::unordered_map<std::string, std::vector<std::string>>& csvData, const std::vector<int>& indexes) {
    std::string contents;
    print("Initializing...");
    readFile(content, contents)
        ? print(content + " read successfully.")
        : print(content + " read failed.");
    std::vector<std::string> data;
    std::vector<std::string> fields;
    splitData(contents, "\n", data);
    // checks if the first line is sep=SEPERATOR
    if (data[0].substr(0, 4) == "sep=") {
        data.erase(data.begin());
    }
    // loop through the data and add the indexes element to the hashmap
    for (int i = 0; i < data.size(); i++) {
        std::vector<std::string> row;
        if (data[i].empty()) continue;
        splitData(data[i], SEPERATOR, row);
        for (int j = 0; j < indexes.size(); ++j) {
            csvData[row[indexes[j]]] = row;
        }
    }
    print("Initialization complete.");
}
#endif
