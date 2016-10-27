/**************************************************************
 * Copyright (c) 2016 Chaerim YEO
 *
 * Distributed under the MIT License.
 **************************************************************/
#ifndef CREAM_STOPWATCH_HPP
#define CREAM_STOPWATCH_HPP

#include <cstdio>
#include <chrono>
#include <ratio>

#define CREAM_PUBLIC_NAMESPACE(NAME)  namespace NAME {}; namespace
#define CREAM_PRIVATE_NAMESPACE(NAME) namespace NAME

namespace cream {
    CREAM_PUBLIC_NAMESPACE(detail) {
        CREAM_PRIVATE_NAMESPACE(detail) {
            template<long long N> struct is_odd : std::integral_constant<bool, N & 1> {};
            template<long long N> struct is_even : std::integral_constant<bool, !is_odd<N>::value> {};

            template<long long B, int N> struct Pow       { static constexpr long long value = (is_odd<N>::value ? B : 1LL) * Pow<B, N / 2>::value * Pow<B, N / 2>::value; };
            template<long long B>        struct Pow<B, 0> { static constexpr long long value = 1LL; };

            template<typename Unit> struct UnitInfo;
            template<>              struct UnitInfo<std::chrono::hours>        { static constexpr const char* name = "h";  };
            template<>              struct UnitInfo<std::chrono::minutes>      { static constexpr const char* name = "m";  };
            template<>              struct UnitInfo<std::chrono::seconds>      { static constexpr const char* name = "s";  };
            template<>              struct UnitInfo<std::chrono::milliseconds> { static constexpr const char* name = "ms"; };
            template<>              struct UnitInfo<std::chrono::microseconds> { static constexpr const char* name = "us"; };
            template<>              struct UnitInfo<std::chrono::nanoseconds>  { static constexpr const char* name = "ns"; };
        }

        template<typename Unit = std::chrono::milliseconds, int Precision = 4, class Clock = std::chrono::system_clock>
        class StopWatch {
        public:
            StopWatch(const char* _title = "") : title(_title), start(Clock::now()) {}
            virtual ~StopWatch() {
                const TimePoint end = Clock::now();
                typename Duration::rep elapsed = std::chrono::duration_cast<Duration>(end - start).count();
                typename Duration::rep elapsedInteger = elapsed / DecimalPow::value;
                typename Duration::rep elapsedDecimal = elapsed % DecimalPow::value;
                std::printf("[%s] Elapsed time : %lld.%lld[%s]\n", title, elapsedInteger, elapsedDecimal, UnitInfo::name);
            }
        private:
            using TimePoint = std::chrono::time_point<Clock>;
            using DecimalPow = detail::Pow<10LL, Precision>;
            using Period = std::ratio_multiply<typename Unit::period, std::ratio<1LL, DecimalPow::value>>;
            using Duration = std::chrono::duration<long long, Period>;
            using UnitInfo = detail::UnitInfo<Unit>;

            TimePoint start;
            const char* title;
        };

    }
}

#endif // CREAM_STOPWATCH_HPP
