#include "SDAL.hpp"
#include <iostream>
#include <stdexcept>

using namespace cop3530;

// Default list constructor, list is initialized to size 50.
template <typename T>
SDAL<T>::SDAL() {
    this->list = new T[50];
    this->currentSize = 0;
    this->maxSize = 50;
}

// List constructor that allows specification of an initial list size
template <typename T>
SDAL<T>::SDAL( int maxSize ) {
    this->list = new T[maxSize];
    this->currentSize = 0;
    this->maxSize = maxSize;
}

// List copy constructor
template <typename T>
SDAL<T>::SDAL( const SDAL& src ) {
    this->list = new T[src.maxSize];
    this->currentSize = src.currentSize;
    this->maxSize = src.maxSize;
    for (int i = 0; i != currentSize; ++i) {
        list[i] = src.list[i];
    }
}

// List deconstructor
template <typename T>
SDAL<T>::~SDAL() {
    delete[] list;
}

// This function resizes the list if the maximum size of the list is greater
// than 100, and more than twice the size of the current size of the list. The
// max Size is reduced by half.
template <typename T>
void SDAL<T>::resizeList() {
    if (maxSize >= 100 && maxSize / currentSize > 2) {
        T* temp = new T[maxSize / 2];
        for ( int i = 0; i != currentSize; ++i ) {
            temp[i] = list[i];
        }
        delete[] list;
        list = temp;
        maxSize = maxSize / 2;
    } else {
        return;
    }
}

// This function replaces an element at a given position with a user passed in
// element. The element that was at the position previously is returned.
template <typename T>
T SDAL<T>::replace( const T& element, int position ) {
    if ( position < currentSize && position >= 0 ) {
        list[position] = element;
    } else {
        throw std::domain_error("Position does not exist");
    }
}

// This function inserts a user passed element at a given position. The function
// does not return anything but does modify the list. The size of the list is
// increased by one upon function completion.
template <typename T>
void SDAL<T>::insert( const T& element, int position ) {
    if ( position <= currentSize && position >= 0) {
        if ( currentSize == maxSize ) {
            T* temp = new T[(int) (maxSize * 1.5)];
            for ( int i = 0; i != currentSize; ++i ) {
                temp[i] = list[i];
            }
            delete[] list;
            list = temp;
            maxSize = maxSize * 1.5;
        }
        for ( int i = currentSize; i != (position); --i ) {
            list[i] = list[i - 1];
        }
        list[position] = element;
        ++currentSize;
    } else {
        throw std::domain_error("Position does not exist");
    }
}

// This function inserts an element at the very front of the list. It does not
// return anything. The size of the list is increased by one upon function
// completion.
template <typename T>
void SDAL<T>::push_front( const T& element ) {
    if ( currentSize == maxSize ) {
        T* temp = new T[(int) (maxSize * 1.5)];
        for ( int i = 0; i != currentSize; ++i ) {
            temp[i] = list[i];
        }
        delete[] list;
        list = temp;
        maxSize = maxSize * 1.5;
    }
    for ( int i = currentSize; i != 0; --i ) {
        list[i] = list[i - 1];
    }
    list[0] = element;
    ++currentSize;
}

// This function inserts an element at the rear of the list. It does not
// return anything. The size of the list is increased by one upon function
// completion.
template <typename T>
void SDAL<T>::push_back( const T& element ) {
    if ( currentSize == maxSize ) {
        T* temp = new T[(int) (maxSize * 1.5)];
        for ( int i = 0; i != currentSize; ++i ) {
            temp[i] = list[i];
        }
        delete[] list;
        list = temp;
        maxSize = maxSize * 1.5;
    }
    list[currentSize] = element;
    ++currentSize;
}

// This function removes the frontmost element from the list and returns it for
// use. The size of the list is reduced by 1 upon function completion.
template <typename T>
T SDAL<T>::pop_front() {
    if ( !is_empty() ) {
        T temp = list[0];
        for ( int i = 0; i != currentSize; ++i ) {
            list[i] = list[i + 1];
        }
        --currentSize;
        resizeList();
        return temp;
    } else {
        throw std::out_of_range("The list is empty");
    }
}

// This function removes the rear element from the list and returns it for
// use. The size of the list is reduced by 1 upon function completion.
template <typename T>
T SDAL<T>::pop_back() {
    if ( !is_empty() ) {
        T temp = list[currentSize - 1];
        --currentSize;
        return temp;
    } else {
        throw std::out_of_range("The list is empty");
    }
}

// This function removes an element from the list at a user specified position
// and returns it for use. The size of the list is reduced by 1 upon function
// completion.
template <typename T>
T SDAL<T>::remove( int position ) {
    if ( position < currentSize && position >= 0 ) {
        T temp = list[position];
        for ( int i = position; i != (currentSize - 1); ++i ) {
            list[i] = list[i + 1];
        }
        --currentSize;
        resizeList();
        return temp;
    } else {
        throw std::domain_error("Position does not exist");
    }
}

// This function returns the value of an element at user-specified position
// without removing it from the list. The list will not be modified as a result
// of this function being called.
template <typename T>
T SDAL<T>::item_at( int position ) const {
    if ( position < currentSize && position >= 0 ) {
        return list[position];
    } else {
        throw std::domain_error("Position does not exist");
    }
}

// This function returns true if the list is empty and false otherwise.
template <typename T>
bool SDAL<T>::is_empty() const {
    if (currentSize == 0) {
        return true;
    } else {
        return false;
    }
}

// This function returns the size of the list.
template <typename T>
size_t SDAL<T>::size() const {
    return currentSize;
}

// This function removes all elements from the list
template <typename T>
void SDAL<T>::clear() {
    delete[] list;
    list = new T[maxSize];
    currentSize = 0;
}

// This function takes an element and a comparison function as parameters and
// checks to see if the user-specified element is contained in the list.
template <typename T>
bool SDAL<T>::contains( const T& element, 
                        bool equals( const T& a, const T& b  ) ) const {
    for (int i = 0; i < currentSize; ++i) {
        if (equals(item_at(i), element)) {
            return true;
        }
    }
    return false;
}

// This function creates a stream for printing the contents of the list
// structure.
template <typename T>
std::ostream& SDAL<T>::print( std::ostream& out ) const {
    out << "{";
    for (int i = 0; i != currentSize; ++i) {
        if ( i != currentSize - 1 ) {
            out << list[i] << ", ";
        } else {
            out << list[i];
        }
    }
    out << "}" << std::endl;
    return out;
}

template <typename T>
T& SDAL<T>::operator[](int i) {
    if ( i < currentSize && i >= 0) {
        return list[i];
    } else {
        throw std::domain_error("Position does not exist");
    }
}

template <typename T>
T const& SDAL<T>::operator[](int i) const {
    if (i < currentSize && i >= 0) {
        return list[i];
    } else {
        throw std::domain_error("Position does not exist");
    }
}
