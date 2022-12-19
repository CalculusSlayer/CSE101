// -----------------------------------------------------------------------------
//  Nayeel Imtiaz, naimtiaz
//  2022 Spring CSE101 PA5
//  List.cpp
//  This file contains the function defintions for the List class
// -----------------------------------------------------------------------------

#include "List.h"
#include <stdexcept>

// Node() : new constructor for Node
List::Node::Node(ListElement x){
   data = x;
   next = nullptr;
   prev = nullptr;
}

// List () : new constructor for List
List::List() {
    frontDummy = new Node(-69);
    backDummy = new Node(69);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
}

// List(const List& L) : copy constructor for List
List::List(const List& L) {
    frontDummy = new Node(-69);
    backDummy = new Node(69);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;

    // iterate through existing list and append to new one
    Node *temp = L.frontDummy->next;
    while(temp != L.backDummy) {
        this->insertBefore(temp->data); // CHECK???
        temp = temp->next;
    }
    // moveFront IS NECESSARY!
    this->moveFront();
}

// ~List() : Destructor for List
List::~List() {
    this->clear();
    delete frontDummy;
    delete backDummy;
}

// length() : Returns length of List
int List::length() const {
    return num_elements;
}

// front() : Returns the front element of the List
// length error
ListElement List::front() const {
    if (length() > 0) {
        return frontDummy->next->data;
    }
    else {
        throw std::length_error("List: front(): empty List\n");
    }
}

// back() : Returns the back element of the List
// length error
ListElement List::back() const {
    if (length() > 0) {
        return backDummy->prev->data;
    }
    else {
        throw std::length_error("List: back(): empty List\n");
    }
}

// position() : returns the position of the cursor.
int List::position() const {
    return pos_cursor;
}

// peekNext() : Returns the element after the cursor
// range error (pretty much everything else is range error)
ListElement List::peekNext() const {
    if (position()<length()) {
        return afterCursor->data;
    }
    else {
        throw std::range_error("List: peekNext(): position() >= length()\n");   
    }
}

// peekPrev() : Returns the element before the cursor
// range eror
ListElement List::peekPrev() const {
    if (position()>0) {
        return beforeCursor->data;
    }
    else {
        throw std::range_error("List: peekPrev(): position() <= 0\n"); 
    }
}

// clear() : Clears the List
void List::clear() {
    this->moveFront();
    while(length() > 0) {
        this->eraseAfter();
    }

}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront() {
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
    pos_cursor = 0;
}

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack() {
    afterCursor = backDummy;
    beforeCursor = backDummy->prev;
    pos_cursor = num_elements;  

}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over. 
// pre: position()<length() 
ListElement List::moveNext() {
    if (position() < length()) {
        beforeCursor = afterCursor;
        afterCursor = afterCursor->next;
        pos_cursor += 1;
        return beforeCursor->data;
    }
    else {
        throw std::range_error("List: moveNext(): position() >= length\n");        
    }
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over. 
// pre: position()>0
ListElement List::movePrev() {
    if (position() > 0) {
        afterCursor = beforeCursor;
        beforeCursor = beforeCursor->prev;
        pos_cursor -= 1;
        return afterCursor->data;
    }
    else {
        throw std::range_error("List: moveNext(): position() <= 0\n"); 
    }
}

// insertAfter()
// Inserts x after cursor.
// cursor value does not change
void List::insertAfter(ListElement x) {
    Node *a = new Node(x);
    beforeCursor->next = a;
    afterCursor->prev = a;
    a->prev = beforeCursor;
    a->next = afterCursor;
    afterCursor = a;
    num_elements += 1;
}

// insertBefore()
// Inserts x before cursor.
// cursor += 1
void List::insertBefore(ListElement x) {
    Node *a = new Node(x);
    beforeCursor->next = a;
    afterCursor->prev = a;
    a->prev = beforeCursor;
    a->next = afterCursor;
    beforeCursor = a;
    pos_cursor += 1;
    num_elements += 1;
}

   // setAfter()
   // Overwrites the List element after the cursor with x.
   // pre: position()<length()
void List::setAfter(ListElement x) {
    if (position()<length()) {
        afterCursor->data = x;
    }
    else {
        throw std::range_error("List: moveNext(): position() >= length()\n");
    }
}

   // setBefore()
   // Overwrites the List element before the cursor with x.
   // pre: position()>0
void List::setBefore(ListElement x) {
    if (position()>0) {
        beforeCursor->data = x;
    }
    else {
        throw std::range_error("List: moveNext(): position() <= 0\n");
    }
}

   // eraseAfter()
   // Deletes element after cursor.
   // pre: position()<length()
void List::eraseAfter() {
    if (position()<length()) {
        Node *delete_me = afterCursor;
        beforeCursor->next = afterCursor->next;
        afterCursor->next->prev = beforeCursor;
        afterCursor = afterCursor->next;
        delete delete_me;
        num_elements -= 1;
    }
    else {
        throw std::range_error("List: eraseAfter(): position() >= length()\n");       
    }
}

   // eraseBefore()
   // Deletes element before cursor.
   // pre: position()>0
void List::eraseBefore() {
    if (position() > 0) {
        Node *delete_me = beforeCursor;
        afterCursor->prev = beforeCursor->prev;
        beforeCursor->prev->next = afterCursor;
        beforeCursor = beforeCursor->prev;
        delete delete_me;
        num_elements -= 1;
        pos_cursor -= 1;

    }
    else {
        throw std::range_error("List: eraseBefore(): position <= 0\n");
    }
}

// findNext() : finds the next closest x value
// from the front dummy and places the cursor after it.
int List::findNext(ListElement x) {
    while(position() < length()) {
        if (peekNext() == x) {
            moveNext();
            return position(); // check?
        }
        moveNext();
    }

    return -1;
}

// findPrev() : finds the closest x value from back dummy
// and places the cursor before it
int List::findPrev(ListElement x) {
    while (position() > 0) {
        if (peekPrev() == x) {
            movePrev();
            return position(); // check?
        }
        movePrev();
    }
    return -1;
}

// cleanup() : removes all the duplicates
// and retains cursor pointer.
void List::cleanup() {
    int i1, i2;
    i1 = 0;
    i2 = 0;

    for (Node *n1 = frontDummy->next; n1 != backDummy; n1 = n1->next, i1++) {
        i2 = i1 + 1;
        for (Node *n2 = n1->next; n2 != backDummy; n2 = n2->next) {
            if (i2 >= position() && n2->data == n1->data && n2 != afterCursor) {
                    Node *delete_me = n2;
                    n2->prev->next = n2->next;
                    n2->next->prev = n2->prev;
                    n2 = n2->prev;
                    delete delete_me;
                    num_elements -= 1;
            }
            else if (i2 < position() && n2->data == n1->data && n2!= beforeCursor) {
                    Node *delete_me = n2;
                    n2->prev->next = n2->next;
                    n2->next->prev = n2->prev;
                    n2 = n2->prev;
                    delete delete_me;
                    pos_cursor -= 1;
                    num_elements -= 1;
            }
            else if (n1->data == n2->data && n2 == beforeCursor) {
                n2 = n2->prev;
                eraseBefore();
            }
            else if (n1->data == n2->data && n2 == afterCursor) {
                n2 = n2->prev;
                eraseAfter();
            }
            else {
                i2++;
                continue;
            }


        }
    }

    // for (Node *n1 = frontDummy->next; n1 != backDummy; n1 = n1->next) {
    //     for (Node *n2 = n1->next; n2 != beforeCursor->next; n2 = n2->next) {
    //         if (n1->data == n2->data) {
    //             if (n2 == beforeCursor) {
    //                 n2 = n2->prev;
    //                 eraseBefore();  // maybe need 'this->' ?
    //             }
    //             else {
    //                 Node *delete_me = n2;
    //                 n2->prev->next = n2->next;
    //                 n2->next->prev = n2->prev;
    //                 n2 = n2->prev;
    //                 delete delete_me;
    //                 pos_cursor -= 1;
    //                 num_elements -= 1;
    //             }
    //         }
    //     }

    //     for (Node *n3 = afterCursor; n3 != backDummy; n3 = n3->next) {
    //         if (n1->data == n3->data) {
    //             if (n3 == afterCursor) {
    //                 n3 = n3->prev;
    //                 eraseAfter();  // maybe need 'this->' ?
    //             }
    //             else {
    //                 Node *delete_me = n3;
    //                 n3->prev->next = n3->next;
    //                 n3->next->prev = n3->prev;
    //                 n3 = n3->prev;
    //                 delete delete_me;
    //                 num_elements -= 1;
    //             }
    //         }
    //     }

    // }
}

// concat(): concatentates two lists together
List List::concat(const List& L) const {
    Node *a = this->frontDummy->next;
    Node *b = L.frontDummy->next;
    List c;
    //c.moveFront();
    while (a != this->backDummy) {
        c.insertBefore(a->data);
        a = a->next;
        
    }
    while (b != L.backDummy) {
        c.insertBefore(b->data);
        b = b->next;
    }
    c.moveFront();
    return c;
}

// to_string() : concerts the list to a string
std::string List::to_string() const {
    if (length() == 0) {
        return "()";
    }
   Node* N = nullptr;
   std::string s = "(";

   for(N=frontDummy->next; N != backDummy->prev; N=N->next){
      s += std::to_string(N->data)+", ";
   }
   s += std::to_string(N->data)+")";
   
   return s;
}

// equals() : returns true if Lists are equal.
bool List::equals(const List& R) const {
    Node *N = nullptr;
    Node *N2 = nullptr;

    if (this->length() != R.length()) {
        return false;
    }

    for (N=this->frontDummy->next, N2=R.frontDummy->next; (N!=this->backDummy) && (N2!=R.backDummy); N=N->next, N2=N2->next) {
        if (N->data != N2->data) {
            return false;
        }
    }

    return true;
}

   // operator<<()
   // Inserts string representation of L into stream.
std::ostream& operator<<( std::ostream& stream, const List& L ) {
    return stream << L.List::to_string();
}

   // operator==()
   // Returns true if and only if A is the same integer sequence as B. The 
   // cursors in both Lists are unchanged.
bool operator==( const List& A, const List& B ) {
    return A.List::equals(B);
}

   // operator=()
   // Overwrites the state of this List with state of L.
List& List::operator=( const List& L ) {
   if( this != &L ){ // not self assignment
      // make a copy of L
        List temp = L;
        // for (Node *t = L.frontDummy->next; t != L.backDummy; t = t->next) {
        //     insertBefore(t->data);
        // }

      // then swap the copy's fields with fields of this
      std::swap(this->frontDummy, temp.frontDummy);
      std::swap(this->backDummy, temp.backDummy);

      std::swap(this->beforeCursor, temp.beforeCursor);
      std::swap(this->afterCursor, temp.afterCursor);
      std::swap(this->pos_cursor, temp.pos_cursor);
      std::swap(this->num_elements, temp.num_elements);
   }

   // return this with the new data installed 
   return *this;

}