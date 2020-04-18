![](https://images.pexels.com/photos/45246/green-tree-python-python-tree-python-green-45246.jpeg?cs=srgb&dl=green-snake-45246.jpg&fm=jpg)

# Simple Quaternions (`squaternion`)

[![Actions Status](https://github.com/MomsFriendlyRobotCompany/squaternion/workflows/CheckPackage/badge.svg)](https://github.com/MomsFriendlyRobotCompany/squaternion/actions)
![GitHub](https://img.shields.io/github/license/MomsFriendlyRobotCompany/squaternion)
![PyPI - Python Version](https://img.shields.io/pypi/pyversions/squaternion)
![PyPI](https://img.shields.io/pypi/v/squaternion)

Generally I don't need all of the capabilities (or complexity) of `quaternion`
math libraries. Basically I just need a way to convert between Euler and
Quaternion representations and have a nice way to print them out.

This has basically no imports outside of standard python 3.x libraries.
It should be easier to get on embedded python systems without having to build
`numpy`. Also, this tries to be *fast* by using a frozen class with slots and
where it makes sense, returns `tuples` instead of `list`s.

### Alternatives

This is a basic library that converts between Euler angles and Quaternions.
There are other libraries that do so much more listed below ... but I don't
need all of that.

- [scipy.spatial.transform.Rotation](https://docs.scipy.org/doc/scipy/reference/generated/scipy.spatial.transform.Rotation.html#scipy.spatial.transform.Rotation): has everything you could want, with lots of imports
- [tinyquaternion](https://github.com/rezaahmadzadeh/tinyquaternion): appears to be more functional but needs `numpy`
- [quaternions](https://github.com/mjsobrep/quaternions): another good lightweight quaternion package

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

# however you typically don't think in 4 dimensions, so create from
# euler angles from_eluer(roll, pitch, yaw), default is radians, but set
# degrees true if giving degrees
q = Quaternion.from_euler(0, -90, 100, degrees=True)

# can get the euler angles back out in degrees (set to True)
e = q.to_euler(degrees=True)
d = q.to_dict()

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
print(q)  # pretty print
w = q.w
x = q.x
y = q.y
z = q.z
```

## References

- [Wikipedia Convert Between Quaternions and Euler Angles](https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles)
- [Wikipedia Euler Angle Definitions](https://en.wikipedia.org/wiki/Euler_angles#Conventions_2)
- [Wikipedia Gimbal Lock](https://en.wikipedia.org/wiki/Gimbal_lock)

# MIT License

Copyright (c) 2018 Kevin Walchko

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
