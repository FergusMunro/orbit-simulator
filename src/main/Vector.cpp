#include "Vector.hpp"
#include <cmath>

Vector::Vector(const long double &_x, const long double &_y,
               const long double &_z)
    : x(_x), y(_y), z(_z) {}

Vector const Vector::operator+(const Vector &vectorToAdd) {

  Vector vector =
      Vector(x + vectorToAdd.x, y + vectorToAdd.y, z + vectorToAdd.z);

  // returns the value of the vector calling the function and the other vector
  // added together

  return vector;
}

Vector const Vector::operator-(const Vector &vectorToSubtract) {

  Vector vector = Vector(x - vectorToSubtract.x, y - vectorToSubtract.y,
                         z - vectorToSubtract.z);

  // very simmilar to add function

  return vector;
}

Vector const Vector::operator*(double scalar) {
  Vector vector = Vector(x * scalar, y * scalar, z * scalar);

  return vector;
}

double Vector::dot(const Vector &v1, const Vector &v2) {

  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vector Vector::cross(const Vector &v1, const Vector &v2) {

  Vector crossProduct =
      Vector(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x - v2.z,
             v1.x * v2.y - v1.y * v1.x);

  return crossProduct;
}

double Vector::magnitude() {
  double mag = x * x + y * y + z * z;

  return sqrt(mag);
}

Vector Vector::normalise() {

  double mag = this->magnitude();

  mag = 1 / mag;

  return *this * mag;

  // this function divides the vector by the magnitude, creating a normalised
  // vector. The last line is a bit confusing because * is used first to
  // dereference the this pointer to access the vector, and is then used to
  // multiply the vector by the reciprocal of the magntude (which is the same as
  // dividing my the magnitude)
}
