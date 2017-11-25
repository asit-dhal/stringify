#include <utility>
#include "common.hpp"

auto const TUPLE_BEGIN = "(";
auto const TUPLE_END = ")";

TEST_CASE("tuple", "[tuple]")
{
    using namespace stringify;
    auto p1 = std::make_tuple(1, 2, 3.4, 'a');
    auto p2 = std::make_tuple("test", 2, std::string("abc"));
    auto p3 = std::make_tuple(std::string("test"), 2.9);
    std::stringstream ss1;
    std::stringstream ss2;

    ss1 << p1;
    ss2 << TUPLE_BEGIN << "1, 2, 3.4, \'a\'" << TUPLE_END;
    REQUIRE(ss1.str() == ss2.str());

    ss1.str(std::string());
    ss2.str(std::string());
    ss1 << p2;
    ss2 << TUPLE_BEGIN << "\"test\", 2, \"abc\"" << TUPLE_END;
    REQUIRE(ss1.str() == ss2.str());

    ss1.str(std::string());
    ss2.str(std::string());
    ss1 << p3;
    ss2 << TUPLE_BEGIN << "\"test\", 2.9" << TUPLE_END;
    REQUIRE(ss1.str() == ss2.str());
}
