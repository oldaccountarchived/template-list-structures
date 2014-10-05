#include <ostream>
#include <iterator>

namespace cop3530 {
    template <typename T>
    class SSLL {
    private:
        struct Node {
            T value;
            Node* next;
        
            // Node with no arguments!
            Node() {
                this->value = NULL;
                this->value = NULL;
            }
        
            // For creating nodes with values.
            Node( T value ) {
                this->value = value;
                this->next = NULL;
            }
        };
        Node* head; 
        Node* tail;
        // Traversing the list every time is lame.
        int listSize;
    
    public:
        
        // Non const iterator.
        class SSLL_Iter //: public std::iterator<std::forward_iterator_tag, T>
        {
        public:
            // inheriting from std::iterator<std::forward_iterator_tag, T>
            // automagically sets up these typedefs...
            typedef T value_type;
            typedef std::ptrdiff_t difference_type;
            typedef T& reference;
            typedef T* pointer;
            typedef std::forward_iterator_tag iterator_category;
      
            // but not these typedefs...
            typedef SSLL_Iter self_type;
            typedef SSLL_Iter& self_reference;
      
        private:
            Node* here;
      
        public:
            explicit SSLL_Iter( Node* start = NULL ) : here( start ) {}
            SSLL_Iter( const SSLL_Iter& src ) : here( src.here ) {}
       
            reference operator*() const {
                return here->value;
            }
            pointer operator->() const {
                T* temp = &here->value;
                return temp;
            }
      
            self_reference operator=( const SSLL_Iter& src ) {
                *this = SSLL_Iter( src );
                return *this;
            }

            self_reference operator++() {
                here = here->next;
                return *this;
            } // preincrement
            
            self_type operator++(int) {
                SSLL_Iter* result = new SSLL_Iter( *this );
                here = here->next;
                return result;
            } // postincrement

            bool operator==(const SSLL_Iter& rhs) const {
                return here->value != rhs.here->value;
            }
            
            bool operator!=(const SSLL_Iter& rhs) const {
                return here->value != rhs.here->value;
            }
        }; // end SSLL_Iter 

        class SSLL_Const_Iter //: public std::iterator<std::forward_iterator_tag, T>
        {
        public:
            // inheriting from std::iterator<std::forward_iterator_tag, T>
            // automagically sets up these typedefs...
            typedef T value_type;
            typedef std::ptrdiff_t difference_type;
            typedef const T& reference;
            typedef const T* pointer; 
            typedef std::forward_iterator_tag iterator_category;
      
            // but not these typedefs...
            typedef SSLL_Iter self_type;
            typedef SSLL_Iter& self_reference;
      
        private:
            const Node* here;
      
        public:
            explicit SSLL_Const_Iter( Node* start = NULL ) : here( start ) {}
            SSLL_Const_Iter( const SSLL_Iter& src ) : here( src.here ) {}
       
            reference operator*() const {
                return here->value;
            }
            
            pointer operator->() const {
                T* temp = &here->value;
                return temp;
            }
      
            self_reference operator=( const SSLL_Iter& src ) {
               *this = SSLL_Iter( src );
               return *this;
            }

            self_reference operator++() {
                here = here->next;
                return *this;
            } // preincrement
            
            self_type operator++(int) {
                SSLL_Iter* result = new SSLL_Iter( *this );
                here = here->next;
                return result;
            } // postincrement

            bool operator==(const SSLL_Iter& rhs) const {
                return here->value == rhs.here->value;
            }
            
            bool operator!=(const SSLL_Iter& rhs) const {
                return here->value != rhs.here->value;
            }
        }; // end SSLL_Iter 

        typedef std::size_t size_t;
        typedef T value_type;
        typedef SSLL_Iter iterator;
        typedef SSLL_Const_Iter const_iterator; 
        iterator begin() { return SSLL_Iter( head ); }
        iterator end() { return SSLL_Iter(); }
        const_iterator begin() const { return SSLL_Const_Iter( head ); }
        const_iterator end() const { return SSLL_Const_Iter(); } 
 
        SSLL();
        SSLL( const SSLL& src );
        ~SSLL();
        SSLL& operator=( const SSLL& src ) {
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
