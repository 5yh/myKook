from conan import ConanFile
from conan.tools.cmake import cmake_layout


class ExampleRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires("sdl/2.30.1")

    # def generate(self):
    #     tc = CMakeToolchain(self)
    #     tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
    # def layout(self):
    #     cmake_layout(self)