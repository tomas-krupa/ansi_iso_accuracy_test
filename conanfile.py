from conans import ConanFile, tools, CMake

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
    license = "Apache 2.0"
    url = "https://git.ba.innovatrics.net/users/tomas.krupa/repos/ansi_iso_sdk_accuracy_test.git"
    description = "Accuracy and performance benchmark tool for Innovatrics' ANSI&ISO biometric SDK."
    settings = "os", "compiler", "build_type", "arch"
    version = get_version()
    short_paths = True
    no_copy_source = True
    scm = {
        "type": "git",
        "url": "auto",
        "revision": "auto"
    }

    build_requires = "iengine_ansi_iso/2.4.0@sdk/stable"

    def cmake_configure(self):
        cmake = CMake(self)
        cmake.configure()
        return(cmake)

    def build(self):
        cmake = self.cmake_configure()
        cmake.build()

    def test(self):
        cmake = self.cmake_configure()
        cmake.test()

    def package(self):
        cmake = self.cmake_configure()
        cmake.install()
