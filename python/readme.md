![](https://upload.wikimedia.org/wikipedia/commons/thumb/d/d5/Inscription_on_Broom_Bridge_%28Dublin%29_regarding_the_discovery_of_Quaternions_multiplication_by_Sir_William_Rowan_Hamilton.jpg/800px-Inscription_on_Broom_Bridge_%28Dublin%29_regarding_the_discovery_of_Quaternions_multiplication_by_Sir_William_Rowan_Hamilton.jpg)

# Simple Quaternions (`squaternion`)

[![Actions Status](https://github.com/MomsFriendlyRobotCompany/squaternion/workflows/CheckPackage/badge.svg)](https://github.com/MomsFriendlyRobotCompany/squaternion/actions)
![GitHub](https://img.shields.io/github/license/MomsFriendlyRobotCompany/squaternion)
![PyPI - Python Version](https://img.shields.io/pypi/pyversions/squaternion)
![PyPI](https://img.shields.io/pypi/v/squaternion)
![PyPI - Downloads](https://img.shields.io/pypi/dm/squaternion?color=aqua)

Generally I don't need all of the capabilities (or complexity) of `quaternion`
math libraries. Basically I just need a way to convert between Euler and
Quaternion representations and have a nice way to print them out.

This has basically no imports outside of standard python 3.x libraries.
It should be easier to get on embedded python systems without having to build
`numpy`. Also, this tries to be *fast* by using a `frozen` `dataclass` available in python3.

## Install

```
pip install squaternion
```

## Usage

```python
from squaternion import Quaternion

# if you know the values you want Quaternion(w, x, y, z), note this is a
# attr frozen class so it is immutable once created
q = Quaternion(1,0,0,0)

# multiplication for scalar (int, double) and with another quaternion
q = Quaternion(1,2,3,4)
q*q => Quaternion(w=-28, x=4, y=6, z=8)
3*q => Quaternion(w=3, x=6, y=9, z=12)
q*3.0 => Quaternion(w=3.0, x=6.0, y=9.0, z=12.0)

# Addition and subtraction
q = Quaternion(1,2,3,4)
q+q => Quaternion(w=2, x=4, y=6, z=8)

# numpy can do some things, but it will change the tuple to an array, so you might
# need to transform it back to a quaternion
q = Quaternion(1,2,3,4)
np.dot(q,q) => 30
np.sqrt(np.dot(q,q)) => 5.477225575051661
q/np.sqrt(np.dot(q,q)) => array([0.18257419, 0.36514837, 0.54772256, 0.73029674])
Quaternion(*(q/np.sqrt(np.dot(q,q)))) => Quaternion(w=0.18257418583505536, x=0.3651483716701107, y=0.5477225575051661, z=0.7302967433402214)

# however you typically don't think in 4 dimensions, so create from
# euler angles from_eluer(roll, pitch, yaw), default is radians, but set
# degrees true if giving degrees
q = Quaternion.from_euler(0, -90, 100, degrees=True)

# can get the euler angles back out in degrees (set to True)
e = q.to_euler(degrees=True)
d = q.to_dict()
t = q.to_tuple()
r = q.to_rot() # returns a rotation matrix as tuple
r = np.array( q.to_rot() ) # rotation matrix as numpy array

# iterate through values
for i in q:
    print(f"{i}")

# indexing like a namedtuple
z = q[3]
z = q[-1]
v = q[-3:]
w = q[0]

# class properties
v = q.vector     # returns a tuple (x,y,z)
s = q.scalar     # returns a double (w)
n = q.normalize  # returns unit quaternion
m = q.magnitude  # returns the magnitude of the quaternion
a = q.angle      # returns angle of rotation in radians
a = q.axis       # returns axis of rotation

# useful attr functions
q == q    # compare will return True
q != q    # will return False

w = q.w
x = q.x
y = q.y
z = q.z

print(q)  # pretty print => Quaternion(w,x,y,z)
print(f"{q:.4f}") # print only 4 decimal places
```

## Alternatives

This is a basic library that converts between Euler angles and Quaternions.
There are other libraries that do so much more listed below ... but I don't
need all of that.

- [scipy.spatial.transform.Rotation](https://docs.scipy.org/doc/scipy/reference/generated/scipy.spatial.transform.Rotation.html#scipy.spatial.transform.Rotation): has everything you could want, with lots of imports
- [tinyquaternion](https://github.com/rezaahmadzadeh/tinyquaternion): appears to be more functional but needs `numpy`
- [quaternions](https://github.com/mjsobrep/quaternions): another good lightweight quaternion package
- [pyrr](https://github.com/adamlwgriffiths/Pyrr): seems good, integrated with `numpy`

## References

- [Wikipedia Convert Between Quaternions and Euler Angles](https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles)
- [Wikipedia Euler Angle Definitions](https://en.wikipedia.org/wiki/Euler_angles#Conventions_2)
- [Wikipedia Gimbal Lock](https://en.wikipedia.org/wiki/Gimbal_lock)

# MIT License

Copyright (c) 2014 Kevin Walchko

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
