/**************************************\
 * The MIT License (MIT)
 * Copyright (c) 2022 Kevin Walchko
 * see LICENSE for full details
\**************************************/
#pragma once
#include <cmath>

using std::sqrt;
using std::atan2;
using std::cos;
using std::sin;
using std::asin;


/**
 * This is a Hamilton quaterion:
 * - order is: (w,x,y,z)
 * - provides a rotation from body to inertial
 * - q_hamilton = q_jpl.conjugate() and vise-a-versa
 */
template <typename T>
struct QuaternionT {
  QuaternionT() : w(1.0), x(0.0), y(0.0), z(0.0) {}

  QuaternionT(T w, T x, T y, T z) : w(w), x(x), y(y), z(z) {}

  QuaternionT(T *v) : w(v[0]), x(v[1]), y(v[2]), z(v[3]) {}

  static constexpr T deg2rad = M_PI / 180.0;
  static constexpr T rad2deg = 180.0 / M_PI;

  inline
  T magnitude() const { return sqrt(w * w + x * x + y * y + z * z); }

  int normalize() {
    T m = sqrt(w * w + x * x + y * y + z * z);

    if (m < 1.0e-6) {
      return 1;
    }

    // use isinf(inv_m) instead?
    // the above test will capture really large inv_m
    // in addition to infinate
    T inv_m = 1.0 / m;

    this->w *= inv_m;
    this->x *= inv_m;
    this->y *= inv_m;
    this->z *= inv_m;

    return 0;
  }

  // Returns QuaternionT(w,-x,-y,-z)
  QuaternionT conjugate() const { return QuaternionT(w, -x, -y, -z); }

  // Returns the Euler angles as a tuple(roll, pitch, yaw)
  // This is a modified version of this:
  // https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
  void to_euler(T *roll, T *pitch, T *yaw,
                const bool degrees = false) const {

    T ysqr = y * y;

    T t0   = +2.0 * (w * x + y * z);
    T t1   = +1.0 - 2.0 * (x * x + ysqr);
    *roll       = atan2(t0, t1);

    T t2   = +2.0 * (w * y - z * x);

    if (t2 > 1.0) t2 = 1.0;
    else if (t2 < -1.0) t2 = -1.0;
    *pitch    = asin(t2);

    T t3 = +2.0 * (w * z + x * y);
    T t4 = +1.0 - 2.0 * (ysqr + z * z);
    *yaw      = atan2(t3, t4);

    if (degrees) {
      *roll *= rad2deg;
      *pitch *= rad2deg;
      *yaw *= rad2deg;
    }
  }

  static
  QuaternionT from_euler(T roll, T pitch, T yaw,
                               const bool degrees = false) {
    // Euler angles euler2quat(roll, pitch, yaw, degrees=False), default is
    // radians, but set degrees True if giving degrees This is a modified
    // version of this:
    // https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles

    if (degrees) {
      roll *= deg2rad;
      pitch *= deg2rad;
      yaw *= deg2rad;
    }

    T cy = cos(yaw * 0.5);
    T sy = sin(yaw * 0.5);
    T cr = cos(roll * 0.5);
    T sr = sin(roll * 0.5);
    T cp = cos(pitch * 0.5);
    T sp = sin(pitch * 0.5);

    T w  = cy * cr * cp + sy * sr * sp;
    T x  = cy * sr * cp - sy * cr * sp;
    T y  = cy * cr * sp + sy * sr * cp;
    T z  = sy * cr * cp - cy * sr * sp;

    return QuaternionT(w, x, y, z);
  }

  // QuaternionT = QuaternionT * QuaternionT
  // anwer = q(this) * r
  QuaternionT operator*(const QuaternionT &r) const {
    const QuaternionT *q = this;
    return QuaternionT(r.w * q->w - r.x * q->x - r.y * q->y - r.z * q->z,
                      r.w * q->x + r.x * q->w - r.y * q->z + r.z * q->y,
                      r.w * q->y + r.x * q->z + r.y * q->w - r.z * q->x,
                      r.w * q->z - r.x * q->y + r.y * q->x + r.z * q->w);
  }

  // answer = q(this) + r
  QuaternionT operator+(const QuaternionT &r) const {
    return QuaternionT(w + r.w, x + r.x, y + r.y, z + r.z);
  }

  // answer = q(this) - r
  QuaternionT operator-(const QuaternionT &r) const {
    return QuaternionT(w - r.w, x - r.x, y - r.y, z - r.z);
  }

  // QuaternionT = QuaternionT / scalar
  // answer = q(this) / scalar
  QuaternionT operator/(T scalar) const {
    return QuaternionT(w / scalar, x / scalar, y / scalar, z / scalar);
  }

  // QuaternionT = QuaternionT * scalar
  // answer = q(this) * r
  QuaternionT operator*(T scalar) const {
    return QuaternionT(w * scalar, x * scalar, y * scalar, z * scalar);
  }

#ifdef ARDUINO
  String to_str() const {
    String ret = "Quaternion(w: " + String(w) + ", x: " + String(x) +
                 ", y: " + String(y) + ", z: " + String(z) + ")";
    return ret;
  }
#else
  std::string to_str() const {
    std::string ret =
        "Quaternion(w: " + std::to_string(w) + ", x: " + std::to_string(x) +
        ", y: " + std::to_string(y) + ", z: " + std::to_string(z) + ")";
    return ret;
  }
#endif

  /**
   * FIXME: double check this is correct
   */
  void rotate(T vec[3]) {
    QuaternionT qq = conjugate();
    QuaternionT v(0.0, vec[0], vec[1], vec[2]);
    QuaternionT ans = *this * v * qq;
    vec[0]         = ans.x;
    vec[1]         = ans.y;
    vec[2]         = ans.z;
  }

  T w, x, y, z;
};



// answer = scalar * q(this)
static
QuaternionT<float> operator*(float scalar, const QuaternionT<float> &q) {
  return QuaternionT<float>(q.w * scalar, q.x * scalar, q.y * scalar, q.z * scalar);
}

static
QuaternionT<double> operator*(double scalar, const QuaternionT<double> &q) {
  return QuaternionT<double>(q.w * scalar, q.x * scalar, q.y * scalar, q.z * scalar);
}

#ifndef ARDUINO
// won't use ostream on Arduino
static
std::ostream &operator<<(std::ostream &os, const QuaternionT<double> &q) {
  return os << q.to_str();
}

static
std::ostream &operator<<(std::ostream &os, const QuaternionT<float> &q) {
  return os << q.to_str();
}
#endif


#if defined(ARDUINO)
  #include <Arduino.h>
  // #define T float
  using Quaternion = QuaternionT<float>;
#else
  #include <cmath>
  #include <ostream>
  #include <string>
  // #define T double
  using Quaternion = QuaternionT<double>;
#endif