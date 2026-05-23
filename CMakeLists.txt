# CMakeList.txt
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project ("CrystalRenderer" CXX)

find_package(Vulkan)
include(FetchContent)
add_subdirectory("libs/glfw")

FetchContent_Declare(
    vk_bootstrap
    GIT_REPOSITORY https://github.com/charles-lunarg/vk-bootstrap
    GIT_TAG        main
)
FetchContent_MakeAvailable(vk_bootstrap)

add_executable (CrystalRenderer
	"src/Main.cpp" 
	"src/Renderer.h"
    "src/Renderer.cpp"

    "src/graphics/vkSwapchain.h"
    "src/graphics/vkSwapchain.cpp"
    "src/graphics/vkDevice.h"
    "src/graphics/vkDevice.cpp"
    "src/graphics/vkCommands.h"
    "src/graphics/vkCommands.cpp"
)

add_library(imgui STATIC
    libs/imgui/imgui.cpp
    libs/imgui/imgui_draw.cpp
    libs/imgui/imgui_tables.cpp
    libs/imgui/imgui_widgets.cpp
    libs/imgui/imgui_demo.cpp
    libs/imgui/backends/imgui_impl_glfw.cpp
    libs/imgui/backends/imgui_impl_vulkan.cpp
)
target_include_directories(imgui PUBLIC 
    "libs/imgui" 
    "libs/imgui/backends"
)
target_compile_definitions(imgui PUBLIC IMGUI_DEFINE_MATH_OPERATORS)

target_include_directories(CrystalRenderer PRIVATE 
    libs/glad/include 
    libs/glm     
    libs      
    libs/imgui
    libs/imgui/backends
)

target_link_libraries(CrystalRenderer PRIVATE
    glfw
    Vulkan::Vulkan 
    vk-bootstrap
    imgui          
)

add_custom_command(TARGET CrystalRenderer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/shaders"
    "$<TARGET_FILE_DIR:CrystalRenderer>/shaders"
)

add_custom_command(TARGET CrystalRenderer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/res"
    "$<TARGET_FILE_DIR:CrystalRenderer>/res"
)

install(TARGETS CrystalRenderer DESTINATION .)