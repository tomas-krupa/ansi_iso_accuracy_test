# -*- coding: utf-8 -*-

from conans import ConanFile, CMake, tools
import os

class TestPackageConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake"

    build_requires = [
        "iengine_ansi_iso/2.4.0@sdk/stable"
    ]

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def test(self):
        if not tools.cross_building(self.settings):
            bin_path = os.path.join(self.build_folder, "bin", "test_package")
            self.run(bin_path, run_environment=True)
