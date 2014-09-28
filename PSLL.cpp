#include "PSLL.hpp"
#include <exception>

template <typename T>
PSLL<T>::PSLL() {
    this->head = NULL;
    this->tail = NULL;
    this->poolHead = NULL;
    poolSize = 0;
    listSize = 0;
}

template <typename T>
PSLL<T>::PSLL( const PSLL& src ) {
    // SOMEDAY, SOMEHOW
    // I'M GONNA IMPLEMENT THIS
    // BUT NOT RIGHT NOW
}

template <typename T>
PSLL<T>::~PSLL() {
    // delete head;
    // delete tail;
    // delete poolHead;
}

template <typename T>
T PSLL<T>::replace( const T& element, int position ) {
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
void PSLL<T>::insert( const T& element, int position ) {
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
        listSize++; 
    } else {
        throw std::domain_error("List is too short!");
    }
}

template <typename T>
void PSLL<T>::push_front( const T& element ) {
    if (listSize == 0) {
        if (poolSize == 0) {
            this->head = new Node( element );
            this->tail = head;
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
void PSLL<T>::push_back( const T& element ) {
    if (listSize == 0) {
        if ( poolSize == 0 ) {
            this->head = new Node( element );
            this->tail = head;
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
            tail->next = new Node( element );
            tail = tail->next;
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
T PSLL<T>::pop_front() {
    if (listSize != 0) {
        T val = head->value;
        Node* temp = head->next;
        // add the current head to the pool, don't delete.
        if ( poolSize == 0 ) {
            poolHead = head;
        } else {
            head->next = poolHead->next;
            poolHead = head;
        }
        ++poolSize;
        head = temp;
        --listSize;
        return val;
    } else {
        throw std::out_of_range("list is empty!");
    }
}

template <typename T>
T PSLL<T>::pop_back() {
    if (listSize != 0) {
        T val;
        if (listSize == 1) {
            val = head->value;
            if ( poolSize == 0 ) {
                poolHead = head;
            } else {
                head->next = poolHead->next;
                poolHead = head;
            }
            ++poolSize;
            head = NULL;
            tail = NULL;
        } else {
            // Go down the list until we reach the element before the tail.
            Node* temp = head;
            for (int i = 1; i != listSize - 1; ++i) {
                temp = temp->next;
            }
            // Get the value from the tail, delete tail node, and make this
            // node the new tail.
            val = temp->next->value;
            if ( poolSize == 0 ) {
                poolHead = temp->next;
            } else {
                temp->next->next = poolHead->next;
                poolHead = temp->next;
            }
            ++poolSize;
            temp->next = NULL;
            tail = temp;
        }
        -- listSize;
        return val;
    }
    else {
        throw std::out_of_range("list is empty!");
    }
}

template <typename T>
T PSLL<T>::remove( int position ) {
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
            if (poolSize == 0) {
                poolHead = temp2;
            } else {
                temp2->next = poolHead->next;
                poolHead = temp2;
            }
            ++poolSize;
            temp2 = NULL;
            --listSize;
            return val;
        }
     } else {
        throw std::domain_error("List is too short!");
    }
}

template <typename T>
T PSLL<T>::item_at( int position ) const {
    Node* temp = head;
    for (int i = 0; i != position; ++i) {
        temp = temp->next;
    }
    T value = temp->value;
    return value;
}

template <typename T>
bool PSLL<T>::is_empty() const {
    if (listSize == 0) {
        return true;
    } else {
        return false;
    }
}

template <typename T>
int PSLL<T>::size() const {
    return listSize;
}

template <typename T>
void PSLL<T>::clear() {
    // TODO: Instead this should add nodes to the head.
    Node* temp = head;
    Node* temp2;
    while (temp != NULL) {
        temp2 = temp->next;
        delete temp;
        temp = temp2;
        --listSize;
    }
}

template <typename T>
bool PSLL<T>::contains( const T& element, 
                        bool equals( const T& a, const T& b  ) ) const {
    
}

template <typename T>
std::ostream& PSLL<T>::print( std::ostream& out ) const {
    // Node* temp = head;
    // ostringstream ostr;
    // for (int i = 0; i != position; i++) {
    //     ostr << temp->value << " ";
    //     temp = temp->next;
    // }
    // return ost
}
