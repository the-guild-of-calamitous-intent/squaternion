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

TEST(squaternion, filter_awm) {
  // no movement, gravity down
  vect_t<double> a{0,0,1};
  // no movement
  vect_t<double> g{0,0,0};
  // I "think", compass facing North
  //    x would have a big value
  //    y would be zero
  //    z would be small
  vect_t<double> m{1,0,.2};

  QCF<double> qcf;
  QuaternionT<double> q = qcf.update(a,g,m,0.001);


  EXPECT_DOUBLE_EQ(q.w, 1.0);
  EXPECT_DOUBLE_EQ(q.x, 0.0);
  EXPECT_DOUBLE_EQ(q.y, 0.0);
  EXPECT_DOUBLE_EQ(q.z, 0.0);

  EXPECT_DOUBLE_EQ(m.x, 1.0);
  EXPECT_DOUBLE_EQ(m.y, 0.0);
  EXPECT_DOUBLE_EQ(m.z, 0.2);
}


TEST(squaternion, filter_aw) {
  vect_t<double> a{0,0,1};
  vect_t<double> g{0,0,0};

  QCF<double> qcf;
  QuaternionT<double> q = qcf.update(a,g,0.001);


  EXPECT_DOUBLE_EQ(q.w, 1.0);
  EXPECT_DOUBLE_EQ(q.x, 0.0);
  EXPECT_DOUBLE_EQ(q.y, 0.0);
  EXPECT_DOUBLE_EQ(q.z, 0.0);

  EXPECT_DOUBLE_EQ(a.x, 0.0);
  EXPECT_DOUBLE_EQ(a.y, 0.0);
  EXPECT_DOUBLE_EQ(a.z, 1.0);
}