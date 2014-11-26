#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "SSLL.cpp"
#include "PSLL.cpp"
#include "SDAL.cpp"
#include "CDAL.cpp"
#include <string>

// First test the SSLL.
TEST_CASE ( "SSLL tests are done now!", "[SSLL]" ) {
    cop3530::SSLL<int> list1;
    SECTION ( "Test exception handling", "[exceptions]" ) {
        try {
            list1.pop_back();
        } catch (std::out_of_range e) {
            REQUIRE ( std::string(e.what()) == std::string("List is empty") );
        }
        try {
            list1.pop_front();
        } catch (std::out_of_range e) {
            REQUIRE ( std::string(e.what()) == std::string("List is empty") );
        }
        try {
            list1.item_at(1);
        } catch (std::domain_error e) {
            REQUIRE ( std::string(e.what()) == std::string("Position does not exist") );
        }
        try {
            list1.insert(56, -2);
        } catch (std::domain_error e) {
            REQUIRE ( std::string(e.what()) == std::string("Position does not exist") );
        }
        try {
            list1.remove(1);
        } catch (std::domain_error e) {
            REQUIRE ( std::string(e.what()) == std::string("Position does not exist") );
        }
        try {
            list1[-2];
        } catch (std::domain_error e) {
            REQUIRE ( std::string(e.what()) == std::string("Position does not exist") );
        }
    }
    SECTION ( "Test iterators", "[SSLL_Iter]" ) {
        for (int i = 0; i < 200; i++) {
            list1.push_back(i * 5);
        }
        const cop3530::SSLL<int> listConst(list1);
        cop3530::SSLL<int>::SSLL_Iter listiter = list1.begin();
        cop3530::SSLL<int>::SSLL_Const_Iter listiter2 = listConst.begin();
        listiter++;
        listiter2++;
        REQUIRE( *listiter == 5 );
        REQUIRE( *listiter2 == 5 );
        ++listiter;
        ++listiter2;
        REQUIRE( *listiter == 10 );
        REQUIRE( *listiter2 == 10 );

        listiter = list1.begin();
        listiter2 = listConst.begin();

        int counter = 0;
        while (listiter != list1.end()) {
            ++counter;
            ++listiter;
        }
        REQUIRE( counter == 200 );

        counter = 0;
        while (listiter2 != listConst.end()) {
            ++counter;
            ++listiter2;
        }
        REQUIRE( counter == 200 );
    }
    SECTION ( "Test pop_front.", "[pop_front]" ) { 
        for (int i = 0; i < 200; i++) {
            list1.push_back(i * 5);
        }
        cop3530::SSLL<int>::SSLL_Iter listiter = list1.begin();
        REQUIRE(list1.pop_front() == 0);
        REQUIRE(list1.pop_front() ==  5);
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
        cop3530::SSLL<int> list2(list1);
        REQUIRE(list2.pop_back() == 995);
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
        list1.insert( 42, 49 );
        REQUIRE( list1.pop_front() == 3 ); 
        REQUIRE( list1.pop_front() == 5 );
        REQUIRE( list1.pop_front() == 4 );
        REQUIRE( list1.remove(46) == 42 );
    }
    SECTION ( "Test Printing", "[print]" ) {
        for (int i = 0; i < 200; i++) {
            list1.push_back(i * 5);
        }
        std::cout << "Testing Printing..." << std::endl;
        list1.print( std::cout );
        std::cout << std::endl;
    }
    SECTION ( "Test []", "[[]]" ) { 
        for (int i = 0; i < 200; i++) {
            list1.push_back(i * 5);
        }
        REQUIRE( list1[2] == 10 );
        REQUIRE( list1[3] == 15 );
        REQUIRE( list1[5] == 25 );
    }
    SECTION ( "Test clear", "[clear]" ) {
        for (int i = 0; i < 200; i++) {
            list1.push_front(i * 5);
        }
        REQUIRE( list1.size() == 200 );
        list1.clear();
        REQUIRE( list1.size() == 0 );
        REQUIRE( list1.is_empty() == true );
    }
}

// Next we'll test the PSLL.
TEST_CASE ( "PSLL tests are done now!", "[PSLL]" ) {
    cop3530::PSLL<int> list1;
    SECTION ( "Test exception handling", "[exceptions]" ) {
        try {
            list1.pop_back();
        } catch (std::out_of_range e) {
            REQUIRE ( std::string(e.what()) == std::string("List is empty") );
        }
        try {
            list1.pop_front();
        } catch (std::out_of_range e) {
            REQUIRE ( std::string(e.what()) == std::string("List is empty") );
        }
        try {
            list1.item_at(1);
        } catch (std::domain_error e) {
            REQUIRE ( std::string(e.what()) == std::string("Position does not exist") );
        }
        try {
            list1.insert(56, -2);
        } catch (std::domain_error e) {
            REQUIRE ( std::string(e.what()) == std::string("Position does not exist") );
        }
        try {
            list1.remove(1);
        } catch (std::domain_error e) {
            REQUIRE ( std::string(e.what()) == std::string("Position does not exist") );
        }
        try {
            list1[-2];
        } catch (std::domain_error e) {
            REQUIRE ( std::string(e.what()) == std::string("Position does not exist") );
        }
    }
    SECTION ( "Test iterators", "[PSLL_Iter]" ) {
        for (int i = 0; i < 200; i++) {
            list1.push_back(i * 5);
        }
        const cop3530::PSLL<int> listConst(list1);
        cop3530::PSLL<int>::PSLL_Iter listiter = list1.begin();
        cop3530::PSLL<int>::PSLL_Const_Iter listiter2 = listConst.begin();
        listiter++;
        listiter2++;
        REQUIRE( *listiter == 5 );
        REQUIRE( *listiter2 == 5 );
        ++listiter;
        ++listiter2;
        REQUIRE( *listiter == 10 );
        REQUIRE( *listiter2 == 10 );

        listiter = list1.begin();
        listiter2 = listConst.begin();

        int counter = 0;
        while (listiter != list1.end()) {
            ++counter;
            ++listiter;
        }
        REQUIRE( counter == 200 );

        counter = 0;
        while (listiter2 != listConst.end()) {
            ++counter;
            ++listiter2;
        }
        REQUIRE( counter == 200 );
    }
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
        cop3530::PSLL<int> list2(list1);
        REQUIRE(list2.pop_back() == 995);
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
        list1.insert( 42, 49 );
        REQUIRE( list1.pop_front() == 3 ); 
        REQUIRE( list1.pop_front() == 5 );
        REQUIRE( list1.pop_front() == 4 );
        REQUIRE( list1.remove(46) == 42 );
    }
    SECTION ( "Test Printing", "[print]" ) {
        for (int i = 0; i < 200; i++) {
            list1.push_back(i * 5);
        }
        std::cout << "Testing Printing..." << std::endl;
        list1.print( std::cout );
        std::cout << std::endl;
    }
    SECTION ( "Test []", "[[]]" ) { 
        for (int i = 0; i < 200; i++) {
            list1.push_back(i * 5);
        }
        REQUIRE( list1[2] == 10 );
        REQUIRE( list1[3] == 15 );
        REQUIRE( list1[5] == 25 );
    }
    SECTION ( "Test clear", "[clear]" ) {
        for (int i = 0; i < 200; i++) {
            list1.push_front(i * 5);
        }
        REQUIRE( list1.size() == 200 );
        list1.clear();
        REQUIRE( list1.size() == 0 );
        REQUIRE( list1.is_empty() == true );
    }
}

TEST_CASE ( "SDAL tests are done now!", "[SDAL]" ) {
    cop3530::SDAL<int> list1;
    SECTION ( "Test exception handling", "[exceptions]" ) {
        try {
            list1.pop_back();
        } catch (std::out_of_range e) {
            REQUIRE ( std::string(e.what()) == std::string("List is empty") );
        }
        try {
            list1.pop_front();
        } catch (std::out_of_range e) {
            REQUIRE ( std::string(e.what()) == std::string("List is empty") );
        }
        try {
            list1.item_at(1);
        } catch (std::domain_error e) {
            REQUIRE ( std::string(e.what()) == std::string("Position does not exist") );
        }
        try {
            list1.insert(56, -2);
        } catch (std::domain_error e) {
            REQUIRE ( std::string(e.what()) == std::string("Position does not exist") );
        }
        try {
            list1.remove(1);
        } catch (std::domain_error e) {
            REQUIRE ( std::string(e.what()) == std::string("Position does not exist") );
        }
        try {
            list1[-2];
        } catch (std::domain_error e) {
            REQUIRE ( std::string(e.what()) == std::string("Position does not exist") );
        }
    }
    SECTION ( "Test iterators", "[SDAL_Iter]" ) {
        for (int i = 0; i < 200; i++) {
            list1.push_back(i * 5);
        }
        const cop3530::SDAL<int> listConst(list1);
        cop3530::SDAL<int>::SDAL_Iter listiter = list1.begin();
        cop3530::SDAL<int>::SDAL_Const_Iter listiter2 = listConst.begin();

        listiter++;
        listiter2++;
        REQUIRE( *listiter == 5 );
        REQUIRE( *listiter2 == 5 );
        ++listiter;
        ++listiter2;
        REQUIRE( *listiter == 10 );
        REQUIRE( *listiter2 == 10 );

        listiter = list1.begin();
        listiter2 = listConst.begin();

        int counter = 0;
        while (listiter != list1.end()) {
            ++counter;
            ++listiter;
        }
        REQUIRE( counter == 200 );

        counter = 0;
        while (listiter2 != listConst.end()) {
            ++counter;
            ++listiter2;
        }
        REQUIRE( counter == 200 );
    }
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
        list1.insert( 42, 49 );
        REQUIRE( list1.pop_front() == 3 ); 
        REQUIRE( list1.pop_front() == 5 );
        REQUIRE( list1.pop_front() == 4 );
        REQUIRE( list1.remove(46) == 42 );
    }
    SECTION ( "Test Printing", "[print]" ) {
        for (int i = 0; i < 200; i++) {
            list1.push_back(i * 5);
        }
        std::cout << "Testing Printing..." << std::endl;
        list1.print( std::cout );
        std::cout << std::endl;
    }
    SECTION ( "Test []", "[[]]" ) { 
        for (int i = 0; i < 200; i++) {
            list1.push_back(i * 5);
        }
        REQUIRE( list1[2] == 10 );
        REQUIRE( list1[3] == 15 );
        REQUIRE( list1[5] == 25 );
    }
    SECTION ( "Test clear", "[clear]" ) {
        for (int i = 0; i < 200; i++) {
            list1.push_front(i * 5);
        }
        REQUIRE( list1.size() == 200 );
        list1.clear();
        REQUIRE( list1.size() == 0 );
        REQUIRE( list1.is_empty() == true);
    }
}

// And then we'll test the CDAL.
TEST_CASE ( "CDAL tests are done now!", "[CDAL]" ) {
    cop3530::CDAL<int> list1;
    // SECTION ( "Test iterators", "[SDAL_Iter]" ) {
    //     for (int i = 0; i < 200; i++) {
    //         list1.push_back(i * 5);
    //     }
    //     const cop3530::CDAL<int> listConst(list1);
    //     cop3530::CDAL<int>::CDAL_Iter listiter = list1.begin();
    //     cop3530::CDAL<int>::CDAL_Const_Iter listiter2 = listConst.begin();

    //     listiter++;
    //     listiter2++;
    //     REQUIRE( *listiter == 5 );
    //     REQUIRE( *listiter2 == 5 );
    //     ++listiter;
    //     ++listiter2;
    //     REQUIRE( *listiter == 10 );
    //     REQUIRE( *listiter2 == 10 );

    //     listiter = list1.begin();
    //     listiter2 = listConst.begin();

    //     int counter = 0;
    //     while (listiter != list1.end()) {
    //         ++counter;
    //         ++listiter;
    //     }
    //     REQUIRE( counter == 200 );

    //     counter = 0;
    //     while (listiter2 != listConst.end()) {
    //         ++counter;
    //         ++listiter2;
    //     }
    //     REQUIRE( counter == 200 );
    // }
    SECTION ( "Test exception handling", "[exceptions]" ) {
        try {
            list1.pop_back();
        } catch (std::out_of_range e) {
            REQUIRE ( std::string(e.what()) == std::string("List is empty") );
        }
        try {
            list1.pop_front();
        } catch (std::out_of_range e) {
            REQUIRE ( std::string(e.what()) == std::string("List is empty") );
        }
        try {
            list1.item_at(1);
        } catch (std::domain_error e) {
            REQUIRE ( std::string(e.what()) == std::string("Position does not exist") );
        }
        try {
            list1.insert(56, -2);
        } catch (std::domain_error e) {
            REQUIRE ( std::string(e.what()) == std::string("Position does not exist") );
        }
        try {
            list1.remove(1);
        } catch (std::domain_error e) {
            REQUIRE ( std::string(e.what()) == std::string("Position does not exist") );
        }
        try {
            list1[-2];
        } catch (std::domain_error e) {
            REQUIRE ( std::string(e.what()) == std::string("Position does not exist") );
        }
    }
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
        list1.insert( 42, 49 );
        list1.insert( 943, 77 );
        list1.insert( 222, 99 );
        
        REQUIRE( list1.pop_front() == 3 ); 
        REQUIRE( list1.pop_front() == 5 );
        REQUIRE( list1.pop_front() == 4 );
        REQUIRE( list1.remove(46) == 42 );
        REQUIRE( list1.remove(73) == 943 );
        REQUIRE( list1.remove(94) == 222 );
    }
    SECTION ( "Test Printing", "[print]" ) {
        for (int i = 0; i < 200; i++) {
            list1.push_back(i * 5);
        }
        std::cout << "Testing Printing..." << std::endl;
        list1.print( std::cout );
        std::cout << std::endl;
    }
    SECTION ( "Test []", "[[]]" ) { 
        for (int i = 0; i < 200; i++) {
            list1.push_back(i * 5);
        }
        REQUIRE( list1[2] == 10 );
        REQUIRE( list1[3] == 15 );
        REQUIRE( list1[5] == 25 );
    }
    SECTION ( "Test clear", "[clear]" ) {
        for (int i = 0; i < 200; i++) {
            list1.push_front(i * 5);
        }
        REQUIRE( list1.size() == 200 );
        list1.clear();
        REQUIRE( list1.size() == 0 );
        REQUIRE( list1.is_empty() == true );
    }
}
