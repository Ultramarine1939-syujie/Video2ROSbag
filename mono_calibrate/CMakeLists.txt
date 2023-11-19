# cmake needs this line
cmake_minimum_required(VERSION 3.1)

# Define project name
project(MY_project)


# 添加子目录
add_subdirectory(calibrate)


# Declare the executable target built from your sources
add_executable(main main.cpp)


# Link your application with OpenCV libraries PRIVATE ${OpenCV_LIBS}
target_link_libraries(main calibrate)
