from __future__ import print_function
from setuptools import setup
from squaternion import __version__ as VERSION
from build_utils import BuildCommand
from build_utils import PublishCommand
from build_utils import BinaryDistribution
from build_utils import SetGitTag


PACKAGE_NAME = 'squaternion'
BuildCommand.pkg = PACKAGE_NAME
PublishCommand.pkg = PACKAGE_NAME
PublishCommand.version = VERSION
README = open('readme.md').read()

setup(
    name=PACKAGE_NAME,
    version=VERSION,
    author="Kevin Walchko",
    keywords=['rotations', 'quaternion', 'euler'],
    author_email="walchko@users.noreply.github.com",
    description="Some simple functions for quaternion math",
    long_description=README,
    long_description_content_type="text/markdown",
    license="MIT",
    classifiers=[
        'Development Status :: 4 - Beta',
        'License :: OSI Approved :: MIT License',
        'Programming Language :: Python :: 2.7',
        'Programming Language :: Python :: 3.6',
        'Operating System :: Unix',
        'Operating System :: POSIX :: Linux',
        'Operating System :: MacOS :: MacOS X',
        'Operating System :: POSIX',
        'Topic :: Scientific/Engineering',
        'Topic :: Scientific/Engineering :: Artificial Intelligence',
        'Topic :: Scientific/Engineering :: Image Recognition',
        'Topic :: Software Development :: Libraries :: Python Modules'
    ],
    install_requires=[
        'build_utils'
    ],
    url="https://github.com/MomsFriendlyRobotCompany/{}".format(PACKAGE_NAME),
    packages=[PACKAGE_NAME],
    cmdclass={
        'publish': PublishCommand,
        'make': BuildCommand,
        'git': SetGitTag
    }
)
