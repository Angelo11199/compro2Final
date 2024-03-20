#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "../include/print.h"
#define SEPERATOR ","  // the seperator used in the csv file to seperate the data
#ifndef HANDLEFILE_H
#define HANDLEFILE_H
#ifdef _WIN32
#include <windows.h>
void checkFolder() {
    // check if the folder exists
    if (GetFileAttributes("data") == INVALID_FILE_ATTRIBUTES) {
        // create the folder if it does not exist
        CreateDirectory("data", NULL);
    }
}
#endif
#if __linux__ || __unix__ || __APPLE__
void checkFolder() {
    // check if the folder exists
    std::ifstream file;
    file.open("./data");
    if (!file.is_open()) {
        print("Folder not found! creating folder...");
        system("mkdir data");
        file.close();
    }
}
#endif

/**
 * @brief Read the file and store the content in a string
 *
 * @param fileName name of the file
 * @param content string to store the content
 * @return true if successful
 * @return false if failed
 */
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
/**
 * @brief Append the content to the file
 *
 * @param fileName  name of the file
 * @param content  content to be appended
 * @return true if successful
 * @return false if failed
 */
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
/**
 * @brief Split the string into a vector
 *
 * @param str string to be split
 * @param delimiter the delimiter to split the string
 * @param vec  vector to store the split string
 */
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
/**
 * @brief Get the row from the csvData
 *
 * @param value the name of the first column
 * @param csvData the hashmap to store the data
 * @return std::vector<std::string> the row
 * @return std::vector<std::string> empty vector if not found
 */
std::vector<std::string> getRow(const std::string& value, std::unordered_map<std::string, std::vector<std::string>>& csvData) {
    std::vector<std::string> contacts;
    // read csvData and check if the name is in the csvData
    if (csvData.find(value) != csvData.end()) {
        return csvData[value];
    }
    // if not found return empty vector
    return {};
}
/**
 * @brief Get the row from the csvData
 *
 * @param fileName file name
 * @param rowName value of the first column
 * @return true if successfull
 * @return false if not successfull
 */
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
/**
 * @brief update the row in the file
 *
 * @param fileName file name
 * @param colName name of the column to update
 * @param newValue new value to be updated
 * @param indexToUpdate index of the value to be updated
 * @return true if successfull
 * @return false if not successfull
 */
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
/**
 * @brief loads the csv file into a hashmap
 *
 * @tparam T
 * @param content content of the file
 * @param csvData vector to store the data
 * @param indexes indexes of the columns used to search the data
 */
template <typename T>
void init(std::string content, std::unordered_map<std::string, std::vector<T>>& csvData, const std::vector<int>& indexes) {
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
bool createFile(std::string fileName) {
    std::ofstream file;
    file.open(fileName);
    if (file.is_open()) {
        file << "sep=" + std::string(SEPERATOR) + "\n";
        file.close();
        return true;
    } else {
        return false;
    }
}
#endif