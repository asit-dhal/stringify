#include <forward_list>
#include "common.hpp"

auto const FL_BEGIN = "[";
auto const FL_END = "]";
auto const FL_NAME = "flst";

TEST_CASE("fl_numbers", "[fl_numbers]")
{
    using namespace stringify;
    std::forward_list<int> fl_int{ 1, 2, 3, 4, 5 };
    std::forward_list<float> fl_float{ 1.1f, 2.2f, 3.3f, 4.4f, 5.5f };
    std::forward_list<int> fl_dup_int{ 1, 1, 1, 2, 3, 3, 4, 5, 0, 0 };
    std::stringstream ss1;
    std::stringstream ss2;

    ss1 << fl_int;
    ss2 << FL_NAME << FL_BEGIN << "1, 2, 3, 4, 5" << FL_END;
    REQUIRE(ss1.str() == ss2.str());

    ss1.str(std::string());
    ss2.str(std::string());
    ss1 << fl_float;
    ss2 << FL_NAME << FL_BEGIN << "1.1, 2.2, 3.3, 4.4, 5.5" << FL_END;
    REQUIRE(ss1.str() == ss2.str());

    ss1.str(std::string());
    ss2.str(std::string());
    ss1 << fl_dup_int;
    ss2 << FL_NAME << FL_BEGIN << "1, 1, 1, 2, 3, 3, 4, 5, 0, 0" << FL_END;
    REQUIRE(ss1.str() == ss2.str());
}

TEST_CASE("fl_string", "[fl_string]")
{
    using namespace stringify;
    std::forward_list<std::string> fl_str{ "one", "two", "three", "four" };
    std::forward_list<char*> fl_cstr{ "cone", "ctwo", "cthree", "cfour" };
    std::stringstream ss1;
    std::stringstream ss2;

    ss1 << fl_str;
    ss2 << FL_NAME << FL_BEGIN << "\"one\", \"two\", \"three\", \"four\"" << FL_END;
    REQUIRE(ss1.str() == ss2.str());

    ss1.str(std::string());
    ss2.str(std::string());
    ss1 << fl_cstr;
    ss2 << FL_NAME << FL_BEGIN << "\"cone\", \"ctwo\", \"cthree\", \"cfour\"" << FL_END;
    REQUIRE(ss1.str() == ss2.str());
}
