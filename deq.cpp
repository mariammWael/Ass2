//Mariam Abdelaal 900231510

#include "deq.h"
#include <stdexcept>
using namespace std;

//I made no assumptions, since I used a template to be as general as possible
template <typename T>
DEQ<T>::DEQ() : front(nullptr), rear(nullptr), length(0) {
}

template <typename T>
DEQ<T>::~DEQ() {
    while (!DEQisEmpty()) {
        Remove_Front();
    }
}

template <typename T>
bool DEQ<T>::DEQisEmpty() const {
    return front == nullptr;
}

template <typename T>
void DEQ<T>::Add_Front(const T& value) {
    Node* newNode = new Node(value);
    if (DEQisEmpty()) {
        front = rear = newNode;
    } else {
        newNode->next = front;
        front->prev = newNode;
        front = newNode;
    }
    length++;
}

template <typename T>
void DEQ<T>::Add_Rear(const T& value) {
    Node* newNode = new Node(value);
    if (DEQisEmpty()) {
        front = rear = newNode;
    } else {
        newNode->prev = rear;
        rear->next = newNode;
        rear = newNode;
    }
    length++;
}

template <typename T>
T DEQ<T>::Remove_Front() {
    if (DEQisEmpty()) {
        throw runtime_error("Cannot remove from an empty DEQ");
    }

    Node* temp = front;
    T value = front->data;

    if (front == rear) {
        front = rear = nullptr;
    } else {
        front = front->next;
        front->prev = nullptr;
    }

    delete temp;
    length--;

    return value;
}

template <typename T>
T DEQ<T>::Remove_Rear() {
    if (DEQisEmpty()) {
        throw runtime_error("Cannot remove from an empty DEQ");
    }

    Node* temp = rear;
    T value = rear->data;

    if (front == rear) {
        front = rear = nullptr;
    } else {
        rear = rear->prev;
        rear->next = nullptr;
    }

    delete temp;
    length--;

    return value;
}

template <typename T>
T DEQ<T>::View_Front() const {
    if (DEQisEmpty()) {
        throw out_of_range("No elements in DEQ");
    }
    return front->data;
}

template <typename T>
T DEQ<T>::View_Rear() const {
    if (DEQisEmpty()) {
        throw out_of_range("No elements in DEQ");
    }
    return rear->data;
}

template <typename T>
int DEQ<T>::DEQ_Length() const {
    return length;
}

template class DEQ<int>;

int main() {
    DEQ<int> deq;

    deq.Add_Front(10);
    deq.Add_Front(20);
    deq.Add_Rear(30);
    deq.Add_Rear(40);

    cout << "DEQ Length: " << deq.DEQ_Length() << endl;
    cout << "Front Element: " << deq.View_Front() << endl;
    cout << "Removing Front: " << deq.Remove_Front() << endl;
    cout << "New Front: " << deq.View_Front() << endl;

    cout << "Rear Element: " << deq.View_Rear() << endl;
    cout << "Removing Rear: " << deq.Remove_Rear() << endl;
    cout << "New Rear: " << deq.View_Rear() << endl;

    return 0;
}
