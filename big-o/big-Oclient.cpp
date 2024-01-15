#include <iostream>
using namespace std;

#include "big-O.h"

int main() {
    const int size = 6;
    int arr[size] = { -1, 12, -3, 14, -4, 3 };

    cout << algoC(arr, size);

}
