#include "SDAL.hpp"

template <typename T>
SDAL<T>::SDAL() {
}

template <typename T>
SDAL<T>::SDAL( int maxSize ) {
}

template <typename T>
SDAL<T>::SDAL( const SDAL& src ) {
}

template <typename T>
SDAL<T>::~SDAL() {
}

template <typename T>
T SDAL<T>::replace( const T& element, int position ) {
}

template <typename T>
void SDAL<T>::insert( const T& element, int position ) {
}

template <typename T>
void SDAL<T>::push_front( const T& element ) {
}

template <typename T>
void SDAL<T>::push_back( const T& element ) {
}

template <typename T>
T SDAL<T>::pop_front() {
}

template <typename T>
T SDAL<T>::pop_back() {
}

template <typename T>
T SDAL<T>::remove( int position ) {
}

template <typename T>
T SDAL<T>::item_at( int position ) const {
}

template <typename T>
bool SDAL<T>::is_empty() const {
}

template <typename T>
int SDAL<T>::size() const {
}

template <typename T>
void SDAL<T>::clear() {
}

template <typename T>
bool SDAL<T>::contains( const T& element, 
                        bool equals( const T& a, const T& b  ) ) const {
}

template <typename T>
std::ostream& SDAL<T>::print( std::ostream& out ) const {
}
