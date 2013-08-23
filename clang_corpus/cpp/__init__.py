from clang_corpus import create_package_modules

create_package_modules(__path__[0], globals())
del create_package_modules
