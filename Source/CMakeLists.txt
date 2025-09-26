message("--- Adding Executable")
add_executable(App)
target_sources(App PRIVATE Main.cpp)
target_link_libraries(App PRIVATE Core flecs SFML::Window SFML::Graphics)
