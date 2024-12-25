// #ifndef TUPLE_H
// #define TUPLE_H
// #include <fstream>
// #include <sstream>
// #include <string>
// #include <tuple>
// #include <vector>
//
//
// template <typename Tuple, size_t Index>
// struct TuplePrinter {
//     static void print_tuple(const Tuple& tp, std::ostream& os) {
//         TuplePrinter<Tuple, Index - 1>::print_tuple(tp, os); // Рекурсивный вызов
//         os << ", " << std::get<Index>(tp);
//     }
// };
//
// template <typename Tuple>
// struct TuplePrinter<Tuple, 0> {
//     static void print_tuple(const Tuple& tp, std::ostream& os) {
//         os << std::get<0>(tp);
//     }
// };
//
// template <typename Ch, typename Tr, typename... Args>
// std::basic_ostream<Ch, Tr>& operator<<(std::basic_ostream<Ch, Tr>& os, const std::tuple<Args...>& t) {
//     os << "(";
//     if (sizeof...(Args) > 0) {
//         TuplePrinter<std::tuple<Args...>, sizeof...(Args) - 1>::print_tuple(t, os);
//     }
//     os << ")";
//     return os;
// }
//
// template <typename T>
// T type_conversion(const std::string& str) {
//     std::stringstream tmp(str);
//     T value;
//     if(!(tmp >> value)) {
//         throw std::invalid_argument("Convert str error");
//     }
//     return value;
// }
//
// template <typename T, typename... Rest>
// std::tuple<T, Rest...> create_tuple_recursive(const std::vector<std::string>& vec, size_t index = 0) {
//     try {
//         T value = type_conversion<T>(vec[index]);
//     }
//     catch (std::invalid_argument& er) {
//         std::ostringstream error_mes;
//         error_mes << "Error at col: " << index + 1;
//         throw std::invalid_argument(error_mes.str());
//     }
//
//     T value = type_conversion<T>(vec[index]);
//     if constexpr (sizeof...(Rest) == 0) {
//         return std::make_tuple(value);
//     } else {
//         return std::tuple_cat(std::make_tuple(value), create_tuple_recursive<Rest...>(vec, index + 1));
//     }
// }
//
// template <typename... Args>
// std::tuple<Args...> create_tuple(const std::vector<std::string>& vec) {
//     return create_tuple_recursive<Args...>(vec);
// }
//
// #endif
//
#ifndef TUPLE_H
#define TUPLE_H

#include <fstream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

template <typename Tuple, size_t Index>
struct TuplePrinter {
    static void print(const Tuple& tp, std::ostream& os) {
        TuplePrinter<Tuple, Index - 1>::print(tp, os); // Рекурсивный вызов для предыдущих элементов
        os << ", " << std::get<Index>(tp);
    }
};

template <typename Tuple>
struct TuplePrinter<Tuple, 0> {
    static void print(const Tuple& tp, std::ostream& os) {
        os << std::get<0>(tp);
    }
};

template <typename Ch, typename Tr, typename... Args>
std::basic_ostream<Ch, Tr>& operator<<(std::basic_ostream<Ch, Tr>& os, const std::tuple<Args...>& t) {
    os << "(";
    if constexpr (sizeof...(Args) > 0) {
        TuplePrinter<std::tuple<Args...>, sizeof...(Args) - 1>::print(t, os);
    }
    os << ")";
    return os;
}

template <typename T>
T convert_from_string(const std::string& str) {
    std::stringstream ss(str);
    T value;
    if (!(ss >> value)) {
        throw std::invalid_argument("Error: Cannot convert string to the desired type");
    }
    return value;
}

template <typename T, typename... Rest>
struct TupleCreator {
    static std::tuple<T, Rest...> create(const std::vector<std::string>& vec, size_t index = 0) {
        if (index >= vec.size()) {
            throw std::out_of_range("Error: Index out of range while creating tuple");
        }
        T value;
        try {
            value = convert_from_string<T>(vec[index]);
        }
        catch (const std::invalid_argument&) {
            throw std::invalid_argument("Error at column: " + std::to_string(index + 1));
        }

        if constexpr (sizeof...(Rest) == 0) {
            return std::make_tuple(value);
        } else {
            return std::tuple_cat(std::make_tuple(value), TupleCreator<Rest...>::create(vec, index + 1));
        }
    }
};

template <typename... Args>
std::tuple<Args...> create_tuple(const std::vector<std::string>& vec) {
    return TupleCreator<Args...>::create(vec);
}

#endif
