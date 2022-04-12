#ifndef MATRIX_IMPL_H
#define MATRIX_IMPL_H

namespace matrix_view {
//================================================================================================
//=============================MatrixColumnIterator===============================================
//================================================================================================
template<typename Matrix, typename InputIterator>
MatrixColumnIterator<Matrix, InputIterator>::MatrixColumnIterator(const Matrix &matrix_, InputIterator currentIter_):
    matrix(matrix_), currentIter(currentIter_)
{

}

template<typename Matrix, typename InputIterator>
MatrixColumnIterator<Matrix, InputIterator>::~MatrixColumnIterator()
{

}

template<typename Matrix, typename InputIterator>
typename InputIterator::reference MatrixColumnIterator<Matrix, InputIterator>::operator*()
{
    return *currentIter;
}

template<typename Matrix, typename InputIterator>
typename InputIterator::pointer MatrixColumnIterator<Matrix, InputIterator>::operator->()
{
    return currentIter->operator->();
}

template<typename Matrix, typename InputIterator>
typename InputIterator::reference MatrixColumnIterator<Matrix, InputIterator>::operator[](size_t n)
{
    return currentIter[n * matrix.columns()];
}

template<typename Matrix, typename InputIterator>
MatrixColumnIterator<Matrix, InputIterator> &MatrixColumnIterator<Matrix, InputIterator>::operator=(const MatrixColumnIterator &other)
{
    currentIter = other.currentIter;
    return *this;
}

template<typename Matrix, typename InputIterator>
MatrixColumnIterator<Matrix, InputIterator> &MatrixColumnIterator<Matrix, InputIterator>::operator++()
{
    currentIter += matrix.columns();
    return *this;
}

template<typename Matrix, typename InputIterator>
MatrixColumnIterator<Matrix, InputIterator> MatrixColumnIterator<Matrix, InputIterator>::operator++(int)
{
    auto temp = *this; 
    ++(*this); 
    return temp;
}

template<typename Matrix, typename InputIterator>
MatrixColumnIterator<Matrix, InputIterator> &MatrixColumnIterator<Matrix, InputIterator>::operator--()
{
    currentIter -= matrix.columns();
    return *this;
}

template<typename Matrix, typename InputIterator>
MatrixColumnIterator<Matrix, InputIterator> MatrixColumnIterator<Matrix, InputIterator>::operator--(int)
{
    auto temp = *this; 
    --(*this); 
    return temp;
}

template<typename Matrix, typename InputIterator>
std::ptrdiff_t MatrixColumnIterator<Matrix, InputIterator>::operator-(const MatrixColumnIterator &other)
{
    return (currentIter - other.currentIter) / matrix.columns();
}

template<typename Matrix, typename InputIterator>
MatrixColumnIterator<Matrix, InputIterator> &MatrixColumnIterator<Matrix, InputIterator>::operator+=(int n)
{
    currentIter += n * matrix.columns();
    return *this;
}

template<typename Matrix, typename InputIterator>
MatrixColumnIterator<Matrix, InputIterator> MatrixColumnIterator<Matrix, InputIterator>::operator+(int n)
{
    auto temp = *this;
    temp += n;
    return temp;
}

template<typename Matrix, typename InputIterator>
MatrixColumnIterator<Matrix, InputIterator> &MatrixColumnIterator<Matrix, InputIterator>::operator-=(int n)
{
    currentIter -= n * matrix.columns();
    return *this;
}

template<typename Matrix, typename InputIterator>
MatrixColumnIterator<Matrix, InputIterator> MatrixColumnIterator<Matrix, InputIterator>::operator-(int n)
{
    auto temp = *this;
    temp -= n;
    return temp;
}

template<typename Matrix, typename InputIterator>
bool MatrixColumnIterator<Matrix, InputIterator>::operator==(const MatrixColumnIterator &other)
{
    return currentIter == other.currentIter;
}

template<typename Matrix, typename InputIterator>
bool MatrixColumnIterator<Matrix, InputIterator>::operator!=(const MatrixColumnIterator &other)
{
    return currentIter != other.currentIter;
}

template<typename Matrix, typename InputIterator>
bool MatrixColumnIterator<Matrix, InputIterator>::operator<(const MatrixColumnIterator &other)
{
    return currentIter < other.currentIter;
}

template<typename Matrix, typename InputIterator>
bool MatrixColumnIterator<Matrix, InputIterator>::operator>(const MatrixColumnIterator &other)
{
    return currentIter > other.currentIter;
}

template<typename Matrix, typename InputIterator>
bool MatrixColumnIterator<Matrix, InputIterator>::operator<=(const MatrixColumnIterator &other)
{
    return currentIter <= other.currentIter;
}

template<typename Matrix, typename InputIterator>
bool MatrixColumnIterator<Matrix, InputIterator>::operator>=(const MatrixColumnIterator &other)
{
    return currentIter >= other.currentIter;
}
//================================================================================================
//=======================================MATRIX===================================================
//================================================================================================

template<typename T>
Matrix<T>::Matrix(): amountRows(0), amountColumns(0) {}

template<typename T>
Matrix<T>::Matrix(size_t amountRows_, size_t amountColumns_, T value):
    vector(amountRows_*amountColumns_, value), amountRows(amountRows_), amountColumns(amountColumns_)
{

}

template<typename T>
Matrix<T>::Matrix(std::initializer_list<T> init_list):
    vector(init_list), amountRows(1), amountColumns(init_list.size())
{

}

template<typename T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T> > init_list):
    amountRows(init_list.size()), amountColumns(0)
{
    //define max amount elements in line
    size_t max_elem = 0;
    for(auto line: init_list){
        if(max_elem < line.size())
            max_elem = line.size();
    }
    amountRows = init_list.size();
    amountColumns = max_elem;
    //copy init_list line in vector and add T() if needed
    for(auto line: init_list){
        std::copy(line.begin(), line.end(), std::back_inserter(vector));
        auto size = line.size();
        while(size != amountColumns){
            vector.push_back(T());
            ++size;
        }
    }
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T> &other):
    vector(other.vector), amountRows(other.amountRows), amountColumns(other.amountColumns)
{
   
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T> &&other) noexcept:
    vector(std::move(other.vector)), amountRows(other.amountRows), amountColumns(other.amountColumns)
{
 
}

template<typename T>
template<typename Tp>
Matrix<T>::Matrix(const Matrix<Tp> &other):
    vector(other.begin(),other.end()), amountRows(other.rows()), amountColumns(other.columns())
{

}

template<typename T>
template<typename IT>
Matrix<T>::Matrix(size_t amountRows_, size_t amountColumns_, IT first, IT last):
    vector(first, last), amountRows(amountRows_), amountColumns(amountColumns_)
{

}

template<typename T>
Matrix<T>::~Matrix() {}

template<typename T>
Matrix<T> &Matrix<T>::operator=(const Matrix<T> &other)
{
    if(this == &other)
        return *this;
    vector = other.vector;
    amountRows = other.amountRows;
    amountColumns = other.amountColumns;
    return *this;
}

template<typename T>
Matrix<T> &Matrix<T>::operator=(Matrix<T> &&other) noexcept
{
    vector = std::move(other.vector);
    amountRows = other.amountRows;
    amountColumns = other.amountColumns;
    return *this;
}

template<typename T>
inline size_t Matrix<T>::rows() const
{
    return amountRows;
}

template<typename T>
inline size_t Matrix<T>::columns() const
{
    return amountColumns;
}

template<typename T>
decltype(auto) Matrix<T>::operator()(size_t i, size_t j) const
{

    if(i >= amountRows || j >= amountColumns)
        throw std::out_of_range("Index exceeds matrix dimensions.");
    if constexpr(is_reference_wrapper_v<T>)
            return (vector[i * amountColumns + j]).get();
    else
    return (vector[i * amountColumns + j]);
}

template<typename T>
decltype(auto) Matrix<T>::operator()(size_t i, size_t j)
{
    //Scott Meyers: rule 3, add const, call operator() const and then remove const
    return const_cast<type_is_t<T>&>(static_cast<const Matrix<T>&>(*this)(i,j));
}

//slice
template<typename T>
decltype (auto) Matrix<T>::operator()(const std::string& range) const
{    
    //check is correct slice
    //(1)(end) | (1:2)(1:end) | (:)
    std::regex r{R"(((\d+|end)|(\d+:(\d+|end))|:),((\d+|end)|(\d+:(\d+|end))|:))"};
    if(!std::regex_match(range, r))
        throw std::logic_error( "slice expression is incorrect");

    auto comma = range.find_first_of(',');
    size_t rangeRow1  = 0, rangeRow2 = amountRows, rangeCol1 = 0, rangeCol2 = amountColumns;
    //parse range rows
    parseSliceExpression(range.substr(0, comma), rangeRow1, rangeRow2, amountRows);
    //parse range columns
    parseSliceExpression(range.substr(comma + 1), rangeCol1, rangeCol2, amountColumns);

    std::vector<std::reference_wrapper<const type_is_t<T>>> ref_vec;
    for(auto i = rangeRow1; i < rangeRow2; i++)
        for(auto j = rangeCol1; j < rangeCol2; j++)
            ref_vec.push_back((*this)(i,j));

    Matrix<std::reference_wrapper<const type_is_t<T>>> res(rangeRow2 - rangeRow1, rangeCol2 - rangeCol1, ref_vec.begin(), ref_vec.end());
    return res;
}

template<typename T>
decltype (auto) Matrix<T>::operator()(const std::string& range)
{

    auto m_const = static_cast<const Matrix<T>&>(*this)(range);
    std::vector<std::reference_wrapper<type_is_t<T>>> vec;

    for(auto it = m_const.begin(); it != m_const.end(); ++it){
        vec.push_back(const_cast<type_is_t<T>&>((*it).get()));
    }
    return Matrix<std::reference_wrapper<type_is_t<T>>>(m_const.rows(), m_const.columns(), vec.begin(), vec.end());
}

template<typename T>
auto Matrix<T>::begin()
{
    return vector.begin();
}

template<typename T>
auto Matrix<T>::end()
{
    return vector.end();
}

template<typename T>
auto Matrix<T>::begin() const
{
    return vector.begin();
}

template<typename T>
auto Matrix<T>::end() const
{
    return vector.end();
}

template<typename T>
auto Matrix<T>::cbegin() const
{
    return vector.begin();
}

template<typename T>
auto Matrix<T>::cend() const
{
    return vector.end();
}

template<typename T>
auto Matrix<T>::begin_row(size_t n)
{
    return vector.begin()+ columns() * n;
}

template<typename T>
auto Matrix<T>::end_row(size_t n)
{
    return vector.begin()+ columns() * (n + 1);
}

template<typename T>
auto Matrix<T>::begin_row(size_t n) const
{
    return vector.begin()+ columns() * n;
}

template<typename T>
auto Matrix<T>::end_row(size_t n) const
{
    return vector.begin()+ columns() * (n + 1);
}

template<typename T>
auto Matrix<T>::cbegin_row(size_t n) const
{
    return vector.begin()+ columns() * n;
}

template<typename T>
auto Matrix<T>::cend_row(size_t n) const
{
    return vector.begin()+ columns() * (n + 1);
}

template<typename T>
auto Matrix<T>::begin_column(size_t n)
{
    return MatrixColumnIterator{*this, vector.begin()+ n};
}

template<typename T>
auto Matrix<T>::end_column(size_t n)
{
    return MatrixColumnIterator{*this, vector.begin() + n + columns()* rows()};
}

template<typename T>
auto Matrix<T>::begin_column(size_t n) const
{
    return MatrixColumnIterator{*this, vector.begin()+ n};
}

template<typename T>
auto Matrix<T>::end_column(size_t n) const
{
    return MatrixColumnIterator{*this, vector.begin() + n + columns()* rows()};
}

template<typename T>
auto Matrix<T>::cbegin_column(size_t n) const
{
    return MatrixColumnIterator{*this, vector.begin()+ n};
}

template<typename T>
auto Matrix<T>::cend_column(size_t n) const
{
    return MatrixColumnIterator{*this, vector.begin() + n + columns()* rows()};
}

template<typename T>
T Matrix<T>::det() const {
    T det = 0;
    int degree = 1;
    if(amountRows != amountColumns)
        throw std::length_error("matrix must be square");
    if(amountRows == 1)
        return (*this)(0,0);
    if(amountRows == 2)
        return (*this)(0,0) * (*this)(1,1) - (*this)(0,1) * (*this)(1,0);
    for(size_t j = 0; j < amountColumns; j++)
    {
        Matrix<T> m(amountRows - 1, amountColumns - 1);
        for(size_t _i = 1; _i< amountRows; _i++){
            for(size_t _j = 0, t = 0; _j< amountColumns; _j++){
                if(_j != j)
                {
                    m(_i-1,t) = (*this)(_i,_j);
                    t++;
                }
            }
        }
        det = det + degree * (*this)(0,j) * m.det();
        degree = -degree;
    }
    return det;
}

template<typename T>
Matrix<T> Matrix<T>::dot(const Matrix &other) const
{
    if(amountColumns != other.amountRows)
        throw std::length_error("Inner matrix dimensions must agree");
    Matrix<T> res(amountRows, other.amountColumns);
    for(size_t i = 0;i< amountRows;i++)
        for(size_t j = 0;j< other.amountColumns; j++)
        {
            T sum = 0;
            for(size_t k = 0;k < amountColumns;k++)
            {
                sum+=(*this)(i,k)*other(k,j);
            }
            res(i,j) = sum;
        }

    return res;
}

template<typename T>
void Matrix<T>::transpose()
{
    std::vector<int> vec(vector);
    for(size_t i = 0; i < amountRows; ++i){
        for(size_t j = 0; j < amountColumns; ++j){
            size_t k = i*amountColumns + j;
            size_t n = j*amountRows + i;
            vector[n] = vec[k];
        }
    }
    std::swap(amountRows, amountColumns);
}

template <typename T>
template <typename Item, typename Operation>
Matrix<T> &Matrix<T>::doOperItself(const Item &item, Operation oper)
{

    if constexpr(is_matrix_v<Item>){
        if(rows() != item.rows() || columns() != item.columns())
            throw std::runtime_error("Matrix dimensions must agree");
        auto it = item.begin();
        for(size_t i = 0; i < vector.size(); ++i)
            oper(vector[i],*(it++));
    }
    else {
        for(size_t i = 0; i < vector.size(); ++i)
            oper(vector[i],item);
    }
    return *this;
}

template<typename T>
template <typename Item>
Matrix<T>& Matrix<T>::operator=(const Item &item)
{
    return this->doOperItself(item, equal<T, type_is_t<Item>>);
}

template<typename T>
template <typename Item>
Matrix<T>& Matrix<T>::operator+=(const Item &item)
{
    return this->doOperItself(item, plus<T, type_is_t<Item>>);
}

template<typename T>
template <typename Item>
Matrix<T>& Matrix<T>::operator-=(const Item &item)
{
    return this->doOperItself(item, minus<T, type_is_t<Item>>);
}

template<typename T>
template <typename Item>
Matrix<T>& Matrix<T>::operator/=(const Item &item)
{
    return this->doOperItself(item, divides<T, type_is_t<Item>>);
}

template<typename T>
template <typename Item>
Matrix<T>& Matrix<T>::operator*=(const Item &item)
{
    return this->doOperItself(item, multiplies<T, type_is_t<Item>>);
}

template<typename T>
template <typename Tp>
bool Matrix<T>::operator==(const Matrix<Tp>& other)
{
    if(rows() != other.rows() || columns() != other.columns())
        return false;

    auto it1 = begin();
    auto it2 = other.begin();

    while(it1 != end()){
        if(*(it1++) != *(it2++))
            return false;
    }

    return true;
}

template<typename T>
template <typename Tp>
bool Matrix<T>::operator!=(const Matrix<Tp>& other)
{
    return !this->operator==(other);
}


//-----------private helper function--------------
//static
template<typename T>
void Matrix<T>::parseSliceExpression(const std::string &expr, size_t &range1,
                                     size_t &range2, const size_t &end)
{
    auto colon = expr.find(":");
    //TODO: replace string on string_view
    //if there's no colon (1 number for range (n) or (end) )
    if(colon == std::string::npos){
        if(expr.find("end") != std::string::npos)
            range1 = end - 1;
        else
            range1 = atoi(expr.data());
        range2 = range1 + 1;
    }
    //if colon not 0 position, there's have two numbers (n:n) or (n:end)
    else if(colon != 0){
        std::string leftSubstr = expr.substr(0, colon);
        range1 = atoi(leftSubstr.data());
        std::string rightSubstr = expr.substr(colon + 1);
        if(rightSubstr.find("end") != std::string::npos)
            range2 = end;
        else
            range2 = atoi(rightSubstr.data());
    }
    //else if colon have 0 position (:), range stay default (all range)
}

//================================================================================================
//====================================not member functions========================================
//================================================================================================
//Concatenate arrays along specified dimension
//dim = 1 - vertical, 2 - horizontal;
template <typename T, typename U>
Matrix<type_is_t<T>> cat(size_t dim,const Matrix<T>& matrix1, const Matrix<U>& matrix2)
{
    if(dim != 1 && dim != 2)
        throw std::logic_error("wrong dimesion");

    if(dim == 1){
        if(matrix1.columns() != matrix2.columns())
            throw std::logic_error("cat arguments dimensions are not consistent.");
        std::vector<type_is_t<T>> vec;
        std::copy(matrix1.begin(), matrix1.end(), std::back_inserter(vec));
        std::copy(matrix2.begin(), matrix2.end(), std::back_inserter(vec));
        return Matrix<type_is_t<T>>(matrix1.rows() + matrix2.rows(), matrix1.columns(),
                                    vec.begin(), vec.end());
    }
    else{
        if(matrix1.rows() != matrix2.rows())
            throw std::logic_error("conarguments dimensions are not consistent.");
        std::vector<type_is_t<T>> vec;
        for(size_t i = 0; i < matrix1.rows(); ++i){
            std::copy(matrix1.begin_row(i), matrix1.end_row(i), std::back_inserter(vec));
            std::copy(matrix2.begin_row(i), matrix2.end_row(i), std::back_inserter(vec));
        }
        return Matrix<type_is_t<T>>(matrix1.rows(), matrix1.columns() + matrix2.columns(),
                                    vec.begin(), vec.end());
    }
}

//do Operation on Matrix(arithmetic Type) and Matrix(arithmetic type)
//+++++++++++++++++++++++++++++++
template <typename T, typename U>
inline std::enable_if_t<is_matrix_v<T>, Matrix<type_is_t<T>>> operator+(T t, U u)
{
    Matrix<type_is_t<T>> res(t);
    res+=u;
    return res;
}

template <typename T, typename U>
inline std::enable_if_t<std::is_arithmetic_v<T> & is_matrix_v<U>,Matrix<type_is_t<T>>> operator+(T t, U u)
{
    Matrix<type_is_t<T>> res(u.rows(), u.columns(), t);
    res+=u;
    return res;
}

//-------------------------------
template <typename T, typename U>
inline std::enable_if_t<is_matrix_v<T>, Matrix<type_is_t<T>>> operator-(T t, U u)
{
    Matrix<type_is_t<T>> res(t);
    res-=u;
    return res;
}

template <typename T, typename U>
inline std::enable_if_t<std::is_arithmetic_v<T> & is_matrix_v<U>,Matrix<type_is_t<T>>> operator-(T t, U u)
{
    Matrix<type_is_t<T>> res(u.rows(), u.columns(), t);
    res-=u;
    return res;
}

/*////////////////////////////////*/
template <typename T, typename U>
inline std::enable_if_t<is_matrix_v<T>, Matrix<type_is_t<T>>> operator/(T t, U u)
{
    Matrix<type_is_t<T>> res(t);
    res/=u;
    return res;
}

template <typename T, typename U>
inline std::enable_if_t<std::is_arithmetic_v<T> & is_matrix_v<U>,Matrix<type_is_t<T>>> operator/(T t, U u)
{
    Matrix<type_is_t<T>> res(u.rows(), u.columns(), t);
    res/=u;
    return res;
}

//*********************************
template <typename T, typename U>
inline std::enable_if_t<is_matrix_v<T>, Matrix<type_is_t<T>>> operator*(T t, U u)
{
    Matrix<type_is_t<T>> res(t);
    res*=u;
    return res;
}

template <typename T, typename U>
inline std::enable_if_t<std::is_arithmetic_v<T> & is_matrix_v<U>,Matrix<type_is_t<T>>> operator*(T t, U u)
{
    Matrix<type_is_t<T>> res(u.rows(), u.columns(), t);
    res*=u;
    return res;
}

template <typename T, typename UnaryOperation>
Matrix<type_is_t<T>> doUnaryOperation(const Matrix<T>& matrix, UnaryOperation oper)
{
    std::vector<type_is_t<T>> vec;
    for(auto it = matrix.begin(); it != matrix.end(); ++it)
        vec.push_back(oper(*it));
    return Matrix<type_is_t<T>>(matrix.rows(), matrix.columns(), vec.begin(), vec.end());
}

template <typename T>
inline auto operator-(const Matrix<T>& matrix){
    return 0 - matrix;
}

template <typename T>
inline auto acos(const Matrix<T>& matrix)
{
    return doUnaryOperation(matrix,std::acos<type_is_t<T>>);
}

template <typename T>
inline auto asin(const Matrix<T>& matrix)
{
    return doUnaryOperation(matrix,std::asin<type_is_t<T>>);
}

template <typename T>
inline auto atan(const Matrix<T>& matrix)
{
    return doUnaryOperation(matrix,std::atan<type_is_t<T>>);
}

template <typename T>
inline auto atan2(const Matrix<T>& matrix_y, const Matrix<T>& matrix_x)
{
    if(matrix_y.rows() != matrix_x.rows() || matrix_y.columns() != matrix_x.item.columns())
        throw std::runtime_error("Matrix dimensions must agree");
    std::vector<type_is_t<T>> vec;
    auto it_y = matrix_y.begin();
    auto it_x = matrix_x.begin();
    while(it_y != matrix_y.end())
        vec.push_back(std::atan2(*(it_y++), *(it_x++)));
    return Matrix<type_is_t<T>>(matrix_y.rows(), matrix_y.columns(), vec.begin(), vec.end());
}

template <typename T>
inline auto cos(const Matrix<T>& matrix)
{
    return doUnaryOperation(matrix,std::cos<type_is_t<T>>);
}

template <typename T>
inline auto sin(const Matrix<T>& matrix)
{
    return doUnaryOperation(matrix,std::sin<type_is_t<T>>);
}

template <typename T>
inline auto tan(const Matrix<T>& matrix)
{
    return doUnaryOperation(matrix,std::tan<type_is_t<T>>);
}

template <typename T>
inline auto exp(const Matrix<T>& matrix)
{
    return doUnaryOperation(matrix,std::exp<type_is_t<T>>);
}

template <typename T>
inline auto sqrt(const Matrix<T>& matrix)
{
    return doUnaryOperation(matrix,std::sqrt<type_is_t<T>>);
}

template <typename T>
inline auto abs(const Matrix<T>& matrix)
{
    return doUnaryOperation(matrix,std::fabs<type_is_t<T>>);
}

template <typename T>
inline auto ceil(const Matrix<T>& matrix)
{
    return doUnaryOperation(matrix,std::ceil<type_is_t<T>>);
}

template <typename T>
inline auto floor(const Matrix<T>& matrix)
{
    return doUnaryOperation(matrix,std::floor<type_is_t<T>>);
}

template <typename T, typename U>
inline auto pow(const Matrix<T>& matrix, U up)
{
    return doUnaryOperation(matrix,std::bind(std::pow<type_is_t<T>>, std::placeholders::_1, up));
}

//-----------------Create matrix-------------------
template <typename T>
inline Matrix<T> make_random_matrix(size_t rows, size_t columns, int min, int max)
{
    //TODO: srand doesn't work, if call this function twice or more times
    srand(time(0));

    Matrix<T> m(rows, columns);

    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < columns; j++){
            m(i, j) = rand() % (max - min) + min;
        }
    }
    return m;
}

template <typename T>
inline Matrix<T> make_ones_matrix(size_t rows, size_t columns)
{
    return Matrix<T>(rows, columns, 1);
}

template <typename T>
inline Matrix<T> make_zeros_matrix(size_t rows, size_t columns)
{
    return Matrix<T>(rows, columns);
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const Matrix<T> &matrix){
    for(size_t i = 0; i < matrix.rows(); ++i){
        for(size_t j = 0; j < matrix.columns(); ++j)
            std::cout << std::setw(5) << matrix(i,j);
        std::cout << std::endl;
    }

    return os;
}

}
#endif // MATRIX_IMPL_H
