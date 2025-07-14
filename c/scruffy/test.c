#include "squaternion.h"
#include "algorithms.h"

#include <scruffy/scruffy.h>


TEST(SQUATERNION, Basic) {

  squaternion_t q1 = quat_init(1.0, 2.0, 3.0, 4.0);
  EXPECT_FLOAT_EQ(q1.w, 1.0f);
}


TEST(SQUATERNION, filters) {
  compfilter_t f = {
    .roll = 0.0f,
    .pitch = 0.0f,
    .yaw = 0.0f,
    .alpha = 0.01f,
    .dt = 0.1f,
    .q = {.w=1.0f,.x=0.0f,.y=0.0f,.z=0.0f}
  };

  EXPECT_EQ(1,1);
}

RUN_ALL()
