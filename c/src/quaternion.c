#include <math.h>
#include "squaternion.h"

// Initialize a quaternion
squaternion_t quat_init(float w, float x, float y, float z) {
  squaternion_t q = {w, x, y, z};
  return q;
}

// Add two quaternions
squaternion_t quat_add(squaternion_t q1, squaternion_t q2) {
  return quat_init(
      q1.w + q2.w,
      q1.x + q2.x,
      q1.y + q2.y,
      q1.z + q2.z);
}

// Subtract two quaternions
squaternion_t quat_sub(squaternion_t q1, squaternion_t q2) {
  return quat_init(
      q1.w - q2.w,
      q1.x - q2.x,
      q1.y - q2.y,
      q1.z - q2.z);
}

// Multiply two quaternions (Hamilton product)
squaternion_t quat_mul(squaternion_t q1, squaternion_t q2) {
  return quat_init(
      q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z,
      q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y,
      q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x,
      q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w);
}

// Conjugate of a quaternion
squaternion_t quat_conj(squaternion_t q) {
  return quat_init(q.w, -q.x, -q.y, -q.z);
}

// Norm (magnitude) of a quaternion
float quat_norm(squaternion_t q) {
  return sqrt(q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z);
}

// Inverse of a quaternion
squaternion_t quat_inv(squaternion_t q) {
  float norm_sq = q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z;
  if (norm_sq == 0) {
    return quat_init(0, 0, 0, 0); // Return zero quaternion if non-invertible
  }
  squaternion_t conj = quat_conj(q);
  return quat_init(
      conj.w / norm_sq,
      conj.x / norm_sq,
      conj.y / norm_sq,
      conj.z / norm_sq);
}

// Convert Euler angles (321 sequence, radians) to quaternion
squaternion_t euler_to_quat(double roll, double pitch, double yaw) {
  double cr = cos(roll * 0.5);
  double sr = sin(roll * 0.5);
  double cp = cos(pitch * 0.5);
  double sp = sin(pitch * 0.5);
  double cy = cos(yaw * 0.5);
  double sy = sin(yaw * 0.5);

  return quat_init(
      cr * cp * cy + sr * sp * sy,
      sr * cp * cy - cr * sp * sy,
      cr * sp * cy + sr * cp * sy,
      cr * cp * sy - sr * sp * cy);
}

// Convert quaternion to Euler angles (321 sequence, radians)
void quat_to_euler(squaternion_t q, double *roll, double *pitch, double *yaw) {
  // Roll (x-axis rotation)
  double sinr_cosp = 2.0 * (q.w * q.x + q.y * q.z);
  double cosr_cosp = 1.0 - 2.0 * (q.x * q.x + q.y * q.y);
  *roll            = atan2(sinr_cosp, cosr_cosp);

  // Pitch (y-axis rotation)
  double sinp = 2.0 * (q.w * q.y - q.z * q.x);
  if (fabs(sinp) >= 1) {
    *pitch = copysign(M_PI / 2.0, sinp); // Handle singularity at ±90 degrees
  }
  else {
    *pitch = asin(sinp);
  }

  // Yaw (z-axis rotation)
  double siny_cosp = 2.0 * (q.w * q.z + q.x * q.y);
  double cosy_cosp = 1.0 - 2.0 * (q.y * q.y + q.z * q.z);
  *yaw             = atan2(siny_cosp, cosy_cosp);
}