from conan import ConanFile
from conan.tools.cmake import cmake_layout


class ExampleRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        # self.requires("sdl/2.30.1")
        self.requires("openssl/3.2.1")
        # self.requires("asio/1.29.0")
        self.requires("boost/1.84.0")
        # self.requires("nlohmann_json/3.11.3")
        # self.requires("websocketpp/0.8.2")
        

    # def generate(self):
    #     tc = CMakeToolchain(self)
    #     tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
    # def layout(self):
    #     cmake_layout(self)