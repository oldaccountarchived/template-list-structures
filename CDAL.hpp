#include <ostream>

namespace cop3530 {
    template <typename T>
    class CDAL {
    private:
        struct Node {
            // Fixed size list of 50.
            T* list;
            Node* next;
        
            Node() {
                this->list = new T[50];
                this->next = NULL;
            }
        };
        Node* head; 
        int maxSize;     // Max number of elements CDAL can hold before adding 
        // a new Array.
        int currentSize; // Current number of elements in CDAL.
    
    public:
        CDAL();
        CDAL( int maxSize );
        CDAL( const CDAL& src );
        ~CDAL();
        CDAL& operator=( const CDAL& src ) {
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
}
