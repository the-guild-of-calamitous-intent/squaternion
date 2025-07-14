
#pragma once

#if defined __cplusplus
extern "C" {
#endif

#include "squaternion.h"


#ifndef __VEC3F__
#define __VEC3F__
typedef struct {
  float x, y, z;
} vec3f_t;
#endif

typedef struct {
  float roll, pitch, yaw;
  float alpha;
  float dt;
  // squaternion_t q = {.w=1.0f,.x=0.0f,.y=0.0f,.z=0.0f};
  squaternion_t q;
} compfilter_t;

// void complementary_filter(compfilter_t *f, float ax, float ay, float az,
//                           float gx, float gy, float gz, float mx, float my,
//                           float mz);

vec3f_t compfilter(compfilter_t *f, vec3f_t a);

#if defined __cplusplus
}
#endif
