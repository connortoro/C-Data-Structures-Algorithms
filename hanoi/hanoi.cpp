#include <iostream>
using namespace std;

int moves;
void hanoi(int n, int start, int end);
void printMove(int start, int end);

int main() {
    moves = 0;
    hanoi(10, 1, 3);
    cout << moves << endl;
}



void hanoi(int n, int start, int end){

    int other = 6 - (start + end);

    //base case
    if(n == 1) {
        printMove(start, end);
        moves++;
        return;
    }

    //Move all the discs, except biggest, to other column
    hanoi(n-1, start, other);

    //Move the biggest disc to the ending column
    printMove(start, end);
    moves++;

    //Move the remaining disc pile ontop of the biggest disc.
    hanoi(n-1, other, end);

}



void printMove(int start, int end){
    cout << start << " -→ " << end << endl;
}
