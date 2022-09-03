from conans import ConanFile
from conans import AutoToolsBuildEnvironment

class MLXWrapperConan(ConanFile):
    name = "minilibx_wrapper"
    version = "1.0"
    license = "MIT"
    author = "agagniere sid.xxdzs@gmail.com"
    url = "https://github.com/agagniere/FDF"
    description = " framework"
    topics = ("x11")
    settings = ("os", "compiler", "arch")
    options = {
        "shared": [True, False],
        "fPIC" : [True, False],
        "optimisation": ['0', '1', '2', '3', 's', 'fast'],
        "debug": [True, False]
    }
    default_options = {
        "shared": False,
        "fPIC": False,
        "optimisation": '2',
        "debug": True
    }
    generators = "make"
    requires = [
        "libft/2.5",
        "minilibx/1.2"
    ]
    exports_sources = 'include*', 'src*', 'Makefile'

    def configure(self):
        del self.settings.compiler.libcxx
        del self.settings.compiler.cppstd

    def build(self):
        autotools = AutoToolsBuildEnvironment(self)
        autotools.flags = [f"-O{self.options.optimisation}"]
        if self.options.debug:
            autotools.flags += ["-g"]
        autotools.make(args=["shared" if self.options.shared else "static", '-C', self.source_folder])

    def package(self):
        self.copy("*.h", dst="include", src="include")
        self.copy("libmlxwrap.a", dst="lib")
        self.copy("libmlxwrap.so", dst="lib")

    def package_info(self):
        self.cpp_info.libs = ["mlxwrap"]
