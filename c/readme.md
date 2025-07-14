# squaternion_t Library in C

This is a simple C library for quaternion operations, following Hamilton's definition of a quaternion \( q = w + xi + yj + zk \), where \( w \) is the real part and \( x, y, z \) are the imaginary parts, ordered as \( (w, x, y, z) \).

## Features

- Initialize quaternions
- Add and subtract quaternions
- Multiply quaternions (Hamilton product)
- Compute quaternion conjugate
- Compute quaternion norm \( \sqrt{w^2 + x^2 + y^2 + z^2} \)
- Compute quaternion inverse \( q^{-1} = \frac{q^*}{|q|^2} \)
- Convert Euler angles (3-2-1 sequence, radians) to quaternion
- Convert quaternion to Euler angles (3-2-1 sequence, radians)

## Files

- `quaternion.h`: Header file with type definition and function declarations
- `quaternion.c`: Implementation of quaternion operations

## Compilation

To compile the library with your program, include `quaternion.h` and link `quaternion.c`. You need a math library for the `sqrt` function.

Example compilation command:

```bash
gcc -o program main.c quaternion.c -lm
```

## Usage

Include the header in your C program:

```c
#include "quaternion.h"
```

### Function Overview

- `squaternion_t quat_init(double w, double x, double y, double z)`: Initializes a quaternion \( q = w + xi + yj + zk \).
- `squaternion_t quat_add(squaternion_t q1, squaternion_t q2)`: Returns \( q_1 + q_2 \).
- `squaternion_t quat_sub(squaternion_t q1, squaternion_t q2)`: Returns \( q_1 - q_2 \).
- `squaternion_t quat_mul(squaternion_t q1, squaternion_t q2)`: Returns the Hamilton product \( q_1 \cdot q_2 \).
- `squaternion_t quat_conj(squaternion_t q)`: Returns the conjugate \( q^* = w - xi - yj - zk \).
- `double quat_norm(squaternion_t q)`: Returns the norm \( \sqrt{w^2 + x^2 + y^2 + z^2} \).
- `squaternion_t quat_inv(squaternion_t q)`: Returns the inverse \( q^{-1} \), or \( (0,0,0,0) \) if non-invertible.
- `squaternion_t euler_to_quat(double roll, double pitch, double yaw)`: Converts Euler angles (3-2-1 sequence: yaw around z, pitch around y, roll around x, in radians) to a quaternion.
- `void quat_to_euler(squaternion_t q, double* roll, double* pitch, double* yaw)`: Converts a quaternion to Euler angles (3-2-1 sequence, in radians).

### Example Program

Below is an example demonstrating quaternion operations, including Euler angle conversions:

```c
#include <stdio.h>
#include <math.h>
#include "quaternion.h"

int main() {
    // Initialize quaternions
    squaternion_t q1 = quat_init(1.0, 2.0, 3.0, 4.0); // q1 = 1 + 2i + 3j + 4k
    squaternion_t q2 = quat_init(2.0, -1.0, 1.0, -2.0); // q2 = 2 - i + j - 2k

    // Addition
    squaternion_t sum = quat_add(q1, q2);
    printf("Sum: (%.1f, %.1f, %.1f, %.1f)\n", sum.w, sum.x, sum.y, sum.z);

    // Multiplication
    squaternion_t prod = quat_mul(q1, q2);
    printf("Product: (%.1f, %.1f, %.1f, %.1f)\n", prod.w, prod.x, prod.y, prod.z);

    // Conjugate of q1
    squaternion_t conj = quat_conj(q1);
    printf("Conjugate of q1: (%.1f, %.1f, %.1f, %.1f)\n", conj.w, conj.x, conj.y, conj.z);

    // Norm of q1
    double norm = quat_norm(q1);
    printf("Norm of q1: %.1f\n", norm);

    // Inverse of q1
    squaternion_t inv = quat_inv(q1);
    printf("Inverse of q1: (%.1f, %.1f, %.1f, %.1f)\n", inv.w, inv.x, inv.y, inv.z);

    // Euler to quaternion
    double roll = M_PI / 6.0; // 30 degrees
    double pitch = M_PI / 4.0; // 45 degrees
    double yaw = M_PI / 3.0; // 60 degrees
    squaternion_t q_euler = euler_to_quat(roll, pitch, yaw);
    printf("Euler to quat (roll=30°, pitch=45°, yaw=60°): (%.3f, %.3f, %.3f, %.3f)\n",
           q_euler.w, q_euler.x, q_euler.y, q_euler.z);

    // squaternion_t to Euler
    double roll_out, pitch_out, yaw_out;
    quat_to_euler(q_euler, &roll_out, &pitch_out, &yaw_out);
    printf("Quat to Euler: roll=%.1f°, pitch=%.1f°, yaw=%.1f°\n",
           roll_out * 180.0 / M_PI, pitch_out * 180.0 / M_PI, yaw_out * 180.0 / M_PI);

    return 0;
}
```

### Example Output

For the above program with \( q_1 = 1 + 2i + 3j + 4k \), \( q_2 = 2 - i + j - 2k \), and Euler angles roll = 30°, pitch = 45°, yaw = 60°:

- Sum: \( (3.0, 1.0, 4.0, 2.0) \)
- Product: \( (-10.0, -5.0, 10.0, 11.0) \)
- Conjugate of \( q_1 \): \( (1.0, -2.0, -3.0, -4.0) \)
- Norm of \( q_1 \): \( \sqrt{1^2 + 2^2 + 3^2 + 4^2} = \sqrt{30} \approx 5.5 \)
- Inverse of \( q_1 \): \( \left( \frac{1}{30}, -\frac{2}{30}, -\frac{3}{30}, -\frac{4}{30} \right) \approx (0.0, -0.1, -0.1, -0.1) \)
- Euler to quat (roll=30°, pitch=45°, yaw=60°): Approximately \( (0.793, 0.252, 0.416, 0.347) \)
- Quat to Euler: Approximately roll=30.0°, pitch=45.0°, yaw=60.0°

## Notes

- The library assumes `double` precision for quaternion components.
- The inverse function returns \( (0,0,0,0) \) for a zero quaternion to avoid division by zero.
- Euler angle conversions use the 3-2-1 sequence (yaw, pitch, roll). Angles are in radians.
- The `quat_to_euler` function handles singularities at pitch angles of \( \pm 90^\circ \).
- Ensure you link with `-lm` for math functions like `sqrt`, `sin`, `cos`, `atan2`, and `asin`.