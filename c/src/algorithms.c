#include <math.h>
#include "algorithms.h"
// #include <squaternion.h>

// void complementary_filter(
//     compfilter_t *f,
//     float ax, float ay, float az,
//     float gx, float gy, float gz,
//     float mx, float my, float mz) {
//   const float DT    = f->dt;
//   const float alpha = f->alpha;

//   // Attitude estimation (complementary filter)
//   const float acc_roll  = atan2f(ay, az) * 180.0f / M_PI;
//   const float acc_pitch = atan2f(-ax, sqrtf(ay * ay + az * az)) * 180.0f / M_PI;

//   f->roll  = alpha * (f->roll + gx * DT) + (1.0f - alpha) * acc_roll;
//   f->pitch = alpha * (f->pitch + gy * DT) + (1.0f - alpha) * acc_pitch;

//   // Yaw from magnetometer
//   float mag_yaw = atan2f(-my, mx) * 180.0f / M_PI;
//   f->yaw        = alpha * (f->yaw + gz * DT) + (1.0f - alpha) * mag_yaw;

//   f->q = euler_to_quat(f->roll, f->pitch, f->yaw);
// }


vec3f_t compfilter(compfilter_t *f, vec3f_t a) {
  return a;
}