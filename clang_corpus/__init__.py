from os import listdir
from os.path import abspath, isfile, join, splitext

# C, C++, Obj-C, & Obj-C++
SOURCE_EXTENSIONS = ('.h', '.hh', '.hpp', '.c', '.cpp', '.cxx', '.m', '.mm')


class SourceFile(object):
    """ A simple object which wraps a text file.
    """
    def __init__(self, path):
        self._path = abspath(path)

    @property
    def path(self):
        return self._path

    @property
    def bytes(self):
        with open(self._path, "rb") as fp:
            bytes = fp.read()
        return bytes


def create_package_modules(package_path, module_dict):
    """ Populate a module dictionary with `SourceFile` objects for each source
    file in a directory.
    """
    package_path = abspath(package_path)
    for filename in listdir(package_path):
        file_path = join(package_path, filename)
        key, ext = splitext(filename)
        if isfile(file_path) and ext in SOURCE_EXTENSIONS:
            key, ext = splitext(filename)
            module_dict[key] = SourceFile(file_path)
