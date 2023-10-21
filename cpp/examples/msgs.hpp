
#pragma once

#include <ostream>
#include <stdint.h>

constexpr uint8_t IMU = 129;

struct __attribute__((packed)) vec_t {
  float x,y,z;
}; // 3*4 = 12

struct __attribute__((packed)) accel_t {
  vec_t accel; // 12 [0:11]
};

struct __attribute__((packed)) gyro_t {
  vec_t gyro;  // 12 [0:11]
};

struct __attribute__((packed)) mag_t {
  vec_t mag;  // 12 [0:11]
};

struct __attribute__((packed)) atmospheric_t {
  float pressure;    // 4
  float temperature; // 4
}; // 4+4 = 8

struct __attribute__((packed)) imu_t: accel_t, gyro_t, mag_t, atmospheric_t {
  enum IMU_Status: uint8_t {
    OK      = 0,
    A_FAIL  = 1,
    G_FAIL  = 2,
    M_FAIL  = 4,
    PT_FAIL = 8
  };
  uint8_t status;
  long timestamp;
};

// std::ostream& operator<<(std::ostream &os, vect_t<double> const &v) {
//   os << "x: " << v.x << " y: " << v.y << " z: " << v.z;
//   return os;
// }
// std::ostream& operator<<(std::ostream &os, vect_t<float> const &v) {
//   os << "x: " << v.x << " y: " << v.y << " z: " << v.z;
//   return os;
// }