#include <utility>
#include "common.hpp"

auto const PAIR_BEGIN = "(";
auto const PAIR_END = ")";
auto const PAIR_NAME = "pr";

TEST_CASE("pair", "[pair]")
{
    using namespace stringify;
    auto p1 = std::make_pair(1, 2.1f);
    auto p2 = std::make_pair('a', 2);
    auto p3 = std::make_pair("test", 2);
    auto p4 = std::make_pair(std::string("test"), 2.9);
    std::stringstream ss1;
    std::stringstream ss2;

    ss1 << p1;
    ss2 << PAIR_NAME << PAIR_BEGIN << "1, 2.1" << PAIR_END;
    REQUIRE(ss1.str() == ss2.str());

    ss1.str(std::string());
    ss2.str(std::string());
    ss1 << p2;
    ss2 << PAIR_NAME << PAIR_BEGIN << "\'a\', 2" << PAIR_END;
    REQUIRE(ss1.str() == ss2.str());

    ss1.str(std::string());
    ss2.str(std::string());
    ss1 << p3;
    ss2 << PAIR_NAME << PAIR_BEGIN << "\"test\", 2" << PAIR_END;
    REQUIRE(ss1.str() == ss2.str());

    ss1.str(std::string());
    ss2.str(std::string());
    ss1 << p4;
    ss2 << PAIR_NAME << PAIR_BEGIN << "\"test\", 2.9" << PAIR_END;
    REQUIRE(ss1.str() == ss2.str());
}
