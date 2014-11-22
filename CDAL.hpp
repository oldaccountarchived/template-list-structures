#include <ostream>
#include <iterator>
#include <cstddef>

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
                this->next = nullptr;
            }
        };
        Node* head;
        int maxSize; // Max number of elements CDAL can hold before adding 
                     // a new Array.
        int currentSize; // Current number of elements in CDAL.
    
    public:

        // Non const iterator.
        class CDAL_Iter //: public std::iterator<std::forward_iterator_tag, T>
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
            typedef CDAL_Iter self_type;
            typedef CDAL_Iter& self_reference;
      
        private:
            int position;
            Node* here;
      
        public:
            explicit CDAL_Iter( Node* start = nullptr ) : here( start ) { 
                if (start == nullptr) {
                    this->position = 0;
                }
                this->position = 0; 
            }
            
            CDAL_Iter( const CDAL_Iter& src ) : here( src.here ) { 
                this->position = src.position; 
            }
            
            reference operator*() const {
                return here->list[position % 50];
            }
            pointer operator->() const {
                T* temp = &here->list[position % 50];
                return temp;
            }
      
            self_reference operator=( const CDAL_Iter& src ) {
                this = CDAL_Iter( src );
                return this;
            }

            self_reference operator++() {
                if ((position / 50) > ((position - 1) / 50)) {
                    here = here->next;
                }
                position++;
                return this;
            } // preincrement

            self_type operator++(int) {
                CDAL_Iter temp = CDAL_Iter( this );
                if ((position / 50) > ((position - 1) / 50)) {
                    here = here->next;
                }
                position++;
                return temp;
            } // postincrement

            bool operator==(const CDAL_Iter& rhs) const {
                return this == rhs;
            }
            bool operator!=(const CDAL_Iter& rhs) const {
                return this != rhs;
            }
        }; // end CDAL_Iter 

        class CDAL_Const_Iter //: public std::iterator<std::forward_iterator_tag, T>
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
            typedef CDAL_Iter self_type;
            typedef CDAL_Iter& self_reference;
      
        private:
            int position;
            const Node* here;
      
        public:
            explicit CDAL_Const_Iter( Node* start = nullptr ) : here( start ) { 
                this->position = 0; 
            }
            CDAL_Const_Iter( const CDAL_Iter& src ) : here( src.here ) {
                this->position = 0;
            }
            reference operator*() const {
                return here->list[position % 50];
            }
            pointer operator->() const {
                T* temp = &here->list[position % 50];
                return temp;
            }      
            self_reference operator=( const CDAL_Iter& src ) {
                this = CDAL_Iter( src );
                return this;
            }
            self_reference operator++() {
                if ((position / 50) > ((position - 1) / 50)) {
                    here = here->next;
                }
                position++;
                return this;
            } // preincrement
            self_type operator++(int) {
                CDAL_Const_Iter temp = CDAL_Const_Iter( this );
                if ((position / 50) > ((position - 1) / 50)) {
                    here = here->next;
                }
                position++;
                return temp;
            } // postincrement

            bool operator==(const CDAL_Const_Iter& rhs) const {
                return this->here->item_at(position % 50) == 
                    rhs->here->item_at(position % 50);
            }
            bool operator!=(const CDAL_Const_Iter& rhs) const {
                return this->here->item_at(position % 50) != 
                    rhs->here->item_at(position % 50);            
            }
        }; // end CDAL_Iter 

        typedef std::size_t size_t;
        typedef T value_type;
        typedef CDAL_Iter iterator;
        typedef CDAL_Const_Iter const_iterator; 
        iterator begin() { return CDAL_Iter( head, 0 ); }
        iterator end() { return CDAL_Iter( nullptr, size() ); }
        const_iterator begin() const { return CDAL_Const_Iter( head ); }
        const_iterator end() const { return CDAL_Const_Iter(); } 
        // CDAL Memeber functions.
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
