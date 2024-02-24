#include <iostream>

#include "./include/snippets.h"
#include "./include/handleFile.cpp"
using namespace std;
int main(int argc, char const *argv[]) {
    string content;
    int index = 0;
    init("data.csv",csvData);
    
    cout << "Content: " << content << endl;
    return 0;

}
