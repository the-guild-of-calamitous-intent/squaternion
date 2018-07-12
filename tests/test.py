from __future__ import print_function, division
from squaternion import Quaternion, euler2quat, quat2euler, quatNorm
from nose.tools import raises


def test_quat():
    delta = 10
    for i in range(-179, 180, delta):
        for j in range(-89, 90, delta):
            for k in range(-179, 180, delta):
                q = euler2quat(i, j, k, degrees=True)
                e = quat2euler(*q, degrees=True)
                for a, b in zip((i, j, k,), e):
                    diff = abs(a - b)
                    assert (diff < 0.001), "{}: {} {} {}".format(diff, i, j, k)


@raises(ZeroDivisionError)
def test_norm_divzero():
    q = Quaternion(0, 0, 0, 0)
    q = quatNorm(*q)


@raises(TypeError)
def test_norm_args():
    q = Quaternion(0, 0, 0, 0)
    q = quatNorm(q)


@raises(TypeError)
def test_quaternion_args():
    q = Quaternion(0)


def test_quaternion_zero():
    q = euler2quat(0, 0, 0)
    assert q == (1, 0, 0, 0)
