from conan import ConanFile
from conan.tools.cmake import cmake_layout


class TesteCvPlot(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        # Usando as versões que você já tem no cache
        self.requires("opencv/4.12.0")
        self.requires("cvplot/1.2.2")

    def configure(self):
        # Importante: Habilitar GUI no Linux para abrir janelas
        if self.settings.os == "Linux":
            self.options["opencv"].with_gtk = True

    # Prevenção contra o erro do WebP/FFmpeg que vimos antes
    default_options = {
        "ffmpeg/*:with_webp": False,
    }

    def layout(self):
        cmake_layout(self)
