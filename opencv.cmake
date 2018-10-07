set(OPENCV3_DIR ${PROJECT_SOURCE_DIR}/3rd/opencv)
set(OPENCV3_INSTALL_DIR ${CMAKE_BINARY_DIR}/opencv)

include(ExternalProject)
ExternalProject_Add(opencv3
    SOURCE_DIR ${OPENCV3_DIR}
    CMAKE_ARGS
        ${ep_common_args}
        -DCPU_BASELINE:String=AVX2
        -DENABLE_CXX11=ON
        ### Enabled modules
        -DBUILD_opencv_imgproc=ON
        -DBUILD_opencv_dnn=ON
        -DBUILD_opencv_video=ON
        -DBUILD_opencv_ml=ON
        ### Disabled modules
        -DBUILD_opencv_apps=ON
        -DBUILD_opencv_calib3d=ON
        -DBUILD_opencv_contrib=ON
        -DBUILD_opencv_features2d=ON
        -DBUILD_opencv_flann=ON
        -DBUILD_opencv_highgui=ON
        -DBUILD_opencv_imgcodecs=ON
        -DBUILD_opencv_objdetect=ON
        -DBUILD_opencv_photo=ON
        -DBUILD_opencv_shape=ON
        -DBUILD_opencv_stitching=ON
        -DBUILD_opencv_superres=ON
        -DBUILD_opencv_videoio=ON
        -DBUILD_opencv_ts=OFF
        -DBUILD_opencv_videostab=OFF
        ###
        -DCMAKE_BUILD_TYPE:STRING=Debug
        -DCMAKE_INSTALL_PREFIX:PATH=${OPENCV3_INSTALL_DIR}
)

include_directories(${OPENCV3_INSTALL_DIR}/include)

file(GLOB libs
		"${OPENCV3_INSTALL_DIR}/lib/*.a")
set(OPENCV3_LIBS ${libs})
link_directories(${CMAKE_BINARY_DIR})
