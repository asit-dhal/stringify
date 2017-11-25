#pragma once

#include <unordered_map>
#include <utility>
#include <string>
#include <sstream>
#include <utility>
#include <tuple>
#include <ostream>
#include <limits>
#include <cstring>

namespace stringify
{
    template<typename T1, typename T2>
    std::string to_string(const std::pair<T1, T2>& pr);

    template<typename T1, typename T2>
    std::ostream& operator<<(std::ostream& xx, const std::pair<T1, T2>& pr);
}


#if __cplusplus==201103L
namespace std
{
	template< bool B, class T = void >
	using enable_if_t = typename enable_if<B, T>::type;

	template< class T >
	using remove_reference_t = typename remove_reference<T>::type;
}
#endif


namespace
{

    constexpr const char* delimiter = ", ";

    enum class CONTAINER_TYPE
    {
        // sequential
        CARRAY,
        ARRAY,
        VECTOR,
        DEQUE,
        LIST,
        STACK,
        QUEUE,
        VALARRAY,
        FORWARD_LIST,

        // associative
        MAP,
        MULTIMAP,
        UNORDERED_MAP,
        UNORDERED_MULTIMAP,
        SET,
        MULTISET,
        UNORDERED_SET,
        UNORDERED_MULTISET,

        // utility
        PAIR,
        TUPLE,

        // pointer
        ITERATOR,
        CONST_ITERATOR,
        REVERSE_ITERATOR,
        CONST_REVERSE_ITERATOR,
        POINTER,
        CONST_POINTER,
        SHARED_POINTER,
        UNIQUE_POINTER,
        WEAK_POINTER,
    };

    constexpr auto CURLY_BRACES_STR = std::array<const char*,2>{{"{", "}"}};
    constexpr auto BOX_BRACES_STR = std::array<const char*,2>{{"[", "]"}};
    constexpr auto PARA_BRACES_STR = std::array<const char*,2>{{"(", ")"}};
    constexpr auto PTR_BRACES_STR = std::array<const char*,2>{{"->", ""}};
    constexpr auto NO_BRACES_STR = std::array<const char*,2>{{"", ""}};

    constexpr auto BEGIN = 0;
    constexpr auto END = 1;

    constexpr const char* get_brace(CONTAINER_TYPE container_type, int pos)
    {
        switch(container_type)
        {
        case CONTAINER_TYPE::CARRAY:
        case CONTAINER_TYPE::ARRAY:
        case CONTAINER_TYPE::VECTOR:
        case CONTAINER_TYPE::DEQUE:
        case CONTAINER_TYPE::LIST:
        case CONTAINER_TYPE::STACK:
        case CONTAINER_TYPE::QUEUE:
        case CONTAINER_TYPE::VALARRAY:
        case CONTAINER_TYPE::FORWARD_LIST:
            return BOX_BRACES_STR.at(pos);

        case CONTAINER_TYPE::MAP:
        case CONTAINER_TYPE::MULTIMAP:
        case CONTAINER_TYPE::UNORDERED_MAP:
        case CONTAINER_TYPE::UNORDERED_MULTIMAP:
            return CURLY_BRACES_STR.at(pos);
        case CONTAINER_TYPE::SET:
        case CONTAINER_TYPE::MULTISET:
        case CONTAINER_TYPE::UNORDERED_SET:
        case CONTAINER_TYPE::UNORDERED_MULTISET:
            return PARA_BRACES_STR.at(pos);

        case CONTAINER_TYPE::PAIR:
        case CONTAINER_TYPE::TUPLE:
            return PARA_BRACES_STR.at(pos);


        case CONTAINER_TYPE::ITERATOR:
        case CONTAINER_TYPE::CONST_ITERATOR:
        case CONTAINER_TYPE::REVERSE_ITERATOR:
        case CONTAINER_TYPE::CONST_REVERSE_ITERATOR:
        case CONTAINER_TYPE::POINTER:
        case CONTAINER_TYPE::CONST_POINTER:
        case CONTAINER_TYPE::SHARED_POINTER:
        case CONTAINER_TYPE::UNIQUE_POINTER:
        case CONTAINER_TYPE::WEAK_POINTER:
            return PTR_BRACES_STR.at(pos);

        default:
            return NO_BRACES_STR.at(pos);
        }
    }

    std::string get_name(CONTAINER_TYPE containertype)
    {
        switch(containertype)
        {
        case CONTAINER_TYPE::ITERATOR: return std::string("itr");
        case CONTAINER_TYPE::CONST_ITERATOR: return std::string("c_itr");
        case CONTAINER_TYPE::REVERSE_ITERATOR: return std::string("r_itr");
        case CONTAINER_TYPE::CONST_REVERSE_ITERATOR: return std::string("cr_itr");
        case CONTAINER_TYPE::POINTER: return std::string("ptr");
        case CONTAINER_TYPE::CONST_POINTER: return std::string("c_ptr");
        case CONTAINER_TYPE::SHARED_POINTER: return std::string("s_ptr");
        case CONTAINER_TYPE::UNIQUE_POINTER: return std::string("u_ptr");
        case CONTAINER_TYPE::WEAK_POINTER: return std::string("w_ptr");
        default: return std::string("");
        }
    }

    // string type traits
    template<class T> struct is_str : std::false_type {};
    template<> struct is_str<char*> : std::true_type {};
    template<> struct is_str<wchar_t*> : std::true_type {};
    template<> struct is_str<const char*> : std::true_type {};
    template<> struct is_str<const wchar_t*> : std::true_type {};
    template<typename C, typename T, typename A>
    struct is_str<std::basic_string<C, T, A>> : std::true_type {};

    // char type traits
    template<class T> struct is_char : std::false_type {};
    template<> struct is_char<char> : std::true_type {};
    template<> struct is_char<wchar_t> : std::true_type {};

    // stl container type traits
    template <typename... Args>
    struct is_map_type { static const bool value = false; };

#if defined(_GLIBCXX_MAP) || defined(_LIBCPP_MAP) || defined(_MAP_)
    template <typename... Args>
    struct is_map_type<std::map<Args...>> { static const bool value = true; };
    template <typename... Args>
    struct is_map_type<std::multimap<Args...>> { static const bool value = true; };
#endif

#if defined(_GLIBCXX_UNORDERED_MAP) || defined(_LIBCPP_UNORDERED_MAP) || defined(_UNORDERED_MAP_)
    template <typename... Args>
    struct is_map_type<std::unordered_map<Args...>> { static const bool value = true; };
    template <typename... Args>
    struct is_map_type<std::unordered_multimap<Args...>> { static const bool value = true; };
#endif


    template<typename T>
    std::enable_if_t<is_str<T>::value, std::string>
        to_string(const T& val)
    {
        std::string str = "\"";
        str += val;
        str += "\"";
        return str;
    }

    template<typename T>
    std::enable_if_t<is_char<T>::value, std::string>
        to_string(const T& val)
    {
        std::string str = "\'";
        str += val;
        str += "\'";
        return str;
    }


    template<typename T>
    std::enable_if_t<!is_str<T>::value && !is_char<T>::value, T>
        to_string(const T& val)
    {
        return val;
    }

    template<size_t N>
    struct TuplePrinter
    {
        template<typename... Types>
        static std::string print(const std::tuple<Types...>& ar)
        {
            std::ostringstream ss;
            ss << TuplePrinter<N - 1>::print(ar);
            ss << to_string(std::get<N - 1>(ar));
            ss << delimiter;
            return ss.str();
        }
    };

    template<>
    struct TuplePrinter<0>
    {
        template<typename... Types>
        static std::string print(const std::tuple<Types...>&)
        {
            return "";
        }
    };


    template<typename T>
	std::enable_if_t<!is_map_type<T>::value, std::string> 
        printElementsCont(const T& ar, CONTAINER_TYPE containerType)
    {
        std::ostringstream ss;

        ss << get_brace(containerType, BEGIN);
        
        auto firstFlag = true;
        for (const auto& x : ar)
        {
            if (firstFlag)
            {
                firstFlag = false;
            }
            else
            {
                ss << delimiter;
            }
            
            using namespace stringify;
            ss << to_string(x);

        }
        ss << get_brace(containerType, END);
        return ss.str();
    }

    template<typename T1, typename T2>
    std::string to_map_string(const std::pair<T1, T2>& pr)
    {
        using namespace stringify;
        std::ostringstream oss;
        oss << to_string(pr.first);
        oss << ":";
        oss << to_string(pr.second);
        return oss.str();
    }

    template<typename T>
    std::enable_if_t<is_map_type<T>::value, std::string>
    printElementsCont(const T& ar, CONTAINER_TYPE containerType)
    {
        std::stringstream ss;
        ss << get_brace(containerType, BEGIN);
        auto firstFlag = true;
        for (const auto& x : ar)
        {
            if (firstFlag)
            {
                firstFlag = false;
            }
            else
            {
                ss << delimiter;
            }
            ss << to_map_string(x);
        }
        ss << get_brace(containerType, END);
        return ss.str();
    }

    template<typename T>
    std::string reversePrintElementsCont(const T& ar, CONTAINER_TYPE containerType)
    {
        std::ostringstream ss;

        ss << get_brace(containerType, BEGIN);

        auto firstFlag = true;
        for(auto it = ar.rbegin(); it != ar.rend(); it++)
        {
            if (firstFlag)
            {
                firstFlag = false;
            }
            else
            {
                ss << delimiter;
            }

            using namespace stringify;
            ss << to_string(*it);

        }

        ss << get_brace(containerType, END);
        return ss.str();
    }

    template<typename T>
    std::string printElementsPtr(const T& ptr, CONTAINER_TYPE containerType)
    {
        std::ostringstream ss;
        ss << get_name(containerType);
        ss << get_brace(containerType, BEGIN);
        ss << to_string(*ptr);
        return ss.str();
    }

    template<typename... TArgs>
    std::string printElementsTup(const std::tuple<TArgs...>& tup, CONTAINER_TYPE containerType)
    {
        std::ostringstream ss;
        constexpr size_t SZ = std::tuple_size<std::tuple<TArgs... >> ::value;
        ss << get_brace(containerType, BEGIN);
        auto tupleStr = TuplePrinter<SZ>::print(tup);
        ss << tupleStr.substr(0, tupleStr.size() - std::strlen(delimiter));
        ss << get_brace(containerType, END);
        return ss.str();
    }

}

namespace stringify
{	
    template<typename T1, typename T2>
    std::string to_string(const std::pair<T1, T2>& pr)
    {
        return printElementsTup(std::make_tuple(pr.first, pr.second), CONTAINER_TYPE::PAIR);
    }

    template<typename... Types>
    std::string to_string(const std::tuple<Types...>& tup)
    {
        return printElementsTup(tup, CONTAINER_TYPE::TUPLE);
    }

    template<typename T1, typename T2>
    std::ostream& operator<<(std::ostream& xx, const std::pair<T1, T2>& pr)
    {
        xx << to_string(pr);
        return xx;
    }

    template<typename... Types>
    std::ostream& operator<<(std::ostream& xx, const std::tuple<Types...>& tup)
    {
        xx << to_string(tup);
        return xx;
    }

    // for std::vector<>
#if defined(_GLIBCXX_VECTOR) || defined(_LIBCPP_VECTOR) || defined(_VECTOR_)

    template<typename T, typename _Alloc>
    std::string to_string(const std::vector<T, _Alloc>& ar)
    {
        return printElementsCont(ar, CONTAINER_TYPE::VECTOR);
    }

    template<typename T, typename _Alloc>
    std::ostream& operator<<(std::ostream& xx, const std::vector<T, _Alloc>& ar)
    {
        xx << to_string(ar);
        return xx;
    }

#endif

#if defined(_GLIBCXX_ARRAY) || defined(_LIBCPP_ARRAY_) || defined(_ARRAY_)

    template<typename T, std::size_t _N>
    std::string to_string(const std::array<T, _N>& ar)
    {
        return printElementsCont(ar, CONTAINER_TYPE::ARRAY);
    }

    template<typename T, std::size_t _N>
    std::ostream& operator<<(std::ostream& xx, const std::array<T, _N>& ar)
    {
        xx << to_string(ar);
        return xx;
    }

#endif

#if defined(_GLIBCXX_VALARRAY) || defined(_LIBCPP_VALARRAY) || defined(_VALARRAY_)

    template<typename T>
    std::ostream& operator<<(std::ostream& xx, const std::valarray<T>& ar)
    {
        xx << printElementsCont(ar, CONTAINER_TYPE::VALARRAY);
        return xx;
    }

    template<typename T, typename R = typename T::value_type>
        std::enable_if_t<std::is_convertible<T, std::valarray<R>>::value, std::ostream&>
    operator<<(std::ostream& xx, const T& ar)
    {
        xx << std::valarray<R>(ar);
        return xx;
    }

#endif

#if defined(_GLIBCXX_DEQUE) || defined(_LIBCPP_DEQUE) || defined(_DEQUE_)

    template<typename T, typename _Alloc>
    std::ostream& operator<<(std::ostream& xx, const std::deque<T, _Alloc>& ar)
    {
        xx << printElementsCont(ar, CONTAINER_TYPE::DEQUE);
        return xx;
    }

#endif

    template<typename T, size_t N>
    std::enable_if_t<!(std::is_same<char, T>::value || std::is_same<wchar_t, T>::value), std::ostream&>
        operator<<(std::ostream& xx, const T(&ar)[N])
    {
        xx << printElementsCont(ar, CONTAINER_TYPE::CARRAY);
        return xx;
    }

    template<typename T>
    struct is_reverse_iterator : std::false_type { };

    template<typename T>
    struct is_reverse_iterator<std::reverse_iterator<T>> : std::true_type{};

    template<typename T,
        typename S = typename std::iterator_traits<T>::reference>
        std::enable_if_t<!(std::is_same<T, char const*>::value ||
            std::is_same<T, wchar_t const*>::value ||
            std::is_same<T, wchar_t*>::value ||
            std::is_same<T, char*>::value), std::ostream&>
        operator<<(std::ostream& xx, const T& it)
    {
        if (std::is_pointer<T>::value)
        {
            if (std::is_const<std::remove_reference_t<S>>::value)
            {
                xx << printElementsPtr(it, CONTAINER_TYPE::CONST_POINTER);
            }
            else
            {
                xx << printElementsPtr(it, CONTAINER_TYPE::POINTER);
            }
        }
        else
        {
            if (is_reverse_iterator<T>::value)
            {
                if (std::is_const<std::remove_reference_t<S>>::value)
                {
                    xx << printElementsPtr(it, CONTAINER_TYPE::CONST_REVERSE_ITERATOR);
                }
                else
                {
                    xx << printElementsPtr(it, CONTAINER_TYPE::REVERSE_ITERATOR);
                }
            }
            else
            {
                if (std::is_const<std::remove_reference_t<S>>::value)
                {
                    xx << printElementsPtr(it, CONTAINER_TYPE::CONST_ITERATOR);
                }
                else
                {
                    xx << printElementsPtr(it, CONTAINER_TYPE::ITERATOR);
                }
            }
        }
        return xx;
    }

#if defined(_GLIBCXX_LIST) || defined(_LIBCPP_LIST) || defined(_LIST_)
    template<typename T, typename _Alloc>
    std::string to_string(const std::list<T, _Alloc>& ar)
    {
        return printElementsCont(ar, CONTAINER_TYPE::LIST);
    }

    template<typename T, typename _Alloc>
    std::ostream& operator<<(std::ostream& xx, const std::list<T, _Alloc>& ar)
    {
        xx << to_string(ar);
        return xx;
    }
#endif

#if defined(_GLIBCXX_FORWARD_LIST) || defined(_LIBCPP_FORWARD_LIST) || defined(_FORWARD_LIST_)
    template<typename T, typename _Alloc>
    std::string to_string(const std::forward_list<T, _Alloc>& ar)
    {
        return printElementsCont(ar, CONTAINER_TYPE::FORWARD_LIST);
    }

    template<typename T, typename _Alloc>
    std::ostream& operator<<(std::ostream& xx, const std::forward_list<T, _Alloc>& ar)
    {
        xx << to_string(ar);
        return xx;
    }
#endif

    // for std::unordered_set<> & std::unordered_multiset<>
#if defined(_GLIBCXX_UNORDERED_SET) || defined(_LIBCPP_UNORDERED_SET) || defined(_UNORDERED_SET_)
    template<typename T, typename _Hasher, typename _Key, typename _Alloc>
    std::ostream& operator<<(std::ostream& xx, const std::unordered_set<T, _Hasher, _Key, _Alloc>& ar)
    {
        xx << printElementsCont(ar, CONTAINER_TYPE::UNORDERED_SET);
        return xx;
    }

    template<typename T, typename _Hasher, typename _Key, typename _Alloc>
    std::ostream& operator<<(std::ostream& xx, const std::unordered_multiset<T, _Hasher, _Key, _Alloc>& ar)
    {
        xx << printElementsCont(ar, CONTAINER_TYPE::UNORDERED_MULTISET);
        return xx;
    }
#endif

    // for std::set<> & std::multiset<>
#if defined(_GLIBCXX_SET) || defined(_LIBCPP_SET) || defined(_SET_)
    template<typename T, typename _Pr, typename _Alloc>
    std::string to_string(const std::set<T, _Pr, _Alloc>& ar)
    {
        return printElementsCont(ar, CONTAINER_TYPE::SET);
    }

    template<typename T, typename _Pr, typename _Alloc>
    std::string to_string(const std::multiset<T, _Pr, _Alloc>& ar)
    {
        return printElementsCont(ar, CONTAINER_TYPE::MULTISET);
    }

    template<typename T, typename _Pr, typename _Alloc>
    std::ostream& operator<<(std::ostream& xx, const std::set<T, _Pr, _Alloc>& ar)
    {
        xx << to_string(ar);
        return xx;
    }

    template<typename T, typename _Pr, typename _Alloc>
    std::ostream& operator<<(std::ostream& xx, const std::multiset<T, _Pr, _Alloc>& ar)
    {
        xx << to_string(ar);
        return xx;
    }
#endif

    // for std::map<> & std::multimap<>
#if defined(_GLIBCXX_MAP) || defined(_LIBCPP_MAP) || defined(_MAP_)
	template<typename T1, typename T2, typename _Pr, typename _Alloc>
	std::string to_string(const std::map<T1, T2, _Pr, _Alloc>& ar)
	{
        return printElementsCont(ar, CONTAINER_TYPE::MAP);
	}

	template<typename T1, typename T2, typename _Pr, typename _Alloc>
	std::string to_string(const std::multimap<T1, T2, _Pr, _Alloc>& ar)
	{
        return printElementsCont(ar, CONTAINER_TYPE::MULTIMAP);
	}

    template<typename T1, typename T2, typename _Pr, typename _Alloc>
    std::ostream& operator<<(std::ostream& xx, const std::map<T1, T2, _Pr, _Alloc>& ar)
    {
        xx << to_string(ar);
        return xx;
    }

    template<typename T1, typename T2, typename _Pr, typename _Alloc>
    std::ostream& operator<<(std::ostream& xx, const std::multimap<T1, T2, _Pr, _Alloc>& ar)
    {
        xx << to_string(ar);
        return xx;
    }
#endif

    // for std::unordered_map<> & std::unordered_multimap<>
#if defined(_GLIBCXX_UNORDERED_MAP) || defined(_LIBCPP_UNORDERED_MAP) || defined(_UNORDERED_MAP_)
	template<typename T1, typename T2, typename _Hasher, typename _Key, typename _Alloc>
	std::string to_string(const std::unordered_map<T1, T2, _Hasher, _Key, _Alloc>& ar)
	{
        return printElementsCont(ar, CONTAINER_TYPE::UNORDERED_MAP);
	}

	template<typename T1, typename T2, typename _Hasher, typename _Key, typename _Alloc>
	std::string to_string(const std::unordered_multimap<T1, T2, _Hasher, _Key, _Alloc>& ar)
	{
        return printElementsCont(ar, CONTAINER_TYPE::UNORDERED_MULTIMAP);
	}

    template<typename T1, typename T2, typename _Hasher, typename _Key, typename _Alloc>
    std::ostream& operator<<(std::ostream& xx, const std::unordered_map<T1, T2, _Hasher, _Key, _Alloc>& ar)
    {
        xx << to_string(ar);
        return xx;
    }

    template<typename T1, typename T2, typename _Hasher,typename _Key, typename _Alloc>
    std::ostream& operator<<(std::ostream& xx, const std::unordered_multimap<T1, T2, _Hasher, _Key, _Alloc>& ar)
    {
        xx << to_string(ar);
        return xx;
    }
#endif

    // for std::stack<>
#if defined(_GLIBCXX_STACK) || defined(_LIBCPP_STACK) || defined(_STACK_)

    template<typename T>
    std::string to_string(const std::stack<T> &ar)
    {
        std::vector<T> vt;
        auto ar_clone = ar;
        vt.reserve(ar_clone.size());
        while (!ar_clone.empty())
        {
            vt.push_back(ar_clone.top());
            ar_clone.pop();
        }
        return reversePrintElementsCont(vt, CONTAINER_TYPE::STACK);
    }

    template<typename T>
    std::ostream& operator<<(std::ostream& xx, const std::stack<T>& ar)
    {
        xx << to_string(ar);
        return xx;
    }

#endif

    // for std::queue<>
#if defined(_GLIBCXX_QUEUE) || defined(_LIBCPP_QUEUE) || defined(_QUEUE_)

    template<typename T>
    std::string to_string(const std::queue<T> &ar)
    {
        std::vector<T> vt;
        auto ar_clone = ar;
        vt.reserve(ar_clone.size());
        while (!ar_clone.empty())
        {
            vt.push_back(ar_clone.front());
            ar_clone.pop();
        }
        return printElementsCont(vt, CONTAINER_TYPE::QUEUE);
    }

    template<typename T>
    std::ostream& operator<<(std::ostream& xx, const std::queue<T>& ar)
    {
        xx << to_string(ar);
        return xx;
    }

#endif

    // for std::shared_ptr<> and std::unique_ptr<>
#if defined(_GLIBCXX_MEMORY) || defined(_LIBCPP_MEMORY) || defined(_MEMORY_)

    template<typename T>
    std::string to_string(const std::shared_ptr<T>& sp)
    {
        if (sp)
        {
           return printElementsPtr(sp, CONTAINER_TYPE::SHARED_POINTER);
        }
        else
        {
            return std::string("nullptr");
        }
    }

    template<typename T>
    std::string to_string(const std::unique_ptr<T>& up)
    {
        // TODO: handle nullptr
        if (up)
        {
            return printElementsPtr(up, CONTAINER_TYPE::UNIQUE_POINTER);
        }
        else
        {
            return std::string("nullptr");
        }
    }

    template<typename T>
    std::string to_string(const std::weak_ptr<T>& wp)
    {
        if (auto sp = wp.lock())
        {
            return printElementsPtr(sp, CONTAINER_TYPE::WEAK_POINTER);
        }
        else
        {
            // TODO: no idea how to hanlde
            return std::string("nullptr");
        }
    }

    template<typename T>
    std::ostream& operator<<(std::ostream& xx, const std::shared_ptr<T>& sp)
    {
        xx << to_string(sp);
        return xx;
    }

    template<typename T>
    std::ostream& operator<<(std::ostream& xx, const std::unique_ptr<T>& up)
    {
        xx << to_string(up);
        return xx;
    }

    template<typename T>
    std::ostream& operator<<(std::ostream& xx, const std::weak_ptr<T>& wp)
    {
        xx << to_string(wp);
        return xx;
    }

#endif
}

