// -----------------------------------------------------------------------------
//  Nayeel Imtiaz, naimtiaz
//  2022 Spring CSE101 PA8
//  Dictionary.cpp
//  This file contains code for Dictionary.cpp functions
// -----------------------------------------------------------------------------

#include "Dictionary.h"

#define RED -10
#define BLACK -9

// Helper Functions (Optional) ---------------------------------------------

   // inOrderString()
   // Appends a string representation of the tree rooted at R to string s. The
   // string appended consists of: "key : value \n" for each key-value pair in
   // tree R, arranged in order by keys.

   // CITE: TA Anderw
   void Dictionary::inOrderString(std::string& s, Node* R) const {
      if (R == nil) {
         return;
      }
      inOrderString(s, R->left);
      s += R->key;
      s += " : ";
      s += std::to_string(R->val);
      s += "\n";
      inOrderString(s, R->right);
   }

   // preOrderString()
   // Appends a string representation of the tree rooted at R to s. The appended
   // string consists of keys only, separated by "\n", with the order determined
   // by a pre-order tree walk.

   // CITE TA Andrew
   void Dictionary::preOrderString(std::string& s, Node* R) const {
      if (R == nil) {
         return;
      }
      s += R->key;
      s += "\n";
      preOrderString(s, R->left);
      preOrderString(s, R->right);
   }

   // preOrderCopy()
   // Recursively inserts a deep copy of the subtree rooted at R into this 
   // Dictionary. Recursion terminates at N.
   void Dictionary::preOrderCopy(Node* R, Node* N) {
      if (R != N) {  // check this statement later maybe?
         setValue(R->key, R->val);
         preOrderCopy(R->left, N);
         preOrderCopy(R->right, N);
      }

   }

   // postOrderDelete()
   // Deletes all Nodes in the subtree rooted at R, sets R to nil.

   // CITE: Tutor Vincent
   void Dictionary::postOrderDelete(Node* R) {
      if (R != nil) {
         postOrderDelete(R->left);
         postOrderDelete(R->right);
         delete R; // delete instead of remove
      }



   }

   // search()
   // Searches the subtree rooted at R for a Node with key==k. Returns
   // the address of the Node if it exists, returns nil otherwise.
   Dictionary::Node* Dictionary::search(Node* R, keyType k) const {
      if (R == nil || R->key == k) {
         return R;
      }
      else if (k < R->key) {
         return search(R->left, k);
      }
      
      return search(R->right, k);
   }

   // findMin()
   // If the subtree rooted at R is not empty, returns a pointer to the 
   // leftmost Node in that subtree, otherwise returns nil.
   Dictionary::Node* Dictionary::findMin(Node* R) {
      if (R == nil) {
         return nil;
      }
      Node *min_node = R;
      while (min_node->left != nil) {
         min_node = min_node->left;
      }
      return min_node;
   }

   // findMax()
   // If the subtree rooted at R is not empty, returns a pointer to the 
   // rightmost Node in that subtree, otherwise returns nil.
   Dictionary::Node* Dictionary::findMax(Node* R) {
      if (R == nil) {
         return nil;
      }
      Node *max_node = R;
      while (max_node->right != nil) {
         max_node = max_node->right;
      }
      return max_node;
   }

   // findNext()
   // If N does not point to the rightmost Node, returns a pointer to the
   // Node after N in an in-order tree walk.  If N points to the rightmost 
   // Node, or is nil, returns nil. 
   Dictionary::Node* Dictionary::findNext(Node* N) {
      Node *x = N;
      if (x->right != nil)                // case 1
         return findMin(x->right);
      
      Node *y = x->parent ;                     // case 2
      while (y != nil && x == y->right) {
         x = y;
         y = y->parent;
      }

      return y;
   }

   // findPrev()
   // If N does not point to the leftmost Node, returns a pointer to the
   // Node before N in an in-order tree walk.  If N points to the leftmost 
   // Node, or is nil, returns nil.
   Dictionary::Node* Dictionary::findPrev(Node* N) {
      Node *x = N;
      if (x->left != nil)                // case 1
         return findMax(x->left);
      
      Node *y = x->parent ;                     // case 2
      while (y != nil && x == y->left) {
         x = y;
         y = y->parent;
      }

      return y;
   }

   // transplant function
   // void Dictionary::transplant(Node* u, Node* v) {
   //    if (u->parent == nil)
   //       root = v;
         
   //    else if (u == u->parent->left)
   //       u->parent->left = v;

   //    else 
   //       u->parent->right = v;
      
   //    if (v != nil)
   //       v->parent = u->parent;

   // }

   // RBT Helper Functions (Optional) -----------------------------------------
   
   // LeftRotate()
   void Dictionary::LeftRotate(Node* N) {
      Node *x = N;
      Node *y = x->right;

      x->right = y->left;
      if (y->left != this->nil) { // not necessary?
         y->left->parent = x;
      }

      y->parent = x->parent;
      if (x->parent == this->nil) {
         this->root = y;
      }

      else if (x == x->parent->left) {
         x->parent->left = y;
      }

      else {
         x->parent->right = y;
      }

      y->left = x; // ????????
      x->parent = y;
   }

   // RightRotate()
   void Dictionary::RightRotate(Node* N) {
      Node *x = N;
      Node *y = x->left;

      x->left = y->right;
      if (y->right != this->nil) {  // not necessary?
         y->right->parent = x;
      }

      y->parent = x->parent;
      if (x->parent == this->nil) {
         this->root = y;
      }
      else if (x == x->parent->right) {
         x->parent->right = y;
      }
      else {
         x->parent->left = y;
      }

      y->right = x;
      x->parent = y;
   }

   // RB_InsertFixUP()
   void Dictionary::RB_InsertFixUp(Node* N) {
      Node *z = N;
      Node *y;
      while (z->parent->color == RED) {
         if (z->parent == z->parent->parent->left) {
            y = z->parent->parent->right;
            if (y->color == RED) {
               z->parent->color = BLACK;
               y->color = BLACK;
               z->parent->parent->color = RED;
               z = z->parent->parent;
            }
            else {
               if (z == z->parent->right) {
                  z = z->parent;
                  this->LeftRotate(z);
               }
               z->parent->color = BLACK;
               z->parent->parent->color = RED;
               this->RightRotate(z->parent->parent);
            }
         }

         else {
            y = z->parent->parent->left;
            if (y->color == RED) {
               z->parent->color = BLACK;
               y->color = BLACK;
               z->parent->parent->color = RED;
               z = z->parent->parent;
            }
            else {
               if (z == z->parent->left) {
                  z = z->parent;    // omfg my mistake was here
                  this->RightRotate(z);
               }
               z->parent->color = BLACK;
               z->parent->parent->color = RED;
               this->LeftRotate(z->parent->parent);
            }
         }
      }
      this->root->color = BLACK;
   }

   void Dictionary::RB_Insert(Node* N) {
      Node *y = this->nil;
      Node *x = this->root;
      Node *z = N;
      while (x != this->nil) {
         y = x;
         if (z->key < x->key) {
            x = x->left;
         }
         else {
            x = x->right;
         }
      }

      z->parent = y;
      if (y == this->nil) {
         this->root = z;
      }
      else if (z->key < y->key) {
         y->left = z;
      }
      else {
         y->right = z;
      }

      z->left = this->nil;
      z->right = this->nil;
      z->color = RED;
      this->RB_InsertFixUp(z);
   }

   // RB_Transplant()
   void Dictionary::RB_Transplant(Node* u, Node* v) {
      if (u->parent == this->nil) {
         this->root = v;
      }
      else if (u == u->parent->left) {
         u->parent->left = v;
      }
      else {
         u->parent->right = v;
      }
      v->parent = u->parent;
   }

   // RB_DeleteFixUp()
   void Dictionary::RB_DeleteFixUp(Node* N) {
      Node* x = N;
      Node* w;
      while ((x != this->root) && (x->color == BLACK)) {
         if (x == x->parent->left) {
            w = x->parent->right;
            if (w->color == RED) {
               w->color = BLACK;
               x->parent->color = RED;
               this->LeftRotate(x->parent);
               w = x->parent->right;
            }
            if ((w->left->color == BLACK) && (w->right->color == BLACK)) {
               w->color = RED;
               x = x->parent;
            }
            else {
               if (w->right->color == BLACK) {
                  w->left->color = BLACK;
                  w->color = RED;
                  this->RightRotate(w);
                  w = x->parent->right;
               }
               w->color = x->parent->color;
               x->parent->color = BLACK;
               w->right->color = BLACK;
               this->LeftRotate(x->parent);
               x = this->root;
            }
         }

         else {
            w = x->parent->left;
            if (w->color == RED) {
               w->color = BLACK;
               x->parent->color = RED;
               this->RightRotate(x->parent);
               w = x->parent->left;
            }
            if ((w->right->color == BLACK) && (w->left->color == BLACK)) {
               w->color = RED;
               x = x->parent;
            }
            else {
               if (w->left->color == BLACK) {
                  w->right->color = BLACK;
                  w->color = RED;
                  this->LeftRotate(w);
                  w = x->parent->left;
               }
               w->color = x->parent->color;
               x->parent->color = BLACK;
               w->left->color = BLACK;
               this->RightRotate(x->parent);
               x = this->root;
            }
         }
      }

      x->color = BLACK;
   }

   // RB_Delete()
   void Dictionary::RB_Delete(Node* N) {
      Node* z = N;
      Node* y = z;
      Node* x;
      int y_original_color = y->color;
      if (z->left == this->nil) {
         x = z->right;     // omfg another mistake
         this->RB_Transplant(z, z->right); //mistake
      }

      // forgot this entire block bruh
      else if (z->right == this->nil) {
         x = z->left;
         this->RB_Transplant(z, z->left);
      }

      else {
         y = this->findMin(z->right);
         y_original_color = y->color;
         x = y->right;
         if (y->parent == z) {
            x->parent = y;
         }
         else {
            this->RB_Transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
         }
         this->RB_Transplant(z, y);
         y->left = z->left;
         y->left->parent = y;
         y->color = z->color;
      }

      if (y_original_color == BLACK) {
         this->RB_DeleteFixUp(x);
      }
   }



Dictionary::Node::Node(keyType k, valType v) {
   key = k;
   val = v;
   parent = nullptr;
   left = nullptr;
   right = nullptr;
   color = BLACK;
}

Dictionary::Dictionary() {
    // create new node. set 'nil' to new node
    // set root parent to nil. set root's right and left to nil.
    // initialize n

    nil = new Node("\0", -5);
    root = nil;
    current = nil;

    // not necessary
   //  nil->parent = nil;
   //  nil->left = nil;
   //  nil->right = nil;

    num_pairs = 0;

}

Dictionary::Dictionary(const Dictionary& D) {
   nil = new Node("\0", 0);
   // root = new Node(D.root.key, D.root.val);
   // root = D.root;
   root = nil;
   current = nil;
   num_pairs = 0;

   // nil->parent = nil;
   // nil->left = nil;
   // nil->right = nil;

   preOrderCopy(D.root, D.nil); // do preOrderCopy
}

   // Destructor
Dictionary::~Dictionary() {
   clear(); // do postOrderDelete
   delete nil;

   // unesscary
   // nil = nullptr;
   // root = nullptr;
   // current = nullptr;
}

  // Access functions --------------------------------------------------------

   // size()
   // Returns the size of this Dictionary.
   int Dictionary::size() const {
      return num_pairs;
   }

   // contains()
   // Returns true if there exists a pair such that key==k, and returns false
   // otherwise.
   bool Dictionary::contains(keyType k) const {
      if (this->search(root, k) == nil) {
         return false;
      }
      else {
         return true;
      }

   }

   // getValue()
   // Returns a reference to the value corresponding to key k.
   // Pre: contains(k)
   valType& Dictionary::getValue(keyType k) const {
      Node *sol = this->search(root, k);
      if (sol == nil) {
         std::length_error("There is a logic error for get_value\n");
      }
      
      return sol->val;
   }

   // hasCurrent()
   // Returns true if the current iterator is defined, and returns false 
   // otherwise.
   bool Dictionary::hasCurrent() const {
      if (current != nil) {
         return true;
      }
      else {
         return false;
      }
   }

   // currentKey()
   // Returns the current key.
   // Pre: hasCurrent() 
   keyType Dictionary::currentKey() const {
      if (hasCurrent()) {
         return current->key;
      }
      else {
         throw std::logic_error("There is a logic error in currentKey.\n");
      }
   }

   // currentVal()
   // Returns a reference to the current value.
   // Pre: hasCurrent()
   valType& Dictionary::currentVal() const {
      if (hasCurrent()) {
         return current->val;
      }
      else {
         throw std::logic_error("There is a logic error in currentVal.\n");
      }
   }


   // Manipulation procedures -------------------------------------------------

   // clear()
   // Resets this Dictionary to the empty state, containing no pairs.
   void Dictionary::clear() {
      if (this->num_pairs > 0) {
         postOrderDelete(root);
         root = nil;
         current = nil;
         num_pairs = 0;
      }
   }

   // setValue()
   // If a pair with key==k exists, overwrites the corresponding value with v, 
   // otherwise inserts the new pair (k, v).

void Dictionary::setValue(keyType k, valType v) {
      Node *temp = search(this->root, k);
      if (temp != nil) {
         temp->val = v;
         return;
      }
      Node* b = new Node(k, v);

      RB_Insert(b);

      num_pairs++;

}

   // remove()
   // Deletes the pair for which key==k. If that pair is current, then current
   // becomes undefined.
   // Pre: contains(k).
   void Dictionary::remove(keyType k) {

      if (contains(k)) {
         Node* a = search(root, k);
         if (a == this->current) {
            current = nil;
         }
         // if (a == this->root) {
         //    root = nil;
         // }
         RB_Delete(a);
         delete a;
         a = nullptr;
         num_pairs--;
      }

      else {
         throw std::logic_error("Dictionary: remove() mistake");
      }
   }

   // begin()
   // If non-empty, places current iterator at the first (key, value) pair
   // (as defined by the order operator < on keys), otherwise does nothing. 
   void Dictionary::begin() {
     // std::cout << num_pairs << std::endl;
      if (this->num_pairs > 0) {
         current = findMin(root);
      }
   }

   // end()
   // If non-empty, places current iterator at the last (key, value) pair
   // (as defined by the order operator < on keys), otherwise does nothing. 
   void Dictionary::end() {
      if (this->num_pairs > 0) {
         current = findMax(root);
      }
   }

   // next()
   // If the current iterator is not at the last pair, advances current 
   // to the next pair (as defined by the order operator < on keys). If 
   // the current iterator is at the last pair, makes current undefined.
   // Pre: hasCurrent()
   void Dictionary::next() {
      if (!hasCurrent()) {
         throw std::logic_error("Dictionary::next mistake");
      }

      current = findNext(current);
      // if () {

      // }
      // return;
   }

   // prev()
   // If the current iterator is not at the first pair, moves current to  
   // the previous pair (as defined by the order operator < on keys). If 
   // the current iterator is at the first pair, makes current undefined.
   // Pre: hasCurrent()
   void Dictionary::prev() {
      if (!hasCurrent()) {
         throw std::logic_error("Dictionary::prev mistake");
      }

      current = findPrev(current);
      return;
   }


   // Other Functions ---------------------------------------------------------

   // to_string()
   // Returns a string representation of this Dictionary. Consecutive (key, value)
   // pairs are separated by a newline "\n" character, and the items key and value 
   // are separated by the sequence space-colon-space " : ". The pairs are arranged 
   // in order, as defined by the order operator <.
   std::string Dictionary::to_string() const {
      std::string empty = "";
      inOrderString(empty, root);
      return empty;
   }

   // pre_string()
   // Returns a string consisting of all keys in this Dictionary. Consecutive
   // keys are separated by newline "\n" characters. The key order is given
   // by a pre-order tree walk.
   std::string Dictionary::pre_string() const {
      std::string empty = "";
      preOrderString(empty, root);
      return empty;
   }

   // equals()
   // Returns true if and only if this Dictionary contains the same (key, value)
   // pairs as Dictionary D.
   bool Dictionary::equals(const Dictionary& D) const {
      if (this->num_pairs != D.num_pairs) {
         return false;
      }

      // Dictionary this_copy = *this;
      // Dictionary D_copy = D;

      std::string a, b;
      a = this->to_string();
      b = D.to_string();

      if (a == b) {
         return true;
      }

      else {
         return false;
      }

   }


std::ostream& operator<<( std::ostream& stream, Dictionary& D ) {
   return stream << D.Dictionary::to_string();
}

   // operator==()
   // Returns true if and only if Dictionary A equals Dictionary B, as defined
   // by member function equals(). 
bool operator==( const Dictionary& A, const Dictionary& B ) {
   return A.Dictionary::equals(B);
}

   // operator=()
   // Overwrites the state of this Dictionary with state of D, and returns a
   // reference to this Dictionary.
Dictionary& Dictionary::operator=( const Dictionary& D ) {
   if( this != &D ){ // not self assignment
      // make a copy of D
        Dictionary temp = D;

      std::swap(this->num_pairs, temp.num_pairs);
      std::swap(this->nil, temp.nil);
      std::swap(this->root, temp.root);
      std::swap(this->current, temp.current);
   }

   // return this with the new data installed 
   return *this;
}
