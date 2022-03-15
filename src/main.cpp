#include "s21_matrix_oop.h"

int main() {
  S21Matrix m1(2, 2);
  m1[0][0] = 5;
  m1[0][1] = 11;
  m1[1][0] = 17;
  m1[1][1] = 24;
  S21Matrix m2 = m1;
  m2[1][0] = 13;
  m2[1][1] = 12;
  S21Matrix res = m2 - m1;
  res.show();
  res = m2 + m1;
  res.show();
  res += m2 + m1;
  res.show();
  res *= 1.0 / 2.0;
  res.show();
  S21Matrix m(5, 3);
  S21Matrix m3(5, 4);
  res = m3 + m;
  std::cout << "random matrix \n";
  m.FillRandom(-200, 200);
  m.show();
  S21Matrix m_tr = m.transpose();
  m_tr.show();

  return 0;
}