#include <math.h>
#include <stdio.h>
#include "squaternion.h"

int main() {
  // Initialize quaternions
  squaternion_t q1 = quat_init(1.0, 2.0, 3.0, 4.0);   // q1 = 1 + 2i + 3j + 4k
  squaternion_t q2 = quat_init(2.0, -1.0, 1.0, -2.0); // q2 = 2 - i + j - 2k

  // Addition
  squaternion_t sum = quat_add(q1, q2);
  printf("Sum: (%.1f, %.1f, %.1f, %.1f)\n", sum.w, sum.x, sum.y, sum.z);

  // Multiplication
  squaternion_t prod = quat_mul(q1, q2);
  printf("Product: (%.1f, %.1f, %.1f, %.1f)\n", prod.w, prod.x, prod.y, prod.z);

  // Conjugate of q1
  squaternion_t conj = quat_conj(q1);
  printf("Conjugate of q1: (%.1f, %.1f, %.1f, %.1f)\n", conj.w, conj.x, conj.y, conj.z);

  // Norm of q1
  double norm = quat_norm(q1);
  printf("Norm of q1: %.1f\n", norm);

  // Inverse of q1
  squaternion_t inv = quat_inv(q1);
  printf("Inverse of q1: (%.1f, %.1f, %.1f, %.1f)\n", inv.w, inv.x, inv.y, inv.z);

  // Euler to quaternion
  double roll  = M_PI / 6.0; // 30 degrees
  double pitch = M_PI / 4.0; // 45 degrees
  double yaw   = M_PI / 3.0; // 60 degrees

  squaternion_t q_euler = euler_to_quat(roll, pitch, yaw);
  printf("Euler to quat (roll=30°, pitch=45°, yaw=60°): (%.3f, %.3f, %.3f, %.3f)\n",
         q_euler.w, q_euler.x, q_euler.y, q_euler.z);

  // squaternion_t to Euler
  double roll_out, pitch_out, yaw_out;
  quat_to_euler(q_euler, &roll_out, &pitch_out, &yaw_out);
  printf("Quat to Euler: roll=%.1f°, pitch=%.1f°, yaw=%.1f°\n",
         roll_out * 180.0 / M_PI, pitch_out * 180.0 / M_PI, yaw_out * 180.0 / M_PI);

  return 0;
}
