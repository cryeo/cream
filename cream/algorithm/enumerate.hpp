/**************************************************************
 * Copyright (c) 2016 Chaerim YEO
 *
 * Distributed under the MIT License.
 **************************************************************/
#ifndef CREAM_ALGORITHM_ENUMERATE_HPP
#define CREAM_ALGORITHM_ENUMERATE_HPP

#include <iterator>
#include <type_traits>

namespace cream {
    template<typename Iterator, class Function>
    inline Function enumerate(Iterator first, Iterator last, Function func,
                              typename std::iterator_traits<Iterator>::difference_type initial = 0) {
        for (; first != last; first++, initial++)
            func(initial, *first);
        return std::move(func);
    }

    template<class Type, int N, class Function>
    inline Function enumerate(Type (&array)[N], Function func) {
        return enumerate(array, array + N, func);
    }

    template<class Container, class Function>
    inline Function enumerate(Container& c, Function func) {
        return enumerate(std::begin(c), std::end(c), func);
    }
}

#endif //CREAM_ENUMERATE_HPP
