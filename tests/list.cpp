#include <list>
#include "common.hpp"

auto const LIST_BEGIN = "[";
auto const LIST_END = "]";
auto const LIST_NAME = "lst";

TEST_CASE("list_numbers", "[list_numbers]")
{
    using namespace stlprint;
    std::list<int> l_int{ 1, 2, 3, 4, 5 };
    std::list<float> l_float{ 1.1f, 2.2f, 3.3f, 4.4f, 5.5f };
    std::stringstream ss1;
    std::stringstream ss2;

    ss1 << l_int;
    ss2 << LIST_NAME << l_int.size() << LIST_BEGIN << "1, 2, 3, 4, 5" << LIST_END;
    REQUIRE(ss1.str() == ss2.str());

    ss1.str(std::string());
    ss2.str(std::string());
    ss1 << l_float;
    ss2 << LIST_NAME << l_float.size() << LIST_BEGIN << "1.1, 2.2, 3.3, 4.4, 5.5" << LIST_END;
    REQUIRE(ss1.str() == ss2.str());
}

TEST_CASE("list_string", "[list_string]")
{
    using namespace stlprint;
    std::list<std::string> l_str{ "one", "two", "three", "four" };
    std::stringstream ss1;
    std::stringstream ss2;

    ss1 << l_str;
    ss2 << LIST_NAME << l_str.size() << LIST_BEGIN << "\"one\", \"two\", \"three\", \"four\"" << LIST_END;
    REQUIRE(ss1.str() == ss2.str());
}

TEST_CASE("list_char", "[list_char]")
{
    using namespace stlprint;
    std::list<char> l_char{ 'a', 'b', 'c', 'd' };
    std::stringstream ss1;
    std::stringstream ss2;

    ss1 << l_char;
    ss2 << LIST_NAME << l_char.size() << LIST_BEGIN << "\'a\', \'b\', \'c\', \'d\'" << LIST_END;
    REQUIRE(ss1.str() == ss2.str());
}
