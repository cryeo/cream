/**************************************************************
 * Copyright (c) 2016 Chaerim YEO
 *
 * Distributed under the MIT License.
 **************************************************************/
#ifndef CREAM_ALGORITHM_PARALLEL_ITERATE_HPP
#define CREAM_ALGORITHM_PARALLEL_ITERATE_HPP

#include <array>
#include <thread>

#include <cream/algorithm/enumerate.hpp>

namespace cream {
    template<std::size_t N = 1, typename Iterator, class Function>
    inline void parallelForEach(const Iterator& first,
                                const Iterator& last,
                                Function&& func) {
        const std::size_t nElements = static_cast<std::size_t>(last - first);
        const std::size_t szGroup = std::max(std::size_t(1), nElements / N);

        std::array<std::thread, N - 1> threads;
        Iterator it = first;

        if (N > 1) {
            for (std::size_t idx = 0; idx < threads.size(); idx++, it += szGroup) {
                threads[idx] = std::thread([=, &func]() { std::for_each(it, std::min(it + szGroup, last), func); });
            }
        }

        std::for_each(it, last, func);
        if (N > 1) {
            std::for_each(threads.begin(), threads.end(), [](std::thread &x) { x.join(); });
        }
    }

    template<std::size_t N = 1, typename Iterator, class Function>
    void parallelEnumerate(const Iterator& first,
                           const Iterator& last,
                           Function&& func) {
        const std::size_t nElements = static_cast<std::size_t>(last - first);
        const std::size_t szGroup = std::max(std::size_t(1), nElements / N);

        std::array<std::thread, N - 1> threads;
        Iterator it = first;

        if (N > 1) {
            for (std::size_t idx = 0; idx < threads.size(); idx++, it += szGroup) {
                threads[idx] = std::thread([=, &func]() { cream::enumerate(it, std::min(it + szGroup, last), func, it - first); });
            }
        }

        cream::enumerate(it, last, func, it - first);
        if (N > 1) {
            std::for_each(threads.begin(), threads.end(), [](std::thread &x) { x.join(); });
        }
    }
}
#endif //CREAM_ALGORITHM_PARALLEL_ITERATE_HPP
