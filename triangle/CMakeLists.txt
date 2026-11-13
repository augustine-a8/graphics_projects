project(triangle)

set(TRIANGLE_MAIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(triangle ${TRIANGLE_MAIN_DIR}/main.cpp ${TRIANGLE_MAIN_DIR}/shader.cpp)

target_include_directories(triangle PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_link_libraries(triangle PRIVATE glad glfw)

target_compile_definitions(triangle PRIVATE
    ASSETS_DIR="${CMAKE_CURRENT_SOURCE_DIR}/assets"
)

