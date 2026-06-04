# CMakeList.txt
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project ("CrystalRenderer" CXX)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

find_package(Vulkan)
add_subdirectory(libs/glfw)
add_subdirectory(libs/glm)
add_subdirectory(libs/vk-bootstrap)

add_executable (CrystalRenderer
	"src/Main.cpp" 
	"src/Renderer.h"
    "src/Renderer.cpp"
)

set(IMGUI_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui/imgui.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui/imgui_draw.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui/imgui_tables.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui/imgui_widgets.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui/backends/imgui_impl_glfw.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui/backends/imgui_impl_vulkan.cpp"
)
target_sources(CrystalRenderer PRIVATE ${IMGUI_SOURCES})

target_include_directories(CrystalRenderer PRIVATE 
    src
    libs/glm
    libs/stb
    libs/imgui
    libs/imgui/backends
)

target_link_libraries(CrystalRenderer PRIVATE
    glfw
    Vulkan::Vulkan
    vk-bootstrap        
)

add_custom_command(TARGET CrystalRenderer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/src/shaders"
    "$<TARGET_FILE_DIR:CrystalRenderer>/shaders"
)

add_custom_command(TARGET CrystalRenderer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/resources"
    "$<TARGET_FILE_DIR:CrystalRenderer>/resources"
)

install(TARGETS CrystalRenderer DESTINATION .)