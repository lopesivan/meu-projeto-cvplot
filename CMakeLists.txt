cmake_minimum_required(VERSION 3.15)
project(CVPlotDemo LANGUAGES CXX)

find_package(OpenCV REQUIRED)

# ---- cvplot include (header-only, sem target) ----
find_path(
  CVPLOT_INCLUDE_DIR CvPlot/cvplot.h # <--- maiúsculo
  PATHS ${CMAKE_PREFIX_PATH}
  PATH_SUFFIXES include REQUIRED)
# --------------------------------------------------

add_executable(cvplot_demo main.cpp)

target_include_directories(cvplot_demo PRIVATE ${CVPLOT_INCLUDE_DIR})
target_link_libraries(cvplot_demo PRIVATE opencv::opencv)
target_compile_features(cvplot_demo PRIVATE cxx_std_17)
