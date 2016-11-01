/**************************************************************
 * Copyright (c) 2016 Chaerim YEO
 *
 * Distributed under the MIT License.
 **************************************************************/
#ifndef CREAM_TYPE_TRAITS_IS_CALLABLE_HPP
#define CREAM_TYPE_TRAITS_IS_CALLABLE_HPP

#include <type_traits>
#include <functional>

#include <cream/common/common.hpp>

namespace cream {
    template<typename T, typename U = void>
    struct is_callable {
        static bool const constexpr value = std::conditional<
                std::is_class<std::remove_reference<T>>::type::value,
                is_callable<typename std::remove_reference<T>::type, int>,
                std::false_type>::type::value;
    };

    template<typename T, typename U, typename ...Args>
    struct is_callable<T(Args...), U> : std::true_type {};
    template<typename T, typename U, typename ...Args>
    struct is_callable<T(*)(Args...), U> : std::true_type {};
    template<typename T, typename U, typename ...Args>
    struct is_callable<T(&)(Args...), U> : std::true_type {};
    template<typename T, typename U, typename ...Args>
    struct is_callable<T(Args..., ...), U> : std::true_type {};
    template<typename T, typename U, typename ...Args>
    struct is_callable<T(*)(Args..., ...), U> : std::true_type {};
    template<typename T, typename U, typename ...Args>
    struct is_callable<T(&)(Args..., ...), U> : std::true_type {};
    template<typename T, typename U, typename ...Args>
    struct is_callable<T(Args...) const, U> : std::true_type {};
    template<typename T, typename U, typename ...Args>
    struct is_callable<T(Args...) volatile, U> : std::true_type {};
    template<typename T, typename U, typename ...Args>
    struct is_callable<T(Args...) const volatile, U> : std::true_type {};
    template<typename T, typename U, typename ...Args>
    struct is_callable<T(Args..., ...) const, U> : std::true_type {};
    template<typename T, typename U, typename ...Args>
    struct is_callable<T(Args..., ...) volatile, U> : std::true_type{};
    template<typename T, typename U, typename ...Args>
    struct is_callable<T(Args..., ...) const volatile, U> : std::true_type {};
    template<typename T, typename U, typename ...Args>
    struct is_callable<T(Args...)&, U> : std::true_type {};
    template<typename T, typename U, typename ...Args>
    struct is_callable<T(Args...) const&, U> : std::true_type{};
    template<typename T, typename U, typename ...Args>
    struct is_callable<T(Args...) volatile&, U> : std::true_type{};
    template<typename T, typename U, typename ...Args>
    struct is_callable<T(Args...) const volatile&, U> : std::true_type{};
    template<typename T, typename U, typename ...Args>
    struct is_callable<T(Args..., ...)&, U> : std::true_type {};
    template<typename T, typename U, typename ...Args>
    struct is_callable<T(Args..., ...) const&, U> : std::true_type{};
    template<typename T, typename U, typename ...Args>
    struct is_callable<T(Args..., ...) volatile&, U> : std::true_type{};
    template<typename T, typename U, typename ...Args>
    struct is_callable<T(Args..., ...) const volatile&, U> : std::true_type{};
    template<typename T, typename U, typename ...Args>
    struct is_callable<T(Args...)&&, U> : std::true_type{};
    template<typename T, typename U, typename ...Args>
    struct is_callable<T(Args...) const&&, U> : std::true_type{};
    template<typename T, typename U, typename ...Args>
    struct is_callable<T(Args...) volatile&&, U> : std::true_type{};
    template<typename T, typename U, typename ...Args>
    struct is_callable<T(Args...) const volatile&&, U> : std::true_type{};
    template<typename T, typename U, typename ...Args>
    struct is_callable<T(Args..., ...)&&, U> : std::true_type{};
    template<typename T, typename U, typename ...Args>
    struct is_callable<T(Args..., ...) const&&, U> : std::true_type{};
    template<typename T, typename U, typename ...Args>
    struct is_callable<T(Args..., ...) volatile&&, U> : std::true_type{};
    template<typename T, typename U, typename ...Args>
    struct is_callable<T(Args..., ...) const volatile&&, U> : std::true_type{};

    template<typename T>
    struct is_callable<T, int> {
    private:
        using Yes = char(&)[1];
        using No = char(&)[2];

        struct Fallback { void operator()(); };
        struct Derived : T, Fallback {};

        template<typename U, U> struct Check;

        template<typename>
        static Yes Test(...);

        template<typename C>
        static No Test(Check<void (Fallback::*)(), &C::operator()>*);

    public:
        static bool const constexpr value = sizeof(Test<Derived>(0)) == sizeof(Yes);
    };
}

#endif
