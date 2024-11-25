#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
	ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}
TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
	ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}
TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
	ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}
TEST(TDynamicMatrix, can_create_copied_matrix)
{
	TDynamicMatrix<int> m(5);

	ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}
TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
	const int size = 10;
	TDynamicMatrix<int> tmp(size);
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			tmp[i][j] = j;
	TDynamicMatrix<int> tmp_(tmp);
	EXPECT_EQ(tmp, tmp_);
}
TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	const int size = 10;
	TDynamicMatrix<int> tmp(size);
	TDynamicMatrix<int> tmp_(tmp);
	EXPECT_NE(&tmp[0], &tmp_[0]);
}
TEST(TDynamicMatrix, can_get_size)
{
	const int size = 10;
	TDynamicMatrix<int> tmp(size);
	EXPECT_EQ(size, tmp.size());
}
TEST(TDynamicMatrix, can_set_and_get_element)
{
	const int size = 10;
	TDynamicMatrix<int> tmp(size);
	tmp[0][0] = 10;
	EXPECT_EQ(tmp[0][0], 10);
}
TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	const int size = 10;
	TDynamicMatrix<int> tmp(size);
	ASSERT_ANY_THROW(tmp.at(0).at(-1) = 10);
	ASSERT_ANY_THROW(tmp.at(-1).at(0) = 10);
	ASSERT_ANY_THROW(tmp.at(-1).at(-1) = 10);
}
TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	const int size = 10;
	TDynamicMatrix<int> tmp(size);
	ASSERT_ANY_THROW(tmp.at(0).at(100) = 10);
	ASSERT_ANY_THROW(tmp.at(100).at(0) = 10);
	ASSERT_ANY_THROW(tmp.at(100).at(100) = 10);
}
TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	const int size = 10;
	TDynamicMatrix<int> tmp(size);

	ASSERT_NO_THROW(tmp = tmp);
}
TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	const int size = 10;
	TDynamicMatrix<int> tmp(size), tmp_(size);
	ASSERT_NO_THROW(tmp = tmp_);
}
TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	const int size1 = 10, size2 = 15;
	TDynamicMatrix<int> tmp1(size1), tmp2(size2);
	tmp1 = tmp2;
	EXPECT_EQ(size2, tmp1.size());
}
TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	const int size1 = 10, size2 = 15;
	TDynamicMatrix<int> tmp(size1), tmp_(size2);
	ASSERT_NO_THROW(tmp = tmp_);
}
TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	const int size = 10;
	TDynamicMatrix<int> tmp(size), tmp_(size);
	tmp[0][1] = 4;
	tmp_[0][1] = 4;
	EXPECT_TRUE(tmp == tmp_);
	tmp_[0][1] = 0;
	EXPECT_FALSE(tmp == tmp_);
}
TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	const int size = 10;
	TDynamicMatrix<int> tmp(size);
	EXPECT_TRUE(tmp == tmp);
}
TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	const int size1 = 10, size2 = 15;
	TDynamicMatrix<int> tmp(size1), tmp_(size2);
	EXPECT_FALSE(tmp == tmp_);
}
TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	const int size = 10;
	TDynamicMatrix<int> tmp(size), tmp_(size);
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			tmp[i][j] = j;
	tmp_ = tmp_ + tmp;
	EXPECT_EQ(tmp_, tmp);
}
TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	const int size1 = 10, size2 = 15;
	TDynamicMatrix<int> tmp(size1), tmp_(size2);
	ASSERT_ANY_THROW(tmp + tmp_);
}
TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	const int size = 10;
	TDynamicMatrix<int> tmp(size), res(size);
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			tmp[i][j] = j;
	TDynamicMatrix<int> copy(tmp);
	tmp = tmp - copy;
	EXPECT_EQ(tmp, res);
}
TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	const int size1 = 10, size2 = 15;
	TDynamicMatrix<int> tmp(size1), tmp_(size2);
	ASSERT_ANY_THROW(tmp - tmp_);
}