from squaternion import Quaternion, euler2quat, quat2euler, quatNorm
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


def test_quaternion_zero():
    q = euler2quat(0, 0, 0)
    assert q == (1, 0, 0, 0)


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
