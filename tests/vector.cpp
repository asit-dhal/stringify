#include <vector>
#include "common.hpp"

auto const VECTOR_BEGIN = "[";
auto const VECTOR_END = "]";
auto const VECTOR_NAME = "vec";

TEST_CASE("vector_numbers", "[vector_numbers]")
{
    using namespace stringify;
    std::vector<int> v_int{ 1, 2, 3, 4, 5 };
    std::vector<float> v_float{ 1.1f, 2.2f, 3.3f, 4.4f, 5.5f };
    std::stringstream ss1;
    std::stringstream ss2;

    ss1 << v_int;
    ss2 << VECTOR_NAME << v_int.size() << VECTOR_BEGIN << "1, 2, 3, 4, 5" << VECTOR_END;
    REQUIRE(ss1.str() == ss2.str());

    ss1.str(std::string());
    ss2.str(std::string());
    ss1 << v_float;
    ss2 << VECTOR_NAME << v_float.size() << VECTOR_BEGIN << "1.1, 2.2, 3.3, 4.4, 5.5" << VECTOR_END;
    REQUIRE(ss1.str() == ss2.str());
}

TEST_CASE("vector_string", "[vector_string]")
{
    using namespace stringify;
    std::vector<std::string> v_str{ "one", "two", "three", "four"};
    std::stringstream ss1;
    std::stringstream ss2;

    ss1 << v_str;
    ss2 << VECTOR_NAME << v_str.size() << VECTOR_BEGIN << "\"one\", \"two\", \"three\", \"four\"" << VECTOR_END;
    REQUIRE(ss1.str() == ss2.str());
}

TEST_CASE("vector_char", "[vector_char]")
{
    using namespace stringify;
    std::vector<char> v_char{ 'a', 'b', 'c', 'd' };
    std::stringstream ss1;
    std::stringstream ss2;

    ss1 << v_char;
    ss2 << VECTOR_NAME << v_char.size() << VECTOR_BEGIN << "\'a\', \'b\', \'c\', \'d\'" << VECTOR_END;
    REQUIRE(ss1.str() == ss2.str());
}
