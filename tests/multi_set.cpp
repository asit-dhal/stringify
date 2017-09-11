#include <set>
#include "common.hpp"

auto const MSET_BEGIN = "(";
auto const MSET_END = ")";
auto const MSET_NAME = "mset";


TEST_CASE("multiset_numbers", "[multiset_numbers]")
{
    using namespace stringify;
    std::multiset<float> ms_float{ 1.1f, 1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 5.5f };
    std::multiset<int> ms_int{ 1, 1, 1, 2, 3, 3, 4, 5, 0, 0 };
    std::stringstream ss1;
    std::stringstream ss2;

    ss1 << ms_int;
    ss2 << MSET_NAME << ms_int.size() << MSET_BEGIN << "0, 0, 1, 1, 1, 2, 3, 3, 4, 5" << MSET_END;
    REQUIRE(ss1.str() == ss2.str());

    ss1.str(std::string());
    ss2.str(std::string());
    ss1 << ms_float;
    ss2 << MSET_NAME << ms_float.size() << MSET_BEGIN << "1.1, 1.1, 2.2, 3.3, 4.4, 5.5, 5.5" << MSET_END;
    REQUIRE(ss1.str() == ss2.str());
}

TEST_CASE("multiset_string", "[multiset_string]")
{
    using namespace stringify;
    std::multiset<std::string> ms_str{ "one", "two", "three", "four", "three", "two" };
    std::stringstream ss1;
    std::stringstream ss2;

    ss1 << ms_str;
    ss2 << MSET_NAME << ms_str.size() << MSET_BEGIN << "\"four\", \"one\", \"three\", \"three\", \"two\", \"two\"" << MSET_END;
    REQUIRE(ss1.str() == ss2.str()); // sorted
}

TEST_CASE("multiset_char", "[multiset_char]")
{
    using namespace stringify;
    std::multiset<char> ms_char{ 'a', 'b', 'c', 'd', 'a', 'b', 'c', 'd', 'a', 'b', 'c', 'd' };
    std::stringstream ss1;
    std::stringstream ss2;

    ss1 << ms_char;
    ss2 << MSET_NAME << ms_char.size() << MSET_BEGIN << "\'a\', \'a\', \'a\', \'b\', \'b\', \'b\', \'c\', \'c\', \'c\', \'d\', \'d\', \'d\'" << MSET_END;
    REQUIRE(ss1.str() == ss2.str());
}
