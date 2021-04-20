//
//  main.cpp
//  Project2
//
//  Created by Edmund Zhi on 4/18/21.
//

#include <iostream>
#include "Set.h"
#include <type_traits>
using namespace std;

#define CHECKTYPE(f, t) { auto p = static_cast<t>(f); (void)p; }

static_assert(std::is_default_constructible<Set>::value,
        "Set must be default-constructible.");
static_assert(std::is_copy_constructible<Set>::value,
        "Set must be copy-constructible.");
static_assert(std::is_copy_assignable<Set>::value,
        "Set must be assignable.");

void thisFunctionWillNeverBeCalled()
{
    CHECKTYPE(&Set::empty,     bool (Set::*)() const);
    CHECKTYPE(&Set::size,      int  (Set::*)() const);
    CHECKTYPE(&Set::insert,    bool (Set::*)(const ItemType&));
    CHECKTYPE(&Set::erase,     bool (Set::*)(const ItemType&));
    CHECKTYPE(&Set::contains,  bool (Set::*)(const ItemType&) const);
    CHECKTYPE(&Set::get,       bool (Set::*)(int, ItemType&) const);
    CHECKTYPE(&Set::swap,      void (Set::*)(Set&));
    CHECKTYPE(unite,      void (*)(const Set&, const Set&, Set&));
    CHECKTYPE(difference, void (*)(const Set&, const Set&, Set&));
}

void test()
        {
            Set ss;
            assert(ss.insert("pita"));
            assert(ss.insert("roti"));
            assert(ss.size() == 2);
            assert(ss.contains("roti"));
            assert(ss.erase("roti"));
            assert(ss.insert("roti"));
            ItemType x = "laobing";
            assert(ss.get(0, x)  &&  x == "roti");
            assert(ss.get(1, x)  &&  x == "pita");
        }

void test2() {
    Set ss;
    assert(ss.insert("1"));
    assert(ss.insert("2"));
    assert(ss.size() == 2);
    ItemType x = "laobing";
    assert(ss.get(0, x)  &&  x == "2");
    assert(ss.get(1, x)  &&  x == "1");
}

void test3() {
    Set s1;
    Set s2;
    assert(s1.insert("2"));
    assert(s1.insert("8"));
    assert(s1.insert("3"));
    assert(s1.insert("9"));
    assert(s1.insert("5"));
    ItemType x = "laobing";
    assert(s1.get(0, x)  &&  x == "9");
    assert(s1.get(1, x)  &&  x == "8");
    assert(s1.get(2, x)  &&  x == "5");
    assert(s1.get(3, x)  &&  x == "3");
    assert(s1.get(4, x)  &&  x == "2");
    assert(s2.insert("10"));
    assert(s2.insert("6"));
    assert(s2.insert("3"));
    assert(s2.insert("8"));
    assert(s2.insert("5"));
    assert(s2.size() == 5);
    assert(s2.get(0, x)  &&  x == "8");
    assert(s2.get(1, x)  &&  x == "6");
    assert(s2.get(2, x)  &&  x == "5");
    assert(s2.get(3, x)  &&  x == "3");
    assert(s2.get(4, x)  &&  x == "10");
    Set result;
    unite(s1, s2, result);
    assert(result.size() == 7);
    assert(result.get(0, x)  &&  x == "9");
    assert(result.get(1, x)  &&  x == "8");
    assert(result.get(2, x)  &&  x == "6");
    assert(result.get(3, x)  &&  x == "5");
    assert(result.get(4, x)  &&  x == "3");
    assert(result.get(5, x)  &&  x == "2");
    assert(result.get(6, x)  &&  x == "10");
}

void test4() {
    Set s1;
    Set s2;
    assert(s1.insert("2"));
    assert(s1.insert("8"));
    assert(s1.insert("3"));
    assert(s1.insert("9"));
    assert(s1.insert("5"));
    assert(s2.insert("10"));
    assert(s2.insert("6"));
    assert(s2.insert("3"));
    assert(s2.insert("8"));
    assert(s2.insert("5"));
    Set result;
    difference(s1, s2, result);
    ItemType x = "laobing";
    assert(result.size() == 4);
    assert(result.get(0, x)  &&  x == "9");
    assert(result.get(1, x)  &&  x == "6");
    assert(result.get(2, x)  &&  x == "2");
    assert(result.get(3, x)  &&  x == "10");
}

void test6() {
    Set s1; //tests constructor
    Set s2;
    Set result;
    result = s1; //tests assignment operator
    assert(s1.size() == s2.size());
    assert(s1.size() == result.size());
    assert(s2.size() == result.size());
    assert(s1.size() == 0); // tests size()
    assert(s1.empty()); // tests empty()
    s1.insert("1");
    s1.insert("2");
    s1.insert("3");
    s2.insert("4");
    Set s3(s2);
    assert(s3.size() == 1);  //checks copy constructor for single node
    Set s4(s1);
    assert(s4.size() == s1.size()); // checks copy constructor for more than one node
}


void test5() {
    Set a;
    Set b;                // Check copy constructor
    Set c;
    c = b;                    // Check assignment operator

    assert(a.size() == 0);                // Check that initial size is zero
    assert(a.size() == b.size());
    assert(b.size() == c.size());
    assert(a.empty() && b.empty() && c.empty());    // Check that EMPTY works

    a.insert("first");
    a.insert("second");
    a.insert("third");
    a.insert("third");

    assert(a.size() == 3); // Check that insert only works if value  is not already present

    b.insert("first");
    b.insert("second");
    b.insert("third");
    b.insert("fourth");

    assert(b.size() == 4);

    c.insert("zero");


    Set d(c);    // Check the copy constructor with only one node
    assert(d.size() == 1);

    Set e(b);    // Check that the copy contructor works with multiple nodes
    assert(e.size() == b.size());

    assert(c.size() == 1); // Check that INSERT increases the size
    assert(!c.empty());

    unite(a, b, c);

    assert(c.contains("first") && c.contains("second") && c.contains("third") && c.contains("fourth"));    // Check that UNITE works properly

    unite(a, a, c);

    assert(c.contains("first") && c.contains("second") && c.contains("third") && c.size() == 3);    // Check aliasing case

    unite(a, b, a);

    assert(c.contains("first") && c.contains("second") && c.contains("third") && c.size() == 3);    // Check alternate aliasing case

    unite(a, a, a);

    assert(c.contains("first") && c.contains("second") && c.contains("third") && c.size() == 3);    // Check last aliasing case

    difference(a, b, c);

    assert(c.size() == 0);    // Check that SUBTRACT works properly

    a.insert("fourth");
    a.insert("fifth");

    difference(a, b, c);

    assert(c.size() == 1 && c.contains("fifth"));    // Check that SUBTRACT works properly


    difference(a, a, c);

    assert(c.size() == 0);    // Check aliasing case

    difference(a, b, a);

    assert(a.size() == 1 && a.contains("fifth"));    // Check alternate aliasing case

    difference(b, b, b);

    assert(b.size() == 0);    // Check last aliasing case

    assert(!a.erase("not"));    // Check that erasing something that is not present returns false

    assert(a.erase("fifth"));    // Check that erasing something that is present returns true

    assert(a.size() == 0);    // Check that ERASE decreases size
    assert(b.size() == 0);
    assert(c.size() == 0);

    a.insert("first");
    a.insert("second");
    a.insert("third");

    b.insert("first");

    a.swap(b);            // Check that two reciprocal swaps cancel out
    b.swap(a);

    assert(a.contains("first") && a.contains("third") && a.contains("second"));    // Check that CONTAINS works properly
    assert(!c.contains("first"));

    ItemType item;
    a.get(0, item);

    assert(item == "third");    // Check that GET works properly

    a.get(1, item);

    assert(item == "second");

    a.get(2, item);

    assert(item == "first");

    a.swap(b);                    // Check that SWAP works properly

    assert(a.size() == 1 && a.contains("first") && b.size() == 3 && b.contains("first") && b.contains("second") && b.contains("third"));

    b.get(0, item);

    assert(item == "third");    // Check that SWAP works properly

    b.get(1, item);

    assert(item == "second");

    b.get(2, item);

    assert(item == "first");

    Set empty;
    Set not_empty(a);

    assert(empty.empty());
    assert(!not_empty.empty());

    empty.swap(not_empty);        // Check SWAP when swapping an empty set

    assert(!empty.empty());
    assert(not_empty.empty());
}

//void test()
//        {
//            Set uls;
//            assert(uls.insert(10));
//            assert(uls.insert(20));
//            assert(uls.size() == 2);
//            assert(uls.contains(20));
//            ItemType x = 30;
//            assert(uls.get(0, x)  &&  x == 20);
//            assert(uls.get(1, x)  &&  x == 10);
//        }

int main() {
    test();
    test2();
    test3();
    test4();
    test5();
    test6();
    cerr << "Passed all tests" << endl;
    return 0;
}
