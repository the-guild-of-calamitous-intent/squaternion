/**************************************\
 * The MIT License (MIT)
 * Copyright (c) 2022 Kevin Walchko
 * see LICENSE for full details
\**************************************/
#pragma once

#ifdef ARDUINO
  #include <Arduino.h>
  #define data_t float
#else
  #include <cmath>
  #include <ostream>
  #include <string>
  #define data_t double
#endif

constexpr data_t deg2rad = M_PI / 180.0;
constexpr data_t rad2deg = 180.0 / M_PI;

/**
 * This is a Hamilton quaterion:
 * - order is: (w,x,y,z)
 * - provides a rotation from body to inertial
 * - q_hamilton = q_jpl.conjugate() and vise-a-versa
 */
struct Quaternion {
  Quaternion() : w(1.0), x(0.0), y(0.0), z(0.0) {}

  Quaternion(data_t w, data_t x, data_t y, data_t z) : w(w), x(x), y(y), z(z) {}

  Quaternion(data_t *v) : w(v[0]), x(v[1]), y(v[2]), z(v[3]) {}

  double magnitude() const { return sqrt(w * w + x * x + y * y + z * z); }

  int normalize() {
    data_t m = sqrt(w * w + x * x + y * y + z * z);

    if (m < 1.0e-6) {
      return 1;
    }

    // use isinf(inv_m) instead?
    // the above test will capture really large inv_m
    // in addition to infinate
    data_t inv_m = 1.0 / m;

    this->w *= inv_m;
    this->x *= inv_m;
    this->y *= inv_m;
    this->z *= inv_m;

    return 0;
  }

  // Returns Quaternion(w,-x,-y,-z)
  Quaternion conjugate() const { return Quaternion(w, -x, -y, -z); }

  // Returns the Euler angles as a tuple(roll, pitch, yaw)
  // This is a modified version of this:
  // https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
  void to_euler(data_t *roll, data_t *pitch, data_t *yaw,
                const bool degrees = false) const {

    data_t ysqr = y * y;

    data_t t0   = +2.0 * (w * x + y * z);
    data_t t1   = +1.0 - 2.0 * (x * x + ysqr);
    *roll       = atan2(t0, t1);

    data_t t2   = +2.0 * (w * y - z * x);

    if (t2 > 1.0) t2 = 1.0;
    else if (t2 < -1.0) t2 = -1.0;
    *pitch    = asin(t2);

    data_t t3 = +2.0 * (w * z + x * y);
    data_t t4 = +1.0 - 2.0 * (ysqr + z * z);
    *yaw      = atan2(t3, t4);

    if (degrees) {
      *roll *= rad2deg;
      *pitch *= rad2deg;
      *yaw *= rad2deg;
    }
  }

  static Quaternion from_euler(data_t roll, data_t pitch, data_t yaw,
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

    data_t cy = cos(yaw * 0.5);
    data_t sy = sin(yaw * 0.5);
    data_t cr = cos(roll * 0.5);
    data_t sr = sin(roll * 0.5);
    data_t cp = cos(pitch * 0.5);
    data_t sp = sin(pitch * 0.5);

    data_t w  = cy * cr * cp + sy * sr * sp;
    data_t x  = cy * sr * cp - sy * cr * sp;
    data_t y  = cy * cr * sp + sy * sr * cp;
    data_t z  = sy * cr * cp - cy * sr * sp;

    return Quaternion(w, x, y, z);
  }

  // Quaternion = Quaternion * Quaternion
  // anwer = q(this) * r
  Quaternion operator*(const Quaternion &r) const {
    const Quaternion *q = this;
    return Quaternion(r.w * q->w - r.x * q->x - r.y * q->y - r.z * q->z,
                      r.w * q->x + r.x * q->w - r.y * q->z + r.z * q->y,
                      r.w * q->y + r.x * q->z + r.y * q->w - r.z * q->x,
                      r.w * q->z - r.x * q->y + r.y * q->x + r.z * q->w);
  }

  // answer = q(this) + r
  Quaternion operator+(const Quaternion &r) const {
    return Quaternion(w + r.w, x + r.x, y + r.y, z + r.z);
  }

  // answer = q(this) - r
  Quaternion operator-(const Quaternion &r) const {
    return Quaternion(w - r.w, x - r.x, y - r.y, z - r.z);
  }

  // Quaternion = Quaternion / scalar
  // answer = q(this) / scalar
  Quaternion operator/(data_t scalar) const {
    return Quaternion(w / scalar, x / scalar, y / scalar, z / scalar);
  }

  // Quaternion = Quaternion * scalar
  // answer = q(this) * r
  Quaternion operator*(data_t scalar) const {
    return Quaternion(w * scalar, x * scalar, y * scalar, z * scalar);
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
  void rotate(data_t vec[3]) {
    Quaternion qq = conjugate();
    Quaternion v(0.0, vec[0], vec[1], vec[2]);
    Quaternion ans = *this * v * qq;
    vec[0]         = ans.x;
    vec[1]         = ans.y;
    vec[2]         = ans.z;
  }

  double w, x, y, z;
};

// answer = scalar * q(this)
static Quaternion operator*(data_t scalar, const Quaternion &q) {
  return Quaternion(q.w * scalar, q.x * scalar, q.y * scalar, q.z * scalar);
}

#ifndef ARDUINO
// won't use ostream on Arduino
static std::ostream &operator<<(std::ostream &os, const Quaternion &q) {
  return os << q.to_str();
}
#endif