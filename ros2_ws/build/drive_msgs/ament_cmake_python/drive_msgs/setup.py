from setuptools import find_packages
from setuptools import setup

setup(
    name='drive_msgs',
    version='0.0.0',
    packages=find_packages(
        include=('drive_msgs', 'drive_msgs.*')),
)
