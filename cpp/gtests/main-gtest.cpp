#include <gtest/gtest.h>
#include <squaternion.hpp>

// // Demonstrate some basic assertions.
// TEST(squaternion, dummy) {
//   // Expect two strings not to be equal.
//   EXPECT_STRNE("hello", "world");
//   // Expect equality.
//   EXPECT_EQ(7 * 6, 42);
// }

TEST(squaternion, basics) {
  Quaternion q;
  EXPECT_DOUBLE_EQ(q.w, 1.0);
  EXPECT_DOUBLE_EQ(q.x + q.y + q.z, 0.0);
  EXPECT_EQ(sizeof(q.w), sizeof(double));
  EXPECT_EQ(sizeof(q.z), sizeof(double));
  EXPECT_EQ(sizeof(q.y), sizeof(double));
  EXPECT_EQ(sizeof(q.x), sizeof(double));

  Quaternion qq(1, 2, 3, 4);
  EXPECT_DOUBLE_EQ(qq.w, 1.0);
  EXPECT_DOUBLE_EQ(qq.x, 2.0);
  EXPECT_DOUBLE_EQ(qq.y, 3.0);
  EXPECT_DOUBLE_EQ(qq.z, 4.0);

  qq = 2.0 * qq / 2.0;
  EXPECT_DOUBLE_EQ(qq.w, 1.0);
  EXPECT_DOUBLE_EQ(qq.x, 2.0);
  EXPECT_DOUBLE_EQ(qq.y, 3.0);
  EXPECT_DOUBLE_EQ(qq.z, 4.0);

  Quaternion qqq(1,1,1,1);
  qqq.normalize();
  EXPECT_DOUBLE_EQ(qqq.w, 1.0 / sqrt(4.0));
  EXPECT_DOUBLE_EQ(qqq.x, 1.0 / sqrt(4.0));
  EXPECT_DOUBLE_EQ(qqq.y, 1.0 / sqrt(4.0));
  EXPECT_DOUBLE_EQ(qqq.z, 1.0 / sqrt(4.0));

}

TEST(squaternion, math_double) {
  QuaternionT<double> q;
  q = q * 2.0;
  EXPECT_DOUBLE_EQ(q.w, 2.0);
  EXPECT_EQ(sizeof(q.w), sizeof(double));
  EXPECT_EQ(sizeof(q.z), sizeof(double));
  EXPECT_EQ(sizeof(q.y), sizeof(double));
  EXPECT_EQ(sizeof(q.x), sizeof(double));

  QuaternionT<double> qq(1, 2, 3, 4);
  qq.normalize();
  q = 2.0 * qq / 2.0;
  ASSERT_DOUBLE_EQ(q.magnitude(), 1.0);
}

TEST(squaternion, math_float) {
  QuaternionT<float> q;
  q = q * 2.0f;
  q = 1.0f * q;
  EXPECT_FLOAT_EQ(q.w, 2.0f);
  EXPECT_EQ(sizeof(q.w), sizeof(float));
  EXPECT_EQ(sizeof(q.z), sizeof(float));
  EXPECT_EQ(sizeof(q.y), sizeof(float));
  EXPECT_EQ(sizeof(q.x), sizeof(float));
  // EXPECT_TRUE(sizeof(q.w) == sizeof(float));

  q.w = 1.0f;
  q.w = 2.0 * q.w;
  q = 1.0 * q;
  q = q * 1.0;
  EXPECT_FLOAT_EQ(q.w, 2.0f);

  QuaternionT<float> qq(1.0f, 2.0f, 3.0f, 4.0f);
  qq.normalize();
  q = 2.0f * qq / 2.0f;
  ASSERT_FLOAT_EQ(q.magnitude(), 1.0f);
}