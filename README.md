### stringify :- pretty print stl containers
- based on https://github.com/mnciitbhu/printers
- can print all stl containers to output stream
- needs C++11/14 compliant compiler _clang not supported_

### Build Status
| Build  | Status |
|------- | -------- |
| AppVeyor | [![Build status](https://ci.appveyor.com/api/projects/status/tlptg967c60jsp11/branch/master?svg=true)](https://ci.appveyor.com/project/asit-dhal/stringify/branch/master) |
| Travis | [![Build Status](https://travis-ci.org/asit-dhal/stringify.svg?branch=master)](https://travis-ci.org/asit-dhal/stringify) |

### install
copy include/stringify.hpp to your source tree

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
| ```std::queue<int>``` | qu_len_ [comma separated values] | qu5[1, 2, 3, 4, 5]|
| ```std::list<int>``` | lst_len_[comma separated values] | lst5[1, 2, 3, 4, 5] |
| ```std::forward_list<int>``` | flst_len_[comma separated values] | flst5[1, 2, 3, 4, 5] |
| ```std::set<int>``` | set_len_(comma separated values) | set5(1, 2, 3, 4, 5) |
| ```std::multiset<int>``` | mset_len_(comma separated values) | mset5(1, 2, 3, 4, 5) |
| ```std::map<int, std::string>``` | map_len_[python style dictionary] |  map4{1:"one", 2:"two", 3:"three", 4:"four"}|
| ```std::multimap<int, std::string>``` | mmap_len_[python style dictionary] |  map4{1:"one", 1:"ekka", 2:"two", 2:"dui", 3:"three", 4:"four"}|
| ```std::pair<int, std::string>``` | pr(comma separated values) |  pr(200, "two hundred")|
| ```tuple<int, std::string, char*, float>``` | tp_len_(comma separated values) |tp4(200, "two hundred", "make string", 2.3)|
