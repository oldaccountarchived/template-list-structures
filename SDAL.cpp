#include "SDAL.hpp"
#include <iostream>
#include <stdexcept>

using namespace cop3530;

template <typename T>
SDAL<T>::SDAL() {
    this->list = new T[50];
    this->currentSize = 0;
    this->maxSize = 50;
}

template <typename T>
SDAL<T>::SDAL( int maxSize ) {
    this->list = new T[maxSize];
    this->currentSize = 0;
    this->maxSize = maxSize;
}

template <typename T>
SDAL<T>::SDAL( const SDAL& src ) {
}

template <typename T>
SDAL<T>::~SDAL() {
    delete[] list;
}

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

template <typename T>
T SDAL<T>::replace( const T& element, int position ) {
    list[position] = element;
}

template <typename T>
void SDAL<T>::insert( const T& element, int position ) {
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
}

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

template <typename T>
void SDAL<T>::push_back( const T& element ) {
    std::cout << currentSize << " " << maxSize << std::endl;
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

template <typename T>
T SDAL<T>::pop_front() {
    T temp = list[0];
    for ( int i = 0; i != currentSize; ++i ) {
        list[i] = list[i + 1];
    }
    --currentSize;
    resizeList();
    return temp;
}

template <typename T>
T SDAL<T>::pop_back() {
    T temp = list[currentSize - 1];
    --currentSize;
    return temp;
}

template <typename T>
T SDAL<T>::remove( int position ) {
    T temp = list[position];
    for ( int i = position; i != (currentSize - 1); ++i ) {
        list[i] = list[i + 1];
    }
    --currentSize;
    resizeList();
    return temp;
}

template <typename T>
T SDAL<T>::item_at( int position ) const {
    return list[position];
}

template <typename T>
bool SDAL<T>::is_empty() const {
    if (currentSize == 0) {
        return true;
    } else {
        return false;
    }
}

template <typename T>
int SDAL<T>::size() const {
    return currentSize;
}

template <typename T>
void SDAL<T>::clear() {
    delete[] list;
    list = new T[maxSize];
    currentSize = 0;
}

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

template <typename T>
std::ostream& SDAL<T>::print( std::ostream& out ) const {
}
