#include "SSLL.hpp"
#include <stdexcept>
#include <sstream>

using namespace cop3530;

// List constructor
template <typename T>
SSLL<T>::SSLL() {
    this->head = nullptr;
    this->tail = nullptr;
    listSize = 0;
}

// List copy constructor
template <typename T>
SSLL<T>::SSLL( const SSLL& src ) {
    if (src.head != nullptr) {
        this->head = new Node(src.head->value);
        Node* temp = src.head;
        Node* temp2 = head;
        while (temp != nullptr) {
            if (temp->next == nullptr) {
                this->tail = temp2;
            } else {
                temp2->next = new Node( temp->next->value );
            }
            temp = temp->next;
            temp2 = temp2->next;
        }
        listSize = src.listSize;
    } else {
        this->head = nullptr;
        this->tail = 0;
        listSize = 0;
    }

}

// List deconstructor
template <typename T>
SSLL<T>::~SSLL() {
    clear();
}

// This function replaces an element at a given position with a user passed in
// element. The element that was at the position previously is returned.
template <typename T>
T SSLL<T>::replace( const T& element, int position ) {
    if ( listSize != 0 ) {
        Node* start = head;
        for (int i = 0; i != position; i++) {
            start = start->next;
        }
        T temp = start->value;
        start->value = element;
        return temp;
    } else {
        throw std::domain_error("list is empty!");
    }
}

// This function inserts a user passed element at a given position. The function
// does not return anything but does modify the list. The size of the list is
// increased by one upon function completion.
template <typename T>
void SSLL<T>::insert( const T& element, int position ) {
    if ( position == listSize ) { 
        push_back( element );
    } else if ( position == 0 ) {
        push_front( element );
    } else if ( position < listSize ) {
        Node* temp = head;
        // get the element before the position, as it will point
        // to the element after the position in the end.
        for (int i = 0; i != (position - 1); ++i) {
            temp = temp->next;
        }
        Node* temp2 = temp->next;
        temp->next = new Node( element );
        temp->next->next = temp2;
        ++listSize; 
    } else {
        throw std::domain_error("List is too short!");
    }
}

// This function inserts an element at the very front of the list. It does not
// return anything. The size of the list is increased by one upon function
// completion.
template <typename T>
void SSLL<T>::push_front( const T& element ) {
    if (listSize == 0) {
        this->head = new Node( element );
        this->tail = head;
    } else {
        Node* temp = new Node( element );
        temp->next = head;
        head = temp;
    }
    ++listSize;
}

// This function inserts an element at the rear of the list. It does not
// return anything. The size of the list is increased by one upon function
// completion.
template <typename T>
void SSLL<T>::push_back( const T& element ) {
    if (listSize == 0) {
        this->head = new Node( element );
        this->tail = head;
    } else {
        tail->next = new Node( element );
        tail = tail->next;
    }
    ++listSize;
}

// This function removes the frontmost element from the list and returns it for
// use. The size of the list is reduced by 1 upon function completion.
template <typename T>
T SSLL<T>::pop_front() {
    if (listSize != 0) {
        T val = head->value;
        Node* temp = head->next;
        delete head;
        head = temp;
        listSize--;
        return val;
    } else {
        throw std::out_of_range("list is empty!");
    }
}

// This function removes the rear element from the list and returns it for
// use. The size of the list is reduced by 1 upon function completion.
template <typename T>
T SSLL<T>::pop_back() {
    if (listSize != 0) {
        T val;
        if (listSize == 1) {
            val = head->value;
            delete head;
            head = nullptr;
            tail = nullptr;
        } else {
            // Go down the list until we reach the element before the tail.
            Node* temp = head;
            for (int i = 1; i != listSize - 1; ++i) {
                temp = temp->next;
            }
            // Get the value from the tail, delete tail node, and make this
            // node the new tail.
            val = temp->next->value;
            delete temp->next;
            temp->next = nullptr;
            tail = temp;
        }
        listSize--;
        return val;
    } else {
        throw std::out_of_range("list is empty!");
    }
}

// This function removes an element from the list at a user specified position
// and returns it for use. The size of the list is reduced by 1 upon function
// completion.
template <typename T>
T SSLL<T>::remove( int position ) {
    if ( position < listSize ) {
        if ( listSize == 1 ) {
            return pop_back();
        } else {
            T val;
            // Works with list size 2 or greater, implement for size 1...
            Node* temp = head;
            // get the element before the position, as it will point
            // to the element after the position in the end.
            for (int i = 0; i != (position - 1); ++i) {
                temp = temp->next;
            }
            Node* temp2 = temp->next;
            temp->next = temp->next->next;
            val = temp2->value;
            delete temp2;
            temp2 = nullptr;
            --listSize;
            return val;
        }
    } else {
        throw std::domain_error("List is too short!");
    }
}

// This function returns the value of an element at user-specified position
// without removing it from the list. The list will not be modified as a result
// of this function being called.
template <typename T>
T SSLL<T>::item_at( int position ) const {
    Node* temp = head;
    for (int i = 0; i != position; ++i) {
        temp = temp->next;
    }
    T value = temp->value;
    return value;
}

// This function returns true if the list is empty and false otherwise.
template <typename T>
bool SSLL<T>::is_empty() const {
    if (listSize == 0) {
        return true;
    } else {
        return false;
    }
}

// This function returns the current size of the list.
template <typename T>
size_t SSLL<T>::size() const {
    return listSize;
}

// This function clears the list, setting the number of elements to 0.
template <typename T>
void SSLL<T>::clear() {
    Node* temp = head;
    Node* temp2;
    while (temp != nullptr) {
        temp2 = temp->next;
        delete temp;
        temp = temp2;
        --listSize;
    }
    head = nullptr;
    tail = nullptr;
}

// This function takes an element and a comparison function as parameters and
// checks to see if the user-specified element is contained in the list.
template <typename T>
bool SSLL<T>::contains( const T& element, 
                        bool equals( const T& a, const T& b  ) ) const {
    for (int i = 0; i < listSize; ++i) {
        if (equals(item_at(i), element)) {
            return true;
        }
    }
    return false;    
}

// This function creates a stream for printing the contents of the list
// structure.
template <typename T>
std::ostream& SSLL<T>::print( std::ostream& out ) const {
    Node* temp = head;
    out << "{";
    for (int i = 0; i != listSize; i++) {
        if ( temp != tail ) {
            out << temp->value << ", ";
        } else {
            out << temp->value;
        }
        temp = temp->next;
    }
    out << "}" << std::endl;
    return out;
}

template <typename T>
T& SSLL<T>::operator[](int i) {
    Node* temp = head;
    for (int j = 0; j != i; ++j) {
        temp = temp->next;
    }
    return temp->value;
}

template <typename T>
T const& SSLL<T>::operator[](int i) const {
    Node* temp = head;
    for (int j = 0; j != i; ++j) {
        temp = temp->next;
    }
    return temp->value;
}
