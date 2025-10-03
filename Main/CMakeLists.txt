# --- Options and Configurations ---
option(TRACY_ENABLE "Enable Tracy profiler" ON)
option(TRACY_VERBOSE "Enable Tracy verbose output" ON)

# --- Sources Files ---
file(GLOB_RECURSE SOURCE_FILES Source/*.cpp)
file(GLOB_RECURSE HEADER_FILES Source/*.h)

set(EXECUTABLE_SOURCE "Source/Main.cpp")
list(REMOVE_ITEM SOURCE_FILES ${EXECUTABLE_SOURCE})

# --- Create the main library, we build a library so import it in the TestBed ---
add_library(MainLibrary)
target_sources(MainLibrary PRIVATE ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(MainLibrary PUBLIC Source)
target_link_libraries(MainLibrary PRIVATE Vendor Core)

# --- Create the main executable ---
add_executable(Main)
target_sources(Main PRIVATE ${EXECUTABLE_SOURCE})
target_link_libraries(Main PRIVATE Vendor Core MainLibrary)

# Enable debug mode if we are in the debug build
target_compile_definitions(MainLibrary PRIVATE $<$<CONFIG:Debug>:DEBUG>)
target_compile_definitions(Main PRIVATE $<$<CONFIG:Debug>:DEBUG>)

# --- Tracy Configuration ---
if (TRACY_ENABLE)
    target_compile_definitions(Main PRIVATE TRACY_ENABLE)
    target_compile_definitions(MainLibrary PRIVATE TRACY_ENABLE)
    if (TRACY_VERBOSE)
        target_compile_definitions(Main PRIVATE TRACY_VERBOSE)
        target_compile_definitions(MainLibrary PRIVATE TRACY_VERBOSE)
    endif ()
endif ()

# --- Post-build assets copy for build-tree runs ---
add_custom_command(TARGET Main POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
          ${CMAKE_CURRENT_SOURCE_DIR}/Assets
          $<TARGET_FILE_DIR:Main>/Assets
  COMMENT "Copying assets to build directory"
)

add_custom_command(TARGET Main POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
          ${CMAKE_CURRENT_SOURCE_DIR}/Content
          $<TARGET_FILE_DIR:Main>/Content
  COMMENT "Copying content to build directory"
)

if(ENABLE_TESTS)
    enable_testing()
    add_subdirectory(TestBed)
endif()
