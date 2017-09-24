#include <unordered_map>
#include <utility>
#include "common.hpp"

auto const UMMAP_BEGIN = "{";
auto const UMMAP_END = "}";
auto const UMMAP_NAME = "ummap";

TEST_CASE("unordered_multimap_numbers", "[unordered_multimap_numbers]")
{
	using namespace stringify;
	std::unordered_multimap<int, int> mp1;
	mp1.insert(std::make_pair<int, int>(1, 10));
	mp1.insert(std::make_pair<int, int>(2, 30));
	mp1.insert(std::make_pair<int, int>(2, 300));
	mp1.insert(std::make_pair<int, int>(3, 50));
	mp1.insert(std::make_pair<int, int>(4, 70));

	std::unordered_multimap<double, int> mp2;
	mp2.insert(std::make_pair<double, int>(1.1, 10));
	mp2.insert(std::make_pair<double, int>(2.3, 30));
	mp2.insert(std::make_pair<double, int>(9.1, 50));
	mp2.insert(std::make_pair<double, int>(9.1, 90));
	mp2.insert(std::make_pair<double, int>(2.7, 70));
	mp2.insert(std::make_pair<double, int>(2.7, 210));

	std::stringstream ss1;
	std::stringstream ss2;

	ss1 << mp1;
	ss2 << UMMAP_NAME << mp1.size() << UMMAP_BEGIN << "1:10, 2:30, 2:300, 3:50, 4:70" << UMMAP_END;
	REQUIRE(ss1.str() == ss2.str());

	ss1.str(std::string());
	ss2.str(std::string());
	ss1 << mp2;
	ss2 << UMMAP_NAME << mp2.size() << UMMAP_BEGIN << "1.1:10, 2.3:30, 2.7:70, 2.7:210, 9.1:50, 9.1:90" << UMMAP_END;
	REQUIRE(ss1.str() == ss2.str());
}

TEST_CASE("unordered_multimap_string", "[unordered_multimap_string]")
{
	using namespace stringify;
	std::unordered_multimap<char, std::string> mp_str1;
	mp_str1.insert(std::pair<char, std::string>('1', "one"));
	mp_str1.insert(std::pair<char, std::string>('1', "ekk"));
	mp_str1.insert(std::pair<char, std::string>('2', "two"));
	mp_str1.insert(std::pair<char, std::string>('3', "three"));
	mp_str1.insert(std::pair<char, std::string>('4', "four"));

	std::unordered_multimap<char, const char*> mp_str2;
	mp_str2.insert(std::pair<char, const char*>('1', "one"));
	mp_str2.insert(std::pair<char, const char*>('1', "ekk"));
	mp_str2.insert(std::pair<char, const char*>('2', "two"));
	mp_str2.insert(std::pair<char, const char*>('3', "three"));
	mp_str2.insert(std::pair<char, const char*>('4', "four"));


	std::stringstream ss1;
	std::stringstream ss2;

	ss1 << mp_str1;
	ss2 << UMMAP_NAME << mp_str1.size() << UMMAP_BEGIN << "\'1\':\"one\", \'1\':\"ekk\", \'2\':\"two\", \'3\':\"three\", \'4\':\"four\"" << UMMAP_END;
	REQUIRE(ss1.str() == ss2.str());

	ss1.str(std::string());
	ss2.str(std::string());

	ss1 << mp_str2;
	ss2 << UMMAP_NAME << mp_str2.size() << UMMAP_BEGIN << "\'1\':\"one\", \'1\':\"ekk\", \'2\':\"two\", \'3\':\"three\", \'4\':\"four\"" << UMMAP_END;
	REQUIRE(ss1.str() == ss2.str());
}
