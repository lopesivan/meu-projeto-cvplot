from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout
from conan.tools.build import check_min_cppstd

class MeuProjetoCvplotConan(ConanFile):
    name = "meu-projeto-cvplot"
    version = "1.0"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    # Exportar os artefatos de build para a pasta 'build'
    def layout(self):
        cmake_layout(self)

    # Requer o OpenCV (necessário para o CvPlot)
    def requirements(self):
        self.requires("opencv/4.12.0")

    # Garante o C++17
    def validate(self):
        check_min_cppstd(self, "17")

