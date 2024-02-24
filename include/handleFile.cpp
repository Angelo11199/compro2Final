#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "./print.cpp"
#define SEPERATOR "|"  // the seperator used in the csv file to seperate the data

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
void readCSV(std::string fileName, std::unordered_map<std::string, std::vector<std::string>>& csvData) {
    std::string content;
    if (readFile(fileName, content)) {
        std::string line;
        std::string key;
        std::vector<std::string> values;
        bool firstLine = true;
        for (int i = 0; i < content.length(); i++) {
            if (content[i] == '\n') {
                if (firstLine) {
                    firstLine = false;
                    continue;
                }
                csvData[key] = values;
                key = "";
                values.clear();
            } else if (content[i] == SEPERATOR[0]) {
                values.push_back(line);
                line = "";
            } else {
                line += content[i];
            }
        }
    }
}
