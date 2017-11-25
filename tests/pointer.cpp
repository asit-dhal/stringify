#include "common.hpp"

auto const POINTER_BEGIN = "->";
auto const POINTER_NAME = "ptr";
auto const CPOINTER_NAME = "c_ptr";

TEST_CASE("pointer_numbers", "[pointer_numbers]")
{
    using namespace stringify;
    int *p1 = new int; *p1 = 20;
    float *p2 = new float; *p2 = 20.1f;
    const int *p3 = new int(3);
    
    std::stringstream ss1;
    std::stringstream ss2;

    ss1 << p1;
    ss2 << POINTER_NAME << POINTER_BEGIN << "20";
    REQUIRE(ss1.str() == ss2.str());

    ss1.str(std::string());
    ss2.str(std::string());
    ss1 << p2;
    ss2 << POINTER_NAME << POINTER_BEGIN << "20.1";
    REQUIRE(ss1.str() == ss2.str());

    ss1.str(std::string());
    ss2.str(std::string());
    ss1 << p3;
    ss2 << CPOINTER_NAME << POINTER_BEGIN << "3";
    REQUIRE(ss1.str() == ss2.str());
}
