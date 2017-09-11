#include <vector>
#include <iterator>
#include "common.hpp"

auto const ITERATOR_BEGIN = "->";
auto const ITERATOR_NAME = "itr";
auto const CITERATOR_NAME = "citr";
auto const REV_ITERATOR_NAME = "ritr";
auto const CREV_ITERATOR_NAME = "critr";

TEST_CASE("iterator_num", "[iterator_num]")
{
    using namespace stringify;
    std::vector<int> v1{ 1, 2, 3, 4 ,5 };
    auto v1_itr = std::begin(v1);
    auto v1_citr = std::cbegin(v1);
    auto v1_ritr = std::rbegin(v1);
    auto v1_critr = std::crbegin(v1);
    
    std::stringstream ss1;
    std::stringstream ss2;

    ss1 << v1_itr;
    ss2 << ITERATOR_NAME << ITERATOR_BEGIN << "1";
    REQUIRE(ss1.str() == ss2.str());

    ss1.str(std::string());
    ss2.str(std::string());
    ss1 << v1_citr;
    ss2 << CITERATOR_NAME << ITERATOR_BEGIN << "1";
    REQUIRE(ss1.str() == ss2.str());

    ss1.str(std::string());
    ss2.str(std::string());
    ss1 << v1_ritr;
    ss2 << REV_ITERATOR_NAME << ITERATOR_BEGIN << "5";
    REQUIRE(ss1.str() == ss2.str());

    ss1.str(std::string());
    ss2.str(std::string());
    ss1 << v1_critr;
    ss2 << CREV_ITERATOR_NAME << ITERATOR_BEGIN << "5";
    REQUIRE(ss1.str() == ss2.str());
}

TEST_CASE("iterator_string", "[iterator_string]")
{
    using namespace stringify;
    std::vector<std::string> v1{ "one", "two", "three", "four"};
    auto v1_itr = std::begin(v1);
    auto v1_citr = std::cbegin(v1);
    auto v1_ritr = std::rbegin(v1);
    auto v1_critr = std::crbegin(v1);

    std::stringstream ss1;
    std::stringstream ss2;

    ss1 << v1_itr;
    ss2 << ITERATOR_NAME << ITERATOR_BEGIN << "\"one\"";
    REQUIRE(ss1.str() == ss2.str());

    ss1.str(std::string());
    ss2.str(std::string());
    ss1 << v1_citr;
    ss2 << CITERATOR_NAME << ITERATOR_BEGIN << "\"one\"";
    REQUIRE(ss1.str() == ss2.str());

    ss1.str(std::string());
    ss2.str(std::string());
    ss1 << v1_ritr;
    ss2 << REV_ITERATOR_NAME << ITERATOR_BEGIN << "\"four\"";
    REQUIRE(ss1.str() == ss2.str());

    ss1.str(std::string());
    ss2.str(std::string());
    ss1 << v1_critr;
    ss2 << CREV_ITERATOR_NAME << ITERATOR_BEGIN << "\"four\"";
    REQUIRE(ss1.str() == ss2.str());
}

