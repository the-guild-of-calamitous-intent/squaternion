#include <cstdio>
#include <iostream>
#include <squaternion.hpp>

using namespace std;

// std::ostream &operator<<(std::ostream &os, const Quaternion &q) {
//     return os << q.to_str();
// }

int main() {
  Quaternion q(1, 2, 3, 4);
  q.normalize();
  cout << "q: " << q.to_str() << endl;

  string s = q.to_str(); // need to save string to avoid dangling pointer
  printf("%s\n", s.c_str());

  Quaternion bad(0, 0, 0, 0);
  cout << "Bad: " << bad << endl;

  int err = bad.normalize();

  if (err) {
    printf("*** division by zero for Quaternion bad ***\n");
  }
  else {
    cout << "Normalized bad: " << bad << " - how?" << endl;
  }

  double r, p, y;
  q.to_euler(&r, &p, &y, true); // get degrees
  printf("to_euler: %lf %lf %lf\n", r, p, y);

  Quaternion qq = Quaternion::from_euler(10, 20, 30, true); // from degrees
  cout << "from_euler: " << qq.to_str() << endl;

  Quaternion qdot = 0.5 * q * Quaternion(0, 0.1, -0.1, 0); // qdot - 1/2 * q * w
  cout << "qdot: " << qdot << endl;

  Quaternion a(1, 2, 3, 4);
  Quaternion b(5, 6, 7, 8);
  cout << "a*b: " << a * b << endl;

  return 0;
}