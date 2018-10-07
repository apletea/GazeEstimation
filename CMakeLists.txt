cmake_minimum_required(VERSION 2.8)
project(gaze)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -Wall  -march=native -Wno-narrowing -std=c++0x -fPIC -DNDEBUG  -O3 -march=native ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall  -march=native -Wno-narrowing -std=c++0x -fPIC -DNDEBUG  -O3 -march=native")


message("${PROJECT_SOURCE_DIR}")

include_directories(${PROJECT_SOURCE_DIR}/include
                    ${PROJECT_SOURCE_DIR}
					${PROJECT_SOURCE_DIR}/3rd/cxxopts/include
        			${PROJECT_SOURCE_DIR}/3rd/Simd/src
)
include(${PROJECT_SOURCE_DIR}/opencv.cmake)

set(SIMD_DIR ${PROJECT_SOURCE_DIR}/3rd/Simd/prj/cmake)
set(SIMD_INSTALL_DIR ${CMAKE_BINARY_DIR}/Simd)

include(ExternalProject)
ExternalProject_Add(Simd
		SOURCE_DIR ${SIMD_DIR}
		CMAKE_ARGS
		-DTOOLCHAIN=/usr/bin/c++
	   	-DTARGET=x86_64
		-DCMAKE_INSTALL_PREFIX:PATH=${SIMD_INSTALL_DIR}
		INSTALL_COMMAND cmake -E echo "Skipping install step."
		)

set(SIMD_LIB ${CMAKE_BINARY_DIR}/Simd-prefix/src/Simd-build/libSimd.a)
message(" ${SIMD_LIB}")
link_directories(${CMAKE_BINARY_DIR})

file(GLOB gazeSRC
           "src/*.cpp")
add_library(${PROJECT_NAME} SHARED ${gazeSRC})


message(" ${OPENCV3_LIBS}")
add_dependencies(${PROJECT_NAME} opencv3 Simd)
target_link_libraries(${PROJECT_NAME} ${OPENCV3_LIBS} ${SIMD_LIB} gcc -ldl -lz -lpthread)

add_executable(demo
               ${PROJECT_SOURCE_DIR}/demo/main.cpp)
add_dependencies(demo opencv3 Simd ${PROJECT_NAME})
link_directories(${CMAKE_BINARY_DIR})
target_link_libraries(demo ${PROJECT_NAME}  ${OPENCV3_LIBS} ${SIMD_LIB} gcc -ldl -lz -lpthread)


