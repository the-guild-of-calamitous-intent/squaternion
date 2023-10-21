/**************************************\
 * The MIT License (MIT)
 * Copyright (c) 2022 Kevin Walchko
 * see LICENSE for full details
\**************************************/
#pragma once

#include "quaternion.hpp"

#if !defined(ARDUINO) && !defined(PICO_SDK)
#include <cmath>

using std::sqrt;
using std::atan2;
#endif

template<typename T>
struct vect_t {
  T x,y,z;

  inline
  T magnitude() {
    return sqrt(x * x + y * y + z * z);
  }

  bool normalize() {
    T n = 1.0 / magnitude();
    if (std::isinf(n)) return false;

    x *= n;
    y *= n;
    z *= n;

    return true;
  }
};

#if !defined(ARDUINO) && !defined(PICO_SDK)
#include <ostream>
std::ostream& operator<<(std::ostream &os, vect_t<double> const &v) {
  os << "x: " << v.x << " y: " << v.y << " z: " << v.z;
  return os;
}
std::ostream& operator<<(std::ostream &os, vect_t<float> const &v) {
  os << "x: " << v.x << " y: " << v.y << " z: " << v.z;
  return os;
}
#endif

/*!
Quaternion complementary filter (QCF) blends the sensor readings from an
accelerometer and a gyro together to get a stable reading and more reliable
overall state of a system.

Ref: https://ahrs.readthedocs.io/en/latest/filters/complementary.html
 */
template<typename T>
class QCF {
public:
  // alpha: [0.0. 1.0]
  QCF(T a) : alpha(a) {}

  QuaternionT<T> update(vect_t<T> a, const vect_t<T>& w, vect_t<T> m, T dt) {
    qw = q + 0.5 * dt * q * QuaternionT<T>(0.0, w.x, w.y, w.z);

    if (!a.normalize()) return q;

    T roll  = atan2(a.y, a.z);
    T pitch = atan2(-a.x, sqrt(a.y * a.y + a.z * a.z));

    // m = mm;
    if (!m.normalize()) return q;

    // WARNING: ahrs.readthedocs switches symbols for roll/pitch compared
    //          to other authors ... below is correct
    T cr = cos(roll);
    T sr = sin(roll);
    T cp = cos(pitch);
    T sp = sin(pitch);
    T yaw = atan2(
      m.z*sp - m.y*cp,
      m.x*cr + sr * (m.y * sp + m.z * cp)
    );

    qam = QuaternionT<T>::from_euler(roll, pitch, yaw);

    q = alpha * qw + (1.0 - alpha) * qam;
    return q;
  }

  QuaternionT<T> update(vect_t<T> a, const vect_t<T>& w, T dt) {
    qw = q + 0.5 * dt * q * QuaternionT<T>(0.0, w.x, w.y, w.z);

    a.normalize();

    T roll  = atan2(a.y, a.z);
    T pitch = atan2(-a.x, sqrt(a.y * a.y + a.z * a.z));
    T yaw   = 0.0; // need magnetometer to calculate this, so default to 0.0

    qam = QuaternionT<T>::from_euler(roll, pitch, yaw);

    q = alpha * qw + (1.0 - alpha) * qam; // match ahrs.readthedocs
    return q;
  }

  QuaternionT<T> q; // current state estimate

protected:
  T alpha;   // ratio between the two quaternion estimates
  QuaternionT<T> qw;  // quaternion from gyros
  QuaternionT<T> qam; // quaternion from accels
  // vect_t<T> a, m; // accel and mag temp values
};

/*
Ref: https://ahrs.readthedocs.io/en/latest/filters/tilt.html
*/
template<typename T>
class TiltCompass {
  public:
  TiltCompass() {}

  const QuaternionT<T> update(vect_t<T> a, vect_t<T> m) {
    // a.normalize();
    if (!a.normalize()) return q;
    T roll  = atan2(a.y, a.z);
    T pitch = atan2(-a.x, sqrt(a.y * a.y + a.z * a.z));

    if (!m.normalize()) return q;

    // WARNING: ahrs.readthedocs switches symbols for roll/pitch compared
    //          to other authors ... below is correct
    T cr = cos(roll);
    T sr = sin(roll);
    T cp = cos(pitch);
    T sp = sin(pitch);
    T yaw = atan2(
      m.z*sp - m.y*cp,
      m.x*cr + sr * (m.y * sp + m.z * cp)
    );

    q = QuaternionT<T>::from_euler(roll, pitch, yaw);
    return q;
  }

  QuaternionT<T> q;
};