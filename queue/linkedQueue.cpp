//
// Created by CY815 on 2023/7/23.
//

#include "linkedQueue.h"

using std::cout;
using std::endl;

void testLinkedQueue() {
    linkedQueue<int> q;

    // add a few elements
    q.push(1);
    cout << "Queue back is " << q.back() << endl;
    q.push(2);
    cout << "Queue back is " << q.back() << endl;
    q.push(3);
    cout << "Queue back is " << q.back() << endl;
    q.push(4);
    cout << "Queue back is " << q.back() << endl;

    cout << "Queue should be 1234, front to back" << endl;

    // test empty and size
    if (q.empty())
        cout << "The queue is empty" << endl;
    else
        cout << "The queue is not empty" << endl;

    cout << "The queue size is " << q.size() << endl;

    while (!q.empty()) {
        cout << "Queue front is " << q.front() << endl;
        q.pop();
        cout << "Popped front element" << endl;
    }

    try { q.pop(); }
    catch (queueEmpty message) {
        cout << "Last pop failed " << endl;
        message.outputMessage();
    }
}
