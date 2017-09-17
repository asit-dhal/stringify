#include <array>
#include "common.hpp"

auto const ARRAY_BEGIN = "[";
auto const ARRAY_END = "]";
auto const ARRAY_NAME = "arr";

TEST_CASE("array_numbers", "[array_numbers]")
{
    using namespace stringify;
    std::array<int, 5> arr_int = { 1, 2, 3, 4, 5 };
    std::array<float, 5> arr_float = { 1.1f, 2.2f, 3.3f, 4.4f, 5.5f };
    std::stringstream ss1;
    std::stringstream ss2;

    ss1 << arr_int;
    ss2 << ARRAY_NAME << 5 << ARRAY_BEGIN << "1, 2, 3, 4, 5" << ARRAY_END;
    REQUIRE(ss1.str() == ss2.str());

    ss1.str(std::string());
    ss2.str(std::string());
    ss1 << arr_float;
    ss2 << ARRAY_NAME << 5 << ARRAY_BEGIN << "1.1, 2.2, 3.3, 4.4, 5.5" << ARRAY_END;
    REQUIRE(ss1.str() == ss2.str());
}

TEST_CASE("array_string", "[array_string]")
{
    using namespace stringify;
    std::array<std::string, 4> carray_str = { "one", "two", "three", "four" };
    std::stringstream ss1;
    std::stringstream ss2;

    ss1 << carray_str;
    ss2 << ARRAY_NAME << 4 << ARRAY_BEGIN << "\"one\", \"two\", \"three\", \"four\"" << ARRAY_END;
    REQUIRE(ss1.str() == ss2.str());
}

TEST_CASE("array_char", "[array_char]")
{
    using namespace stringify;
    std::array<char, 4> array_char = { 'a', 'b', 'c', 'd'};
    std::stringstream ss1;
    std::stringstream ss2;
    ss1 << array_char;
    ss2 << ARRAY_NAME << 4 << ARRAY_BEGIN << "\'a\', \'b\', \'c\', \'d\'" << ARRAY_END;
    REQUIRE(ss1.str() == ss2.str());
}
