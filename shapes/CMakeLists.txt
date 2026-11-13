project(shapes)

set(PROJECT_MAIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(shapes ${PROJECT_MAIN_DIR}/main.cpp ${PROJECT_MAIN_DIR}/shader.cpp)

target_include_directories(shapes PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_link_libraries(shapes PRIVATE glad glfw)

target_compile_definitions(shapes PRIVATE
    ASSETS_DIR="${CMAKE_CURRENT_SOURCE_DIR}/assets"
)

