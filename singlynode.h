#ifndef SINGLYNODE_H
#define SINGLYNODE_H

template <typename T>
class Node {
public:
    T data;
    Node* next;

    Node(T value) : data(value), next(nullptr) {}
};

#endif // SINGLYNODE_H
