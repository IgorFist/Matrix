#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include <iomanip>
#include <iterator>
#include <regex>
#include <cmath>
#include <functional>

#include <Matrix/helper.h>


namespace  matrix_view{

//--------------------------------------------------------------------------------
template<typename Matrix, typename InputIterator>
class MatrixColumnIterator: public std::iterator<std::random_access_iterator_tag,typename InputIterator::value_type>{

    static_assert(std::is_same_v<typename InputIterator::iterator_category,
    std::random_access_iterator_tag>,"Container must have random access iterator");

public:

    MatrixColumnIterator(const Matrix& matrix_, InputIterator currentIter_);
    ~MatrixColumnIterator();

    typename InputIterator::reference operator*();
    typename InputIterator::pointer   operator->();
    typename InputIterator::reference operator[](size_t n);

    MatrixColumnIterator& operator=(const MatrixColumnIterator& other);
    MatrixColumnIterator& operator++();
    MatrixColumnIterator operator++(int);
    MatrixColumnIterator& operator--();
    MatrixColumnIterator operator--(int);
    std::ptrdiff_t operator-(const MatrixColumnIterator &other);
    MatrixColumnIterator& operator+=(int n);
    MatrixColumnIterator operator+(int n);
    MatrixColumnIterator& operator-=(int n);
    MatrixColumnIterator operator-(int n);

    bool operator==(const MatrixColumnIterator& other);
    bool operator!=(const MatrixColumnIterator& other);
    bool operator<(const MatrixColumnIterator& other);
    bool operator>(const MatrixColumnIterator& other);
    bool operator<=(const MatrixColumnIterator& other);
    bool operator>=(const MatrixColumnIterator& other);

private:
    const Matrix &matrix;
    InputIterator currentIter;
};

//-----------------------------MATRIX-----------------------------------------
template<typename T>
class Matrix{
public:
    //T value must be arithmetic
    static_assert (std::is_arithmetic_v<type_is_t<T>>, "Type must be arithmetic");

    using value_type = T;
    using reference = T&;
    using const_reference = const T&;

    Matrix();
    Matrix(size_t amountRows_, size_t amountColumns_, T value = T());
    Matrix(std::initializer_list<T> init_list);
    Matrix(std::initializer_list<std::initializer_list<T>> init_list);
    Matrix(const Matrix<T> &other);
    Matrix(const Matrix<T>&& other) noexcept;
    template<typename Tp>
    Matrix(const Matrix<Tp> &other);
    template<typename IT>
    Matrix(size_t amountRows_, size_t amountColumns_, IT first, IT last);
    ~Matrix();

    Matrix &operator=(const Matrix &other);
    Matrix &operator=(Matrix &&other) noexcept;

    size_t rows() const;
    size_t columns() const;

    //access to elements
    decltype(auto) operator()(size_t i,size_t j) const;
    decltype(auto) operator()(size_t i, size_t j);
    //slice matrix
    decltype (auto) operator()(const std::string& range) const;
    decltype (auto) operator()(const std::string& range);

    //vector's iterators
    auto begin();
    auto end();
    auto begin() const;
    auto end() const;
    auto cbegin() const;
    auto cend() const;

    //row iterators, n - number of row
    auto begin_row(size_t n);
    auto end_row(size_t n);
    auto begin_row(size_t n) const;
    auto end_row(size_t n) const;
    auto cbegin_row(size_t n) const;
    auto cend_row(size_t n) const;

    //column iterators, n - number of column
    auto begin_column(size_t n);
    auto end_column(size_t n);
    auto begin_column(size_t n) const;
    auto end_column(size_t n) const;
    auto cbegin_column(size_t n) const;
    auto cend_column(size_t n) const;

    //Linear algebra
    //determinant
    T det() const;
    //matrix multiplies
    Matrix dot(const Matrix &other) const;
    //transpose
    void transpose();

    //do operation itself
    template <typename Item, typename Operation>
    Matrix &doOperItself(const Item &item, Operation oper);

    //Arithmetic operations
    template <typename Item>
    Matrix& operator=(const Item &item);
    template <typename Item>
    Matrix& operator+=(const Item &item);
    template <typename Item>
    Matrix& operator-=(const Item &item);
    template <typename Item>
    Matrix& operator/=(const Item &item);
    template <typename Item>
    Matrix& operator*=(const Item &item);

    //logic operations
    template <typename Tp>
    bool operator==(const Matrix<Tp>& other);
    template <typename Tp>
    bool operator!=(const Matrix<Tp>& other);


private:
    //parse rangeExpression
    static void parseSliceExpression(const std::string &str, size_t &range1,
                                     size_t &range2,const size_t &end);
private:
    std::vector<T> vector;
    size_t amountRows;
    size_t amountColumns;
};



//-------------------------not member functions-----------------------------------------
//do poperation on Matrix and arithmeric type (Matrix)
//++++++++++++++++++++++++++++++++++++++++++++++++++++++
//if left type is Matrix, right Matrix or arithmetic type
template <typename T, typename U>
inline std::enable_if_t<is_matrix_v<T>, Matrix<type_is_t<T>>> operator+(T t, U u);
//if left type is arithmetic type, right is Matrix
template <typename T, typename U>
inline std::enable_if_t<std::is_arithmetic_v<T> & is_matrix_v<U>,Matrix<type_is_t<T>>> operator+(T t, U u);

//--------------------------------------------------------
//if left type is Matrix, right Matrix or arithmetic type
template <typename T, typename U>
inline std::enable_if_t<is_matrix_v<T>, Matrix<type_is_t<T>>> operator-(T t, U u);
//if left type is arithmetic type, right is Matrix
template <typename T, typename U>
inline std::enable_if_t<std::is_arithmetic_v<T> & is_matrix_v<U>,Matrix<type_is_t<T>>> operator-(T t, U u);

/*/////////////////////////////////////////////////////////*/
//if left type is Matrix, right type is Matrix or arithmetic type
template <typename T, typename U>
inline std::enable_if_t<is_matrix_v<T>, Matrix<type_is_t<T>>> operator/(T t, U u);
//if left type is arithmetic type, right Matrix
template <typename T, typename U>
inline std::enable_if_t<std::is_arithmetic_v<T> & is_matrix_v<U>,Matrix<type_is_t<T>>> operator/(T t, U u);

//************************************************************
//if left type is Matrix, right Matrix or arithmetic type
template <typename T, typename U>
inline std::enable_if_t<is_matrix_v<T>, Matrix<type_is_t<T>>> operator*(T t, U u);
//if left type is arithmetic type, right is Matrix
template <typename T, typename U>
inline std::enable_if_t<std::is_arithmetic_v<T> & is_matrix_v<U>,Matrix<type_is_t<T>>> operator*(T t, U u);

template <typename T, typename UnaryOperation>
Matrix<type_is_t<T>> doUnaryOperation(const Matrix<T>& matrix, UnaryOperation oper);

template <typename T>
inline auto operator-(const Matrix<T>& matrix);

template <typename T>
inline auto acos(const Matrix<T>& matrix);

template <typename T>
inline auto asin(const Matrix<T>& matrix);

template <typename T>
inline auto atan(const Matrix<T>& matrix);

template <typename T>
inline auto atan2(const Matrix<T>& matrix_y, const Matrix<T>& matrix_x);
template <typename T>
inline auto cos(const Matrix<T>& matrix);

template <typename T>
inline auto sin(const Matrix<T>& matrix);

template <typename T>
inline auto tan(const Matrix<T>& matrix);

template <typename T>
inline auto exp(const Matrix<T>& matrix);

template <typename T>
inline auto sqrt(const Matrix<T>& matrix);

template <typename T>
inline auto abs(const Matrix<T>& matrix);

template <typename T>
inline auto ceil(const Matrix<T>& matrix);

template <typename T>
inline auto floor(const Matrix<T>& matrix);

template <typename T, typename U>
inline auto pow(const Matrix<T>& matrix, U up);

//------------------Create Matrix----------------------
template <typename T>
Matrix<T> make_random_matrix(size_t rows, size_t columns, int min, int max);

template <typename T>
Matrix<T> make_ones_matrix(size_t rows, size_t columns);

template <typename T>
Matrix<T> make_zeros_matrix(size_t rows, size_t columns);

//-----------output matrix to ostream
template<typename T>
std::ostream &operator<<(std::ostream &os, const Matrix<T> &matrix);



}

#include <Matrix/matrix_impl.h>

#endif // MATRIX_H
