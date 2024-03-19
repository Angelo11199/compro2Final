#include <iostream>

#include "./helpers/consoleprint.h"
#include "./include/print.h"

using namespace std;

int main(int argc, char const *argv[]) {
    int maxWidth = getWidth();
    for (int i = 0; i < 3; i++) {
        if (i % 2 == 1) {
            print(centerText("Hello", maxWidth, '|'));
            print(shortenText("Hello", 3));
        }
        if (i % 2 == 0) {
            for (int i = 0; i < maxWidth; i++) {
                cout << "-";
            }
        }
    }
    tablePrint table(3, maxWidth, new string[3]{"Name", "Age", "Section"});
    table.printHeaders();
    table.printRow(new string[3]{"John Doe", "20", "A"});
    table.printRow(new string[3]{"Jane Doe", "21", "B"});
    table.printRow(new string[3]{"John Doe asdasd", "20", "A"});
    table.printRow(new string[3]{"Jane Doe", "21", "B"});

    /* code */
    return 0;
}
