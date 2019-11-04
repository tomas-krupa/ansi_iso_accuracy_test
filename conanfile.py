from conans import ConanFile, tools, CMake
import re, os

def get_version():
    try:
        content = tools.load("CMakeLists.txt")
        version = re.search("VERSION (.*) LANGUAGES", content).group(1)
        return version.strip()
    except Exception as _:
        return None

class ConanPackage(ConanFile):
    """Innovatrics ANSI&ISO accuracy and performace test"""
    name = "ansi_iso_accuracy_test"
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

    build_requires = [
        "iengine_ansi_iso/2.4.0@sdk/stable",
        "Catch2/2.7.2@catchorg/stable",
    ]

    def cmake_configure(self):
        cmake = CMake(self)
        cmake.configure()
        return(cmake)

    def build(self):
        cmakedefs = {}
        cmake = self.cmake_configure()
        cmake.configure(defs=cmakedefs)
        cmake.build()
        cmake.install()
        if not tools.get_env("CONAN_RUN_TESTS", False):
            cmake.test()

    def package(self):
        cmake = self.cmake_configure()
        cmake.install()
        self.copy("bin")
        self.copy("doc")
        self.copy("include")
        self.copy("lib")
        self.copy("README.md")
        self.copy("LICENSE.txt")

    def package_info(self):
        self.env_info.PATH.append(os.path.join(self.package_folder, "Bin"))
        self.cpp_info.builddirs = [ "." ]
