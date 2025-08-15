#include <iostream>
#include <vector>
#include <string>
using namespace std;


int main() {
    vector<string> oraclePath = {"S", "A", "C", "G"};

    cout << "Oracle path: ";
    for (size_t i = 0; i < oraclePath.size(); i++) {
        cout << oraclePath[i] << (i + 1 < oraclePath.size() ? " -> " : "");
    }
    cout << "\n";
    return 0;
}
