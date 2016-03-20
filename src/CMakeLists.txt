set (CMAKE_CXX_STANDARD 11)

if(MSVC)
  # Force to always compile with W4
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  # Update if necessary
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")
endif()

file(GLOB_RECURSE SOURCES "*.cpp")
file(GLOB_RECURSE EXT_SOURCES "../ext/*.cpp")

find_package(GLFW REQUIRED)
find_package(GLEW REQUIRED)

if (WIN32)
  set(OPENGL_LIBRARY "opengl32")
else()
  set(OPENGL_LIBRARY "GL")
endif()

include_directories(
    .
    ../ext
    ./gl
    ${GLFW_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIRS}
    ${GLM_INCLUDE_DIR}
)

add_executable(game ${SOURCES} ${EXT_SOURCES})

target_link_libraries(game ${GLFW_glfw_LIBRARY} ${GLEW_LIBRARY} ${OPENGL_LIBRARY})
