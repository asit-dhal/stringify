#include <memory>
#include <algorithm>
#include "common.hpp"

TEST_CASE("shared_ptr", "[shared_ptr]")
{
    using namespace stringify;
    std::stringstream ss;

    std::shared_ptr<int> ptr1 = std::make_shared<int>(2);
    std::shared_ptr<std::string> ptr2 = std::make_shared<std::string>("test");
    auto ptr3 = ptr2;
    auto ptr4 = ptr2;

    ss << ptr1;
    REQUIRE(ss.str() == "s_ptr->2");

    ss.str(std::string());
    ss << ptr2;
    REQUIRE(ss.str() == "s_ptr->\"test\"");

    ss.str(std::string());
    ss << ptr3;
    REQUIRE(ss.str() == "s_ptr->\"test\"");

    ptr4 = nullptr;
    ss.str(std::string());
    ss << ptr4;
    REQUIRE(ss.str() == "nullptr");
}

TEST_CASE("unique_ptr", "[unique_ptr]")
{
    using namespace stringify;
    std::stringstream ss;

    std::unique_ptr<int> ptr1 = std::make_unique<int>(2);
    std::unique_ptr<std::string> ptr2 = std::make_unique<std::string>("test");

    ss << ptr1;
    REQUIRE(ss.str() == "u_ptr->2");

    ss.str(std::string());
    ss << ptr2;
    REQUIRE(ss.str() == "u_ptr->\"test\"");

    ptr1.reset();
    ss.str(std::string());
    ss << ptr1;
    REQUIRE(ss.str() == "nullptr");
}

TEST_CASE("weak_ptr", "[weak_ptr]")
{
    using namespace stringify;
    std::stringstream ss;

    std::shared_ptr<int> sp_ptr1 = std::make_shared<int>(2);
    std::weak_ptr<int> wk_ptr1 = sp_ptr1;
    std::shared_ptr<std::string> sp_ptr2 = std::make_shared<std::string>("test");
    std::weak_ptr<std::string> wk_ptr2 = sp_ptr2;
    
    ss << wk_ptr1;
    REQUIRE(ss.str() == "w_ptr->2");

    ss.str(std::string());
    ss << wk_ptr2;
    REQUIRE(ss.str() == "w_ptr->\"test\"");

    sp_ptr1.reset();
    ss.str(std::string());
    ss << wk_ptr1;
    REQUIRE(ss.str() == "nullptr");
}
