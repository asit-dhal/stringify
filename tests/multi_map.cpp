#include <map>
#include <utility>
#include "common.hpp"

auto const MMAP_BEGIN = "{";
auto const MMAP_END = "}";

TEST_CASE("multimap_numbers", "[multimap_numbers]")
{
    using namespace stringify;
    std::multimap<int, int> mp1;
	mp1.insert(std::make_pair<int, int>(1, 10));
	mp1.insert(std::make_pair<int, int>(2, 30));
	mp1.insert(std::make_pair<int, int>(2, 300));
	mp1.insert(std::make_pair<int, int>(3, 50));
	mp1.insert(std::make_pair<int, int>(4, 70));
    
    std::multimap<double, int> mp2;
    mp2.insert(std::make_pair<double, int>(1.1, 10));
	mp2.insert(std::make_pair<double, int>(2.3, 30));
	mp2.insert(std::make_pair<double, int>(9.1, 50));
	mp2.insert(std::make_pair<double, int>(9.1, 90));
	mp2.insert(std::make_pair<double, int>(2.7, 70));
	mp2.insert(std::make_pair<double, int>(2.7, 210));
    
    std::stringstream ss1;
    std::stringstream ss2;

    ss1 << mp1;
    ss2 << MMAP_BEGIN << "1:10, 2:30, 2:300, 3:50, 4:70" << MMAP_END;
    REQUIRE(ss1.str() == ss2.str());

    ss1.str(std::string());
    ss2.str(std::string());
    ss1 << mp2;
    ss2 << MMAP_BEGIN << "1.1:10, 2.3:30, 2.7:70, 2.7:210, 9.1:50, 9.1:90" << MMAP_END;
    REQUIRE(ss1.str() == ss2.str());
}

TEST_CASE("multimap_string", "[multimap_string]")
{
    using namespace stringify;
    std::multimap<char, std::string> mp_str1;
	mp_str1.insert(std::pair<char, std::string>('1', "one"));
	mp_str1.insert(std::pair<char, std::string>('1', "ekk"));
	mp_str1.insert(std::pair<char, std::string>('2', "two"));
	mp_str1.insert(std::pair<char, std::string>('3', "three"));
	mp_str1.insert(std::pair<char, std::string>('4', "four"));

	std::multimap<char, const char*> mp_str2;
	mp_str2.insert(std::pair<char, const char*>('1', "one"));
	mp_str2.insert(std::pair<char, const char*>('1', "ekk"));
	mp_str2.insert(std::pair<char, const char*>('2', "two"));
	mp_str2.insert(std::pair<char, const char*>('3', "three"));
	mp_str2.insert(std::pair<char, const char*>('4', "four"));


    std::stringstream ss1;
    std::stringstream ss2;

    ss1 << mp_str1;
    ss2 << MMAP_BEGIN << "\'1\':\"one\", \'1\':\"ekk\", \'2\':\"two\", \'3\':\"three\", \'4\':\"four\"" << MMAP_END;
    REQUIRE(ss1.str() == ss2.str());

	ss1.str(std::string());
	ss2.str(std::string());

	ss1 << mp_str2;
    ss2 << MMAP_BEGIN << "\'1\':\"one\", \'1\':\"ekk\", \'2\':\"two\", \'3\':\"three\", \'4\':\"four\"" << MMAP_END;
	REQUIRE(ss1.str() == ss2.str());
}
