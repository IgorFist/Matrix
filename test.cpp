#define BOOST_TEST_MODULE test_matrix_module

#include <matrix.h>

#include <vector>
#include <algorithm>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_matrix)

BOOST_AUTO_TEST_CASE(check_init_default_matrix)
{
    matrix_view::Matrix<int> matr;
    BOOST_CHECK(matr.rows() == 0);
    BOOST_CHECK(matr.columns() == 0);
}

BOOST_AUTO_TEST_CASE(check_init_matrix_value)
{
    matrix_view::Matrix<int> matr(3, 4, 7);
    std::vector<int> vec(12, 7);
    BOOST_CHECK(matr.rows() == 3);
    BOOST_CHECK(matr.columns() == 4);
    BOOST_CHECK_EQUAL_COLLECTIONS(matr.begin(), matr.end(), vec.begin(), vec.end());
}

BOOST_AUTO_TEST_CASE(check_init_matrix_init_list)
{
    
    matrix_view::Matrix<int> m{{1,2,4,5},
                                {6,7,9,-2},
                                {-5,6,-9,3}};

    const int n = 3, k = 4;

    int arr[n][k] = {{1,2,4,5},
                     {6,7,9,-2},
                     {-5,6,-9,3}};

    BOOST_CHECK(m.rows() == 3);
    BOOST_CHECK(m.columns() == 4);

    for(int i = 0; i < 3; ++i)
        for(int j = 0; j < 4; ++j)
            BOOST_CHECK(m(i,j) == arr[i][j]);
}

BOOST_AUTO_TEST_CASE(check_copy_constructor)
{
    matrix_view::Matrix<int> m1{{1,2,4},
                                {6,7,9},
                                {-5,6,-9}};
    auto m2(m1);

    BOOST_CHECK(m1.rows() == m2.rows());
    BOOST_CHECK(m1.columns() == m2.columns());
    BOOST_CHECK_EQUAL_COLLECTIONS(m1.begin(), m1.end(), m2.begin(), m2.end());        
}

BOOST_AUTO_TEST_CASE(check_move_constructor)
{
    matrix_view::Matrix<int> m1{{1,2,4},
                                {6,7,9},
                                {-5,6,-9}};
    auto m2(std::move(matrix_view::Matrix<int>{{1,2,4},
                                {6,7,9},
                                {-5,6,-9}}));

    BOOST_CHECK(m1.rows() == m2.rows());
    BOOST_CHECK(m1.columns() == m2.columns());
    BOOST_CHECK_EQUAL_COLLECTIONS(m1.begin(), m1.end(), m2.begin(), m2.end());        
}

BOOST_AUTO_TEST_CASE(check_init_matrix_other_type)
{
    matrix_view::Matrix<double> m1{{1,2,4},
                                {6,7,9},
                                {-5,6,-9}};

    matrix_view::Matrix<int>  m2(m1);

    BOOST_CHECK(m1.rows() == m2.rows());
    BOOST_CHECK(m1.columns() == m2.columns());
    BOOST_CHECK_EQUAL_COLLECTIONS(m1.begin(), m1.end(), m2.begin(), m2.end());         
}

BOOST_AUTO_TEST_CASE(check_row_iterators)
{
 
    matrix_view::Matrix<int> m{{1,2,4,5},
                               {6,7,9,-2},
                               {-5,6,-9,3}};

    std::vector<int> row_0 = {1,2,4,5};
    std::vector<int> row_1 = {6,7,9,-2};
    std::vector<int> row_2 = {-5,6,-9,3};

    BOOST_CHECK_EQUAL_COLLECTIONS(m.begin_row(0), m.end_row(0), row_0.begin(), row_0.end()); 
    BOOST_CHECK_EQUAL_COLLECTIONS(m.begin_row(1), m.end_row(1), row_1.begin(), row_1.end()); 
    BOOST_CHECK_EQUAL_COLLECTIONS(m.begin_row(2), m.end_row(2), row_2.begin(), row_2.end()); 

}

BOOST_AUTO_TEST_CASE(check_column_iterators)
{
 
    matrix_view::Matrix<int> m{{1,2,4,5},
                               {6,7,9,-2},
                               {-5,6,-9,3}};

    std::vector<int> column_0 = {1,6,-5};
    std::vector<int> column_1 = {2,7,6};
    std::vector<int> column_2 = {4,9,-9};
    std::vector<int> column_3 = {5,-2,3};

    BOOST_CHECK_EQUAL_COLLECTIONS(m.begin_column(0), m.end_column(0), column_0.begin(), column_0.end()); 
    BOOST_CHECK_EQUAL_COLLECTIONS(m.begin_column(1), m.end_column(1), column_1.begin(), column_1.end()); 
    BOOST_CHECK_EQUAL_COLLECTIONS(m.begin_column(2), m.end_column(2), column_2.begin(), column_2.end()); 

}

BOOST_AUTO_TEST_CASE(check_iterators_work_with_stl_algorithms)
{
    matrix_view::Matrix<int> m1{{1,2,4,5},
                                {6,7,9,-2},
                                {-5,6,-9,3}};
    auto m2(m1);
    
    std::vector<int> sortRow_2 = {-9,-5,3,6};
    std::vector<int> sortColumn_2 = {-9, 4,9};

    std::sort(m1.begin_row(2), m1.end_row(2));
    std::sort(m2.begin_column(2), m2.end_column(2));

    BOOST_CHECK_EQUAL_COLLECTIONS(m1.begin_row(2), m1.end_row(2), sortRow_2.begin(), sortRow_2.end()); 
    BOOST_CHECK_EQUAL_COLLECTIONS(m2.begin_column(2), m2.end_column(2), sortColumn_2.begin(), sortColumn_2.end()); 
    
}

BOOST_AUTO_TEST_CASE(check_throw_exception_out_of_range)
{
    matrix_view::Matrix<int> m{{1,2,4,5},
                               {6,7,9,-2},
                               {-5,6,-9,3}};

    BOOST_CHECK_THROW(m(4,1), std::out_of_range);
    BOOST_CHECK_THROW(m(1,5), std::out_of_range);

}

BOOST_AUTO_TEST_CASE(check_get_slice_matrix)
{
    matrix_view::Matrix<int> m{{1,2,4,5},
                               {6,7,9,-2},
                               {-5,6,-9,3}};

    auto m_slice = m("0:2,1:3");

    matrix_view::Matrix<int> m1{{2,4},
                                {7,9}};

    BOOST_CHECK(m1 == m_slice);   
}

BOOST_AUTO_TEST_CASE(check_get_slice_matrix_and_assignment)
{
    matrix_view::Matrix<int> m{{1,2,4,5},
                               {6,7,9,-2},
                               {-5,6,-9,3}};

    auto m_slice = m("0:2,1:3");
    m_slice(0,0) = 99;
    m_slice(0,1) = 77;
    m_slice(1,0) = 88;
    m_slice(1,1) = 33;

    const matrix_view::Matrix<int> m1{{1,99,77,5},
                                      {6,88,33,-2},
                                      {-5,6,-9,3}};

    BOOST_CHECK(m == m1);   
}

BOOST_AUTO_TEST_CASE(check_operation_itself_and_number)
{
    matrix_view::Matrix<int> m{{1,2,4,5},
                            {6,7,9,-2},
                            {-5,6,-9,3}};
    
    std::vector<int> vec(m.begin(), m.end());
    std::transform(vec.begin(), vec.end(), vec.begin(), [](auto item){ return item + 3;});
    m += 3;
    BOOST_CHECK_EQUAL_COLLECTIONS(m.begin(), m.end(), vec.begin(), vec.end()); 

    std::transform(vec.begin(), vec.end(), vec.begin(), [](auto item){ return item - 5;});
    m -= 5;
    BOOST_CHECK_EQUAL_COLLECTIONS(m.begin(), m.end(), vec.begin(), vec.end()); 

    std::transform(vec.begin(), vec.end(), vec.begin(), [](auto item){ return item * 6;});
    m *= 6;
    BOOST_CHECK_EQUAL_COLLECTIONS(m.begin(), m.end(), vec.begin(), vec.end()); 

    std::transform(vec.begin(), vec.end(), vec.begin(), [](auto item){ return item / 2;});
    m /= 2;
    BOOST_CHECK_EQUAL_COLLECTIONS(m.begin(), m.end(), vec.begin(), vec.end()); 
}

BOOST_AUTO_TEST_CASE(check_arithmetic_operation_itself_and_matrix)
{
    matrix_view::Matrix<int> m1{{1,2,4,5},
                            {6,7,9,-2},
                            {-5,6,-9,3}};
    
    matrix_view::Matrix<int>m2{{3,6,7,1},
                               {4,2,5,3},
                               {2,6,7,1}};

    std::vector<int> vec1(m1.begin(), m1.end());
    std::vector<int> vec2(m2.begin(), m2.end());

    std::transform(vec1.begin(), vec1.end(), vec2.begin(), vec1.begin(), std::plus<int>());
    m1 += m2;
    BOOST_CHECK_EQUAL_COLLECTIONS(m1.begin(), m1.end(), vec1.begin(), vec1.end()); 

    std::transform(vec1.begin(), vec1.end(), vec2.begin(), vec1.begin(), std::minus<int>());
    m1 -= m2;
    BOOST_CHECK_EQUAL_COLLECTIONS(m1.begin(), m1.end(), vec1.begin(), vec1.end()); 

    std::transform(vec1.begin(), vec1.end(), vec2.begin(), vec1.begin(), std::multiplies<int>());
    m1 *= m2;
    BOOST_CHECK_EQUAL_COLLECTIONS(m1.begin(), m1.end(), vec1.begin(), vec1.end()); 

    std::transform(vec1.begin(), vec1.end(), vec2.begin(), vec1.begin(), std::divides<int>());
    m1 /= m2;
    BOOST_CHECK_EQUAL_COLLECTIONS(m1.begin(), m1.end(), vec1.begin(), vec1.end()); 
}

BOOST_AUTO_TEST_CASE(check_arithmetic_operation)
{
        matrix_view::Matrix<int> m1{{1,2,4,5},
                                    {6,7,9,-2},
                                    {-5,6,-9,3}};
    
    matrix_view::Matrix<int>m2{{3,6,7,1},
                               {4,2,5,3},
                               {2,6,7,1}};

    std::vector<int> vec1(m1.begin(), m1.end());
    std::vector<int> vec2(m2.begin(), m2.end());

    auto m3 = 2 - (sqrt(m1 * m1) + 3 * m2 + m2 / 5);

    std::vector<int> vec3;
    
    std::transform(vec1.begin(), vec1.end(), vec2.begin(), std::back_inserter(vec3), 
    [](int item1, int item2){
        return 2 - (sqrt(item1 * item1) + 3 * item2 + item2 / 5);
    });

    BOOST_CHECK(m3.rows() == 3);
    BOOST_CHECK(m3.columns() == 4);
    BOOST_CHECK_EQUAL_COLLECTIONS(m3.begin(), m3.end(), vec3.begin(), vec3.end()); 
}

BOOST_AUTO_TEST_SUITE_END()