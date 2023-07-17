# CMakeList.txt : CMake project for OS-RP, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (OS-RP "OS-RP.cpp" "OS-RP.h" )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET OS-RP PROPERTY CXX_STANDARD 20)
endif()

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fsanitize=address  -g") 

# TODO: Add tests and install targets if needed.
add_subdirectory(discord_gamesdk_cmake)

target_link_libraries(OS-RP
	discord
)

set(source_dir "discord_gamesdk_cmake/lib")
set(destination_dir "${CMAKE_BINARY_DIR}/OS-RP")
file(GLOB FILES_TO_COPY "${source_dir}/*")

foreach(FILE ${FILES_TO_COPY})
    file(COPY ${FILE} DESTINATION ${destination_dir})
endforeach()