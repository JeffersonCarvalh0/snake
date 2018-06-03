# include "sqrt.h"
# include "catch.hpp"

SCENARIO("Testing the squareRoot function") {
    GIVEN("Some positive numbers") {
        REQUIRE(squareRoot(36.0) == 6);
        REQUIRE(squareRoot(324.0) == 18.0);
        REQUIRE(squareRoot(645.16) == 25.4);
        REQUIRE(squareRoot(0.0) == 0);
    }

    GIVEN("Some negativive numbers") {
        REQUIRE(squareRoot(-15.0) == -1.0);
        REQUIRE(squareRoot(-0.2) == -1.0);
    }
}
