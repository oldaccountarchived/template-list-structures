#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "SSLL.cpp"

TEST_CASE ( "SSLL tests are done now!", "[SSLL]" ) {
    SSLL<int> list1;
    SECTION ( "Test pop_front.", "[pop_front]" ) { 
        list1.push_back(1);
        REQUIRE( list1.pop_front() == 1 );
    }
    SECTION ( "Test pop_back.", "[pop_back]" ) {
        list1.push_back(3);
        list1.push_back(5);
        REQUIRE( list1.pop_back() == 5 );
        REQUIRE( list1.pop_back() == 3 );
    }
    SECTION ( "Test item_at.", "[item_at]" ) {
        list1.push_back(3);
        list1.push_back(1);
        list1.push_back(5);
        REQUIRE( list1.item_at(3) == 5 );
        REQUIRE( list1.item_at(2) == 1 );
        REQUIRE( list1.item_at(3) == 5 );
    }
    SECTION ( "Test remove", "[remove]" ) {
        list1.push_back(3);
        list1.push_back(1);
        list1.push_back(5);
        REQUIRE( list1.remove(2) == 1 );
        REQUIRE( list1.remove(2) == 5 );
    }
} 
