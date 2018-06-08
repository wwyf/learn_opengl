cmake_minimum_required(VERSION 3.0.0)

project(hw4-2-meshlab VERSION 0.1.0)

###################################################
# include
###################################################

# include目录
# include_directories ("${PROJECT_SOURCE_DIR}/")
include_directories("../include")

###################################################
# library
###################################################

# lib目录
link_directories("../lib")

# 连接库
set (EXTRA_LIBS ${EXTRA_LIBS} glfw3 opengl32 gdi32 GLAD)

###################################################
# source
###################################################

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(source DIR_SRCS)

# 指定生成目标
add_executable(hw4-2-meshlab ${DIR_SRCS})


###################################################
# option,编译选项
###################################################

target_link_libraries (hw4-2-meshlab  ${EXTRA_LIBS})
# 可以静态链接C库，不过似乎会有一点问题。在读取Aply文件的时候，有的三角形没有绘制出来。
# set(CMAKE_EXE_LINKER_FLAGS -static) 