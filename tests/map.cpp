#include <map>
#include "common.hpp"

auto const MAP_BEGIN = "{";
auto const MAP_END = "}";
auto const MAP_NAME = "map";

TEST_CASE("map_numbers", "[map_numbers]")
{
    using namespace stringify;
    std::map<int, int> mp1;
    mp1[1] = 10;
    mp1[2] = 30;
    mp1[3] = 50;
    mp1[4] = 70;
    std::map<double, int> mp2;
    mp2[1.1] = 10;
    mp2[2.3] = 30;
    mp2[9.1] = 50;
    mp2[2.7] = 70;

    
    std::stringstream ss1;
    std::stringstream ss2;

    ss1 << mp1;
	ss2 << MAP_NAME << mp1.size() << MAP_BEGIN << "1:10, 2:30, 3:50, 4:70" << MAP_END;
    REQUIRE(ss1.str() == ss2.str());

    ss1.str(std::string());
    ss2.str(std::string());
    ss1 << mp2;
    ss2 << MAP_NAME << mp2.size() << MAP_BEGIN << "1.1:10, 2.3:30, 2.7:70, 9.1:50" << MAP_END;
    REQUIRE(ss1.str() == ss2.str());
}

TEST_CASE("map_string", "[map_string]")
{
    using namespace stringify;
    std::map<char, std::string> mp_str1;
    mp_str1['1'] = "one";
    mp_str1['2'] = "two";
    mp_str1['3'] = "three";
    mp_str1['4'] = "four";

    std::stringstream ss1;
    std::stringstream ss2;

    ss1 << mp_str1;
    ss2 << MAP_NAME << mp_str1.size() << MAP_BEGIN << "\'1\':\"one\", \'2\':\"two\", \'3\':\"three\", \'4\':\"four\"" << MAP_END;
    REQUIRE(ss1.str() == ss2.str());
}

TEST_CASE("map_nested", "[map_nested]")
{
    return;
    using namespace stringify;
    std::map<char, std::map<int, std::string>> mp_str1;
    mp_str1['1'].insert(std::make_pair(1, "one"));
    mp_str1['1'].insert(std::make_pair(10, "ten"));
    mp_str1['2'].insert(std::make_pair(2, "two"));
    mp_str1['2'].insert(std::make_pair(20, "twenty"));
    mp_str1['3'].insert(std::make_pair(3, "three"));
    mp_str1['3'].insert(std::make_pair(30, "thirty"));
	mp_str1['3'].insert(std::make_pair(32, "thirty two"));
	mp_str1['3'].insert(std::make_pair(33, "thirty three"));
    mp_str1['4'].insert(std::make_pair(4, "four"));
    mp_str1['4'].insert(std::make_pair(40, "fourty"));

    std::stringstream ss1;
    std::stringstream ss2;

    ss1 << mp_str1;
	ss2 << MAP_NAME << mp_str1.size() << MAP_BEGIN
		<< "\'1\':" << MAP_NAME << mp_str1['1'].size() << MAP_BEGIN << "1:\"one\", 10:\"ten\"" << MAP_END
		<< ", \'2\':" << MAP_NAME << mp_str1['2'].size() << MAP_BEGIN << "2:\"two\", 20:\"twenty\"" << MAP_END
		<< ", \'3\':" << MAP_NAME << mp_str1['3'].size() << MAP_BEGIN << "3:\"three\", 30:\"thirty\", 32:\"thirty two\", 33:\"thirty three\"" << MAP_END
		<< ", \'4\':" << MAP_NAME << mp_str1['4'].size() << MAP_BEGIN << "4:\"four\", 40:\"fourty\"" << MAP_END
		<< MAP_END;
    REQUIRE(ss1.str() == ss2.str());
}
