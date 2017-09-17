#include <stack>
#include <deque>
#include "common.hpp"

auto const STACK_BEGIN = "[";
auto const STACK_END = "]";
auto const STACK_NAME = "st";


TEST_CASE("stack_numbers", "[stack_numbers]")
{
    using namespace stringify;
    std::deque<int> d_int{ 1, 2, 3, 4, 5 };
    std::deque<float> d_float{ 1.1f, 2.2f, 3.3f, 4.4f, 5.5f };
    std::stack<int> s_int(d_int);
    std::stack<float> s_float(d_float);
    std::stringstream ss1;
    std::stringstream ss2;

    ss1 << s_int;
    ss2 << STACK_NAME << d_int.size() << STACK_BEGIN << "1, 2, 3, 4, 5" << STACK_END;
    REQUIRE(ss1.str() == ss2.str());

    ss1.str(std::string());
    ss2.str(std::string());
    ss1 << s_float;
    ss2 << STACK_NAME << d_float.size() << STACK_BEGIN << "1.1, 2.2, 3.3, 4.4, 5.5" << STACK_END;
    REQUIRE(ss1.str() == ss2.str());
}

TEST_CASE("stack_string", "[stack_string]")
{
    using namespace stringify;
    std::deque<std::string> d_str{ "one", "two", "three", "four" };
    std::stack<std::string> s_str(d_str);
    std::stringstream ss1;
    std::stringstream ss2;
    ss1 << s_str;
    ss2 << STACK_NAME << s_str.size() << STACK_BEGIN << "\"one\", \"two\", \"three\", \"four\"" << STACK_END;
    REQUIRE(ss1.str() == ss2.str());
}

TEST_CASE("stack_char", "[stack_char]")
{
    using namespace stringify;
    std::deque<char> d_char{ 'a', 'b', 'c', 'd' };
    std::stack<char> s_char(d_char);
    std::stringstream ss1;
    std::stringstream ss2;

    ss1 << s_char;
    ss2 << STACK_NAME << s_char.size() << STACK_BEGIN << "\'a\', \'b\', \'c\', \'d\'" << STACK_END;
    REQUIRE(ss1.str() == ss2.str());
}
