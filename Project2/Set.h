//
//  Set.hpp
//  Project2
//
//  Created by Edmund Zhi on 4/18/21.
//

#ifndef Set_h
#define Set_h

#include <string>

  // Later in the course, we'll see that templates provide a much nicer
  // way of enabling us to have Sets of different types.  For now,
  // we'll use a type alias.
//using ItemType = int;
using ItemType = std::string;
//using ItemType = unsigned long;

class Set {
public:
    Set();               // Create an empty set (i.e., one with no items).
    
    ~Set();
    Set(const Set& other);
    Set& operator=(const Set& rhs);
    
    bool empty() const;  // Return true if the set is empty, otherwise false.
    int size() const;    // Return the number of items in the set.

    bool insert(const ItemType& value);
      // Insert value into the set if it is not already present.  Return
      // true if the value is actually inserted.  Leave the set unchanged
      // and return false if the value is not inserted (perhaps because it
      // was already in the set or because the set has a fixed capacity and
      // is full).

    bool erase(const ItemType& value);
      // Remove the value from the set if it is present.  Return true if the
      // value was removed; otherwise, leave the set unchanged and
      // return false.

    bool contains(const ItemType& value) const;
      // Return true if the value is in the set, otherwise false.
     
    bool get(int i, ItemType& value) const;
      // If 0 <= i < size(), copy into value the item in the set that is
      // strictly less than exactly i items in the set and return true.
      // Otherwise, leave value unchanged and return false.

    void swap(Set& other);
      // Exchange the contents of this set with the other one.
    
private:
    int m_size; // number of items in the set
    
    struct Node {
        ItemType m_value;
        Node* m_prev;
        Node* m_next;
    };
    
    Node* m_head;
};

void unite(const Set& s1, const Set& s2, Set& result);

void difference(const Set& s1, const Set& s2, Set& result);

#endif /* Set_h */
