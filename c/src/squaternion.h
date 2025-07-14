#pragma once

#if defined __cplusplus
extern "C" {
#endif

#ifndef QUATERNION_H
#define QUATERNION_H

typedef struct {
  float w; // Real part
  float x; // i component
  float y; // j component
  float z; // k component
} squaternion_t;

typedef struct {
  float roll;
  float pitch;
  float yaw;
} euler_t;

// Initialize a quaternion
squaternion_t quat_init(float w, float x, float y, float z);

// Add two quaternions
squaternion_t quat_add(squaternion_t q1, squaternion_t q2);

// Subtract two quaternions
squaternion_t quat_sub(squaternion_t q1, squaternion_t q2);

// Multiply two quaternions
squaternion_t quat_mul(squaternion_t q1, squaternion_t q2);

// Conjugate of a quaternion
squaternion_t quat_conj(squaternion_t q);

// Norm (magnitude) of a quaternion
float quat_norm(squaternion_t q);

// Inverse of a quaternion
squaternion_t quat_inv(squaternion_t q);

// Convert Euler angles (321 sequence, radians) to quaternion
squaternion_t euler_to_quat(double roll, double pitch, double yaw);

// Convert quaternion to Euler angles (321 sequence, radians)
void quat_to_euler(squaternion_t q, double *roll, double *pitch, double *yaw);

#endif

#if defined __cplusplus
}
#endif
