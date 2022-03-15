#include <gtest/gtest.h>

#include <iostream>

#include "s21_matrix_oop.h"

// constructors tests
TEST(Test, default_constructor) {
  S21Matrix m;
  EXPECT_EQ(0, m.GetColumn());
  EXPECT_EQ(0, m.GetRow());
  EXPECT_EQ(m.IsNull(), true);
}

TEST(Test, rows_column_constructor) {
  S21Matrix m(3, 3);
  EXPECT_EQ(3, m.GetColumn());
  EXPECT_EQ(3, m.GetRow());
  EXPECT_EQ(m.IsNull(), false);
}

TEST(Test, copy_constructor) {
  S21Matrix m(3, 3);
  S21Matrix copy(m);
  EXPECT_EQ(3, copy.GetColumn());
  EXPECT_EQ(3, copy.GetRow());
  EXPECT_EQ(copy.IsNull(), false);
}

TEST(Test, assert_construct_move) {
  S21Matrix m1(3, 3);
  m1[1][1] = 2;
  S21Matrix m2(std::move(m1));

  EXPECT_EQ(2, m2[1][1]);
  EXPECT_EQ(m1.IsNull(), true);
}

TEST(Test, assert_throw_calc_complements) {
  S21Matrix m1(3, 2);
  ASSERT_THROW(m1.calc_complements(), std::exception);
}

TEST(Test, assert_eq_test) {
  S21Matrix m1(2, 2), m2(2, 2), m3(2, 3);
  EXPECT_EQ(true, m1.eq_matrix(m2));
  EXPECT_EQ(false, m1.eq_matrix(m3));
  m2[0][0] = 0.5;
  EXPECT_EQ(false, m1.eq_matrix(m2));
  m2[0][0] = 0.5;
  m2[0][1] = 0.6;
  m2[1][0] = 0.7;
  m2[1][1] = 0.8;

  m1[0][0] = 0.5;
  m1[0][1] = 0.6;
  m1[1][0] = 0.7;
  m1[1][1] = 0.8;
  EXPECT_EQ(true, m1.eq_matrix(m2));
  EXPECT_EQ(true, m2.eq_matrix(m1));
  EXPECT_EQ(true, m1 == m2);
  EXPECT_EQ(true, m2 == m1);
  EXPECT_EQ(false, m1 == m3);
}

TEST(Test, assert_sum) {
  S21Matrix m1(2, 2), m2(2, 2);
  m1[0][0] = 0.1;
  m2[0][1] = 0.2;
  m2[1][0] = 0.3;
  m1[1][1] = 0.4;
  S21Matrix res = m1 + m2;
  S21Matrix or_res(2, 2);
  or_res[0][0] = 0.1;
  or_res[0][1] = 0.2;
  or_res[1][0] = 0.3;
  or_res[1][1] = 0.4;
  EXPECT_EQ(true, res.eq_matrix(or_res));
  res = m1;
  res += m2;
  EXPECT_EQ(true, res.eq_matrix(or_res));
  res = res + res;
  or_res[0][0] = 0.2;
  or_res[0][1] = 0.4;
  or_res[1][0] = 0.6;
  or_res[1][1] = 0.8;
  EXPECT_EQ(true, res.eq_matrix(or_res));
  or_res[1][1] = 0.89;
  EXPECT_EQ(false, res.eq_matrix(or_res));
}

TEST(Test, assert_sub) {
  S21Matrix m1(2, 2), m2(2, 2);
  m1[0][0] = 0.1;
  m2[0][1] = 0.2;
  m2[1][0] = 0.3;
  m1[1][1] = 0.4;
  S21Matrix res = m1 - m2;
  S21Matrix or_res(2, 2);
  or_res[0][0] = 0.1;
  or_res[0][1] = -0.2;
  or_res[1][0] = -0.3;
  or_res[1][1] = 0.4;
  EXPECT_EQ(true, res.eq_matrix(or_res));
  res = m1;
  res -= m2;
  EXPECT_EQ(true, res.eq_matrix(or_res));
  res = res - m1;
  EXPECT_EQ(false, res.eq_matrix(or_res));
  or_res[0][0] = 0;
  or_res[1][1] = 0;
  EXPECT_EQ(true, res.eq_matrix(or_res));
}

TEST(Test, assert_mul_number) {
  S21Matrix m1(2, 2), m2(2, 2);
  m1[0][0] = 0.1;
  m1[1][1] = 0.4;

  S21Matrix res = m1 * 2;
  S21Matrix or_res(2, 2);
  or_res[0][0] = 0.2;
  // or_res[0][1] = -0.2;
  // or_res[1][0] = -0.3;
  or_res[1][1] = 0.8;
  EXPECT_EQ(true, res.eq_matrix(or_res));
  res = m1;
  res *= 2;
  EXPECT_EQ(true, res.eq_matrix(or_res));
  res[0][1] = 0.2;
  res[1][0] = 0.3;
  res = res * 0.5;
  or_res[0][0] = 0.1;
  or_res[0][1] = 0.1;
  or_res[1][0] = 0.15;
  EXPECT_EQ(false, res.eq_matrix(or_res));
  or_res[1][1] = 0.4;
  EXPECT_EQ(true, res.eq_matrix(or_res));
}

TEST(Test, assert_mul_matr) {
  S21Matrix m1(3, 3), m2(3, 3);
  m1[0][0] = 1;
  m1[0][1] = 2;
  m1[0][2] = 3;
  m1[1][0] = 4;
  m1[1][1] = 5;
  m1[1][2] = 6;
  m1[2][0] = 7;
  m1[2][1] = 8;
  m1[2][2] = 9;

  m2[0][0] = 10;
  m2[0][1] = 20;
  m2[0][2] = 30;
  m2[1][0] = 40;
  m2[1][1] = 50;
  m2[1][2] = 60;
  m2[2][0] = 70;
  m2[2][1] = 80;
  m2[2][2] = 90;

  S21Matrix res = m1 * m2;
  S21Matrix orRes(3, 3);

  orRes[0][0] = 300;
  orRes[0][1] = 360;
  orRes[0][2] = 420;
  orRes[1][0] = 660;
  orRes[1][1] = 810;
  orRes[1][2] = 960;
  orRes[2][0] = 1020;
  orRes[2][1] = 1260;
  orRes[2][2] = 1500;

  EXPECT_EQ(true, res.eq_matrix(orRes));
  res = m2 * m1;
  EXPECT_EQ(true, res.eq_matrix(orRes));
  res = m1;
  res *= m2;
  EXPECT_EQ(true, res.eq_matrix(orRes));
}

TEST(Test, assert_transpose) {
  S21Matrix m1(2, 3);
  S21Matrix m2(5, 5);
  m1[1][2] = 3.5;
  S21Matrix res = m1.transpose();
  S21Matrix orRes(3, 2);
  orRes[2][1] = 3.5;
  EXPECT_EQ(true, res.eq_matrix(orRes));
  orRes = m2;
  m2[4][4] = 1.5;
  m2[3][4] = 100;
  m2[0][4] = 259;
  orRes[2][1] = 0;
  orRes[4][4] = 1.5;
  orRes[4][3] = 100;
  orRes[4][0] = 259;
  res = m2.transpose();
  EXPECT_EQ(true, res.eq_matrix(orRes));
}

TEST(Test, assert_determinant) {
  S21Matrix m1(3, 3);
  double res;
  m1[0][0] = 1;
  m1[0][1] = 2;
  m1[0][2] = 3;
  m1[1][0] = 4;
  m1[1][1] = 5;
  m1[1][2] = 6;
  m1[2][0] = 7;
  m1[2][1] = 8;
  m1[2][2] = 9;
  res = m1.determinant();
  EXPECT_EQ(res, 0.0);
  m1[2][2] = 10;
  res = m1.determinant();
  EXPECT_EQ(res, -3);
}

TEST(Test, assert_calc_complements) {
  S21Matrix m1(3, 3);

  m1[0][0] = 1;
  m1[0][1] = 2;
  m1[0][2] = 3;
  m1[1][0] = 4;
  m1[1][1] = 5;
  m1[1][2] = 6;
  m1[2][0] = 7;
  m1[2][1] = 8;
  m1[2][2] = 10;
  S21Matrix res = m1.calc_complements();
  S21Matrix orRes(3, 3);
  orRes[0][0] = 2;
  orRes[0][1] = 2;
  orRes[0][2] = -3;
  orRes[1][0] = 4;
  orRes[1][1] = -11;
  orRes[1][2] = 6;
  orRes[2][0] = -3;
  orRes[2][1] = 6;
  orRes[2][2] = -3;
  EXPECT_EQ(true, res.eq_matrix(orRes));
}

TEST(Test, assert_inverse) {
  S21Matrix m1(3, 3);
  m1[0][0] = 1;
  m1[0][1] = 2;
  m1[0][2] = 3;
  m1[1][0] = 4;
  m1[1][1] = 5;
  m1[1][2] = 6;
  m1[2][0] = 7;
  m1[2][1] = 8;
  m1[2][2] = 10;
  S21Matrix res = m1.inverse_matrix();
  S21Matrix orRes(3, 3);
  orRes[0][0] = -0.6666666666666666666;
  orRes[0][1] = -1.3333333333333333333;
  orRes[0][2] = 1;
  orRes[1][0] = -0.6666666666666666667;
  orRes[1][1] = 3.6666666666666666666;
  orRes[1][2] = -2;
  orRes[2][0] = 1;
  orRes[2][1] = -2;
  orRes[2][2] = 1;
  EXPECT_EQ(true, res.eq_matrix(orRes));
}
TEST(Test, assert_getter_setter) {
  S21Matrix m(5, 5);
  m(3, 3) = 5.0;
  m(2, 2) = 1;
  EXPECT_EQ(1, m[2][2]);
  EXPECT_EQ(5.0, m(3, 3));
  double val = m(3, 3);
  EXPECT_EQ(5.0, val);
}

TEST(Test, assert_accessor_mutator) {
  S21Matrix m(5, 5);
  m[1][1] = 1;
  EXPECT_EQ(5, m.GetRow());
  EXPECT_EQ(5, m.GetColumn());
  m.EditColumn(4);
  EXPECT_EQ(4, m.GetColumn());
  m.EditRow(4);
  EXPECT_EQ(4, m.GetRow());
}

TEST(Test, assert_throw_accessor_mutator) {
  S21Matrix m(5, 5);
  ASSERT_THROW(m.EditColumn(-3), std::exception);
  ASSERT_THROW(m.EditRow(0), std::exception);
}

TEST(Test, assert_throw_sum) {
  S21Matrix m1(10, 20), m2(1, 2);
  ASSERT_THROW(m1 + m2, std::exception);
}
TEST(Test, assert_throw_sub) {
  S21Matrix m1(10, 20), m2(1, 2);
  ASSERT_THROW(m1 - m2, std::exception);
}

TEST(Test, assert_throw_mul) {
  S21Matrix m1(10, 20), m2(1, 2);
  ASSERT_THROW(m1 * m2, std::exception);
}

TEST(Test, assert_throw_index) {
  S21Matrix m2(1, 2);
  ASSERT_THROW(m2(3, 3), std::exception);
}

TEST(Test, assert_throw_deter) {
  S21Matrix m2(1, 2);
  ASSERT_THROW(m2.determinant(), std::exception);
}

TEST(Test, assert_throw_inverse) {
  S21Matrix m2(1, 2), zeroDeter(3, 3);
  ASSERT_THROW(m2.inverse_matrix(), std::exception);
  zeroDeter[0][0] = 1;
  zeroDeter[0][1] = 2;
  zeroDeter[0][2] = 3;
  zeroDeter[1][0] = 4;
  zeroDeter[1][1] = 5;
  zeroDeter[1][2] = 6;
  zeroDeter[2][0] = 7;
  zeroDeter[2][1] = 8;
  zeroDeter[2][2] = 9;
  ASSERT_THROW(zeroDeter.inverse_matrix(), std::exception);
}

TEST(Test, assert_throw_brackets) {
  S21Matrix m2(1, 2);
  ASSERT_THROW(m2(3, 3), std::exception);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}