#pragma once

class Vector {
public:
  /* Attributes
   * Long double is used to avoid any possibility
   * of size restrainsts, which could cause
   * unexpected behavoir if not accounted for
   */

  long double x;
  long double y;
  long double z;

  // operator overloading methods

  Vector const operator+(const Vector &vectorToAdd);
  Vector const operator-(const Vector &vectorToSubtract);
  Vector const operator*(double scalar);

  // static methods

  static Vector cross(const Vector &v1, const Vector &v2);
  static double dot(const Vector &v1, const Vector &v2);

  double magnitude();
  Vector normalise();

  // constructor
  Vector(const long double &x, const long double &y, const long double &z);
};
