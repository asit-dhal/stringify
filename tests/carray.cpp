#include "common.hpp"

auto const CARRAY_BEGIN = "[";
auto const CARRAY_END = "]";
auto const CARRAY_NAME = "carr";

TEST_CASE("carray_numbers", "[carray_numbers]")
{
    using namespace stringify;
    int arr_int[5] = { 1, 2, 3, 4, 5 };
    float arr_float[5] = { 1.1f, 2.2f, 3.3f, 4.4f, 5.5f };
    std::stringstream ss1;
    std::stringstream ss2;

    ss1 << arr_int;
    ss2 << CARRAY_BEGIN << "1, 2, 3, 4, 5" << CARRAY_END;
    REQUIRE(ss1.str() == ss2.str());

    ss1.str(std::string());
    ss2.str(std::string());
    ss1 << arr_float;
    ss2 << CARRAY_BEGIN << "1.1, 2.2, 3.3, 4.4, 5.5" << CARRAY_END;
    REQUIRE(ss1.str() == ss2.str());
}

TEST_CASE("carray_string", "[carray_string]")
{
    using namespace stringify;
    std::string carray_str[4] = { "one", "two", "three", "four" };
    std::stringstream ss1;
    std::stringstream ss2;

    ss1 << carray_str;
    ss2 << CARRAY_BEGIN << "\"one\", \"two\", \"three\", \"four\"" << CARRAY_END;
    REQUIRE(ss1.str() == ss2.str());
}

TEST_CASE("carray_char", "[carray_char]")
{
    using namespace stringify;
    char array_char[5] = { 'a', 'b', 'c', 'd', '\0' };
    std::stringstream ss;
    ss << array_char;
    REQUIRE(ss.str() == "abcd");
}
