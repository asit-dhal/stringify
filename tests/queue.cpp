#include <queue>
#include <deque>
#include "common.hpp"

auto const QUEUE_BEGIN = "[";
auto const QUEUE_END = "]";


TEST_CASE("queue_numbers", "[queue_numbers]")
{
    using namespace stringify;
    std::deque<int> d_int{ 1, 2, 3, 4, 5 };
    std::deque<float> d_float{ 1.1f, 2.2f, 3.3f, 4.4f, 5.5f };
    std::queue<int> q_int(d_int);
    std::queue<float> q_float(d_float);
    std::stringstream ss1;
    std::stringstream ss2;

    ss1 << q_int;
    ss2 << QUEUE_BEGIN << "1, 2, 3, 4, 5" << QUEUE_END;
    REQUIRE(ss1.str() == ss2.str());

    ss1.str(std::string());
    ss2.str(std::string());
    ss1 << q_float;
    ss2 << QUEUE_BEGIN << "1.1, 2.2, 3.3, 4.4, 5.5" << QUEUE_END;
    REQUIRE(ss1.str() == ss2.str());
}

TEST_CASE("queue_string", "[queue_string]")
{
    using namespace stringify;
    std::deque<std::string> d_str{ "one", "two", "three", "four" };
    std::queue<std::string> q_str(d_str);
    std::stringstream ss1;
    std::stringstream ss2;
    ss1 << q_str;
    ss2 << QUEUE_BEGIN << "\"one\", \"two\", \"three\", \"four\"" << QUEUE_END;
    REQUIRE(ss1.str() == ss2.str());
}

TEST_CASE("queue_char", "[queue_char]")
{
    using namespace stringify;
    std::deque<char> d_char{ 'a', 'b', 'c', 'd' };
    std::queue<char> q_char(d_char);
    std::stringstream ss1;
    std::stringstream ss2;

    ss1 << q_char;
    ss2 << QUEUE_BEGIN << "\'a\', \'b\', \'c\', \'d\'" << QUEUE_END;
    REQUIRE(ss1.str() == ss2.str());
}
