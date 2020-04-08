from __future__ import absolute_import

from squaternion.squaternion import Quaternion
from squaternion.squaternion import euler2quat
from squaternion.squaternion import quat2euler
from squaternion.squaternion import quatNorm

__author__ = "Kevin Walchko"
__license__ = "MIT"

try:
    from importlib.metadata import version # type: ignore
except ImportError:
    from importlib_metadata import version # type: ignore
