//
// Created by CY815 on 2023/4/5.
//

#include "arrayList.h"
#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

void testArrayList() {
    // test constructor
    linearList<double> *x = new arrayList<double>(20);
    arrayList<int> y(2), z;

    //test capacity
    cout << "Capacity of x, y and z = "
         << ((arrayList<double> *) x)->capacity() << ", "
         << y.capacity() << ", "
         << z.capacity() << endl;

    // test size
    cout << "Initial size of x, y, and z = "
         << x->size() << ", "
         << y.size() << ", "
         << z.size() << endl;

    // test empty
    if (x->empty())
        cout << "x is empty" << endl;
    else
        cout << "x is not empty" << endl;
    if (y.empty())
        cout << "y is empty" << endl;
    else
        cout << "y is not empty" << endl;

    // test insert
    y.insert(0, 2);
    y.insert(1, 6);
    y.insert(0, 1);
    y.insert(2, 4);
    y.insert(3, 5);
    y.insert(2, 3);
    cout << "Inserted 6 integers, list y should be 1 2 3 4 5 6" << endl;
    cout << "Size of y = " << y.size() << endl;
    cout << "Capacity of y = " << y.capacity() << endl;
    if (y.empty())
        cout << "y is empty" << endl;
    else
        cout << "y is not empty" << endl;
    y.output(cout);
    cout << endl << "Testing overloaded << " << endl;
    cout << y << endl;

    // test indexOf
    int index = y.indexOf(4);
    if (index < 0)
        cout << "4 not found" << endl;
    else
        cout << "The index of 4 is " << index << endl;

    index = y.indexOf(7);
    if (index < 0)
        cout << "7 not found" << endl;
    else
        cout << "The index of 7 is " << index << endl;

    // test get
    cout << "Element with index 0 is " << y.get(0) << endl;
    cout << "Element with index 3 is " << y.get(3) << endl;

    // test erase
    y.erase(1);
    cout << "Element 1 erased" << endl;
    cout << "The list is " << y << endl;
    y.erase(2);
    cout << "Element 2 erased" << endl;
    cout << "The list is " << y << endl;

    cout << "Size of y = " << y.size() << endl;
    cout << "Capacity of y = " << y.capacity() << endl;
    if (y.empty())
        cout << "y is empty" << endl;
    else
        cout << "y is not empty" << endl;

    try {
        y.insert(-3, 0);
    } catch (std::invalid_argument &e) {
        cout << "Illegal index exception" << endl;
        cout << "Insert index must be between 0 and list size" << endl;
        cout << e.what() << endl;
    }

    // test copy constructor
    arrayList<int> w(y);
    y.erase(0);
    y.erase(0);
    cout << "w should be old y, new y has first 2 elements removed" << endl;
    cout << "w is " << w << endl;
    cout << "y is " << y << endl;

    //
    y.insert(0, 4);
    y.insert(0, 5);
    y.insert(0, 6);
    y.insert(0, 7);
    cout << "y is " << y << endl;
}

void testArrayIterator() {
    arrayList<int> y(2);
    y.insert(0, 2);
    y.insert(1, 6);
    y.insert(0, 1);
    y.insert(2, 4);
    y.insert(3, 5);
    y.insert(2, 3);
    cout << "Inserted 6 integers, list y should be 1 2 3 4 5 6" << endl;
    cout << "Size of y = " << y.size() << endl;
    cout << "Capacity of y = " << y.capacity() << endl;

    cout << "Output using forward iterators pre and post ++" << endl;
    for (arrayList<int>::iterator i = y.begin(); i != y.end(); i++) {
        cout << *i << " ";
    }
    cout << endl;
    for (arrayList<int>::iterator i = y.begin(); i != y.end(); ++i) {
        cout << *i << " ";
    }
    cout << endl;

    cout << "Output using backward iterators pre and post --" << endl;
    for (arrayList<int>::iterator i = y.end(); i != y.begin(); cout << *(--i) << " ");
    cout << endl;
    for (arrayList<int>::iterator i = y.end(); i != y.begin();) {
        i--;
        cout << *i << " ";
        *i += 1;
    }
    cout << endl;
    cout << "Incremented by 1 list is " << y << endl;

    reverse(y.begin(), y.end());
    cout << "The reversed list is " << y << endl;
    int sum = accumulate(y.begin(), y.end(), 0);
    cout << "The sum of the elements is " << sum << endl;
}
