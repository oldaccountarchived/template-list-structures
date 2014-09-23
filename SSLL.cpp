#include "SSLL.hpp"
#include <exception>

template <typename T>
SSLL<T>::SSLL() {
    this->head = NULL;
    this->tail = NULL;
    listSize = 0;
}

template <typename T>
SSLL<T>::SSLL( const SSLL& src ) {
    // SOMEDAY, SOMEHOW
    // I'M GONNA IMPLEMENT THIS
    // BUT NOT RIGHT NOW
}

template <typename T>
SSLL<T>::~SSLL() {
    // delete head;
    // delete tail;
}

template <typename T>
T SSLL<T>::replace( const T& element, int position ) {
    // Probably not correct!
    if (listSize != 0) {
        Node* start = head;
        for (int i = 1; i != position; i++) {
            start = start->next;
        }
        *start = element;
    }
    else {
        throw std::out_of_range("list is empty!");
    }
}


template <typename T>
void SSLL<T>::insert( const T& element, int position ) {
    Node* temp = head;
    // get the element before the position, as it will point
    // to the element after the position in the end.
    for (int i = 1; i != position -1; ++i) {
        temp = temp->next;
    }
    listSize++
}

template <typename T>
void SSLL<T>::push_front( const T& element ) {
    if (listSize == 0) {
        Node* temp = new Node( element );
        this->head = temp;
        this->tail = temp;
        listSize++;
    } else {
        Node* temp = new Node( element );
        Node* temp2;
        temp2 = head;
        head = temp;
        head->next = temp2;
        temp1 = NULL;
        temp2 = NULL;
        delete temp1, temp2;
        listSize++;
    }
}

template <typename T>
void SSLL<T>::push_back( const T& element ) {
    if (listSize == 0) {
        Node* temp = new Node( element );
        this->head = temp;
        this->tail = temp;
        listSize++;
    }
    else {
        Node* temp = new Node( element );
        tail->next = temp;
        tail = temp;
        listSize++;
    }
}

template <typename T>
T SSLL<T>::pop_front() {
    if (listSize != 0) {
        T temp = head->value;
        head = head->next;
        listSize--;
        return temp;
    } else {
        throw std::out_of_range("list is empty!");
    }
}

template <typename T>
T SSLL<T>::pop_back() {
    if (listSize != 0) {
        T val;
        if (listSize == 1) {
            Node* temp = head;
            val = temp->value;
            head = NULL;
            tail = NULL;
            delete temp;
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
            tail = temp;
            temp = NULL;
            delete temp;
        }
        listSize--;
        return val;
    }
    else {
        throw std::out_of_range("list is empty!");
    }
}

template <typename T>
T SSLL<T>::remove( int position ) {
    T val;
    // Works with list size 2 or greater, implement for size 1...
    Node* temp = head;
    // get the element before the position, as it will point
    // to the element after the position in the end.
    for (int i = 1; i != position -1; ++i) {
        temp = temp->next;
    }
    Node* temp2 = temp->next;
    temp->next = temp->next->next;
    val = temp2->value;
    delete temp2;
    temp = NULL;
    delete temp;
    listSize--;
    return val;
}

template <typename T>
T SSLL<T>::item_at( int position ) const {
    Node* temp = head;
    for (int i = 1; i != position; ++i) {
        temp = temp->next;
    }
    T value = temp->value;
    temp = NULL;
    delete temp;
    return value;
}

template <typename T>
bool SSLL<T>::is_empty() const {
    if (listSize == 0) {
        return true;
    } else {
        return false;
    }
}

template <typename T>
int SSLL<T>::size() const {
    return listSize;
}

template <typename T>
void SSLL<T>::clear() {
  
}

template <typename T>
bool SSLL<T>::contains( const T& element, 
                        bool equals( const T& a, const T& b  ) ) const {
    
}

template <typename T>
std::ostream& SSLL<T>::print( std::ostream& out ) const {
    
}
