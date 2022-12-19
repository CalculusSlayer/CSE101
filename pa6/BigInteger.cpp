// -----------------------------------------------------------------------------
//  Nayeel Imtiaz, naimtiaz
//  2022 Spring CSE101 PA6
//  BigInteger.cpp
//  This file contains code for BigInteger ADT functions.
// -----------------------------------------------------------------------------

#include "BigInteger.h"
#include "List.h"
#include <stdexcept>
#include <ctype.h> // isdigit

int power = 9;  // hardcode power to 9
long base = 1000000000; // hardcode base to billion

// BigInteger()
// Constructor that creates a new BigInteger in the zero state: 
// signum=0, digits=().
BigInteger::BigInteger() {
    signum = 0;
}

// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s) {
    if (s.length() == 0) {
        throw std::invalid_argument("Length of string argument is 0\n");
        // return; // not necessary?
    }
    else if (s[0] == '+') {
        signum = 1;
        s = s.substr(1, s.length());
    }
    else if (s[0] == '-') {
        signum = -1;
        s = s.substr(1, s.length());
    }
    else {
        signum = 1;
    }

    // if (std::stol(s) == 0) {
    //     signum = 0;
    //     return;
    // }

    for (char const &c: s) {
        if (!isdigit(c)) {
            throw std::invalid_argument("There is a non-digit in string argument\n");
        }
    }

    bool exit1 = false;
    for (int start = s.length() - power; ; start -= power) {
        if (start < 0) {
            digits.insertAfter(std::stol(s.substr(0, start + power)));
            exit1 = true;
        }

        else if (start == 0) {
            digits.insertAfter(std::stol(s.substr(start, power)));
            exit1 = true;
        }
        else {
            digits.insertAfter(std::stol(s.substr(start, power)));
        }

        if (exit1) {
            break;
        }
    }

    digits.moveFront();
    while (digits.position() < digits.length() && digits.peekNext() == 0) {
        digits.eraseAfter();
        digits.moveNext();
    }

    if (digits.length() == 0) {
        signum = 0;
    }
}

// BigInteger()
// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger& N) {
    this->signum = N.signum;
    this->digits = N.digits;
}

// Optional Destuctor
// ~BigInteger()
// ~BigInteger();


// Access functions --------------------------------------------------------

// sign()
// Returns -1, 1 or 0 according to whether this BigInteger is positive, 
// negative or 0, respectively.
int BigInteger::sign() const {
    return this->signum;
}

// compare()
// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger& N) const {
    if (this->signum > N.signum) {
        return 1;
    }
    else if (this->signum < N.signum) {
        return -1;
    }
    else if (this->signum == 0 && N.signum == 0) {
        return 0;
    }

    List this_copy = this->digits;
    List N_copy = N.digits;
    if (this->signum == 1 && N.signum == 1) {            // check here?
        if (this_copy.length() != N_copy.length()) {
            if (this_copy.length() > N_copy.length()) {
                return 1;
            }
            else {
                return -1;
            }
        }

        this_copy.moveFront();
        N_copy.moveFront();
        for (;this_copy.position() < this_copy.length(); this_copy.moveNext(), N_copy.moveNext()) {
            if (this_copy.peekNext() > N_copy.peekNext()){
                return 1;
            }
            else if (this_copy.peekNext() < N_copy.peekNext()) {
                return -1;
            }
        }
        return 0;
    }

   if (signum == -1 && N.signum == -1) {            // check here?
        if (this_copy.length() != N_copy.length()) {
            if (this_copy.length() > N_copy.length()) {
                return -1;  // bigger magnitude means smaller number for negatives
            }
            else {
                return 1;
            }
        }

        this_copy.moveFront();
        N_copy.moveFront();
        for (;this_copy.position() < this_copy.length(); this_copy.moveNext(), N_copy.moveNext()) {
            if (this_copy.peekNext() > N_copy.peekNext()){
                return -1;
            }
            else if (this_copy.peekNext() < N_copy.peekNext()) {
                return 1;
            }
        }
        return 0;
    }

    else {
        std::cerr << "something went wrong" << std::endl;
        return 69;
    }

}


// Manipulation procedures -------------------------------------------------

// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero() {
    signum = 0;
    digits.clear();
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of 
// this BigInteger positive <--> negative. 
void BigInteger::negate() {
    signum *= -1;
}

// helper functions ---------------------------------

// negateList()
// Changes the sign of each integer in List L. Used by sub().
void negateList(List& L);

void negateList(List& L) {
    L.moveFront();
    while (L.position() < L.length()) {
        L.setAfter(-1 * L.peekNext());
        L.moveNext();
    }
}

// sumList()
// Overwrites the state of S with A + sgn*B (considered as vectors).
// Used by both sum() and sub().
void sumList(List& S, List A, List B, int sgn);

void sumList(List& S, List A, List B, int sgn) {
    // multiply every element in B by 'sgn'
    S.clear();

    B.moveFront();
    while (B.position() < B.length()) {
        B.setAfter(sgn * B.peekNext());
        B.moveNext();
    }

    A.moveBack();
    B.moveBack();

    while (A.position() > 0 && B.position() > 0) {
        S.insertAfter(A.peekPrev() + B.peekPrev());
        A.movePrev();
        B.movePrev();
    }

    while (A.position() > 0) {
        S.insertAfter(A.peekPrev());
        A.movePrev();
    }

    while (B.position() > 0) {
        S.insertAfter(B.peekPrev());
        B.movePrev();
    }

    S.moveFront();
    while (S.front() == 0 && S.length() > 1) {
        S.eraseAfter();
    }

}

// normalizeList()
// Performs carries from right to left (least to most significant
// digits), then returns the sign of the resulting integer. Used
// by add(), sub() and mult().
int normalizeList(List& L);

// CITE: Code is partially inspired from Tutor Norton Choy
int normalizeList(List& L) {
    if (L.front() == 0) {
        return 0;
    }

    // bool pos_carry = false;
    // bool neg_carry = false;
    int sig1 = 1;

    if (L.front() < 0) {
        negateList(L);
        sig1 = -1;
    }

    L.moveBack();
    ListElement num = 0;
    int carry = 0;
    while (L.position() > 0) {
        num = L.peekPrev();
        if (num < 0) {
            num += base + carry;
            L.setBefore(num);
            carry = -1;
        }
        else {
            num += carry;
            carry = 0;
            if (num >= base) {
                carry = num / base;
                num = num % base;
            }
            L.setBefore(num);
        }

        L.movePrev();
    //     if (L.peekPrev() >= base) {
    //         pos_carry = true;
    //         L.setBefore(L.peekPrev() - base)
    //     }
    //     else {
    //         pos_carry = false;
    //     }
    //     if (pos_carry) {
    //         L.setBefore(L.peekPrev() + 1);
    //     }
    // }

    // if (pos_carry) {
    //     L.moveFront();
    //     L.insertAfter(1); // is casting to a long necessary?
    }

    if (carry != 0) {
        L.moveFront();
        L.insertAfter(carry);
    }

    return sig1;
}
// shiftList()
// Prepends p zero digits to L, multiplying L by base^p. Used by mult().
void shiftList(List& L, int p) {
    L.moveBack();
    for (int i = 0; i < p; i++) {
        L.insertAfter(0);
    }
}

// scalarMultList()
// Multiplies L (considered as a vector) by m. Used by mult().
void scalarMultList(List& L, ListElement m) {
    L.moveFront();
    while (L.position() < L.length()) {
        L.setAfter(L.peekNext() * m);
        L.moveNext();
    }
}


// BigInteger Arithmetic operations ----------------------------------------

// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const {
    BigInteger sum;
    List sum_list;
    List this_copy = this->digits;
    List N_copy = N.digits;

    if (this->signum == 1 && N.signum == 1) {
        sumList(sum_list, this_copy, N_copy, 1);
        sum.signum = normalizeList(sum_list);
        sum.digits = sum_list;
    }

    else if (this->signum == -1 && N.signum== -1) {
        negateList(this_copy);
        negateList(N_copy);
        sumList(sum_list, this_copy, N_copy, 1);
        sum.signum = normalizeList(sum_list);
        sum.digits = sum_list;
    }

    else {
        if (this->signum < 0) {
            negateList(this_copy);
        }
        if (N.signum < 0) {
            negateList(N_copy);
        }

        sumList(sum_list, this_copy, N_copy, 1);
        sum.signum = normalizeList(sum_list);
        sum.digits = sum_list;
    }

    return sum;
}

// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const {
    BigInteger dif;
    BigInteger copy_param = N;
    negateList(copy_param.digits);

    dif = this->add(copy_param);
    return dif;
}

// mult()
// Returns a BigInteger representing the product of this and N. 
BigInteger BigInteger::mult(const BigInteger& N) const {
    BigInteger r;
    if (this->signum == 0 || N.signum == 0) {
        return r;
    }

    List product;
    product.insertAfter(0);
    List B;

    //List this_copy = this->digits;
    List N_copy = N.digits;

    N_copy.moveBack();
    int shift = 0;
    while (N_copy.position() > 0) {
        B = this->digits;
        scalarMultList(B, N_copy.peekPrev());
        shiftList(B, shift);
        //std::cout << B << std::endl;
        List product_copy = product;
        sumList(product, product_copy, B, 1);
        //std::cout << "unnormal: " << product << std::endl;
        normalizeList(product);
        //std::cout << "normal: " << product << std::endl;
        N_copy.movePrev();
        shift += 1;
        //std::cout << "shift: " << shift << " " << N_copy.position() << std::endl;
    }

    r.digits = product;
    if (this->signum == N.signum) {
        r.signum = 1;
    }
    else {
        r.signum = -1;
    }

    return r;

}


// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string 
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string BigInteger::to_string() {
    if (this->signum == 0) {
        return "0";
    }

    std::string r = "";
    if (this->signum == -1) {
        r += "-";
    }

    digits.moveFront();
    while (digits.front() == 0 && digits.length() > 1) {
        digits.eraseAfter();
    }

    for (digits.moveFront(); digits.position() < digits.length(); digits.moveNext()) {
        std::string a = std::to_string(digits.peekNext()); // 4 power=3 400
        std::string b = "";
        while ((int) (b.length() + a.length()) < power && digits.position() != 0) { // 
            b += '0';
        }
        //std::reverse(a.begin(), a.end()); // 004
        r += (b+a);

    }

    return r;
}


// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ) {
    return stream << N.BigInteger::to_string();
}

// operator==()
// Returns true if and only if A equals B. 
bool operator==( const BigInteger& A, const BigInteger& B ) {
    if (A.compare(B) == 0) {
        return true;
    }
    else {
        return false;
    }
}

// operator<()
// Returns true if and only if A is less than B. 
bool operator<( const BigInteger& A, const BigInteger& B ) {
    if (A.compare(B) == -1) {
        return true;
    }
    else {
        return false;
    }    
}

// operator<=()
// Returns true if and only if A is less than or equal to B. 
bool operator<=( const BigInteger& A, const BigInteger& B ) {
    if (A.compare(B) == -1 || A.compare(B) == 0) {
        return true;
    }
    else {
        return false;
    }
}

// operator>()
// Returns true if and only if A is greater than B. 
bool operator>( const BigInteger& A, const BigInteger& B ) {
    if (A.compare(B) == 1) {
        return true;
    }
    else {
        return false;
    }
}

// operator>=()
// Returns true if and only if A is greater than or equal to B. 
bool operator>=( const BigInteger& A, const BigInteger& B ) {
    if (A.compare(B) == 1 || A.compare(B) == 0) {
        return true;
    }
    else {
        return false;
    } 
}

// operator+()
// Returns the sum A+B. 
BigInteger operator+( const BigInteger& A, const BigInteger& B ) {
    return A.add(B);

}

// operator+=()
// Overwrites A with the sum A+B. 
BigInteger operator+=( BigInteger& A, const BigInteger& B ) {
    A = A.add(B);
    return A;
}

// operator-()
// Returns the difference A-B. 
BigInteger operator-( const BigInteger& A, const BigInteger& B ) {
    return A.sub(B);
}

// operator-=()
// Overwrites A with the difference A-B. 
BigInteger operator-=( BigInteger& A, const BigInteger& B ) {
    A = A.sub(B);
    return A;
}

// operator*()
// Returns the product A*B. 
BigInteger operator*( const BigInteger& A, const BigInteger& B ) {
    return A.mult(B);
}

// operator*=()
// Overwrites A with the product A*B. 
BigInteger operator*=( BigInteger& A, const BigInteger& B ) {
    A = A.mult(B);
    return A;
}