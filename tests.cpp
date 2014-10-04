#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "SSLL.cpp"
#include "PSLL.cpp"
#include "SDAL.cpp"
#include "CDAL.cpp"

// First test the SSLL.
TEST_CASE ( "SSLL tests are done now!", "[SSLL]" ) {
    cop3530::SSLL<int> list1;
    SECTION ( "Test pop_front.", "[pop_front]" ) { 
         for (int i = 0; i < 200; i++) {
            list1.push_back(i * 5);
         }
         REQUIRE(list1.pop_front() == 0);
         REQUIRE(list1.pop_front() == 5);
         REQUIRE(list1.pop_front() == 10);
         REQUIRE(list1.pop_front() == 15);
         REQUIRE(list1.pop_front() == 20);
         REQUIRE(list1.pop_front() == 25);
         REQUIRE(list1.pop_front() == 30);
         REQUIRE(list1.pop_front() == 35);
    }
    SECTION ( "Test pop_back.", "[pop_back]" ) {
        for (int i = 0; i < 200; i++) {
            list1.push_back(i * 5);
        }
        REQUIRE(list1.pop_back() == 995);
        REQUIRE(list1.pop_back() == 990);
        REQUIRE(list1.pop_back() == 985);
        REQUIRE(list1.pop_back() == 980);
        REQUIRE(list1.pop_back() == 975);
        REQUIRE(list1.pop_back() == 970);
        REQUIRE(list1.pop_back() == 965);
        REQUIRE(list1.pop_back() == 960);
    }
    SECTION ( "Test item_at.", "[item_at]" ) {
        for (int i = 0; i < 200; i++) {
            list1.push_back(i * 5);
        }
        REQUIRE(list1.item_at(199) == 995);
        REQUIRE(list1.item_at(198) == 990);
        REQUIRE(list1.item_at(150) == 750);
        REQUIRE(list1.item_at(42) == 210);
        REQUIRE(list1.item_at(0) == 0);
    }
    SECTION ( "Test remove", "[remove]" ) {
        for (int i = 0; i < 200; i++) {
            list1.push_back(i * 5);
        }
        REQUIRE( list1.remove(198) == 990 );
        REQUIRE( list1.remove(198) == 995 );
        REQUIRE( list1.remove(50) == 250 );
        REQUIRE( list1.remove(50) == 255 ); 
        list1.clear();
        for (int i = 0; i < 200; i++) {
            list1.push_front(i * 5);
        }
        // Reverse order now, just to make sure pop_front is working!
        REQUIRE( list1.remove(50) == 745 );
        REQUIRE( list1.remove(1) == 990 );
        REQUIRE( list1.remove(1) == 985 );
        // Add a case for when it's empty.
    }
    SECTION ( "Test insert", "[insert]" ) {
        for (int i = 0; i < 200; i++) {
            list1.push_front(i * 5);
        }
        list1.insert( 3, 0 );
        list1.insert( 4, 1 );
        list1.insert( 5, 1 );
        REQUIRE( list1.pop_front() == 3 ); 
        REQUIRE( list1.pop_front() == 5 );
        REQUIRE( list1.pop_front() == 4 );
    }
    SECTION ( "Test clear", "[clear]" ) {
        list1.push_back(3);
        list1.push_back(1);
        list1.push_back(5);
        REQUIRE( list1.size() == 3 );
        list1.clear();
        REQUIRE( list1.size() == 0 );
    }
}

// Next we'll test the PSLL.
TEST_CASE ( "PSLL tests are done now!", "[PSLL]" ) {
    cop3530::PSLL<int> list1;
    SECTION ( "Test pop_front.", "[pop_front]" ) { 
        list1.push_back(1);
        REQUIRE( list1.pop_front() == 1 );
        // Add a case for when it's empty.
    }
    SECTION ( "Test pop_back.", "[pop_back]" ) {
        list1.push_back(3);
        list1.push_back(5);
        REQUIRE( list1.pop_back() == 5 );
        REQUIRE( list1.pop_back() == 3 );
        // Add a case for when it's empty.
    }
    SECTION ( "Test item_at.", "[item_at]" ) {
         for (int i = 0; i < 200; i++) {
            list1.push_back(i * 5);
        }
        REQUIRE(list1.item_at(199) == 995);
        REQUIRE(list1.item_at(198) == 990);
        REQUIRE(list1.item_at(150) == 750);
        REQUIRE(list1.item_at(42) == 210);
        REQUIRE(list1.item_at(0) == 0);
    }
    SECTION ( "Test remove", "[remove]" ) {
        list1.push_back(3);
        list1.push_back(1);
        list1.push_back(5);
        REQUIRE( list1.remove(1) == 1 );
        REQUIRE( list1.remove(1) == 5 );
        // Add a case for when it's empty.
    }
    SECTION ( "Test insert", "[insert]" ) {
        list1.insert( 3, 0 );
        list1.insert( 4, 1 );
        list1.insert( 5, 1 );
        REQUIRE( list1.pop_front() == 3 ); 
        REQUIRE( list1.pop_front() == 5 );
        REQUIRE( list1.pop_front() == 4 );
    }
    SECTION ( "Test clear", "[clear]" ) {
        list1.push_back(3);
        list1.push_back(1);
        list1.push_back(5);
        REQUIRE( list1.size() == 3 );
        list1.clear();
        REQUIRE( list1.size() == 0 );
    }
}

// And then we'll test the SDAL.
TEST_CASE ( "SDAL tests are done now!", "[SDAL]" ) {
    cop3530::SDAL<int> list1;
    SECTION ( "Test pop_front.", "[pop_front]" ) { 
        list1.push_back(1);
        REQUIRE( list1.pop_front() == 1 );
        // Add a case for when it's empty.
    }
    SECTION ( "Test pop_back.", "[pop_back]" ) {
        list1.push_back(3);
        list1.push_back(5);
        REQUIRE( list1.pop_back() == 5 );
        REQUIRE( list1.pop_back() == 3 );
        // Add a case for when it's empty.
    }
    SECTION ( "Test item_at.", "[item_at]" ) {
        list1.push_back(3);
        list1.push_back(1);
        list1.push_back(5);
        REQUIRE( list1.item_at(2) == 5 );
        REQUIRE( list1.item_at(1) == 1 );
        REQUIRE( list1.item_at(2) == 5 );
    }
    SECTION ( "Test remove", "[remove]" ) {
        list1.push_back(3);
        list1.push_back(1);
        list1.push_back(55);
        REQUIRE( list1.remove(1) == 1 );
        REQUIRE( list1.remove(1) == 5 );
        // Add a case for when it's empty.
    }
    SECTION ( "Test insert", "[insert]" ) {
        list1.insert( 3, 0 );
        list1.insert( 4, 1 );
        list1.insert( 5, 1 );
        REQUIRE( list1.pop_front() == 3 ); 
        REQUIRE( list1.pop_front() == 5 );
        REQUIRE( list1.pop_front() == 4 );
    }
    SECTION ( "Test clear", "[clear]" ) {
        list1.push_back(3);
        list1.push_back(1);
        list1.push_back(5);
        REQUIRE( list1.size() == 3 );
        list1.clear();
        REQUIRE( list1.size() == 0 );
    }
}

// And then we'll test the CDAL.
TEST_CASE ( "CDAL tests are done now!", "[CDAL]" ) {
    cop3530::CDAL<int> list1;
    SECTION ( "Test pop_front.", "[pop_front]" ) { 
        list1.push_back(1);
        REQUIRE( list1.pop_front() == 1 );
        // Add a case for when it's empty.
    }
    SECTION ( "Test pop_back.", "[pop_back]" ) {
        list1.push_back(3);
        list1.push_back(5);
        REQUIRE( list1.pop_back() == 5 );
        REQUIRE( list1.pop_back() == 3 );
        // Add a case for when it's empty.
    }
    SECTION ( "Test item_at.", "[item_at]" ) {
        for (int i = 0; i < 200; i++) {
            list1.push_back(i * 5);
        }
        REQUIRE(list1.item_at(199) == 995);
        REQUIRE(list1.item_at(198) == 990);
        REQUIRE(list1.item_at(150) == 750);
        REQUIRE(list1.item_at(42) == 210);
        REQUIRE(list1.item_at(0) == 0);
    }
    SECTION ( "Test remove", "[remove]" ) {
        list1.push_back(3);
        list1.push_back(1);
        list1.push_back(5);
        REQUIRE( list1.remove(1) == 1 );
        REQUIRE( list1.remove(1) == 5 );
        // Add a case for when it's empty.
    }
    SECTION ( "Test insert", "[insert]" ) {
        list1.insert( 3, 0 );
        list1.insert( 4, 1 );
        list1.insert( 5, 1 );
        REQUIRE( list1.pop_front() == 3 ); 
        REQUIRE( list1.pop_front() == 5 );
        REQUIRE( list1.pop_front() == 4 );
    }
    SECTION ( "Test clear", "[clear]" ) {
        list1.push_back(3);
        list1.push_back(1);
        list1.push_back(5);
        REQUIRE( list1.size() == 3 );
        list1.clear();
        REQUIRE( list1.size() == 0 );
    }
}
