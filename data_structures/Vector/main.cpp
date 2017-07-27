#include <iostream>
#include "vector.h"

using namespace std;

int main() {
    vector a;
    for (int i = 0; i < 5; ++i) {
        a.push_back(string(i + 1, i + 'a'));
    }
    for (int i = 0; i < a.size(); ++i) {
        cout << a[i] << endl;
    }
    cout << endl;
    while (a.size() > 0) {
        cout << a.back() << endl;
        a.pop_back();
    }
    cout << "I'm here" << endl;

    a = vector();
    for (int i = 0; i < 10; ++i) {
        a.push_back(string(i + 1, i + '0'));
    }
    cout << endl;
    for (int i = 0; i < a.size(); ++i) {
        cout << a[i] << endl;
    }
    cout << "Erase a[5]" << endl;
    a.erase(a.begin() + 5);
    for (int i = 0; i < a.size(); ++i) {
        cout << a[i] << endl;
    }
    cout << endl;
    cout << "Insert !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! at 5" << endl;
    a.insert(a.begin() + 5, string("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"));
    for (int i = 0; i < a.size(); ++i) {
        cout << a[i] << endl;
    }
    cout << endl;
    cout << "b = a" << endl;
    vector b = a;
    cout << "b.size() = " << b.size() <<  endl;
    for (int i = 0; i < b.size(); ++i) {
        cout << b[i] << endl;
    }
    cout <<"The end";
    return 0;
}
