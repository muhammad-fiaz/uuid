from conan import ConanFile
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout
from conan.tools.files import copy, collect_libs
import os


class UUIDConan(ConanFile):
    name = "uuid"
    version = "0.1.0"
    license = "MIT"
    author = "Muhammad Fiaz"
    url = "https://github.com/muhammad-fiaz/uuid"
    homepage = "https://muhammad-fiaz.github.io/uuid"
    description = "Production-grade UUID library for C/C++ implementing RFC 9562"
    topics = ("uuid", "rfc9562", "guid", "c", "c++")
    settings = "os", "compiler", "build_type", "arch"
    options = {
        "shared": [True, False],
        "fPIC": [True, False],
        "build_tests": [True, False],
        "build_examples": [True, False],
        "build_benchmarks": [True, False],
    }
    default_options = {
        "shared": False,
        "fPIC": True,
        "build_tests": False,
        "build_examples": False,
        "build_benchmarks": False,
    }
    exports_sources = (
        "CMakeLists.txt",
        "src/*",
        "include/*",
        "tests/*",
        "examples/*",
        "benchmarks/*",
        "cmake/*",
    )
    no_copy_source = True

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def configure(self):
        if self.options.shared:
            self.options.rm("fPIC")

    def layout(self):
        cmake_layout(self)

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.variables["UUID_BUILD_SHARED"] = self.options.shared
        tc.variables["UUID_BUILD_STATIC"] = not self.options.shared
        tc.variables["UUID_BUILD_TESTS"] = self.options.build_tests
        tc.variables["UUID_BUILD_EXAMPLES"] = self.options.build_examples
        tc.variables["UUID_BUILD_BENCHMARKS"] = self.options.build_benchmarks
        tc.variables["UUID_WERROR"] = False
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        copy(self, "LICENSE", dst=os.path.join(self.package_folder, "licenses"), src=self.source_folder)
        cmake = CMake(self)
        cmake.install()

    def package_id(self):
        self.info.clear()

    def package_info(self):
        self.cpp_info.libs = collect_libs(self)
        self.cpp_info.includedirs = [os.path.join("include", "uuid")]
        self.cpp_info.set_property("cmake_file_name", "uuid")
        self.cpp_info.set_property("cmake_target_name", "uuid::uuid")
        self.cpp_info.set_property("pkg_config_name", "uuid")

        if self.settings.os in ("Linux", "FreeBSD"):
            self.cpp_info.system_libs = ["pthread"]
