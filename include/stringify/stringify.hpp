#pragma once

#include <unordered_map>
#include <utility>
#include <string>
#include <sstream>
#include <utility>
#include <tuple>
#include <ostream>
#include <limits>

namespace stringify
{
    template<typename T1, typename T2>
    std::string to_string(const std::pair<T1, T2>& pr);

    template<typename T1, typename T2>
    std::ostream& operator<<(std::ostream& xx, const std::pair<T1, T2>& pr);
}

namespace
{
    constexpr size_t INVALID_SIZE_T = std::numeric_limits<size_t>::max();
    const std::string delimiter = ", ";
    enum
    {
        LEFT,
        RIGHT
    };

    enum
    {
        NAME,
        BRACE_TYPE
    };

    using brace_type = std::pair<std::string, std::string>;
    brace_type const CURLY_BRACES   = std::make_pair("{", "}");
    brace_type const ANGULAR_BRACES = std::make_pair("<", ">");
    brace_type const BOX_BRACES     = std::make_pair("[", "]");
    brace_type const PARA_BRACES    = std::make_pair("(", ")");
    brace_type const PTR_BRACES     = std::make_pair("->", "");
    brace_type const NO_BRACES      = std::make_pair("", "");


    std::unordered_map<std::string, std::pair<std::string, brace_type>> Names =
    {
        { "carray", std::make_pair("carr", BOX_BRACES) },
        { "array", std::make_pair("arr", BOX_BRACES) },
        { "vector", std::make_pair("vec", BOX_BRACES) },
        { "deque", std::make_pair("deq", BOX_BRACES) },
        { "list", std::make_pair("lst", BOX_BRACES) },
        { "tuple", std::make_pair("tp", PARA_BRACES) },
        { "pair", std::make_pair("pr", PARA_BRACES) },
        { "map", std::make_pair("map", CURLY_BRACES) },
        { "multimap", std::make_pair("mmap", CURLY_BRACES) },
        { "set", std::make_pair("set", PARA_BRACES) },
        { "multiset", std::make_pair("mset", PARA_BRACES) },
        { "unordered_map", std::make_pair("umap", PARA_BRACES) },
        { "unordered_multimap", std::make_pair("ummap", CURLY_BRACES) },
        { "unordered_multiset", std::make_pair("umset", CURLY_BRACES) },
        { "unordered_set", std::make_pair("uset", CURLY_BRACES) },
        { "valarray", std::make_pair("valarr", CURLY_BRACES) },
        { "forward_list", std::make_pair("flst", BOX_BRACES) },

        { "iterator", std::make_pair("itr", PTR_BRACES) },
        { "const_iterator", std::make_pair("citr", PTR_BRACES) },
        { "reverse_iterator", std::make_pair("ritr", PTR_BRACES) },
        { "const_reverse_iterator", std::make_pair("critr" , PTR_BRACES) },

        { "pointer", std::make_pair("ptr", PTR_BRACES) },
        { "const_pointer", std::make_pair("cptr", PTR_BRACES) },
        { "shared_ptr", std::make_pair("sp", PTR_BRACES) },
        { "unique_ptr", std::make_pair("up", PTR_BRACES) },
        { "weak_ptr", std::make_pair("wp", PTR_BRACES) },
    };

    inline std::string get_name(std::string _name) { return std::get<NAME>(Names[_name]); }
    inline std::string get_begin_brace(std::string _name) { return std::get<LEFT>(std::get<BRACE_TYPE>(Names[_name])); }
    inline std::string get_end_brace(std::string _name) { return std::get<RIGHT>(std::get<BRACE_TYPE>(Names[_name])); }

    // string type traits
    template<class T> struct is_str : std::false_type {};
    template<> struct is_str<char*> : std::true_type {};
    template<> struct is_str<wchar_t*> : std::true_type {};
    template<> struct is_str<const char*> : std::true_type {};
    template<> struct is_str<const wchar_t*> : std::true_type {};
    template<> struct is_str<std::string> : std::true_type {};
    template<> struct is_str<const std::string> : std::true_type {};
    template<> struct is_str<std::wstring> : std::true_type {};
    template<> struct is_str<const std::wstring> : std::true_type {};

    // char type traits
    template<class T> struct is_char : std::false_type {};
    template<> struct is_char<char> : std::true_type {};
    template<> struct is_char<wchar_t> : std::true_type {};

    template<typename T>
    std::enable_if_t<is_str<T>::value, std::string>
        to_string(const T& val)
    {
        std::stringstream ss;
        ss << "\"" << val << "\"";
        return ss.str();
    }

    template<typename T>
    std::enable_if_t<is_char<T>::value, std::string>
        to_string(const T& val)
    {
        std::stringstream ss;
        ss << "\'" << val << "\'";
        return ss.str();
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
            std::stringstream ss;
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
    std::string printElementsCont(const T& ar, std::string&& _name, std::size_t N)
    {
        std::stringstream ss;
        ss << get_name(_name);
        if (N != INVALID_SIZE_T)
        {
            ss << N;
        }

        ss << get_begin_brace(_name);
        
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
            //ss << x;

        }
        ss << get_end_brace(_name);
        return ss.str();
    }

    template<typename T>
    std::string printElementsPtr(const T& ptr, std::string&& _name)
    {
        std::stringstream ss;
        ss << get_name(_name);
        ss << get_begin_brace(_name);
        ss << to_string(*ptr);
        return ss.str();
    }

    template<typename... TArgs>
    std::string printElementsTup(const std::tuple<TArgs...>& tup, std::string&& _name)
    {
        std::stringstream ss;
        ss << get_name(_name);
        constexpr size_t SZ = std::tuple_size<
            std::tuple<TArgs... >> ::value;
        if (_name != "pair")
        {
            ss << SZ;
        }
        ss << get_begin_brace(_name);
        auto tupleStr = TuplePrinter<SZ>::print(tup);
        ss << tupleStr.substr(0, tupleStr.size() - delimiter.size());
        ss << get_end_brace(_name);
        return ss.str();
    }

}

namespace stringify
{
    template<typename T1, typename T2>
    std::string to_string(const std::pair<T1, T2>& pr)
    {
        return printElementsTup(std::make_tuple(pr.first, pr.second), "pair");
    }

    template<typename... Types>
    std::string to_string(const std::tuple<Types...>& tup)
    {
        return printElementsTup(tup, "tuple");
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
        return printElementsCont(ar, "vector", ar.size());
    }

    template<typename T, typename _Alloc>
    std::ostream& operator<<(std::ostream& xx, const std::vector<T, _Alloc>& ar)
    {
        xx << to_string(ar);
        return xx;
    }

#endif

// for std::valarray<>
#if defined(_GLIBCXX_VALARRAY) || defined(_LIBCPP_VALARRAY) || defined(_VALARRAY_)

    template<typename T>
    std::ostream& operator<<(std::ostream& xx, const std::valarray<T>& ar)
    {
        xx << printElementsCont(ar, "valarray", ar.size());
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

    // for std::deque<>
#if defined(_GLIBCXX_DEQUE) || defined(_LIBCPP_DEQUE) || defined(_DEQUE_)

    template<typename T, typename _Alloc>
    std::ostream& operator<<(std::ostream& xx, const std::deque<T, _Alloc>& ar)
    {
        xx << printElementsCont(ar, "deque", ar.size());
        return xx;
    }

#endif

    template<typename T, size_t N>
    std::enable_if_t<!(std::is_same<char, T>::value || std::is_same<wchar_t, T>::value), std::ostream&>
        operator<<(std::ostream& xx, const T(&ar)[N])
    {
        xx << printElementsCont(ar, "carray", N);
        return xx;
    }

    template<typename T>
    struct is_reverse_iterator : std::false_type { };

    template<typename T>
    struct is_reverse_iterator<std::reverse_iterator<T>> : std::true_type{};

    template<typename T,
        typename S = typename std::iterator_traits<T>::reference>
#ifdef SHOW_ADDR
        std::enable_if_t<!std::is_pointer<T>::value, std::ostream&>
#else
        std::enable_if_t<!(std::is_same<T, char const*>::value ||
            std::is_same<T, wchar_t const*>::value ||
            std::is_same<T, wchar_t*>::value ||
            std::is_same<T, char*>::value), std::ostream&>
        //std::ostream&
#endif
        operator<<(std::ostream& xx, const T& it)
    {
        if (std::is_pointer<T>::value)
        {
            if (std::is_const<std::remove_reference_t<S>>::value)
            {
                xx << printElementsPtr(it, "const_pointer");
            }
            else
            {
                xx << printElementsPtr(it, "pointer");
            }
        }
        else
        {
            if (is_reverse_iterator<T>::value)
            {
                if (std::is_const<std::remove_reference_t<S>>::value)
                {
                    xx << printElementsPtr(it, "const_reverse_iterator");
                }
                else
                {
                    xx << printElementsPtr(it, "reverse_iterator");
                }
            }
            else
            {
                if (std::is_const<std::remove_reference_t<S>>::value)
                {
                    xx << printElementsPtr(it, "const_iterator");
                }
                else
                {
                    xx << printElementsPtr(it, "iterator");
                }
            }
        }
        return xx;
    }

    // for std::array<>
#if defined(_GLIBCXX_ARRAY) || defined(_LIBCPP_ARRAY) || defined(_ARRAY_)
    template<typename T, size_t N>
    std::ostream& operator<<(std::ostream& xx, const std::array<T, N>& ar)
    {
        xx << printElementsCont(ar, "array", N);
        return xx;
    }
#endif

    // for std::list<>
#if defined(_GLIBCXX_LIST) || defined(_LIBCPP_LIST) || defined(_LIST_)
    template<typename T, typename _Alloc>
    std::ostream& operator<<(std::ostream& xx, const std::list<T, _Alloc>& ar)
    {
        xx << printElementsCont(ar, "list", ar.size());
        return xx;
    }
#endif

    // for std::forward_list<>
#if defined(_GLIBCXX_FORWARD_LIST) || defined(_LIBCPP_FORWARD_LIST) || defined(_FORWARD_LIST_)
    template<typename T, typename _Alloc>
    std::ostream& operator<<(std::ostream& xx, const std::forward_list<T, _Alloc>& ar)
    {
        xx << printElementsCont(ar, "forward_list", INVALID_SIZE_T);
        return xx;
    }
#endif

    // for std::unordered_set<> & std::unordered_multiset<>
#if defined(_GLIBCXX_UNORDERED_SET) || defined(_LIBCPP_UNORDERED_SET) || defined(_UNORDERED_SET_)
    template<typename T, typename _Hasher, typename _Key, typename _Alloc>
    std::ostream& operator<<(std::ostream& xx, const std::unordered_set<T, _Hasher, _Key, _Alloc>& ar)
    {
        xx << printElementsCont(ar, "unordered_set", ar.size());
        return xx;
    }

    template<typename T, typename _Hasher, typename _Key, typename _Alloc>
    std::ostream& operator<<(std::ostream& xx, const std::unordered_multiset<T, _Hasher, _Key, _Alloc>& ar)
    {
        xx << printElementsCont(ar, "unordered_multiset", ar.size());
        return xx;
    }
#endif

    // for std::set<> & std::multiset<>
#if defined(_GLIBCXX_SET) || defined(_LIBCPP_SET) || defined(_SET_)
    template<typename T, typename _Pr, typename _Alloc>
    std::string to_string(const std::set<T, _Pr, _Alloc>& ar)
    {
        return printElementsCont(ar, "set", ar.size());
    }

    template<typename T, typename _Pr, typename _Alloc>
    std::string to_string(const std::multiset<T, _Pr, _Alloc>& ar)
    {
        return printElementsCont(ar, "multiset", ar.size());
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
    std::ostream& operator<<(std::ostream& xx, const std::map<T1, T2, _Pr, _Alloc>& ar)
    {
        xx << printElementsCont(ar, "map", ar.size());
        return xx;
    }

    template<typename T1, typename T2, typename _Pr, typename _Alloc>
    std::ostream& operator<<(std::ostream& xx, const std::multimap<T1, T2, _Pr, _Alloc>& ar)
    {
        xx << printElementsCont(ar, "multimap", ar.size());
        return xx;
    }
#endif

    // for std::unordered_map<> & std::unordered_multimap<>
#if defined(_GLIBCXX_UNORDERED_MAP) || defined(_LIBCPP_UNORDERED_MAP) || defined(_UNORDERED_MAP_)
    template<typename T1, typename T2, typename _Hasher, typename _Key, typename _Alloc>
    std::ostream& operator<<(std::ostream& xx, const std::unordered_map<T1, T2, _Hasher, _Key, _Alloc>& ar)
    {
        xx << printElementsCont(ar, "unordered_map", ar.size());
        return xx;
    }

    template<typename T1, typename T2, typename _Hasher,typename _Key, typename _Alloc>
    std::ostream& operator<<(std::ostream& xx, const std::unordered_multimap<T1, T2, _Hasher, _Key, _Alloc>& ar)
    {
        xx << printElementsCont(ar, "unordered_multimap", ar.size());
        return xx;
    }
#endif

    // for std::shared_ptr<> and std::unique_ptr<>
#if defined(_GLIBCXX_MEMORY) || defined(_LIBCPP_MEMORY) || defined(_MEMORY_)

    template<typename T>
    std::string to_string(const std::shared_ptr<T>& sp)
    {
        std::stringstream ss;
        if (sp)
        {
            ss << printElementsPtr(sp, "shared_ptr");
            ss << delimiter;
            ss << "ref_cnt=" << sp.use_count();
        }
        else
        {
            ss << get_name("shared_ptr");
            ss << get_begin_brace("shared_ptr");
            ss << "nullptr";
        }
        return ss.str();
    }

    template<typename T>
    std::string to_string(const std::unique_ptr<T>& up)
    {
        std::stringstream ss;
        // TODO: handle nullptr
        if (up)
        {
            ss << printElementsPtr(up, "unique_ptr");
        }
        else
        {
            ss << get_name("unique_ptr");
            ss << get_begin_brace("unique_ptr");
            ss << "nullptr";
        }
        return ss.str();
    }

    template<typename T>
    std::string to_string(const std::weak_ptr<T>& wp)
    {
        std::stringstream ss;
        if (auto sp = wp.lock())
        {
            ss << printElementsPtr(sp, "weak_ptr");
        }
        else
        {
            // TODO: no idea how to hanlde
            ss << get_name("weak_ptr");
            ss << get_begin_brace("weak_ptr");
            ss << "nullptr";
        }
        return ss.str();
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

