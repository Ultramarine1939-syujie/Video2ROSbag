# cmake needs this line
cmake_minimum_required(VERSION 3.1)

# Find OpenCV, you may need to set OpenCV_DIR variable
# to the absolute path to the directory containing OpenCVConfig.cmake file
# via the command line or GUI
find_package(OpenCV REQUIRED)

# If the package has been found, several variables will
# be set, you can find the full list with descriptions
# in the OpenCVConfig.cmake file.
# Print some message showing some of them
message(STATUS "OpenCV library status:")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")


# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_LIB_SRCS 变量
#aux_source_directory(. DIR_LIB_SRCS)
# 生成链接库
#add_library (calibrate ${DIR_LIB_SRCS})

# 生成链接库
SET(LIB_SRC calibrate.cpp)
add_library (calibrate ${LIB_SRC})

# 生成链接库
add_executable(takephoto takephoto.cpp)

target_link_libraries(takephoto ${OpenCV_LIBS})
target_link_libraries(calibrate ${OpenCV_LIBS})


