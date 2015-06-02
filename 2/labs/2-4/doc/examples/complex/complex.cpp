#include "complex.h"
#include <iostream>
#include <math.h>
using namespace std;

Complex::Complex() {
  im = 0.0;
  re = 0.0;
}

Complex::Complex(double a, double b) {
  re = a;
  im = b;
}

Complex &Complex::operator=(const Complex &z1) {
  im = z1.im;
  re = z1.re;
  return *this;
}

istream &operator>>(istream &in, Complex &z) {
  in >> z.re >> z.im;
  return in;
}

ostream &operator<<(ostream &out, Complex &z) {
  out << z.re << "+" << z.im << "i";
  return out;
}

bool operator==(const Complex &z1, const Complex &z2) {
  if ((z1.im == z2.im) && (z1.re == z1.re)) return true;

  return false;
}

double Complex::mod() { return (sqrt(im * im + re * re)); }

bool operator>(const Complex &z1, const Complex &z2) {
  if (sqrt(z1.im * z1.im + z1.re * z1.re) > sqrt(z2.im * z2.im + z2.re * z2.re))
    return true;
  else
    return false;
}

Complex operator+(const Complex &z1, const Complex &z2) {
  Complex tmp;
  tmp.im = z1.im + z2.im;
  tmp.re = z1.re + z2.re;
  return tmp;
}

Complex operator-(const Complex &z1, const Complex &z2) {
  Complex tmp;
  tmp.im = z1.im - z2.im;
  tmp.re = z1.re - z2.re;
  return tmp;
}

Complex operator*(const Complex &z1, const Complex &z2) {
  Complex tmp;
  tmp.re = z1.re * z2.re - z1.im * z2.im;
  tmp.im = z1.im * z2.re + z1.re * z2.im;
  return tmp;
}

double Complex::arg() {
  if ((re == 0) && (im >= 0))
    return 3.1415 / 2;
  else if ((re == 0) && (im < 0))
    return -3.1415 / 2;
  else
    return (atan(im / re));
}

Complex operator/(const Complex &z1, const Complex &z2) {
  Complex tmp;
  if (z2.im * z2.im + z2.re * z2.re == 0.0)
    throw zero_divide();
  else {
    tmp.re = (z1.re * z2.re + z2.im * z1.im) / (z2.im * z2.im + z2.re * z2.re);
    tmp.im = (z1.im * z2.re - z2.im * z1.re) / (z2.im * z2.im + z2.re * z2.re);
  }
  return tmp;
}

Complex &Complex::operator+=(const Complex &z1) {
  re = z1.re + re;
  im = z1.im + im;
  return *this;
}

Complex &Complex::operator-() {
  re = -re;
  im = -im;
  return *this;
}

double Complex::operator[](const int &i) {
  switch (i) {
    case 0:
      return re;
    case 1:
      return im;
    default:
      throw bad_index();
  }
}

Complex &Complex::operator++(int) {
  re = re + 1;
  return Complex(re - 1, im);
}

Complex &Complex::operator++() {
  re = re + 1;
  return *this;
}