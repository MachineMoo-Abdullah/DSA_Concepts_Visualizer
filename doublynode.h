#ifndef DOUBLYNODE_H
#define DOUBLYNODE_H

template <typename T>
class DoublyNode {
public:
    T data;
    DoublyNode* next;
    DoublyNode* prev;

    DoublyNode(T value) : data(value), next(nullptr), prev(nullptr) {}
};

#endif // DOUBLYNODE_H
