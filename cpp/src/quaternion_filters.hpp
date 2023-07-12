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
class QCF {
public:
  QCF(data_t a = 0.02) : alpha(a) {}

  Quaternion update(data_t ax, data_t ay, data_t az, data_t wx, data_t wy,
                    data_t wz, data_t dt) {
    qw        = q + 0.5 * dt * Quaternion(0.0f, wx, wy, wz);
    data_t an = 1.0f / sqrtf(ax * ax + ay * ay + az * az);

    if (isinf(an)) return q;

    ax *= an;
    ay *= an;
    az *= an;

    data_t roll  = atan2(ay, az);
    data_t pitch = atan2(-ax, sqrtf(ay * ay + az * az));
    data_t yaw   = 0.0f;

    qam          = Quaternion::from_euler(roll, pitch, yaw);

    q            = (1.0f - alpha) * qw + alpha * qam;
    return q;
  }

  Quaternion q; // current state estimate

protected:
  data_t alpha;   // ratio between the two quaternion estimates
  Quaternion qw;  // quaternion from gyros
  Quaternion qam; // quaternion from accels
};