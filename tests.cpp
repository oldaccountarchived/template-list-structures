#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "SSLL.cpp"

TEST_CASE ( "SSLL tests are done now!", "[SSLL]" ) {
    SSLL<int> list1;
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
