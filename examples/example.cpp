
#include <vector>
#include <iostream>
#include <string>
#include <list>
#include <deque>
#include <array>
#include <algorithm>
#include <set>
#include <memory>
#include <utility>
#include <tuple>

#include "stringify\stringify.hpp"

using namespace stringify;

void containerExample()
{
    std::vector<int> v1;
    for (auto i = 0; i < 10; i++)
        v1.push_back(i);
    std::cout << "vector<int>: " << v1 << std::endl;

    std::vector<std::string> v2;
    for (auto i = 0; i < 10; i++)
        v2.push_back(std::to_string(i*i));
    std::cout << "vector<string>: " << v2 << std::endl;

    std::list<int> l1(v1.begin(), v1.end());
    std::cout << "list<int>: " << l1 << std::endl;
    std::list<std::string> l2(v2.begin(), v2.end());
    std::cout << "list<string>: " << l2 << std::endl;

    std::deque<int> d1(v1.begin(), v1.end());
    std::cout << "deque<int>: " << d1 << std::endl;
    std::deque<std::string> d2(v2.begin(), v2.end());
    std::cout << "deque<string>: " << d2 << std::endl;

    std::array<int, 10> arr1;
    std::copy_n(v1.begin(), 10, arr1.begin());
    std::cout << "array<int>: " << arr1 << std::endl;
    std::array<std::string, 10> arr2;
    std::copy_n(v2.begin(), 10, arr2.begin());
    std::cout << "array<string>: " << arr2 << std::endl;

    std::set<int> s1(v1.begin(), v1.end());
    std::cout << "set<int>: " << s1 << std::endl;
    std::set<std::string> s2(v2.begin(), v2.end());
    std::cout << "set<string>: " << s2 << std::endl;

    std::multiset<int> ms1(v1.begin(), v1.end());
    for (auto i = 0; i < 10; i += 2) ms1.emplace(i);
    std::cout << "multiset<int>: " << ms1 << std::endl;
    std::multiset<std::string> ms2(v2.begin(), v2.end());
    for (auto i = 0; i < 10; i += 2) ms2.emplace(std::to_string(i*i));
    std::cout << "multiset<string>: " << ms2 << std::endl;
}

void pointerExample()
{
    auto sp1 = std::make_shared<int>(200);
    std::cout << "shared_ptr<int>: " << sp1 << std::endl;
    auto sp2 = std::make_shared<std::string>("test122");
    std::cout << "shared_ptr<string>: " << sp2 << std::endl;
    auto up1 = std::make_unique<int>(200);
    std::cout << "unique_ptr<int>: " << up1 << std::endl;
    auto up2 = std::make_unique<std::string>("test122");
    std::cout << "unique_ptr<string>: " << up2 << std::endl;
    std::weak_ptr<int> wp1 = sp1;
    std::cout << "weak_ptr<int>: " << wp1 << std::endl;
    std::weak_ptr<std::string> wp2 = sp2;
    std::cout << "weak_ptr<sring>: " << wp2 << std::endl;
    std::cout << "nullptr: " << std::shared_ptr<int>() << std::endl;
}

void tupleExample()
{
    auto pr = std::make_pair<int, std::string>(200, "two hundred");
    std::cout << "pair<int, std::string>: " << pr << std::endl;
    //auto tp = std::make_tuple<int, std::string, char*, float>(200, "two hundred", "make string", 2.3f);
    //std::cout << "tuple<int, std::string, char*, float>: " << tp << std::endl;
}

int main()
{
    containerExample();
    pointerExample();
    tupleExample();
}