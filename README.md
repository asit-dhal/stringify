### stringify :- pretty print stl containers
- based on https://github.com/mnciitbhu/printers
- can print all stl containers to output stream

### Build Status
| Build  | Status |
|------- | -------- |
| AppVeyor | [![Build status](https://ci.appveyor.com/api/projects/status/tlptg967c60jsp11/branch/master?svg=true)](https://ci.appveyor.com/project/asit-dhal/stringify/branch/master) |
| Travis | [![Build Status](https://travis-ci.org/asit-dhal/stringify.svg?branch=master)](https://travis-ci.org/asit-dhal/stringify) |

### install
copy include to your source tree

### local build
```sh
git clone https://github.com/asit-dhal/stringify
cd stringify
mkdir build 
cd build
```
#### for windows(Visual Studio 2015) build
```sh
cmake -G"Visual Studio 14 2015 Win64" ..
```

#### for linux
```sh
cmake ..
```

### Usages
```cpp
#include "stringify\stringify.hpp"
using namespace stringify;
std::vector<int> v1;
    for (auto i = 0; i < 10; i++)
        v1.push_back(i);
    std::cout << "vector<int>: " << v1 << std::endl;
```
If you don't want to include namespace, you can use stringify::to_string()
```cpp
#include "stringify\stringify.hpp"
std::vector<int> v1;
    for (auto i = 0; i < 10; i++)
        v1.push_back(i);
    std::cout << "vector<int>: " << stringify::to_string(v1) << std::endl;
```

### Print Format
| container | format | example |
| --------- | ------ | ------- |
| ```std::string, const char*```| within double quote | "dummy" |
| ```char, wchar_t``` | within single quote | 'a' |
| ```std::array<int, N>``` | arr_len_[ comma separated values] | arr5[1, 2, 3, 4, 5]|
| ```int []``` |   carr_len_[ comma separated values] | carr5[1, 2, 3, 4, 5] |
| ```std::deque<int>``` | deq_len_ [comma separated values] | deq5[1, 2, 3, 4, 5]|
| ```std::forward_list<int>``` | flst_len_[comma separated values] | flst5[1, 2, 3, 4, 5] |


### Example
```cpp
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
#include <map>

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
    auto tp = std::make_tuple(200, "two hundred", "make string", 2.3f);
    std::cout << "tuple<int, std::string, char*, float>: " << tp << std::endl;
}

void mapExample()
{
    std::map<int, int> mp1;
    mp1[1] = 10;
    mp1[2] = 30;
    mp1[3] = 50;
    mp1[4] = 70;
    std::map<double, int> mp2;
    std::cout << "map<int, int>: " << mp1 << std::endl;
}

int main()
{
    containerExample();
    pointerExample();
    tupleExample();
    mapExample();
}
```

Output
```bash
vector<int>: vec10[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
vector<string>: vec10["0", "1", "4", "9", "16", "25", "36", "49", "64", "81"]
list<int>: lst10[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
list<string>: lst10["0", "1", "4", "9", "16", "25", "36", "49", "64", "81"]
deque<int>: deq10[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
deque<string>: deq10["0", "1", "4", "9", "16", "25", "36", "49", "64", "81"]
array<int>: arr10[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
array<string>: arr10["0", "1", "4", "9", "16", "25", "36", "49", "64", "81"]
set<int>: set10(0, 1, 2, 3, 4, 5, 6, 7, 8, 9)
set<string>: set10("0", "1", "16", "25", "36", "4", "49", "64", "81", "9")
multiset<int>: mset15(0, 0, 1, 2, 2, 3, 4, 4, 5, 6, 6, 7, 8, 8, 9)
multiset<string>: mset15("0", "0", "1", "16", "16", "25", "36", "36", "4", "4", "49", "64", "64", "81", "9")
shared_ptr<int>: sp->200, ref_cnt=1
shared_ptr<string>: sp->"test122", ref_cnt=1
unique_ptr<int>: up->200
unique_ptr<string>: up->"test122"
weak_ptr<int>: wp->200
weak_ptr<sring>: wp->"test122"
nullptr: sp->nullptr
pair<int, std::string>: pr(200, "two hundred")
tuple<int, std::string, char*, float>: tp4(200, "two hundred", "make string", 2.3)
map<int, int>: map4{1:10, 2:30, 3:50, 4:70}
```
