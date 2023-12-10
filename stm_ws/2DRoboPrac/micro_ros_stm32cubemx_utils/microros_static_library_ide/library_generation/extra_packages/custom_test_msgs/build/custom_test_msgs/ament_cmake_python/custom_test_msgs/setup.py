from setuptools import find_packages
from setuptools import setup

setup(
    name='custom_test_msgs',
    version='0.0.0',
    packages=find_packages(
        include=('custom_test_msgs', 'custom_test_msgs.*')),
)
