cmake_minimum_required(VERSION 3.15)
project(CVPlotDemo LANGUAGES CXX)

find_package(cvplot REQUIRED)   # header-only
find_package(OpenCV REQUIRED)   # cvplot depende de OpenCV

add_executable(cvplot_demo
    main.cpp
)

target_link_libraries(cvplot_demo
    PRIVATE
        cvplot::cvplot
        opencv::opencv
)

set_target_properties(cvplot_demo PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
