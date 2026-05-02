#ifndef CIRCULAR_HPP_INCLUDED
#define CIRCULAR_HPP_INCLUDED

#include <iostream>
#include <stdexcept>

class list_error : public std::runtime_error {
public:
    explicit list_error(const std::string& msg) : std::runtime_error(msg) {}
};

template<typename T>
class CircularList {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;

        Node(const T& val) : data(val), prev(nullptr), next(nullptr) {}
        Node(T&& val) : data(std::move(val)), prev(nullptr), next(nullptr) {}
    };

    Node* current_;
    size_t size_;

    void copy_from(const CircularList& other);

public:
    CircularList();
    CircularList(const CircularList& other);
    CircularList(CircularList&& other) noexcept;
    ~CircularList();

    CircularList& operator=(const CircularList& other);
    CircularList& operator=(CircularList&& other) noexcept;

    void insert_before(const T& value);
    void insert_before(T&& value);
    void insert_after(const T& value);
    void insert_after(T&& value);

    void delete_current();

    void next();
    void prev();

    T* get_current();
    const T* get_current() const;

    bool is_empty() const;
    size_t size() const;

    friend std::ostream& operator<<(std::ostream& os, const CircularList& list) {
        if (list.is_empty()) {
            os << "[]";
            return os;
        }
        os << "[";
        Node* start = list.current_;
        Node* n = start;
        do {
            os << n->data;
            n = n->next;
            if (n != start) os << ", ";
        } while (n != start);
        os << "]";
        return os;
    }
};

#include "circular.inl"

#endif // CIRCULAR_HPP_INCLUDED
