#include <iostream>
using namespace std;
#include "stack_L_T.h"

int main() {
    Stack<int> s;
    s.push(3);
    s.push(4);
    s.push(5);

    Stack<int> c;
    c = s;
    c.getTop()++;

    cout << "ORIGINAL: " << endl << s << endl;
    cout << "COPY: " << endl << c << endl;
}
