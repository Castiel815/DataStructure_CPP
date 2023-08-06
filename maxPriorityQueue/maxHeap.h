//
// Created by CY815 on 2023/8/6.
//

#ifndef DATASTRUCTURE_MAXHEAP_H
#define DATASTRUCTURE_MAXHEAP_H

#include "maxPriorityQueue.h"
#include "myExceptions.h"
#include "common.h"
#include <sstream>
#include <algorithm>
#include <iterator>

template<typename T>
class maxHeap : public maxPriorityQueue<T> {
public:
    explicit maxHeap(int initialCapacity = 10);

    ~maxHeap() override {
        delete[] heap;
        heap = nullptr;
    }

    bool empty() const override { return heapSize == 0; }

    int size() const override { return heapSize; }

    const T &top() override {
        if (heapSize == 0) {
            throw queueEmpty();
        }
        return heap[1];
    }

    void pop() override;

    void push(const T &theElement) override;

    void initialize(T *theHeap, int theSize);

    void deactivateArray() {
        heap = nullptr;
        arrayLength = heapSize = 0;
    }

    void output(std::ostream &out) const;

    friend std::ostream &operator<<(std::ostream &out, const maxHeap<T> &x) {
        x.output(out);
        return out;
    }

private:
    int heapSize;
    int arrayLength;
    T *heap;
};

template<typename T>
maxHeap<T>::maxHeap(int initialCapacity) {
    if (initialCapacity < 1) {
        std::ostringstream s;
        s << "Initial capacity = " << initialCapacity << " Must be > 0";
        throw illegalParameterValue(s.str());
    }
    arrayLength = initialCapacity + 1;
    heap = new T[arrayLength];
    heapSize = 0;
}

/**
 * 把元素theElement加入堆
 * @tparam T
 * @param theElement
 */
template<typename T>
void maxHeap<T>::push(const T &theElement) {
    // 必要时增加数组长度
    if (heapSize == arrayLength - 1) {
        // 数组长度加倍
        changeLength1D(heap, arrayLength, 2 * arrayLength);
        arrayLength *= 2;
    }

    // 为元素theElement寻找插入位置，currentNode从新叶子向上移动
    int currentNode = ++heapSize;
    while (currentNode != 1 && heap[currentNode / 2] < theElement) {
        // 不能把元素theElement插入在heap[currentNode]
        heap[currentNode] = heap[currentNode / 2];      // 把元素向下移动
        currentNode /= 2;                               // currentNode移向双亲
    }

    heap[currentNode] = theElement;
}

/**
 * 删除最大元素
 * @tparam T
 */
template<typename T>
void maxHeap<T>::pop() {
    // 如果堆为空，抛出异常
    if (heapSize == 0) {            // 堆为空
        throw queueEmpty();
    }

    // 删除最大元素
    heap[1].~T();

    // 删除最后一个元素，然后重新建堆
    T lastElement = heap[heapSize--];

    // 从根开始，为最后一个元素寻找位置
    int currentNode = 1,
            child = 2;      // currentNode的孩子
    while (child <= heapSize) {
        // heap[child]应该是currentNode的更大的孩子
        if (child < heapSize && heap[child] < heap[child + 1]) {
            child++;
        }

        // 可以把lastElement放在heap[currentNode]吗？
        if (lastElement >= heap[child]) {
            break;  // 可以
        }

        // 不可以
        heap[currentNode] = heap[child];    // 把孩子child向上移动
        currentNode = child;                // 向下移动一层寻找位置
        child *= 2;
    }

    heap[currentNode] = lastElement;
}

/**
 * 在数组theHeap[1:theSize]中建大根堆
 * @tparam T
 * @param theHeap
 * @param theSize
 */
template<typename T>
void maxHeap<T>::initialize(T *theHeap, int theSize) {
    delete[] heap;
    heap = theHeap;
    heapSize = theSize;

    // 堆化
    for (int root = heapSize / 2; root >= 1; --root) {
        T rootElement = heap[root];

        // 为元素rootElement寻找位置
        int child = 2 * root;       // 孩子child的双亲是元素rootElement的位置

        while (child <= heapSize) {
            // heap[child]应该是兄弟中较大者
            if (child < heapSize && heap[child] < heap[child + 1]) {
                child++;
            }

            // 可以把元素rootElement放在heap[child / 2]吗
            if (rootElement >= heap[child]) {
                break;  // 可以
            }

            // 不可以
            heap[child / 2] = heap[child];      // 把孩子向上移
            child *= 2;                         // 移到下一层
        }
        heap[child / 2] = rootElement;
    }
}

template<typename T>
void maxHeap<T>::output(std::ostream &out) const {
    std::copy(heap + 1, heap + heapSize + 1, std::ostream_iterator<T>(out, " "));
}

#endif //DATASTRUCTURE_MAXHEAP_H
