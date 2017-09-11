#include <set>
#include "common.hpp"

auto const SET_BEGIN = "(";
auto const SET_END = ")";
auto const SET_NAME = "set";

TEST_CASE("set_numbers", "[set_numbers]")
{
    using namespace stringify;
    std::set<int> s_int{ 1, 2, 3, 4, 5 };
    std::set<float> s_float{ 1.1f, 2.2f, 3.3f, 4.4f, 5.5f };
    std::set<int> s_dup_int{ 1, 1, 1, 2, 3, 3, 4, 5, 0, 0 };
    std::stringstream ss1;
    std::stringstream ss2;

    ss1 << s_int;
    ss2 << SET_NAME << s_int.size() << SET_BEGIN << "1, 2, 3, 4, 5" << SET_END;
    REQUIRE(ss1.str() == ss2.str());

    ss1.str(std::string());
    ss2.str(std::string());
    ss1 << s_dup_int;
    ss2 << SET_NAME << s_dup_int.size() << SET_BEGIN << "0, 1, 2, 3, 4, 5" << SET_END;
    REQUIRE(ss1.str() == ss2.str());

    ss1.str(std::string());
    ss2.str(std::string());
    ss1 << s_float;
    ss2 << SET_NAME << s_int.size() << SET_BEGIN << "1.1, 2.2, 3.3, 4.4, 5.5" << SET_END;
    REQUIRE(ss1.str() == ss2.str());
}

TEST_CASE("set_string", "[set_string]")
{
    using namespace stringify;
    std::set<std::string> s_str{ "one", "two", "three", "four" };
    std::stringstream ss1;
    std::stringstream ss2;

    ss1 << s_str;
    ss2 << SET_NAME << s_str.size() << SET_BEGIN << "\"four\", \"one\", \"three\", \"two\"" << SET_END;
    REQUIRE(ss1.str() == ss2.str()); // sorted
}

TEST_CASE("set_char", "[set_char]")
{
    using namespace stringify;
    std::set<char> s_char{ 'a', 'b', 'c', 'd' };
    std::stringstream ss1;
    std::stringstream ss2;

    ss1 << s_char;
    ss2 << SET_NAME << s_char.size() << SET_BEGIN << "\'a\', \'b\', \'c\', \'d\'" << SET_END;
    REQUIRE(ss1.str() == ss2.str());
}
