#ifndef HELPER_H
#define HELPER_H

#include <type_traits>

namespace matrix_view{

template<typename T>
class Matrix;

//---------------------Helper traits structures----------------
//type traits
//is_matrix
template <typename T>
struct is_matrix{
    static const bool value = false;
};

template <typename T>
struct is_matrix<Matrix<T>>{
    static const bool value = true;
};


//is_reference_wrapper
template <typename T>
struct is_reference_wrapper{
    static const bool value = false;
};

template <typename T>
struct is_reference_wrapper<std::reference_wrapper<T>>{
    static const bool value = true;
};

template <typename T>
struct type_is{
    using type = T;
};

template <typename T>
struct type_is<std::reference_wrapper<T>>{
    using type = T;
};

template <typename T>
struct type_is<Matrix<T>>{
    using type = T;
};

template <typename T>
struct type_is<Matrix<std::reference_wrapper<T>>>{
    using type = T;
};

//value is_matrix
template <typename T>
inline constexpr bool is_matrix_v = is_matrix<T>::value;

//value is_reference_wrapper
template <typename T>
inline constexpr bool is_reference_wrapper_v = is_reference_wrapper<T>::value;

//inner type T
template <typename T>
using type_is_t = typename type_is<T>::type;

//---------------------Helper arithmetic function----------------
template <typename Tp, typename U>
inline std::enable_if_t<is_reference_wrapper_v<Tp>> equal(Tp& t, const U& u)
{
  t.get() = u;
};

template <typename Tp, typename U>
inline std::enable_if_t<std::is_arithmetic_v<Tp>> equal(Tp& t, const U& u)
{
  t = u;
};

template <typename Tp, typename U>
inline void plus(Tp& t,const U& u)
{
    t+=u;
}

template <typename Tp, typename U>
inline void minus(Tp& t,const U& u)
{
    t-=u;
}

template <typename Tp, typename U>
inline void divides(Tp& t,const U& u)
{
    t/=u;
}

template <typename Tp, typename U>
inline void multiplies(Tp& t,const U& u)
{
    t*=u;
}

}
#endif // HELPER_H
