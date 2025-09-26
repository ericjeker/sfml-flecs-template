add_library(Vendor INTERFACE)

message("--- Fetching Content")
include(FetchContent)
FetchContent_Declare(
  SFML
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG 3.0.1
  GIT_SHALLOW ON
  EXCLUDE_FROM_ALL SYSTEM)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(
  Flecs
  GIT_REPOSITORY https://github.com/SanderMertens/flecs.git
  GIT_TAG v4.1.1
  GIT_SHALLOW ON
  EXCLUDE_FROM_ALL SYSTEM)
FetchContent_MakeAvailable(flecs)

target_link_libraries(Vendor INTERFACE SFML::Graphics flecs)
