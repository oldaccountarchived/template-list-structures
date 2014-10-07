#include "CDAL.hpp"
#include <stdexcept>
#include <iostream>

using namespace cop3530;

template <typename T>
CDAL<T>::CDAL() {
    this->head = new Node();
    this->currentSize = 0;
    this->maxSize = 50;
}

template <typename T>
CDAL<T>::CDAL( const CDAL& src ) {
    // SOMEDAY
}

template <typename T>
CDAL<T>::~CDAL() {
    clear();
    delete head;
}

template <typename T>
T CDAL<T>::replace( const T& element, int position ) {
    if ( position < currentSize ) {
        int counter = position / 50; // Tells us which array the data is in.
        int pos = position % 50; // Tells us where the data is in that array.
        Node* temp = head;
        for (int i = 0; i != counter; i++) {
            temp = temp->next;
        }
        T val = temp->list[pos];
        temp->list[pos] = element;
        temp = NULL;
        return val;
    } else {
        throw std::domain_error("Position does not exist \"Too Large\"");
    }
}

template <typename T>
void CDAL<T>::insert( const T& element, int position ) {
    if ( position == currentSize ) {
        push_back(element);
    } else if ( position == 0 ) {
        push_front(element);
    } else if ( position < currentSize ) {
        T nextVal;
        T nextNextVal;
        Node* temp = head;
        int currentNode = position / 50;
        // Get to the right node first...
        for (int i = 0; i != currentNode; ++i) {
            temp = temp->next;
        }
        // Move the element at the position to position + 1 and store what's in position + 1
        // in a temporary variable.
        nextVal = temp->list[(position + 1) % 50];
        temp->list[(position + 1) % 50] = temp->list[position % 50];
        // Push element to the front
        temp->list[position % 50] = element;
        // Re-order the remaining elements.
        for ( int i = position + 2; i <= currentSize; ++i ) {
            if ( currentNode < (i / 50) ) { // Check if the index is past the current node.
                ++currentNode; // If it is, increment the current node.
                if ( temp->next == NULL ) {
                    // Make a new node if one isn't there!
                    temp->next = new Node();
                }
                temp = temp->next; // And set the temp node to that node.
            }
            nextNextVal = temp->list[i % 50];
            temp->list[i % 50] = nextVal;
            nextVal = nextNextVal;
        }
        ++currentSize;
    } else {
        throw std::domain_error("Position does not exist \"Too Large\"");
    }
}

template <typename T>
void CDAL<T>::push_front( const T& element ) {
    if (currentSize > 1) {
        T nextVal;
        T nextNextVal;
        Node* temp = head;
        int currentNode = 0;
        // Move the 0th element to position 1 and store what's in position 1 
        // in a temporary variable.
        nextVal = temp->list[1];
        temp->list[1] = temp->list[0];
        // Push element to the front
        temp->list[0] = element;
        // Re-order the remaining elements.
        for ( int i = 2; i <= currentSize; ++i ) {
            if ( currentNode < i/50 ) { // Check if the index is past the current node.
                ++currentNode; // If it is, increment the current node.
                if ( temp->next == NULL ) {
                    // Make a new node if one isn't there!
                    temp->next = new Node();
                    maxSize += 50;
                }
                temp = temp->next; // And set the temp node to that node.
            }
            nextNextVal = temp->list[i % 50];
            temp->list[i % 50] = nextVal;
            nextVal = nextNextVal;
        }
        temp = NULL;
        ++currentSize;
    } else if ( currentSize == 1 ) {
        head->list[1] = head->list[0];
        // Push element to the front
        head->list[0] = element;
        ++currentSize;
    } else {
        if (head == NULL) {
            head = new Node();
        }
        head->list[0] = element;
        ++currentSize;
    }
}

template <typename T>
void CDAL<T>::push_back( const T& element ) {
    Node* temp = head;
    int counter = (currentSize / 50);
    if ( currentSize >= maxSize ) {
        for (int i = 0; i != counter; i++) {
            if (temp->next == NULL) {
                temp->next = new Node();
            }
            temp = temp->next;
        } 
        maxSize += 50;
        temp = NULL;
    } 
    int pos = (currentSize % 50); // Tells us where the data is in that array.
    // counter = (currentSize) / 50; // Tells us which array the data is in.
    temp = head;
    for (int i = 0; i != counter; i++) {
        temp = temp->next;
    }
    temp->list[pos] = element;
    temp = NULL;
    ++currentSize;
}

template <typename T>
T CDAL<T>::pop_front() {
    if ( currentSize != 0 ) {
        T val = head->list[0];
        Node* temp = head;
        int currentNode = 0; // We start at the first node.
        for ( int i = 0; i < currentSize - 1; ++i ) {
            if ( currentNode < i / 50 ) { // Check if the index is past the current node.
                ++currentNode; // If it is, increment the current node.
                temp = temp->next; // And set the temp node to that node.
            }
            if ((i + 1)/50 > i / 50) { // Deals with the case where i + 1 is in the next node.
                temp->list[i % 50] = temp->next->list[(i + 1) % 50];
            } else {
                temp->list[i % 50] = temp->list[(i + 1) % 50];
            }
        }
        --currentSize;
        return val;
    } else {
        throw std::out_of_range("List is empty");
    }
}

template <typename T>
T CDAL<T>::pop_back() {
    if ( currentSize != 0 ) {
        int counter = (currentSize - 1) / 50; // Tells us which array the data is in.
        int pos = (currentSize - 1) % 50; // Tells us where the data is in that array.
        Node* temp = head;
        for (int i = 0; i != counter; i++) {
            temp = temp->next;
        }
        T val = temp->list[pos];
        temp = NULL;
        --currentSize;
        return val;
    } else {
        throw std::domain_error("Position does not exist \"Too Large\"");
    }
}

template <typename T>
T CDAL<T>::remove( int position ) {
    if ( position == currentSize - 1 ) {
        return pop_back();
    } else if ( position == 0 ) {
        return pop_front();
    } else if ( position < currentSize ) {
        Node* temp = head;
        int currentNode = position / 50; // We start at the first node.
        for (int i = 0; i != currentNode; ++i) {
            temp = temp->next;
        }
        T val = temp->list[position % 50];
        for ( int i = position; i < currentSize - 1; ++i ) {
            if ( currentNode < i/50 ) { // Check if the index is past the current node.
                ++currentNode; // If it is, increment the current node.
                temp = temp->next; // And set the temp node to that node.
            }
            if (((i + 1) / 50) > (i / 50)) { // Deals with the case where i + 1 is in the next node.
                temp->list[i % 50] = temp->next->list[(i + 1) % 50];
            } else { 
                temp->list[i % 50] = temp->list[(i + 1) % 50];
            }
        }
        --currentSize;
        return val;
    } else {
        throw std::domain_error("Position does not exist \"Too Large\"");
    }
}

template <typename T>
T CDAL<T>::item_at( int position ) const {
    if ( position < currentSize ) {
        int counter = position / 50; // Tells us which array the data is in.
        int pos = position % 50; // Tells us where the data is in that array.
        Node* temp = head;
        for (int i = 0; i != counter; i++) {
            temp = temp->next;
        }
        T val = temp->list[pos];
        temp = NULL;
        return val;
    } else {
        throw std::domain_error("Position does not exist \"Too Large\"");
    }
}

template <typename T>
bool CDAL<T>::is_empty() const {
    if (currentSize == 0)
        return false;
    else 
        return true;
}

template <typename T>
int CDAL<T>::size() const {
    return currentSize;
}

template <typename T>
void CDAL<T>::clear() {
    Node* temp = head;
    Node* temp2;
    while (temp != NULL) {
        temp2 = temp->next;
        delete[] temp->list;
        delete temp;
        temp = temp2;
    }
    head = new Node();
    currentSize = 0;
    maxSize = 50;
}

template <typename T>
bool CDAL<T>::contains( const T& element, 
                        bool equals( const T& a, const T& b  ) ) const {
    for (int i = 0; i < currentSize; ++i) {
        if (equals(item_at(i), element)) {
            return true;
        }
    }
    return false;
}

template <typename T>
std::ostream& CDAL<T>::print( std::ostream& out ) const {

}
