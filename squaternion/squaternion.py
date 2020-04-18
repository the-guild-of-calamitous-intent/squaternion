# -*- coding: utf-8 -*-
##############################################
# The MIT License (MIT)
# Copyright (c) 2014 Kevin Walchko
# see LICENSE for full details
##############################################
from math import sin, cos, atan2, pi, sqrt, asin
import attr


rad2deg = 180.0/pi
deg2rad = pi/180

@attr.s(slots=True, frozen=True)
class Quaternion:
    """
    q = Quaternion(w,x,y,z)

    class properties:
        q.scalar: q.w
        q.vector: (q.x, q.y, q.z)
        q.normalize: return a normalized quaternion
        q.magnitude: returns the magnitude of the quaternion

    class methods:
        q.to_euler: returns (roll, pitch, yaw)
        Quaternion.from_euler: returns a quaternion from euler angles (Z,Y,X)
        q*q: multiply 2 quaternions together
    """
    w=attr.ib(default=1.0)
    x=attr.ib(default=0.0)
    y=attr.ib(default=0.0)
    z=attr.ib(default=0.0)

    @property
    def magnitude(self):
        """Returns the magnitude of the quaternion"""
        return sqrt(self.w**2 + self.x**2 + self.y**2 + self.z**2)

    @property
    def normalize(self):
        """
        Returns a normalized a quaterion (unit quaternion) so its
        magnitude is 1.0
        """
        m = self.magnitude

        w, x, y, z = self.w, self.x, self.y, self.z

        if m == 1.0:
            return Quaternion(w, x, y, z)
        elif m < 1e-6:
            raise ZeroDivisionError('normQuat(): div by {}'.format(m))

        w /= m
        x /= m
        y /= m
        z /= m

        return Quaternion(w, x, y, z)

    @property
    def scalar(self):
        """Returns the scalar component of the quaternion"""
        return self.w

    @property
    def vector(self):
        """Returns the vector component of the quaternion"""
        return (self.x, self.y, self.z)

    def to_euler(self, degrees=False):
        """
        Returns the Euler angles as a tuple(roll, pitch, yaw)

        This is a modified version of this:
        https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
        """
        ysqr = self.y * self.y

        t0 = +2.0 * (self.w * self.x + self.y * self.z)
        t1 = +1.0 - 2.0 * (self.x * self.x + ysqr)
        X = atan2(t0, t1)

        t2 = +2.0 * (self.w * self.y - self.z * self.x)
        t2 = +1.0 if t2 > +1.0 else t2
        t2 = -1.0 if t2 < -1.0 else t2
        Y = asin(t2)

        t3 = +2.0 * (self.w * self.z + self.x * self.y)
        t4 = +1.0 - 2.0 * (ysqr + self.z * self.z)
        Z = atan2(t3, t4)

        if degrees:
            X *= rad2deg
            Y *= rad2deg
            Z *= rad2deg

        return (X, Y, Z,)


    @staticmethod
    def from_rot(r):
        """Why would I need this?"""
        raise NotImplementedError("Quaternion.from_rot")

    @staticmethod
    def from_euler(roll, pitch, yaw, degrees=False):
        """
        Euler angles euler2quat(roll, pitch, yaw, degrees=False), default is radians, but set
        degrees True if giving degrees

        This is a modified version of this:
        https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles#Quaternion_to_Euler_Angles_Conversion
        """
        if degrees:
            roll  *= deg2rad
            pitch *= deg2rad
            yaw   *= deg2rad

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

    def to_rot(self):
        """
        Given a quaternion, return a 3x3 rotation matrix array.

        https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
        """
        r = [[0,0,0],[0,0,0],[0,0,0]]

        r[0][0] = self.w * self.w + self.x * self.x - self.y * self.y - self.z * self.z
        r[0][1] = 2 * (self.x * self.y - self.w * self.z)
        r[0][2] = 2 * (self.x * self.z + self.w * self.y)

        r[1][0] = 2 * (self.x * self.y + self.w * self.z)
        r[1][1] = self.w * self.w - self.x * self.x + self.y * self.y - self.z * self.z
        r[1][2] = 2 * (self.y * self.z - self.w * self.x)

        r[2][0] = 2 * (self.x * self.z - self.w * self.y)
        r[2][1] = 2 * (self.y * self.z + self.w * self.x)
        r[2][2] = self.w * self.w - self.x * self.x - self.y * self.y + self.z * self.z

        return r

    def __mul__(self, r):
        """
        Return the quaternion result of multiplication: q*r

        https://www.mathworks.com/help/aeroblks/quaternionmultiplication.html
        """
        q = self
        w = q.w*r.w - q.x*r.x - q.y*r.y - q.z*r.z
        x = q.x*r.w + q.w*r.x - q.z*r.y + q.y*r.z
        y = q.y*r.w + q.z*r.x + q.w*r.y - q.x*r.z
        z = q.z*r.w - q.y*r.x + q.x*r.y + q.w*r.z
        return Quaternion(w,x,y,z)

    def __rmul__(self, r):
        """Would handle things like: 2*q"""
        raise NotImplementedError("Quaternion.__rmul__")
