// DEQ implementation

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
        throw std::runtime_error("Cannot remove from an empty DEQ");
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
        throw std::runtime_error("Cannot remove from an empty DEQ");
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
        throw std::out_of_range("No elements in DEQ");
    }
    return front->data;
}

template <typename T>
T DEQ<T>::View_Rear() const {
    if (DEQisEmpty()) {
        throw std::out_of_range("No elements in DEQ");
    }
    return rear->data;
}

template <typename T>
int DEQ<T>::DEQ_Length() const {
    return length;
}
