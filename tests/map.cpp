#include <map>
#include "common.hpp"

auto const MAP_BEGIN = "(";
auto const MAP_END = ")";
auto const MAP_NAME = "mp";

//TEST_CASE("map_numbers", "[map_numbers]")
//{
//    using namespace stringify;
//    std::map<int, int> mp1;
//    mp1[1] = 10;
//    mp1[2] = 30;
//    mp1[3] = 50;
//    mp1[4] = 70;
//    std::map<double, int> mp2;
//    mp2[1.1] = 10;
//    mp2[2.3] = 30;
//    mp2[9.1] = 50;
//    mp2[2.7] = 70;
//
//    
//    std::stringstream ss1;
//    std::stringstream ss2;
//
//    ss1 << mp1;
//    ss2 << MAP_NAME << mp1.size() << MAP_BEGIN << "1, 2, 3, 4, 5" << MAP_END;
//    REQUIRE(ss1.str() == ss2.str());
//
//    ss1.str(std::string());
//    ss2.str(std::string());
//    ss1 << mp2;
//    ss2 << MAP_NAME << mp2.size() << MAP_BEGIN << "0, 1, 2, 3, 4, 5" << MAP_END;
//    REQUIRE(ss1.str() == ss2.str());
//}

//TEST_CASE("set_string", "[set_string]")
//{
//    using namespace stringify;
//    std::set<std::string> s_str{ "one", "two", "three", "four" };
//    std::stringstream ss1;
//    std::stringstream ss2;
//
//    ss1 << s_str;
//    ss2 << SET_NAME << s_str.size() << SET_BEGIN << "\"four\", \"one\", \"three\", \"two\"" << SET_END;
//    REQUIRE(ss1.str() == ss2.str()); // sorted
//}
//
//TEST_CASE("set_char", "[set_char]")
//{
//    using namespace stringify;
//    std::set<char> s_char{ 'a', 'b', 'c', 'd' };
//    std::stringstream ss1;
//    std::stringstream ss2;
//
//    ss1 << s_char;
//    ss2 << SET_NAME << s_char.size() << SET_BEGIN << "\'a\', \'b\', \'c\', \'d\'" << SET_END;
//    REQUIRE(ss1.str() == ss2.str());
//}
