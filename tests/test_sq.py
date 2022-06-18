from squaternion import Quaternion
# from squaternion import Axis
import pytest
import numpy as np

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

def test_norm_divzero():
    q = Quaternion(0, 0, 0, 0)

    with pytest.raises(ZeroDivisionError):
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
    assert 2*a*b*0.5 == Quaternion(1, 0, 0, 0), "multiplcation failed"

def test_rmul():
    assert 2*Quaternion()*0.5 == Quaternion(1, 0, 0, 0)

def test_rotation_matrix():
    q = Quaternion(1,0,0,0)
    r = q.to_rot()

    for i, row in enumerate(((1, 0, 0), (0, 1, 0), (0, 0, 1))):
        for j, col in enumerate(row):
            assert r[i][j] == col

    with pytest.raises(NotImplementedError):
        Quaternion.from_rot(r)

def test_eq():
    assert Quaternion(1,1,1,1) == Quaternion(1,1,1,1)
    assert Quaternion(1,1,1,1) != Quaternion(1,1,1,0)

    with pytest.raises(AssertionError):
        assert Quaternion(1,1,1,1) == Quaternion(1,1,1,0)

# def test_axis():
#     assert Axis.x == 1
#     assert Axis.y == 2
#     assert Axis.z == 4

def test_quaternion():
    q = Quaternion(1,2,3,4)
    assert q.w == 1
    assert q.x == 2
    assert q.y == 3
    assert q.z == 4

    assert len(q) == 4

    for i, ii in zip(q, (1,2,3,4)):
        assert i == ii

    assert q.to_dict() == {'w':1, 'x':2, 'y':3, 'z':4}

    assert q[0] == 1
    assert q[1] == 2
    assert q[2] == 3
    assert q[3] == 4

    assert q[3] == q[-1]
    assert q[0] == q.scalar
    assert q[1:] == q.vector
    assert q[-3:] == q.vector

    qq = q.conjugate
    assert q.w == qq.w == 1
    assert q.x == -qq.x == 2
    assert q.y == -qq.y == 3
    assert q.z == -qq.z == 4

    with pytest.raises(IndexError):
        q[4]


def test_e2q():
    q = Quaternion.from_euler(0, 0, 0)
    assert q == Quaternion(1, 0, 0, 0), f"{q} != Quaternion(1,0,0,0)"
    assert q.magnitude == 1.0, f"{q.magnitude} magnitude != 1.0"

    # q = Quaternion.from_euler(30,40,50,degrees=True)
    # a = (0.8600422, 0.0808047, 0.4021985, 0.3033718)
    # dd = 0.001
    # assert tuple(x**2 - y**2 for x,y in zip(a,q)) == (dd, dd, dd, dd), f"{q} != (0.7852207, 0.3600422, 0.1966282, 0.4638269)"


def test_q2r():
    q = Quaternion(1,0,0,0)
    r = q.to_rot()
    r = np.array(r)
    assert np.eye(3).all() == r.all(), f"{r} != np.eye(3)"

    q = Quaternion(0,0,0,1)
    r = q.to_rot()
    r = np.array(r)
    assert np.diag([-1.0,-1.0,1.0]).all() == r.all(), f"{r} != np.diag([-1,-1,1])"

    q = Quaternion(0.,0.5773503, 0.5773503, 0.5773503)
    r = q.to_rot()
    r = np.array(r)
    a = np.array([
            [-0.3333333,  0.6666667,  0.6666667],
            [0.6666667, -0.3333333,  0.6666667],
            [0.6666667,  0.6666667, -0.3333333]
        ])
    # print(r,a)
    assert r.all() == a.all(), f"{r} != {a}"

def test_numpy():
    q = Quaternion(1,2,3,4)
    assert np.dot(q,q) == 30
    assert np.sqrt(np.dot(q,q)) == 5.477225575051661
    assert (q/np.sqrt(np.dot(q,q))).all() == np.array([0.18257419, 0.36514837, 0.54772256, 0.73029674]).all()
    assert Quaternion(*(q/np.sqrt(np.dot(q,q)))) == Quaternion(w=0.18257418583505536, x=0.3651483716701107, y=0.5477225575051661, z=0.7302967433402214)
