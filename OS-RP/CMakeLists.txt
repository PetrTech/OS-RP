# CMakeList.txt : CMake project for OS-RP, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (OS-RP "OS-RP.cpp" "OS-RP.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET OS-RP PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
