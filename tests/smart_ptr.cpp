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
    REQUIRE(ss.str() == "sp->2, ref_cnt=1");

    ss.str(std::string());
    ss << ptr2;
    REQUIRE(ss.str() == "sp->\"test\", ref_cnt=3");

    ss.str(std::string());
    ss << ptr3;
    REQUIRE(ss.str() == "sp->\"test\", ref_cnt=3");

    ptr4 = nullptr;
    ss.str(std::string());
    ss << ptr3;
    REQUIRE(ss.str() == "sp->\"test\", ref_cnt=2");

    ss.str(std::string());
    ss << ptr4;
    REQUIRE(ss.str() == "sp->nullptr");
}

TEST_CASE("unique_ptr", "[unique_ptr]")
{
    using namespace stringify;
    std::stringstream ss;

    std::unique_ptr<int> ptr1 = std::make_unique<int>(2);
    std::unique_ptr<std::string> ptr2 = std::make_unique<std::string>("test");

    ss << ptr1;
    REQUIRE(ss.str() == "up->2");

    ss.str(std::string());
    ss << ptr2;
    REQUIRE(ss.str() == "up->\"test\"");

    ptr1.reset();
    ss.str(std::string());
    ss << ptr1;
    REQUIRE(ss.str() == "up->nullptr");
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
    REQUIRE(ss.str() == "wp->2");

    ss.str(std::string());
    ss << wk_ptr2;
    REQUIRE(ss.str() == "wp->\"test\"");

    sp_ptr1.reset();
    ss.str(std::string());
    ss << wk_ptr1;
    REQUIRE(ss.str() == "wp->nullptr");
}
