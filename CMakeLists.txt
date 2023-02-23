cmake_minimum_required(VERSION 3.12)

project(ControllerAudioProgram LANGUAGES C CXX)

add_executable(ControllerAudioProgram WIN32
	"main.cpp"
	"ImGui/imconfig.h"
	"ImGui/imgui.cpp"
	"ImGui/imgui.h"
	"ImGui/imgui_demo.cpp"
	"ImGui/imgui_draw.cpp"
	"ImGui/imgui_impl_sdl.cpp"
	"ImGui/imgui_impl_sdl.h"
	"ImGui/imgui_impl_sdlrenderer.cpp"
	"ImGui/imgui_impl_sdlrenderer.h"
	"ImGui/imgui_internal.h"
	"ImGui/imgui_tables.cpp"
	"ImGui/imgui_widgets.cpp"
	"ImGui/imstb_rectpack.h"
	"ImGui/imstb_textedit.h"
	"ImGui/imstb_truetype.h"
)

set_property(DIRECTORY . PROPERTY VS_STARTUP_PROJECT ControllerAudioProgram)

add_subdirectory("SDL" EXCLUDE_FROM_ALL)

target_link_libraries(ControllerAudioProgram SDL2::SDL2main SDL2::SDL2-static)