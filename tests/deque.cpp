#include <deque>
#include "common.hpp"

auto const DEQUE_BEGIN = "[";
auto const DEQUE_END = "]";
auto const DEQUE_NAME = "deq";


TEST_CASE("deque_numbers", "[deque_numbers]")
{
    using namespace stlprint;
    std::deque<int> d_int{ 1, 2, 3, 4, 5 };
    std::deque<float> d_float{ 1.1f, 2.2f, 3.3f, 4.4f, 5.5f };
    std::stringstream ss1;
    std::stringstream ss2;

    ss1 << d_int;
    ss2 << DEQUE_NAME << d_int.size() << DEQUE_BEGIN << "1, 2, 3, 4, 5" << DEQUE_END;
    REQUIRE(ss1.str() == ss2.str());

    ss1.str(std::string());
    ss2.str(std::string());
    ss1 << d_float;
    ss2 << DEQUE_NAME << d_float.size() << DEQUE_BEGIN << "1.1, 2.2, 3.3, 4.4, 5.5" << DEQUE_END;
    REQUIRE(ss1.str() == ss2.str());
    std::stringstream ss;
}

TEST_CASE("deque_string", "[deque_string]")
{
    using namespace stlprint;
    std::deque<std::string> d_str{ "one", "two", "three", "four" };
    std::stringstream ss1;
    std::stringstream ss2;

    ss1 << d_str;
    ss2 << DEQUE_NAME << d_str.size() << DEQUE_BEGIN << "\"one\", \"two\", \"three\", \"four\"" << DEQUE_END;
    REQUIRE(ss1.str() == ss2.str());
}

TEST_CASE("deque_char", "[deque_char]")
{
    using namespace stlprint;
    std::deque<char> d_char{ 'a', 'b', 'c', 'd' };
    std::stringstream ss1;
    std::stringstream ss2;

    ss1 << d_char;
    ss2 << DEQUE_NAME << d_char.size() << DEQUE_BEGIN << "\'a\', \'b\', \'c\', \'d\'" << DEQUE_END;
    REQUIRE(ss1.str() == ss2.str());
}
