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
DSLL<T>::DSLL( const DSLL& src ) {
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
    } else {
        throw std::domain_error("list is empty!");
    }
}

template <typename T>
void DSLL<T>::insert( const T& element, int position ) {
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
        if (poolSize == 0) {
            temp->next = new Node( element );
        } else {
            temp->next = poolHead;
            temp->next->value = element;
            --poolSize;
            if ( poolSize == 0 ) {
                poolHead = NULL;
            } else {
                poolHead = poolHead->next;
            }
        }
        temp->next->next = temp2;
        temp = NULL;
        temp2 = NULL;
        delete temp, temp2;
    } else {
        throw std::domain_error("List is too short!");
    }
    listSize++; 
}

template <typename T>
void DSLL<T>::push_front( const T& element ) {
    if (listSize == 0) {
        if (poolSize == 0) {
            Node* temp = new Node( element );
            this->head = temp;
            this->tail = temp;
        } else {
            poolHead->value = element;
            this->head = poolHead;
            this->tail = poolHead;
            poolSize--;
            if (poolSize == 0) {
                poolHead = NULL;
            } else {
                poolHead = poolHead->next;
            }
        }
    } else {
        if (poolSize == 0) {
            Node* temp = new Node( element );
            temp->next = head;
            head = temp;
            temp = NULL;
            delete temp;
        } else {
            poolHead->value = element;
            poolHead->next = head;
            head = poolHead;
            --poolSize;
            if (poolSize == 0) {
                poolHead = NULL;
            } else {
                poolHead = poolHead->next;
            }
        }
    }
    listSize++;
}

template <typename T>
void DSLL<T>::push_back( const T& element ) {
    if (listSize == 0) {
        if ( poolSize == 0 ) {
            Node* temp = new Node( element );
            this->head = temp;
            this->tail = temp;
        } else {
            // Use the pool, dude!
            poolHead->value = element;
            this->head = tail;
            this->tail = head;
            --poolSize;
            if (poolSize == 0) {
                poolHead = NULL;
            } else {
                poolHead = poolHead->next;
            }
        }
    }
    else {
        if ( poolSize == 0 ) {
            Node* temp = new Node( element );
            tail->next = temp;
            tail = temp;
        } else {
            poolHead->value = element;
            tail->next = poolHead;
            tail = poolHead;
            --poolSize;
            if (poolSize == 0) {
                poolHead = NULL;
            } else {
                poolHead = poolHead->next;
            }
        }
    }
    listSize++;
}

template <typename T>
T DSLL<T>::pop_front() {
    if (listSize != 0) {
        T val = head->value;
        Node* temp = head->next;
        // add the current head to the pool, don't delete.
        head->next = poolHead->next;
        poolHead = head;
        head = temp;
        listSize--;
        return val;
    } else {
        throw std::out_of_range("list is empty!");
    }
}
