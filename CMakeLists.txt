cmake_minimum_required(VERSION 3.0)
project(chat)

#编译命令
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

#生成的可执行文件路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

#附加头文件路径
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/db)
include_directories(${PROJECT_SOURCE_DIR}/include/server)
include_directories(${PROJECT_SOURCE_DIR}/include/model)
include_directories(${PROJECT_SOURCE_DIR}/include/redis)
include_directories(${PROJECT_SOURCE_DIR}/thirdParty)


#加载子目录
add_subdirectory(src)


