add_library(glfw STATIC IMPORTED GLOBAL)
set_target_properties(glfw PROPERTIES 
	IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/glfw/lib/libglfw3.a"
	INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/glfw/include"
)
find_package(OpenGL REQUIRED)
target_link_libraries(glfw INTERFACE OpenGL::GL)


add_library(glad STATIC "${CMAKE_CURRENT_SOURCE_DIR}/glad/lib/glad.c")
target_include_directories(glad PUBLIC 
	"${CMAKE_CURRENT_SOURCE_DIR}/glad/include"
)


add_library(stbi INTERFACE)
target_include_directories(stbi INTERFACE
	"${CMAKE_CURRENT_SOURCE_DIR}/stbi/include"
)


add_library(glm INTERFACE)
target_include_directories(glm INTERFACE
	"${CMAKE_CURRENT_SOURCE_DIR}/glm/include"
)