#include <iostream>
#include <map>
#include <string>
using namespace std;

int main() {
    map<string, string> myPile;

    myPile["name"] = "Obinnaya";
    myPile["school"] = "Northwestern";

    cout << myPile["name"] << std::endl;
    cout << myPile["school"] << std::endl;

    return 0;
}