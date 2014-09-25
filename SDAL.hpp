#include <ostream>

template <typename T>
class SDAL {
private:
    int maxSize;
    int currentSize;
    T* list;
    
public:
    SDAL();
    SDAL( int maxSize );
    SDAL( const SDAL& src );
    ~SDAL();
    SDAL& operator=( const SDAL& src ) {
        if ( &src == this )
            return *this;
    }
    T replace( const T& element, int position );
    void insert( const T& element, int position );
    void push_front( const T& element );
    void push_back( const T& element );
    T pop_front();
    T pop_back();
    T remove( int position );
    T item_at( int position ) const;
    bool is_empty() const;
    int size() const;
    void clear();
    bool contains( const T& element, 
                   bool equals( const T& a, const T& b  ) ) const;
    std::ostream& print( std::ostream& out ) const;
};
