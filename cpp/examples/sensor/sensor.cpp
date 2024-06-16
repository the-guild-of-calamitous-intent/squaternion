
#include <squaternion.hpp>
#include <serialcomm/serialcomm.hpp>
#include <yivo.hpp>
#include <cstdio>
#include <iostream>
#include "msgs.hpp"
#include "serial_help.hpp"

using namespace std;

Yivo yivo;

imu_t imu;
// AHRS<double> ahrs(0.1); // 1.0
QCF<double> qcf(0.05);
TiltCompass<double> tc;
SerialPort ser;

void publish(const Quaternion& q) {
  static uint64_t count = 0;
  double r, p, y;
  bool degrees = true;
  q.to_euler(&r,&p,&y,degrees);

  if (count++ % 50 == 0) {
    cout << "Attitude: " << r << " " << p << " " << y << " -> " << q << endl;
  }
}

void read_sensors() {
  static uint64_t count = 0;

  int avail = ser.available();

  if (avail <= 6) return;

  while (avail-- > 0) {
    char c = ser.read();
    uint8_t msgid = yivo.read(c);

    if (msgid == IMU) {

      imu = yivo.unpack<imu_t>();

      vect_t<double> a;
      vect_t<double> g;
      vect_t<double> m;

      a.x = imu.accel.x;
      a.y = imu.accel.y;
      a.z = imu.accel.z;

      g.x = imu.gyro.x;
      g.y = imu.gyro.y;
      g.z = imu.gyro.z;

      m.x = imu.mag.x; // uT
      m.y = imu.mag.y;
      m.z = imu.mag.z;
      // ahrs.update(a, g, m, 0.01);
      // ahrs.update(a, g, 0.01);
      // publish(ahrs.q);
      tc.update(a, m);

      // qcf.update(a, g, 0.01);
      // publish(qcf.q);
      // publish(tc.q);

      if (count++ % 50 == 0) {
        // cout << "a: " << a << "  m: " << m << endl;
        // cout << "a: " << a << "  g: " << g << endl;
        cout << "m: " << m << " -> " << m.magnitude() << endl;
        // cout << "a: " << a << "  g: " << g << "  m: " << m  << endl;
      }
    }
  }
}

int main() {

  cout << "*** START ***" << endl;

  string port;
  bool found_port = get_serial("ls /dev/tty.usbmodem*", port);
  if (!found_port) return 1;
  ser.open(port, B1000000);
  cout << "* Opened serial port" << endl;

  while (true) {
    read_sensors();
  }

  return 0;
}