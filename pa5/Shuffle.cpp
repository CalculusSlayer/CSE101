// -----------------------------------------------------------------------------
//  Nayeel Imtiaz, naimtiaz
//  2022 Spring CSE101 PA5
//  Shuffle.cpp
//  This file contains code for the main shuffle program.
// -----------------------------------------------------------------------------

#include "List.h"
#include <iomanip>

using namespace std;

void shuffle(List& D);

void shuffle(List& D) {
    List a, b;
    int size_D = D.length() / 2;
    D.moveFront();
    for (int i = 0; i < size_D; i++) {
        a.insertBefore(D.moveNext());
    }
    for (int i = 0; i < D.length()-size_D; i++) {
        b.insertBefore(D.moveNext());
    }
    //cout << a << " " << b << endl;
    a.moveFront();
    b.moveFront();

    for (int i = 0; i < size_D; i++) {
        a.insertBefore(b.peekNext());
        a.moveNext();
        b.eraseAfter();
    }

    if (b.length() == 1) {
        a.moveBack();
        a.insertAfter(b.peekNext());
        b.eraseAfter();
    }

    D = a;
}

int main(int argc, char* argv[]) {
    int number_args = atoi(argv[1]);
    if (number_args <= 0) {
        cerr << "Shuffle number is 0 or less." << endl;
        exit(1);
    }

    cout << setw(16) << left << "deck size" << setw(13) << "shuffle count" << endl;
    cout << string(30, '-') << endl;

    for (int shuffle_s = 1; shuffle_s <= number_args; shuffle_s++) {  
        List l1;
        for (int i = 1; i <= shuffle_s; i++) {
            l1.insertBefore(i);
        }

        List original = l1;
        int count = 0;
        do {
            shuffle(l1);
            count++;
        } while (!(l1 == original));
        cout << " " << setw(16) << left << shuffle_s << setw(16) << left << count << endl;
        // cout << count << endl;
    }
}