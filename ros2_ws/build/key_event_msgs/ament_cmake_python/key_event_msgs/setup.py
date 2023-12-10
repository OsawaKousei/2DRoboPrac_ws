from setuptools import find_packages
from setuptools import setup

setup(
    name='key_event_msgs',
    version='0.0.0',
    packages=find_packages(
        include=('key_event_msgs', 'key_event_msgs.*')),
)
