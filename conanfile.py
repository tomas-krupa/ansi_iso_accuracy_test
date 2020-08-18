from conans import ConanFile, tools, CMake
import re, os

def get_version():
    try:
        content = tools.load("CMakeLists.txt")
        version = re.search("VERSION (.*)\s+LANGUAGES", content).group(1)
        return version.strip()
    except Exception as _:
        return None

class ConanPackage(ConanFile):
    """Innovatrics ANSI&ISO accuracy and performance test"""
    name = "ansiiso_accuracy_test"
    version = get_version()
    license = "Apache 2.0"
    author = "Tomas Krupa (tomas.krupa@innovatrics.com)"
    url = "https://git.ba.innovatrics.net/users/tomas.krupa/repos/ansi_iso_sdk_accuracy_test.git"
    homepage = "https://git.ba.innovatrics.net/users/tomas.krupa/repos/ansi_iso_sdk_accuracy_test.git"
    description = "Accuracy and performance benchmark tool for Innovatrics' ANSI&ISO biometric SDK."
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake_paths"
    short_paths = True
    no_copy_source = True
    scm = {
        "type": "git",
        "url": "auto",
        "revision": "auto"
    }

    requires = [
        "iengine_ansi_iso/2.4.6@sdk/stable",
    ]

    build_requires = [
        "boost/1.71.0@conan/stable",
    ]

    def build_requirements(self):
        if not tools.get_env("CONAN_RUN_TESTS", False):
            self.build_requires("Catch2/2.7.2@catchorg/stable")

    def build(self):
        cmakedefs = {}
        cmake = CMake(self)

        cmake.configure(defs=cmakedefs)
        cmake.build(target="clang-format-%s" % self.name)
        cmake.build()
        cmake.install()
        if not tools.get_env("CONAN_RUN_TESTS", False):
            cmake.test()

    def package_info(self):
        self.env_info.PATH.append(os.path.join(self.package_folder, "Bin"))
        self.cpp_info.builddirs = [ "." ]
