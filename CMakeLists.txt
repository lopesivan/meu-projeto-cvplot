cmake_minimum_required(VERSION 3.15)
project(CvPlotTest CXX)

# Garante o padrão C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# ============== INTEGRAÇÃO CVPLOT (VIA GITHUB) ==============
include(FetchContent)
FetchContent_Declare(
    cvplot_source
    GIT_REPOSITORY https://github.com/Profactor/cv-plot.git
    GIT_TAG        v1.2.2  # Versão Estável para API consistente
)
FetchContent_GetProperties(cvplot_source)
if (NOT cvplot_source_POPULATED)
    FetchContent_Populate(cvplot_source)
endif()

# 2. Define o target como STATIC e ADICIONA O ARQUIVO FONTE (soluciona "undefined reference")
add_library(cv-plot_manual STATIC
    # Incluindo a pasta CvPlot/ no caminho do código-fonte
    ${cvplot_source_SOURCE_DIR}/CvPlot/src/cvplot.cpp
)

# 3. Propaga os diretórios de cabeçalho
# CMakeLists.txt: Bloco target_include_directories
target_include_directories(cv-plot_manual PUBLIC
    # 1. Este caminho era para os cabeçalhos públicos (.h)
    ${cvplot_source_SOURCE_DIR}/CvPlot/inc

    # 2. CORREÇÃO: Adicione o diretório raiz do código-fonte
    ${cvplot_source_SOURCE_DIR}
)
# 4. Propaga a dependência do OpenCV
target_link_libraries(cv-plot_manual PUBLIC
    opencv::opencv
)
# ==========================================================

# ============== INTEGRAÇÃO PRINCIPAL ==============
find_package(OpenCV REQUIRED)

add_executable(cvplot_demo main.cpp)

# Linka TUDO: O executável herda todas as dependências (includes, libs) de cv-plot_manual
target_link_libraries(cvplot_demo PRIVATE
    cv-plot_manual
)

