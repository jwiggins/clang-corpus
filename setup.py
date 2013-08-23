#! /usr/bin/env python
from distutils.core import setup

import setuptools

with open('README.rst') as f:
    long_description = f.read()

setup(name='clang_corpus',
      version='0.1',
      author='John Wiggins',
      description='C language corpus',
      long_description=long_description,
      author_email='jwiggins@enthought.com',
      url='https://github.com/jwiggins/clang_corpus',
      packages=setuptools.find_packages(),
      include_package_data=True,
      package_data={'clang_corpus.data': ['*.h', 'cpp/*']},
      )
