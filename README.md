[![Build status](https://ci.appveyor.com/api/projects/status/tlptg967c60jsp11/branch/master?svg=true)](https://ci.appveyor.com/project/asit-dhal/stringify/branch/master)

### stringify :- pretty print stl containers
- based on https://github.com/mnciitbhu/printers
- can print all stl containers to output stream

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
Please check example project to have an overview how to use

