cmake_minimum_required(VERSION 3.31..4.1)
project(SFMLFlecsProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# --- Sub-Directories ---
add_subdirectory(Vendor)
add_subdirectory(Core)
add_subdirectory(Main)

# --- Installation ---
install(TARGETS Main
        EXPORT Main
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/test
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
