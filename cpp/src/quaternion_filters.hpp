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

/*!
Quaternion complementary filter (QCF) blends the sensor readings from an
accelerometer and a gyro together to get a stable reading and more reliable
overall state of a system.
 */
template<typename T>
class QCF {
public:
  QCF(T a = 0.02) : alpha(a) {}

  QuaternionT<T> update(T ax, T ay, T az, T wx, T wy, T wz, T dt) {
    qw        = q + 0.5 * dt * QuaternionT<T>(0.0, wx, wy, wz);
    T an = 1.0f / sqrtf(ax * ax + ay * ay + az * az);

    if (std::isinf(an)) return q;

    ax *= an;
    ay *= an;
    az *= an;

    T roll  = atan2(ay, az);
    T pitch = atan2(-ax, sqrtf(ay * ay + az * az));
    T yaw   = 0.0;

    qam          = QuaternionT<T>::from_euler(roll, pitch, yaw);

    q            = (1.0 - alpha) * qw + alpha * qam;
    return q;
  }

  QuaternionT<T> q; // current state estimate

protected:
  T alpha;   // ratio between the two quaternion estimates
  QuaternionT<T> qw;  // quaternion from gyros
  QuaternionT<T> qam; // quaternion from accels
};