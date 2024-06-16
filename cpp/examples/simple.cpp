#include <cstdio>
#include <string>
#include <squaternion.hpp>

using namespace std;

int main() {
  string s;
  Quaternion q(1, 2, 3, 4);
  q.normalize();
  printf("q: %s\n", q.to_str().c_str());

  s = q.to_str(); // need to save string to avoid dangling pointer
  printf("%s\n", s.c_str());

  Quaternion bad(0, 0, 0, 0);
  printf("Bad %s\n", bad.to_str().c_str());

  // int err = bad.normalize();

  if (bad.normalize() > 0) {
    printf("*** CORRECT: division by zero for Quaternion bad ***\n");
  }
  else {
    printf("normalized bad ... how?\n");
  }

  double r, p, y;
  q.to_euler(&r, &p, &y, true); // get degrees
  printf("to_euler: %lf %lf %lf\n", r, p, y);

  Quaternion qq = Quaternion::from_euler(10, 20, 30, true); // from degrees
  printf("from_euler: %s\n", qq.to_str().c_str());

  Quaternion qdot = 0.5 * q * Quaternion(0, 0.1, -0.1, 0); // qdot - 1/2 * q * w
  printf("qdot: %s\n", qdot.to_str().c_str());

  Quaternion a(1, 2, 3, 4);
  Quaternion b(5, 6, 7, 8);
  Quaternion ans = 0.5*a*b/2.0;
  printf("a*b: %s\n", ans.to_str().c_str());

  return 0;
}