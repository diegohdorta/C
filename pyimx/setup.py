#from setuptools import setup, find_packages
#    packages=find_packages(),
from setuptools import setup

setup(
    name='pyimx',
    version='0.0.1b',
    description='Python Tools for i.MX Boards',
    license='MIT',
    packages=['imx','imx/example'],
    author='NXP',
    author_email='diego.dorta@nxp.com',
    keywords=['example'],
    url='https://github.com/diegohdorta/pyimx'
)
