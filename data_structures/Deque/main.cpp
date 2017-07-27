#include <iostream>
#include "deque.h"

using namespace std;

int main() {
    deque a;
    for (int i = 0; i < 5; ++i) {
        a.push_back(string(i + 1, i + 'a'));
    }
    for (int i = 0; i < a.size(); ++i) {
        cout << a[i] << endl;
    }
    cout << endl;
    deque b = a;
    while (b.size() > 0) {
        cout << b.back() << endl;
        b.pop_back();
    }
    cout << "I'm here" << endl;
    a = deque();
    for (int i = 0; i < 10; ++i) {
        a.push_back(string(i + 1, i + '0'));
        cout << a[i] << endl;
    }

    cout << "Erase a[5]" << endl;
    a.erase(a.begin() + 5);
    for (int i = 0; i < a.size(); ++i) {
        cout << a[i] << endl;
    }

    a.push_front("saf");
    a.pop_back();
    for (int i = 0; i < a.size(); ++i) {
        cout << a[i] << endl;
    }

    cout <<"The end";
    return 0;
}
