/**************************************************************
 * Copyright (c) 2016 Chaerim YEO
 *
 * Distributed under the MIT License.
 **************************************************************/
#ifndef CREAM_ALGORITHM_FOR_EACH_HPP
#define CREAM_ALGORITHM_FOR_EACH_HPP

#include <iterator>
#include <type_traits>

namespace cream {
    template<typename Iterator, class Function>
    inline Function forEach(Iterator first, Iterator last, Function func,
                              typename std::iterator_traits<Iterator>::difference_type initial = 0) {
        for (; first != last; first++)
            func(*first);
        return std::move(func);
    }

    template<class Type, int N, class Function>
    inline Function forEach(Type (&array)[N], Function func, std::ptrdiff_t initial = 0) {
        return forEach(array, array + N, func);
    }

    template<class Container, class Function>
    inline Function forEach(Container& c, Function func) {
        return forEach(std::begin(c), std::end(c), func);
    }
}

#endif
