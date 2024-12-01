#pragma once

class Vector {
public:
  /* Attributes
   * __float128 is used to avoid any possibility
   * of size restrainsts, which could cause
   * unexpected behavoir if not accounted for
   */

  __float128 x;
  __float128 y;
  __float128 z;

  // operator overloading methods

  Vector operator+(const Vector &vectorToAdd) const;

  Vector operator-(const Vector &vectorToSubtract) const;
  Vector operator*(double scalar) const;

  // static methods

  static Vector cross(const Vector &v1, const Vector &v2);
  static double dot(const Vector &v1, const Vector &v2);

  double magnitude() const;
  Vector normalise() const;

  // constructor
  Vector(const __float128 &x, const __float128 &y, const __float128 &z);
};
