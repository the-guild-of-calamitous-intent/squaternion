from squaternion import Quaternion, euler2quat, quat2euler, quatNorm
from squaternion.squaternion import quat2rot
# import numpy as np
import pytest


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


@pytest.mark.xfail(raises=ZeroDivisionError)
def test_norm_divzero():
    q = Quaternion(0, 0, 0, 0)
    q = quatNorm(*q)


@pytest.mark.xfail(raises=TypeError)
def test_norm_args():
    q = Quaternion(1, 0, 0, 0)
    q = quatNorm(q)


@pytest.mark.xfail(raises=TypeError)
def test_quaternion_args():
    Quaternion(0)


def test_e2q():
    q = euler2quat(0, 0, 0)
    assert q == (1, 0, 0, 0)

    # q = euler2quat(30,40,50,degrees=True)
    # a = (0.8600422, 0.0808047, 0.4021985, 0.3033718)
    # dd = 0.001
    # assert tuple(x**2 - y**2 for x,y in zip(a,q)) == (dd, dd, dd, dd), f"{q} != (0.7852207, 0.3600422, 0.1966282, 0.4638269)"


# def test_q2r():
#     q = Quaternion(1,0,0,0)
#     r = quat2rot(q)
#     assert np.eye(3).all() == r.all(), f"{r} != np.eye(3)"

#     q = Quaternion(0,0,0,1)
#     r = quat2rot(q)
#     assert np.diag([-1.0,-1.0,1.0]).all() == r.all(), f"{r} != np.diag([-1,-1,1])"

#     q = Quaternion(0.,0.5773503, 0.5773503, 0.5773503)
#     r = quat2rot(q)
#     a = np.array([
#             [-0.3333333,  0.6666667,  0.6666667],
#             [0.6666667, -0.3333333,  0.6666667],
#             [0.6666667,  0.6666667, -0.3333333]
#         ])
#     print(r,a)
#     assert r.all() == a.all(), f"{r} != {a}"

# def test_quaternion():
#     euler = [
#         (0.,-45.,0.)
#     ]
#     quat = [
#         (0.9238795325112867, 0.0, -0.3826834323650898, 0.0)
#     ]
#     for q, e in zip(quat, euler):
#         qq = euler2quat(e[0], e[1], e[2], True)
#         assert qq == q, f"{q} != {qq}"
#
#         ee = quat2euler(q[0],q[1],q[2],q[3], True)
#         assert ee == e, f"{ee} != {e}"
