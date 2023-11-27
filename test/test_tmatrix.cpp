#include "utmatrix.h"

#include <gtest.h>

TEST(TMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TMatrix<int> m(5));
}

TEST(TMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TMatrix<int> m(-5));
}

TEST(TMatrix, can_create_copied_matrix)
{
  TMatrix<int> m(5);

  ASSERT_NO_THROW(TMatrix<int> m1(m));
}

TEST(TMatrix, copied_matrix_is_equal_to_source_one)////////////
{
	TMatrix<int> m(5);
	for (int i = 0; i < m.GetSize(); ++i) {
		TVector<int> tmp(m.GetSize(),i);
		for (int j = i; j < tmp.GetSize(); ++j) {
			tmp[j] = 1;
		}
		m[i] = tmp;
	}
	cout << m << " ";
	TMatrix<int> mc(m);
	EXPECT_EQ(m,mc);
}

TEST(TMatrix, copied_matrix_has_its_own_memory)
{
	TMatrix<int>* m;
	m = new TMatrix<int>(5);
	for (int i = 0; i < (*m).GetSize(); i++) {
		TVector<int> tmp((*m).GetSize() - i, i);
		for (int j = i; j < tmp.GetSize(); ++j) {
			tmp[j] = 1;
		}
		(*m)[i] = tmp;
	}
	TMatrix<int> mc(*m);
	delete m;
	TMatrix<int> res(5);
	for (int i = 0; i < res.GetSize(); i++) {
		TVector<int> tmp(res.GetSize() - i, i);
		for (int j = i; j < tmp.GetSize(); ++j) {
			tmp[j] = 1;
		}
		res[i] = tmp;
	}
	EXPECT_EQ(res, mc);
}

TEST(TMatrix, can_get_size)
{
	TMatrix<int> m(5);
	EXPECT_EQ(m.GetSize(), 5);
}

TEST(TMatrix, can_set_and_get_element)
{
	TMatrix<int> m(5);
	m[0][0] = 5;
	EXPECT_EQ(m[0][0],5);
}

TEST(TMatrix, throws_when_set_element_with_negative_index)
{
	TMatrix<int> m(5);
	ASSERT_ANY_THROW(m[-1][0] = 1;);
}

TEST(TMatrix, throws_when_set_element_with_too_large_index)
{
	TMatrix<int> m(5);
	ASSERT_ANY_THROW(m[6][0] = 1;);
}

TEST(TMatrix, can_assign_matrix_to_itself)
{
	TMatrix<int> m(5);
	for (int i = 0; i < m.GetSize(); ++i) {
		TVector<int> tmp(m.GetSize() - i, i);
		for (int j = i; j < tmp.GetSize(); ++j) {
			tmp[j] = 1;
		}
		m[i] = tmp;
	}
	ASSERT_NO_THROW(m = m);

	TMatrix<int> res(5);
	for (int i = 0; i < res.GetSize(); ++i) {
		TVector<int> tmp(res.GetSize() - i, i);
		for (int j = i; j < tmp.GetSize(); ++j) {
			tmp[j] = 1;
		}
		res[i] = tmp;
	}
	EXPECT_EQ(m, res);
}

TEST(TMatrix, can_assign_matrices_of_equal_size)
{
	TMatrix<int> m1(5);
	TMatrix<int> m2(5);
	m1 = m2;
	EXPECT_EQ(5, m1.GetSize());
}

TEST(TMatrix, assign_operator_change_matrix_size)
{
	TMatrix<int> m1(4);
	TMatrix<int> m2(5);
	m1 = m2;
	EXPECT_EQ(5, m1.GetSize());
}

TEST(TMatrix, can_assign_matrices_of_different_size)
{
	TMatrix<int> m1(4);
	TMatrix<int> m2(5);
	m1 = m2;
	EXPECT_EQ(m1, m2);
}

TEST(TMatrix, compare_equal_matrices_return_true)
{
	TMatrix<int> m1(5);
	for (int i = 0; i < m1.GetSize(); ++i) {
		TVector<int> tmp(m1.GetSize() - i, i);
		for (int j = i; j < tmp.GetSize(); ++j) {
			tmp[j] = 1;
		}
		m1[i] = tmp;
	}
	TMatrix<int> m2(5);
	for (int i = 0; i < m2.GetSize(); ++i) {
		TVector<int> tmp(m2.GetSize() - i, i);
		for (int j = i; j < tmp.GetSize(); ++j) {
			tmp[j] = 1;
		}
		m2[i] = tmp;
	}
	EXPECT_EQ(m1, m2);
}

TEST(TMatrix, compare_matrix_with_itself_return_true)
{
	TMatrix<int> m1(5);
	for (int i = 0; i < m1.GetSize(); ++i) {
		TVector<int> tmp(m1.GetSize() - i, i);
		for (int j = i; j < tmp.GetSize(); ++j) {
			tmp[j] = 1;
		}
		m1[i] = tmp;
	}
	EXPECT_EQ(m1, m1);
}

TEST(TMatrix, matrices_with_different_size_are_not_equal)
{
	TMatrix<int> m1(4);
	for (int i = 0; i < m1.GetSize(); ++i) {
		TVector<int> tmp(m1.GetSize() - i, i);
		for (int j = i; j < tmp.GetSize(); ++j) {
			tmp[j] = 1;
		}
		m1[i] = tmp;
	}
	TMatrix<int> m2(5);
	for (int i = 0; i < m2.GetSize(); ++i) {
		TVector<int> tmp(m2.GetSize() - i, i);
		for (int j = i; j < tmp.GetSize(); ++j) {
			tmp[j] = 1;
		}
		m2[i] = tmp;
	}
	EXPECT_NE(m1, m2);
}

TEST(TMatrix, can_add_matrices_with_equal_size)/////////////////
{
	TMatrix<int> m1(4);
	for (int i = 0; i < m1.GetSize(); ++i) {
		TVector<int> tmp(m1.GetSize(), i);
		for (int j = i; j < tmp.GetSize(); ++j) {
			tmp[j] = 1;
		}
		m1[i] = tmp;
	}
	cout << m1 << endl;
	TMatrix<int> m2(4);
	for (int i = 0; i < m2.GetSize(); ++i) {
		TVector<int> tmp(m2.GetSize(), i);
		for (int j = i; j < tmp.GetSize(); ++j) {
			tmp[j] = 1;
		}
		m2[i] = tmp;
	}
	cout << m2 << endl;
	TMatrix<int> res(4);
	for (int i = 0; i < res.GetSize(); ++i) {
		TVector<int> tmp(res.GetSize(), i);
		for (int j = i; j < tmp.GetSize(); ++j) {
			tmp[j] = 2;
		}
		res[i] = tmp;
	}
	cout << res << endl;
	EXPECT_EQ(m1+m2,res);
}

TEST(TMatrix, cant_add_matrices_with_not_equal_size)
{
	TMatrix<int> m1(4);
	for (int i = 0; i < m1.GetSize(); ++i) {
		TVector<int> tmp(m1.GetSize() - i, i);
		for (int j = i; j < tmp.GetSize(); ++j) {
			tmp[j] = 1;
		}
		m1[i] = tmp;
	}
	TMatrix<int> m2(5);
	for (int i = 0; i < m2.GetSize(); ++i) {
		TVector<int> tmp(m2.GetSize() - i, i);
		for (int j = i; j < tmp.GetSize(); ++j) {
			tmp[j] = 1;
		}
		m2[i] = tmp;
	}
	ASSERT_ANY_THROW(m1 + m2);
}

TEST(TMatrix, can_subtract_matrices_with_equal_size)
{
	TMatrix<int> m1(4);
	for (int i = 0; i < m1.GetSize(); ++i) {
		TVector<int> tmp(m1.GetSize(), i);
		for (int j = i; j < tmp.GetSize(); ++j) {
			tmp[j] = 2;
		}
		m1[i] = tmp;
	}
	cout << m1 << endl;
	TMatrix<int> m2(4);
	for (int i = 0; i < m2.GetSize(); ++i) {
		TVector<int> tmp(m2.GetSize(), i);
		for (int j = i; j < tmp.GetSize(); ++j) {
			tmp[j] = 1;
		}
		m2[i] = tmp;
	}
	cout << m2 << endl;
	TMatrix<int> res(4);
	for (int i = 0; i < res.GetSize(); ++i) {
		TVector<int> tmp(res.GetSize(), i);
		for (int j = i; j < tmp.GetSize(); ++j) {
			tmp[j] = 1;
		}
		res[i] = tmp;
	}
	cout << res << endl;
	EXPECT_EQ(m1 - m2, res);
}

TEST(TMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TMatrix<int> m1(4);
	for (int i = 0; i < m1.GetSize(); ++i) {
		TVector<int> tmp(m1.GetSize() - i, i);
		for (int j = i; j < tmp.GetSize(); ++j) {
			tmp[j] = 1;
		}
		m1[i] = tmp;
	}
	TMatrix<int> m2(5);
	for (int i = 0; i < m2.GetSize(); ++i) {
		TVector<int> tmp(m2.GetSize() - i, i);
		for (int j = i; j < tmp.GetSize(); ++j) {
			tmp[j] = 1;
		}
		m2[i] = tmp;
	}
	ASSERT_ANY_THROW(m1 - m2);
}

TEST(TMatrix, can_multiply_matrices_with_equal_size) {
	TMatrix<int> m1(4);
	for (int i = 0; i < m1.GetSize(); ++i) {
		TVector<int> tmp(m1.GetSize(), i);
		for (int j = i; j < tmp.GetSize(); ++j) {
			tmp[j] = 1;
		}
		m1[i] = tmp;
	}
	cout << m1 << endl;
	TMatrix<int> m2(4);
	for (int i = 0; i < m2.GetSize(); ++i) {
		TVector<int> tmp(m2.GetSize(), i);
		for (int j = i; j < tmp.GetSize(); ++j) {
			tmp[j] = 1;
		}
		m2[i] = tmp;
	}
	cout << m2 << endl;
	TVector<int> res(4);
	for (int i = 0; i < res.GetSize(); ++i) {
		res[i] = 4 - i;
	}
	EXPECT_EQ(m1 * m2, res);
}

TEST(TMatrix, cant_multiply_matrixes_with_not_equal_size) {
	ADD_FAILURE();
}
