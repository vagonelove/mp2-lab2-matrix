#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
	ASSERT_NO_THROW(TDynamicVector<int> v(5));
}
TEST(TDynamicVector, cant_create_too_large_vector)
{
	ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}
TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
	ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}
TEST(TDynamicVector, can_create_copied_vector)
{
	TDynamicVector<int> v(10);

	ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}
TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
	TDynamicVector<int> orig(10);
	TDynamicVector<int> copy(orig);
	EXPECT_EQ(orig, copy);
}
TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	TDynamicVector<int> orig(10);
	TDynamicVector<int> copy(orig);
	EXPECT_NE(&orig[0], &copy[0]);
}
TEST(TDynamicVector, can_get_size)
{
	TDynamicVector<int> v(4);
	EXPECT_EQ(4, v.size());
}
TEST(TDynamicVector, can_set_and_get_element)
{
	TDynamicVector<int> v(4);
	v[0] = 4;
	EXPECT_EQ(4, v[0]);
}
TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
	TDynamicVector<int> tmp(10);
	ASSERT_ANY_THROW(tmp.at(-1) = 0);
}
TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	TDynamicVector<int> tmp(10);
	ASSERT_ANY_THROW(tmp.at(10) = 10);
}
TEST(TDynamicVector, can_assign_vector_to_itself)
{
	TDynamicVector<int> tmp(10);
	ASSERT_NO_THROW(tmp = tmp);
}
TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	TDynamicVector<int> tmp(10), tmp_(10);
	tmp[0] = 100;
	tmp = tmp_;
	EXPECT_EQ(tmp, tmp_);
}
TEST(TDynamicVector, assign_operator_change_vector_size)
{
	TDynamicVector<int> tmp(10), tmp_(5);
	tmp = tmp_;
	EXPECT_EQ(tmp.size(), tmp_.size());
}
TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	TDynamicVector<int> tmp(10), tmp_(5);
	tmp[0] = 100;
	tmp = tmp_;
	EXPECT_EQ(tmp, tmp_);
}
TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	TDynamicVector<int> tmp(10), tmp_(10);
	EXPECT_TRUE(tmp == tmp_);
}
TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	TDynamicVector<int> tmp(10);
	EXPECT_TRUE(tmp == tmp);
}
TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	TDynamicVector<int> tmp(10), tmp_(5);
	EXPECT_FALSE(tmp == tmp_);
}
TEST(TDynamicVector, can_add_scalar_to_vector)
{
	TDynamicVector<int> tmp(4);
	tmp = tmp + 5;
	EXPECT_EQ(tmp[0], 5);
	EXPECT_EQ(tmp[1], 5);
	EXPECT_EQ(tmp[2], 5);
	EXPECT_EQ(tmp[3], 5);
}
TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	TDynamicVector<int> tmp(4);
	tmp = tmp - 5;
	EXPECT_EQ(tmp[0], -5);
	EXPECT_EQ(tmp[1], -5);
	EXPECT_EQ(tmp[2], -5);
	EXPECT_EQ(tmp[3], -5);
}
TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	TDynamicVector<int> tmp(4);
	tmp = tmp + 5;
	tmp = tmp * 5;
	EXPECT_EQ(tmp[0], 25);
	EXPECT_EQ(tmp[1], 25);
	EXPECT_EQ(tmp[2], 25);
	EXPECT_EQ(tmp[3], 25);
}
TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	const int size = 4;
	TDynamicVector<int> tmp(size), tmp_(size), rez(size);
	tmp = tmp + 2;
	for (int i = 0; i < size; i++)
		tmp_[i] = i;
	rez = tmp + tmp_;
	EXPECT_EQ(rez[0], 2);
	EXPECT_EQ(rez[1], 3);
	EXPECT_EQ(rez[2], 4);
	EXPECT_EQ(rez[3], 5);
}
TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	const int size = 4;
	TDynamicVector<int> tmp(size), tmp_(2 * size);
	ASSERT_ANY_THROW(tmp + tmp_);
}
TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	const int size = 4;
	TDynamicVector<int> tmp(size), tmp_(size), rez(size);
	tmp = tmp + 2;
	for (int i = 0; i < size; i++)
		tmp_[i] = i;
	rez = tmp - tmp_;
	EXPECT_EQ(rez[0], 2);
	EXPECT_EQ(rez[1], 1);
	EXPECT_EQ(rez[2], 0);
	EXPECT_EQ(rez[3], -1);
}
TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	const int size = 4;
	TDynamicVector<int> tmp(size), tmp_(2 * size);
	ASSERT_ANY_THROW(tmp - tmp_);
}
TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	const int size = 4;
	TDynamicVector<int> tmp(size), tmp_(size);
	for (int i = 0; i < size; i++)
		tmp[i] = i + 1;
	for (int i = 0; i < size; i++)
		tmp_[i] = i + 2;
	EXPECT_EQ(40, tmp * tmp_);
}
TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	const int size1 = 4, size2 = 5;
	TDynamicVector<int> tmp(size1), tmp_(size2);
	ASSERT_ANY_THROW(tmp * tmp_);
}