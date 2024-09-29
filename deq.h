#ifndef DEQ_H
#define DEQ_H

#include <stdexcept>

template <typename T>
class DEQ {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(const T& val) : data(val), next(nullptr), prev(nullptr) {}
    };
    Node* front;
    Node* rear;
    int length;

public:
    DEQ();
    ~DEQ();
    bool DEQisEmpty() const;
    void Add_Front(const T& value);
    void Add_Rear(const T& value);
    T Remove_Front();
    T Remove_Rear();
    T View_Front() const;
    T View_Rear() const;
    int DEQ_Length() const;
};

// Include implementation in header file
#include "DEQ.cpp"

#endif // DEQ_H
