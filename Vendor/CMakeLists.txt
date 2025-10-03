add_library(Vendor INTERFACE)

message("--- Fetching Content")
include(FetchContent)
FetchContent_Declare(
        SFE
        GIT_REPOSITORY https://github.com/ericjeker/sfml-flecs-engine.git
        GIT_SHALLOW ON
        GIT_TAG v1.0.2
        EXCLUDE_FROM_ALL SYSTEM)
FetchContent_MakeAvailable(SFE)

target_link_libraries(Vendor INTERFACE SFE::Core)
