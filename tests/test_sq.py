from squaternion import Quaternion, Axis
import pytest


def test_euler():
    q = Quaternion.from_euler(0, 0, 0)
    assert q == Quaternion(1, 0, 0, 0), f"{q} != Quaternion(1,0,0,0)"
    assert q.magnitude == 1.0, f"{q.magnitude} magnitude != 1.0"

    delta = 10
    for i in range(-179, 180, delta):
        for j in range(-89, 90, delta):
            for k in range(-179, 180, delta):
                q = Quaternion.from_euler(i, j, k, degrees=True)
                e = q.to_euler(degrees=True)
                for a, b in zip((i, j, k,), e):
                    diff = abs(a - b)
                    assert (diff < 0.001), "{}: {} {} {}".format(diff, i, j, k)

@pytest.mark.xfail(raises=ZeroDivisionError)
def test_norm_divzero():
    q = Quaternion(0, 0, 0, 0)
    q = q.normalize

def test_norm_mag():
    q = Quaternion(1, 1, 1, 1)
    assert q.magnitude == 2.0

    q = q.normalize
    assert q.magnitude == 1.0

    q = Quaternion(0, 0, 0, 0)
    assert q.magnitude == 0.0

def test_compare():
    a = Quaternion(1,1,1,1)
    b = Quaternion(1,0,0,1)
    c = Quaternion(1,1,1,1)

    assert a == a
    assert a == c
    assert c == a
    assert a.normalize == c.normalize

    assert a != b
    assert b != a
    assert a.normalize != b.normalize

    assert a.magnitude == c.magnitude
    assert a.magnitude != b.magnitude

def test_mult():
    a = Quaternion(1, 0, 0, 0)
    b = Quaternion(1, 0, 0, 0)
    assert a*b == Quaternion(1, 0, 0, 0), f"multiplcation failed"

@pytest.mark.xfail(raises=NotImplementedError)
def test_rmul():
    2*Quaternion()

@pytest.mark.xfail(raises=NotImplementedError)
def test_from_rot():
    Quaternion.from_rot(3)

@pytest.mark.xfail(raises=AssertionError)
def test_eq():
    assert Quaternion(1,1,1,1) == Quaternion(1,1,1,0)

def test_axis():
    assert Axis.x == 1
    assert Axis.y == 2
    assert Axis.z == 4





# def test_e2q():
#     q = Quaternion.from_euler(0, 0, 0)
#     assert q == Quaternion(1, 0, 0, 0), f"{q} != Quaternion(1,0,0,0)"
#     assert q.magnitude == 1.0, f"{q.magnitude} magnitude != 1.0"

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
