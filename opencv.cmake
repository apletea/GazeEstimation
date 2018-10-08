set(OPENCV3_DIR ${PROJECT_SOURCE_DIR}/3rd/opencv)
set(OPENCV3_INSTALL_DIR ${CMAKE_BINARY_DIR}/opencv)




macro(ow_cache variable value type text)
    if ("${text}" STREQUAL "")
        message(FATAL_ERROR "ow_cache(overwrite_cache) macro NEEDS a 'text' paramter")
    else()
        set(${variable} ${value} CACHE ${type} ${text} FORCE)
    endif()
endmacro()

# set opencv paramers
ow_cache(BUILD_opencv_apps      OFF BOOL    "Build utility applications (used for example to train classifiers)")
ow_cache(BUILD_ANDROID_EXAMPLES OFF BOOL    "Build examples for Android platform")
ow_cache(BUILD_DOCS             OFF BOOL    "Create build rules for OpenCV Documentation")
ow_cache(BUILD_EXAMPLES         OFF BOOL    "Build all examples")
ow_cache(BUILD_PACKAGE          OFF BOOL    "Enables 'make package_source' command")
ow_cache(BUILD_PERF_TESTS       OFF BOOL    "Build performance tests")
ow_cache(BUILD_TESTS            OFF BOOL    "Build accuracy & regression tests")
ow_cache(BUILD_WITH_DEBUG_INFO  ON  BOOL    "Include debug info into debug libs (not MSCV only)")
ow_cache(WITH_GTK_2_X           ON  BOOL    "Use GTK version 2")
ow_cache(WITH_LIBV4L            ON  BOOL    "Use libv4l for Video 4 Linux support")
ow_cache(BUILD_opencv_ts        ON  BOOL    "Build opencv_ts")
ow_cache(BUILD_opencv_python    OFF  BOOL   "Build opencv_python")
ow_cache(BUILD_opencv_python2   OFF  BOOL   "Build opencv_python2")
ow_cache(BUILD_opencv_python3   OFF  BOOL   "Build opencv_python3")
ow_cache(WITH_GSTREAMER_0_10    ON   BOOL   "Build with gstreamer")

# include opencv
add_subdirectory(${OPENCV3_DIR})

# find opencv module headers and include them
macro(find_opencv_headers return_list)
    file(GLOB new_list ${PROJECT_SOURCE_DIR}/3rd/opencv/modules/**/*)
    get_filename_component(CMAKE_CURRENT_LIST_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
    set(dir_list "")
    FOREACH(file_path ${new_list})
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        SET(dir_list ${dir_list} ${dir_path}/include)
    ENDFOREACH()
    list(REMOVE_DUPLICATES dir_list)
    set(${return_list} ${dir_list})
endmacro()
find_opencv_headers(open_cv_headers)
set(OpenCV_INCLUDE_DIRS ${open_cv_headers})
include_directories(${OpenCV_INCLUDE_DIRS})

# include generated opencv headers
include_directories(${PROJECT_SOURCE_DIR}/3rd/opencv/include)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/3rd/opencv)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/3rd)

# set all avaialbe libs to the OpenCV_LIBS variable
SET(OpenCV_LIBS
    opencv_calib3d
    opencv_core
    opencv_features2d
    opencv_flann
    opencv_highgui
    opencv_imgcodecs
    opencv_imgproc
    opencv_ml
    opencv_objdetect
    opencv_photo
    opencv_shape
    opencv_stitching
    opencv_superres
    opencv_ts
    opencv_video
    opencv_videoio
    opencv_videostab
)
