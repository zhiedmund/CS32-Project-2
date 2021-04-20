//
//  Set.cpp
//  Project2
//
//  Created by Edmund Zhi on 4/18/21.
//

#include "Set.h"

Set::Set() : m_size(0) {
    // initializes new head node
    m_head = new Node;
    m_head->m_next = m_head;
    m_head->m_prev = m_head;
}

Set::~Set() {
    while (!empty()) {
        Node* item = m_head->m_next;
        // unlinks item 1 by 1 and deletes them
        item->m_prev->m_next = item->m_next;
        item->m_next->m_prev = item->m_prev;
        delete item;
        m_size--;
    }
    // deletes head node
    delete m_head;
}

Set::Set(const Set& other)
{
    m_size = 0;
    m_head = new Node;
    m_head->m_next = m_head;
    m_head->m_prev = m_head;
    // loop through each item in other
    for (Node* dummy = other.m_head->m_next; dummy != other.m_head; dummy = dummy->m_next) {
        // allocates a new node as a new item in Set
        Node* item = new Node;
        // appends item to end of list, or before the head since list is circular
        item->m_prev = m_head->m_prev;
        item->m_next = m_head;
        // gives item a value and connects to Set
        item->m_value = dummy->m_value;
        item->m_next->m_prev = item;
        item->m_prev->m_next = item;
        m_size++;
    }
}

Set& Set::operator=(const Set& rhs)
{
    if (this != &rhs)
    {
        Set temp(rhs);
        swap(temp);
    }
    return *this;
}

int Set::size() const
{
    return m_size;
}

bool Set::empty() const
{
    return size() == 0;
}

bool Set::contains(const ItemType& value) const
{
    bool isPresent = false;
    Node* item = m_head->m_next;
    while(item != m_head) {
        if(item->m_value == value) {
            isPresent = true;
            break;
        }
        item = item->m_next;
    }
    return isPresent;
}

bool Set::insert(const ItemType& value)
{
    // special case for first item
    if (m_size == 0) {
        Node* item = new Node;
        item->m_value = value;
        item->m_next = m_head;
        item->m_prev = m_head;
        m_head->m_next = item;
        m_head->m_prev = item;
        m_size++;
        return true;
    }
    // return false if value is already in Set
    if (contains(value)) {
        return false;
    }
    // uses pointer to Node to search for where new item belongs
    Node* ptr = m_head->m_next;
    while (ptr != m_head) {
        if(ptr->m_value < value) {
            break;
        }
        ptr = ptr->m_next;
    }
    // allocates a new node as a new item in Set
    Node* item = new Node;
    // inserts new item before ptr
    item->m_prev = ptr->m_prev;
    item->m_next = ptr;
    // gives item a value and links to rest of Set
    item->m_value = value;
    item->m_next->m_prev = item;
    item->m_prev->m_next = item;
    m_size++;
    
    return true;
}

bool Set::erase(const ItemType& value)
{
    // if value isn't in Set, erase won't work
    if (!contains(value)) {
        return false;
    }
    Node* item;
    // finds node of item to delete
    for (item = m_head->m_next; item != m_head; item = item->m_next) {
        if (item->m_value == value) {
            break;
        }
    }
    // unlinks item and deletes it, then reduce size of Set
    item->m_prev->m_next = item->m_next;
    item->m_next->m_prev = item->m_prev;
    delete item;
    m_size--;
    return true;
}
     
bool Set::get(int i, ItemType& value) const
{
    // checks bounds
    if (i < 0  ||  i >= m_size)
        return false;
    // searches through set for value
    Node* item = m_head->m_next;
    for (int pos = 0; pos != i; pos++) {
        item = item->m_next;
    }
    // assigns value with m_value
    value = item->m_value;
    return true;
}

void Set::swap(Set& other) {
    // switches head node
    Node* newHead = other.m_head;
    other.m_head = m_head;
    m_head = newHead;
    // switches size
    int newSize = other.m_size;
    other.m_size = m_size;
    m_size = newSize;
}

void unite(const Set& s1, const Set& s2, Set& result) {
    // allocates temporary set
    Set temp;
    // inserts everything from s1
    for (int i = 0; i < s1.size(); i++) {
        ItemType item;
        s1.get(i, item);
        temp.insert(item);
    }
    //inserts everything from s2
    for (int i = 0; i < s2.size(); i++) {
        ItemType item;
        s2.get(i, item);
        temp.insert(item);
    }
    // swaps temp with result so result is destroyed after function is finished
    result.swap(temp);
}

void difference(const Set& s1, const Set& s2, Set& result) {
    // allocates temporary set
    Set temp;
    // adds everything in s1 that is not found in s2
    for (int i = 0; i < s1.size(); i++) {
        ItemType s1_item;
        s1.get(i, s1_item);
        if (!s2.contains(s1_item)) {
            temp.insert(s1_item);
        }
    }
    // adds everything in s2 that is not found in s1
    for (int i = 0; i < s2.size(); i++) {
        ItemType s2_item;
        s2.get(i, s2_item);
        if (!s1.contains(s2_item)) {
            temp.insert(s2_item);
        }
    }
    // swaps temp with result so result is destroyed after function is finished
    result.swap(temp);
}
