# CMakeList.txt
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(FetchContent)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("CrystalRenderer" CXX C)

find_package(Vulkan)
add_subdirectory("libs/glfw")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

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

target_include_directories(CrystalRenderer PRIVATE 
    libs/glfw/include
    libs/glad/include 
    libs/glm     
    libs      
    libs/imgui
    libs/imgui/backends
)

target_link_libraries(CrystalRenderer PRIVATE
    glfw           
    Vulkan::Vulkan 
    imgui          
)

add_custom_command(TARGET CrystalRenderer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/shaders"
    "$<TARGET_FILE_DIR:CrystalRenderer>/shaders"
)

add_custom_command(TARGET CrystalRenderer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/resources"
    "$<TARGET_FILE_DIR:CrystalRenderer>/resources"
)

install(TARGETS CrystalRenderer DESTINATION .)