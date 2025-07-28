#ifndef UNSA_LINKED_LIST_TPP
#define UNSA_LINKED_LIST_TPP

#include <stdexcept> // std::out_of_range
#include <utility>   // std::swap

namespace unsa {

// ======================= Nodo =======================

template <typename T>
LinkedList<T>::Node::Node(const T& d, Node* n) : data(d), next(n) {}

// ======================= Iterador =======================

template <typename T>
LinkedList<T>::Iterator::Iterator(Node* ptr) : current(ptr) {}

template <typename T>
typename LinkedList<T>::Iterator::reference LinkedList<T>::Iterator::operator*() const {
    return current->data;
}

template <typename T>
typename LinkedList<T>::Iterator& LinkedList<T>::Iterator::operator++() {
    current = current->next;
    return *this;
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::Iterator::operator++(int) {
    Iterator temp = *this;
    ++(*this);
    return temp;
}

template <typename T>
bool LinkedList<T>::Iterator::operator==(const Iterator& other) const {
    return current == other.current;
}

template <typename T>
bool LinkedList<T>::Iterator::operator!=(const Iterator& other) const {
    return !(*this == other);
}

// ======================= Constructores y destructores =======================

template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr), count(0) {}

template <typename T>
LinkedList<T>::~LinkedList() {
    clear();
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList& other) : head(nullptr), tail(nullptr), count(0) {
    copy_from(other);
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& other) {
    if (this != &other) {
        clear();
        copy_from(other);
    }
    return *this;
}

template <typename T>
LinkedList<T>::LinkedList(LinkedList&& other) noexcept
    : head(other.head), tail(other.tail), count(other.count) {
    other.head = other.tail = nullptr;
    other.count = 0;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList&& other) noexcept {
    if (this != &other) {
        clear();
        head = other.head;
        tail = other.tail;
        count = other.count;
        other.head = other.tail = nullptr;
        other.count = 0;
    }
    return *this;
}

// ======================= Métodos =======================

template <typename T>
void LinkedList<T>::push_front(const T& value) {
    Node* new_node = new Node(value, head);
    head = new_node;
    if (!tail) tail = head;
    ++count;
}

template <typename T>
void LinkedList<T>::push_back(const T& value) {
    Node* new_node = new Node(value);
    if (tail) {
        tail->next = new_node;
        tail = new_node;
    } else {
        head = tail = new_node;
    }
    ++count;
}

template <typename T>
void LinkedList<T>::pop_front() {
    if (!head) throw std::out_of_range("Lista vacía");
    Node* temp = head;
    head = head->next;
    delete temp;
    --count;
    if (!head) tail = nullptr;
}

template <typename T>
void LinkedList<T>::pop_back() {
    if (!head) throw std::out_of_range("Lista vacía");
    if (head == tail) {
        delete head;
        head = tail = nullptr;
    } else {
        Node* prev = head;
        while (prev->next != tail)
            prev = prev->next;
        delete tail;
        tail = prev;
        tail->next = nullptr;
    }
    --count;
}

template <typename T>
typename LinkedList<T>::reference LinkedList<T>::front() {
    if (!head) throw std::out_of_range("Lista vacía");
    return head->data;
}

template <typename T>
typename LinkedList<T>::const_reference LinkedList<T>::front() const {
    if (!head) throw std::out_of_range("Lista vacía");
    return head->data;
}

template <typename T>
typename LinkedList<T>::reference LinkedList<T>::back() {
    if (!tail) throw std::out_of_range("Lista vacía");
    return tail->data;
}

template <typename T>
typename LinkedList<T>::const_reference LinkedList<T>::back() const {
    if (!tail) throw std::out_of_range("Lista vacía");
    return tail->data;
}

template <typename T>
bool LinkedList<T>::empty() const noexcept {
    return count == 0;
}

template <typename T>
typename LinkedList<T>::size_type LinkedList<T>::size() const noexcept {
    return count;
}

template <typename T>
void LinkedList<T>::clear() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
    count = 0;
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::begin() noexcept {
    return Iterator(head);
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::end() noexcept {
    return Iterator(nullptr);
}

template <typename T>
void LinkedList<T>::copy_from(const LinkedList& other) {
    for (Node* cur = other.head; cur != nullptr; cur = cur->next) {
        push_back(cur->data);
    }
}

} // namespace unsa

#endif // UNSA_LINKED_LIST_TPP
