#include "DSLL.hpp"
#include <exception>

template <typename T>
DSLL<T>::DSLL() {
    this->head = NULL;
    this->tail = NULL;
    this->poolHead = NULL;
    poolSize = 0;
    listSize = 0;
}

template <typename T>
DSLL<T>::DSLL( const SSLL& src ) {
    // SOMEDAY, SOMEHOW
    // I'M GONNA IMPLEMENT THIS
    // BUT NOT RIGHT NOW
}

template <typename T>
DSLL<T>::~DSLL() {
    // delete head;
    // delete tail;
    // delete poolHead;
}

template <typename T>
T DSLL<T>::replace( const T& element, int position ) {
    // Probably not correct!
    if ( listSize != 0 ) {
        Node* start = head;
        for (int i = 0; i != position; i++) {
            start = start->next;
        }
        T temp = start->value;
        start->value = element;
        return temp;
    }
    else {
        throw std::out_of_range("list is empty!");
    }
}

template <typename T>
void SSLL<T>::insert( const T& element, int position ) {
    if ( position == listSize ){ 
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
        temp = NULL;
        temp2 = NULL;
        delete temp, temp2;
    } else {
        throw std::domain_error("List is too short!");
    }
    listSize++; 
}
