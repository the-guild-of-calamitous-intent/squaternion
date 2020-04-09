# -*- coding: utf-8 -*-
##############################################
# The MIT License (MIT)
# Copyright (c) 2014 Kevin Walchko
# see LICENSE for full details
##############################################
from squaternion.squaternion import Quaternion
from squaternion.squaternion import euler2quat
from squaternion.squaternion import quat2euler
from squaternion.squaternion import quatNorm


try:
    from importlib.metadata import version # type: ignore
except ImportError:
    from importlib_metadata import version # type: ignore

__author__ = "Kevin Walchko"
__license__ = "MIT"
__version__ = version("squaternion")
