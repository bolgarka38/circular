#ifndef CIRCULAR_INL_INCLUDED
#define CIRCULAR_INL_INCLUDED

#include <utility>

template<typename T>
void CircularList<T>::copy_from(const CircularList& other) {
    if (other.is_empty()) {
        current_ = nullptr;
        size_ = 0;
        return;
    }

    Node* other_curr = other.current_;
    Node* new_node = new Node(other_curr->data);
    current_ = new_node;
    new_node->prev = new_node;
    new_node->next = new_node;
    size_ = 1;

    Node* other_node = other_curr->next;
    Node* last = new_node;
    while (other_node != other_curr) {
        Node* copy = new Node(other_node->data);
        copy->prev = last;
        copy->next = last->next;
        last->next->prev = copy;
        last->next = copy;
        last = copy;
        ++size_;
        other_node = other_node->next;
    }
}

template<typename T>
CircularList<T>::CircularList() : current_(nullptr), size_(0) {}

template<typename T>
CircularList<T>::CircularList(const CircularList& other)
    : current_(nullptr), size_(0) {
    copy_from(other);
}

template<typename T>
CircularList<T>::CircularList(CircularList&& other) noexcept
    : current_(other.current_), size_(other.size_) {
    other.current_ = nullptr;
    other.size_ = 0;
}

template<typename T>
CircularList<T>::~CircularList() {
    while (!is_empty()) {
        delete_current();
    }
}

template<typename T>
CircularList<T>& CircularList<T>::operator=(const CircularList& other) {
    if (this != &other) {
        CircularList tmp(other);
        std::swap(current_, tmp.current_);
        std::swap(size_, tmp.size_);
    }
    return *this;
}

template<typename T>
CircularList<T>& CircularList<T>::operator=(CircularList&& other) noexcept {
    if (this != &other) {
        while (!is_empty()) delete_current();
        current_ = other.current_;
        size_ = other.size_;
        other.current_ = nullptr;
        other.size_ = 0;
    }
    return *this;
}

template<typename T>
void CircularList<T>::insert_before(const T& value) {
    Node* new_node = new Node(value);
    if (is_empty()) {
        new_node->prev = new_node;
        new_node->next = new_node;
        current_ = new_node;
    } else {
        new_node->next = current_;
        new_node->prev = current_->prev;
        current_->prev->next = new_node;
        current_->prev = new_node;
    }
    ++size_;
}

template<typename T>
void CircularList<T>::insert_before(T&& value) {
    Node* new_node = new Node(std::move(value));
    if (is_empty()) {
        new_node->prev = new_node;
        new_node->next = new_node;
        current_ = new_node;
    } else {
        new_node->next = current_;
        new_node->prev = current_->prev;
        current_->prev->next = new_node;
        current_->prev = new_node;
    }
    ++size_;
}

template<typename T>
void CircularList<T>::insert_after(const T& value) {
    Node* new_node = new Node(value);
    if (is_empty()) {
        new_node->prev = new_node;
        new_node->next = new_node;
        current_ = new_node;
    } else {
        new_node->prev = current_;
        new_node->next = current_->next;
        current_->next->prev = new_node;
        current_->next = new_node;
    }
    ++size_;
}

template<typename T>
void CircularList<T>::insert_after(T&& value) {
    Node* new_node = new Node(std::move(value));
    if (is_empty()) {
        new_node->prev = new_node;
        new_node->next = new_node;
        current_ = new_node;
    } else {
        new_node->prev = current_;
        new_node->next = current_->next;
        current_->next->prev = new_node;
        current_->next = new_node;
    }
    ++size_;
}

template<typename T>
void CircularList<T>::delete_current() {
    if (is_empty()) {
        throw list_error("delete_current(): список пуст");
    }

    Node* to_delete = current_;
    if (size_ == 1) {
        current_ = nullptr;
    } else {
        current_->prev->next = current_->next;
        current_->next->prev = current_->prev;
        current_ = current_->next;
    }
    delete to_delete;
    --size_;
}

template<typename T>
void CircularList<T>::next() {
    if (is_empty()) {
        throw list_error("next(): список пуст");
    }
    current_ = current_->next;
}

template<typename T>
void CircularList<T>::prev() {
    if (is_empty()) {
        throw list_error("prev(): список пуст");
    }
    current_ = current_->prev;
}

template<typename T>
T* CircularList<T>::get_current() {
    if (is_empty()) return nullptr;
    return &(current_->data);
}

template<typename T>
const T* CircularList<T>::get_current() const {
    if (is_empty()) return nullptr;
    return &(current_->data);
}

template<typename T>
bool CircularList<T>::is_empty() const {
    return size_ == 0;
}

template<typename T>
size_t CircularList<T>::size() const {
    return size_;
}


#endif // CIRCULAR_INL_INCLUDED
