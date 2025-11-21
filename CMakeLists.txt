cmake_minimum_required(VERSION 3.15)
project(CvPlotTest CXX)

# Garante o padrão C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ============== INTEGRAÇÃO CVPLOT (VIA GITHUB) ==============
# 1. Baixa o código-fonte do CvPlot
include(FetchContent)
FetchContent_Declare(
    cvplot_source
    GIT_REPOSITORY https://github.com/Profactor/cv-plot.git
    GIT_TAG        v1.2.2  # <--- ALTERAÇÃO AQUI: Usando a tag estável
    #GIT_TAG        master
)
FetchContent_GetProperties(cvplot_source)
if (NOT cvplot_source_POPULATED)
    FetchContent_Populate(cvplot_source)
endif()

# 2. Define o target manual como INTERFACE (Apenas cabeçalhos)
add_library(cv-plot_manual INTERFACE)

# 3. Propaga os diretórios de cabeçalho (resolve o "No such file or directory")
target_include_directories(cv-plot_manual INTERFACE
    ${cvplot_source_SOURCE_DIR}/CvPlot/inc
)

# 4. Propaga a dependência do OpenCV para a biblioteca
target_link_libraries(cv-plot_manual INTERFACE
    opencv::opencv
)
# ==========================================================


# ============== INTEGRAÇÃO PRINCIPAL ==============

# 5. Encontra o OpenCV (gerenciado pelo Conan)
find_package(OpenCV REQUIRED)

# 6. Define o Executável
add_executable(teste_plot main.cpp)

# 7. Linka TUDO: O executável precisa da biblioteca CvPlot manual,
# que já carrega o OpenCV (e seus includes) automaticamente.
target_link_libraries(teste_plot PRIVATE
    cv-plot_manual
)
