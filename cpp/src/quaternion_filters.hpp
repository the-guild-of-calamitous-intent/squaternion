/**************************************\
 * The MIT License (MIT)
 * Copyright (c) 2022 Kevin Walchko
 * see LICENSE for full details
\**************************************/
#pragma once

/********************************************
Attitude from gravity: https://ahrs.readthedocs.io/en/latest/filters/tilt.html
Quaternion complementary filter:
https://ahrs.readthedocs.io/en/latest/filters/complementary.html
*********************************************/

#include "quaternion.hpp"
#include <cmath>

using std::sqrt;
using std::atan2;

template<typename T>
struct vect_t {
  T x,y,z;

  bool normalize() {
    T n = 1.0 / sqrt(x * x + y * y + z * z);
    if (std::isinf(n)) return false;

    x *= n;
    y *= n;
    z *= n;

    return true;
  }
};

/*!
Quaternion complementary filter (QCF) blends the sensor readings from an
accelerometer and a gyro together to get a stable reading and more reliable
overall state of a system.
 */
template<typename T>
class QCF {
public:
  QCF(T a = 0.02) : alpha(a) {}

  // QuaternionT<T> update(const vect_t<T>& aa, const vect_t<T>& w, const vect_t<T>& mm, T dt) {
  //   qw = q + 0.5 * dt * q * QuaternionT<T>(0.0, w.x, w.y, w.z);

  //   vect_t<T> a = aa;
  //   if (!a.normalize()) return q;

  //   T roll  = atan2(a.y, a.z);
  //   T pitch = atan2(-a.x, sqrt(a.y * a.y + a.z * a.z));

  //   vect_t<T> m = mm;
  //   if (!m.normalize()) return q;

  //   T cr = cos(roll);
  //   T sr = sin(roll);
  //   T cp = cos(pitch);
  //   T sp = sin(pitch);
  //   T yaw = atan2(
  //     m.z*sr - m.y*cr,
  //     m.x*cp + sp * (m.y * sr + m.z * cr)
  //   );

  //   qam = QuaternionT<T>::from_euler(roll, pitch, yaw);

  //   q = (1.0 - alpha) * qw + alpha * qam;
  //   return q;
  // }

  QuaternionT<T> update(const vect_t<T>& aa, const vect_t<T>& w, const vect_t<T>& mm, T dt) {
    qw = q + 0.5 * dt * q * QuaternionT<T>(0.0, w.x, w.y, w.z);

    vect_t<T> a = aa;
    if (!a.normalize()) return q;

    T roll  = atan2(a.y, a.z);
    T pitch = atan2(-a.x, sqrt(a.y * a.y + a.z * a.z));

    vect_t<T> m = mm;
    if (!m.normalize()) return q;

    // WARNING: ahrs.readmedocs switches symbols for roll/pitch compared
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

  QuaternionT<T> update(const vect_t<T>& aa, const vect_t<T>& w, T dt) {
    qw = q + 0.5 * dt * q * QuaternionT<T>(0.0, w.x, w.y, w.z);

    vect_t<T> a = aa;
    a.normalize();

    T roll  = atan2(a.y, a.z);
    T pitch = atan2(-a.x, sqrt(a.y * a.y + a.z * a.z));
    T yaw   = 0.0;

    qam = QuaternionT<T>::from_euler(roll, pitch, yaw);

    q = (1.0 - alpha) * qw + alpha * qam;
    return q;
  }

  QuaternionT<T> q; // current state estimate

protected:
  T alpha;   // ratio between the two quaternion estimates
  QuaternionT<T> qw;  // quaternion from gyros
  QuaternionT<T> qam; // quaternion from accels
};