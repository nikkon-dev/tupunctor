#include <iostream>
#include <utility>
#include <tuple>
#include "tupunctor.h"

using namespace std;
using namespace NTupunctor;

template <size_t _Depth, class _R, class _F, class _Tup>
struct Explode {
    template <class ... _Args>
    inline static _R call(_F&& func, _Tup&& tup, _Args&& ... args) {
        return Explode<_Depth - 1, _R, _F, _Tup>::call(
            std::forward<_F>(func),
            std::forward<_Tup>(tup),
            get<_Depth - 1>(std::forward<_Tup>(tup)),
            std::forward<_Args>(args)...);
    }
};

template <class _R, class _F, class _Tup>
struct Explode<0, _R, _F, _Tup> {
    template <class ... _Args>
    inline static _R call(_F&& func, _Tup&& tup, _Args&& ... args) {
        return func(std::forward<_Args>(args)...);
    }
};

template <class _F, class ... _Args>
inline auto explode(_F&& func, const std::tuple<_Args...>& tup) -> typename result_of<_F(_Args...)>::type
{
    return Explode<
        sizeof...(_Args),
        typename result_of<_F(_Args...)>::type,
        _F,
        const std::tuple<_Args...>& >::call(func, tup);
}

template <class _F, class ... _Args>
inline auto explode(_F&& func, _Args&& ... args) -> typename result_of<_F(_Args...)>::type
{
    return explode(std::forward<_F>(func), make_tuple(std::forward<_Args>(args)...));
}

int test(int, double, const char*){
    cout << "int test(int, double, const char*)" << endl;
    return -1;
}

int main() {
    auto t = make_tuple(10, 0.1, "hello");
    cout << explode(test, t) << endl;
    cout << explode(test, 10, 0.1, "hello") << endl;;
}
