from __future__ import print_function, division
from math import sin, cos, atan2, pi, sqrt, asin
from collections import namedtuple

Quaternion = namedtuple('Quaternion', 'w x y z')


def quatNorm(w, x, y, z):
    m = sqrt(w**2 + x**2 + y**2 + z**2)

    if m == 1.0:
        return Quaternion(w, x, y, z)
    elif m < 1e-6:
        raise ZeroDivisionError('normQuat(): div by {}'.format(m))

    w /= m
    x /= m
    y /= m
    z /= m

    return Quaternion(w, x, y, z)


def euler2quat(roll, pitch, yaw, degrees=False):
    """
    This is a modified version of this:
    https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles#Quaternion_to_Euler_Angles_Conversion
    """
    if degrees:
        roll *= pi/180
        pitch *= pi/180
        yaw *= pi/180

    cy = cos(yaw * 0.5)
    sy = sin(yaw * 0.5)
    cr = cos(roll * 0.5)
    sr = sin(roll * 0.5)
    cp = cos(pitch * 0.5)
    sp = sin(pitch * 0.5)

    w = cy * cr * cp + sy * sr * sp
    x = cy * sr * cp - sy * cr * sp
    y = cy * cr * sp + sy * sr * cp
    z = sy * cr * cp - cy * sr * sp

    return Quaternion(w, x, y, z)


def quat2euler(w, x, y, z, degrees=False):
    """
    This is a modified version of this:
    https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
    """
    ysqr = y * y

    t0 = +2.0 * (w * x + y * z)
    t1 = +1.0 - 2.0 * (x * x + ysqr)
    X = atan2(t0, t1)

    t2 = +2.0 * (w * y - z * x)
    t2 = +1.0 if t2 > +1.0 else t2
    t2 = -1.0 if t2 < -1.0 else t2
    Y = asin(t2)

    t3 = +2.0 * (w * z + x * y)
    t4 = +1.0 - 2.0 * (ysqr + z * z)
    Z = atan2(t3, t4)

    if degrees:
        X *= 180/pi
        Y *= 180/pi
        Z *= 180/pi

    return (X, Y, Z,)
