#include <squaternion.hpp>

void setup() {}

void loop() {
  Quaternion q;
  Quaternion qq(1,2,3,4);
  qq.normalize();
  q = 2.0*qq/2.0;
}
