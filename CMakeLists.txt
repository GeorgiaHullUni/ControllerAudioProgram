cmake_minimum_required(VERSION 3.12)

project(SDL2Playground LANGUAGES C CXX)

add_executable(SDL2Playground WIN32
	"main.cpp"
)

add_subdirectory("SDL" EXCLUDE_FROM_ALL)

target_link_libraries(SDL2Playground SDL2::SDL2main SDL2::SDL2-static)