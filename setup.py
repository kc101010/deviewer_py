from distutils.core import setup, Extension

#usage: 
#       `Python3 setup.py build`        to create folder w/ library
#       `Python3 setup.py install`      to install library to system

module = Extension("deviewer", sources = ["deviewer.c"])

setup(name="deviewer-dev",
            version = "0.4",
            description="Package for deviewer",
            ext_modules = [module])
